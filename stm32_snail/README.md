# grbl_can — период шага и количество шагов (GO_CMD)

Документ описывает, **где в коде** и **как** вычисляются `step_per` (период таймера шага) и `steps` (число шагов), которые master отправляет по CAN командой `GO_CMD`, и как slave их применяет.

## Общая схема

```
G-code / jog
    → planner (plan_buffer.c)          — длина хода, шаги по осям, профиль скорости
    → st_prep_buffer() (can_stepper.c) — сегменты ~5 ms: n_step, cycles_per_tick, can_step_per
    → st_execute_can_segments()        — Bresenham → накопление в batch
    → st_can_batch_flush()             — один или несколько GO_CMD на ось
    → CAN (go_cmd_t)
    → slave can_thr.c → go_cmd_run()   — set_mot_per(), put_mot_nStep()
    → motor_tsk.c                      — TIM1 шаговый таймер
```

Пакет CAN (`common/can/can_cmds.h`):

```c
typedef struct go_cmd_s_ {
  uint8_t  cmd;        // GO_CMD = 0x01
  uint8_t  dirs;       // бит направления оси
  uint16_t step_per;   // период (prescaled, см. ниже)
  uint32_t steps;      // число шагов по этой оси
} go_cmd_t;
```

CAN ID оси: `(1 << axis) << 5` (например X → `0x20`).

---

## Master: период шага (`step_per`)

### 1. Базовая частота Grbl — `F_TIM`

Файл: `common_stm32/grbl/nuts_bolts.h`

```c
#define F_TIM SystemCoreClock/2
#define TICKS_PER_MICROSECOND (F_TIM/1000000)
```

Все расчёты «тиков на шаг» в stepper привязаны к `F_TIM` (как в классическом Grbl ISR).

### 2. Скорость сегмента — `cycles_per_tick`

Файл: `common_stm32/grbl/can_stepper.c`, функция **`st_prep_buffer()`** (~стр. 1175–1236).

Для каждого сегмента буфера (~5 ms движения):

1. По оставшемуся пути в блоке считается число шагов сегмента `prep_segment->n_step`.
2. По времени сегмента `dt` и поправке `dt_remainder` вычисляется `inv_rate` (минуты на шаг).
3. Тики таймера на один шаг:

```c
cycles = ceil((TICKS_PER_MICROSECOND * 1000000) * inv_rate * 60);  // тики F_TIM / шаг
```

При включённом **AMASS** (`ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING`):

- выбирается `amass_level` (0…3);
- `cycles` делится на `2^amass_level`;
- `n_step` умножается на `2^amass_level` (несколько мелких шагов за один ISR-тик).

Без AMASS используется поле `prescaler` (1/8/64) — логика как в `stepper.c`.

### 3. Prescaled `can_step_per` для CAN

Файл: `common_stm32/grbl/can_stepper.c`, **`st_can_step_per_from_segment()`** (~стр. 557).

AMASS/prescaler **восстанавливаются** в полный `cycles`, затем деление на prescale CAN:

```c
// AMASS: cycles <<= seg->amass_level
cycles = (cycles + CAN_STEP_PER_PRESCALE - 1) / CAN_STEP_PER_PRESCALE;  // PRESCALE = 64
prep_segment->can_step_per = st_can_step_per_clamp(cycles);
```

Константа: `common_stm32/grbl/can_stepper.h`

```c
#define CAN_STEP_PER_PRESCALE  64U   // на slave: period_ticks ≈ step_per * 64
```

### 4. Ограничения и квантование перед отправкой

Файл: `common_stm32/grbl/can_stepper.c`

| Функция | Назначение |
|---------|------------|
| `st_can_step_per_clamp()` | нижний предел `CAN_STEP_PER_MIN` (по умолчанию **500**, `config.h`) |
| `st_can_step_per_batch_key()` | округление к `CAN_STEP_PER_QUANT` (по умолчанию **8**) для слияния GO |

Итоговое значение попадает в поле `segment_t.can_step_per` и далее в batch.

### 5. Слияние сегментов (batch) — один GO на зону скорости

Файл: `common_stm32/grbl/can_stepper.c`, **`st_execute_can_segments()`** + **`st_can_batch_flush()`**.

Сегменты Grbl не отправляются по CAN по одному. Шаги Bresenham накапливаются в `can_batch_steps[]`, пока не сработает flush:

- смена направления (`can_batch_dirs`);
- смена `st_block_index` (новый planner block);
- смена **speed zone**: `step_per_key >> CAN_SPEED_ZONE_SHIFT` (по умолчанию shift **8**);
- смена фазы разгона (ACCEL / CRUISE / DECEL), кроме явных merge:
  - ACCEL → CRUISE: обновить `step_per`, не flush;
  - CRUISE → DECEL при той же speed zone: продолжить batch;
- `can_batch_steps` ≥ `CAN_BATCH_MAX_STEPS` (65535);
- конец движения: `st_can_batch_flush_if_pending()` при опустошении planner.

При отправке:

```c
st_send_segment_can(can_batch_dirs, can_batch_step_per, can_batch_steps, wait_done);
```

`can_batch_step_per` — период **начала** текущего batch (не максимум по DECEL).

Ограничение шагов по planner: **`st_can_batch_clamp_to_planner()`** — не больше `planner_steps[]` минус уже отправленные `can_batch_sent_steps[]`.

Отправка на шину: **`can_send_axis_go()`** — для каждой оси с ненулевым счётчиком формируется `go_cmd_t` и `can_master_tx()`.

---

## Master: количество шагов (`steps`)

### 1. Planner — физические шаги блока

Файл: `common_stm32/grbl/planner.c` (классический Grbl).

Для блока G-code в `plan_block_t` задаются:

- `step_event_count` — шаги ведущей оси;
- `steps[X/Y/Z]` — шаги по каждой оси;
- `millimeters`, `programmed_rate` (F), профиль ускорения.

При загрузке блока в stepper (`st_prep_buffer`, ~стр. 894):

```c
st_prep_block->planner_steps[idx] = pl_block->steps[idx];
```

### 2. Число шагов одного сегмента — `n_step`

Файл: `can_stepper.c`, **`st_prep_buffer()`**:

```c
step_dist_remaining = prep.step_per_mm * mm_remaining;
n_steps_remaining   = ceil(step_dist_remaining);
prep_segment->n_step = last_n_steps_remaining - n_steps_remaining;
```

С AMASS: `n_step` дополнительно умножается на `2^amass_level` (см. выше).

### 3. Распределение по осям — Bresenham

Файл: `can_stepper.c`, **`st_execute_can_segments()`**:

Для каждого сегмента цикл `n_step` раз вызывается **`st_bresenham_one_step(axis_steps)`**:

- счётчики `counter_x/y/z` и дельты `st.exec_block->steps[]` (с учётом AMASS);
- в `axis_steps[idx]` попадает число **физических** шагов по оси за сегмент.

Накопление в batch:

```c
can_batch_steps[idx] += axis_steps[idx];
```

### 4. Что уходит в CAN

В **`can_send_axis_go(axis, dirs, step_per, steps)`** поле `steps` = `can_batch_steps[axis]` после clamp.

Для одноосевого jog `$J=G21G91X100…` шаги по X равны накопленному Bresenham по X (обычно совпадает с `planner_steps[X]` блока).

---

## Slave: применение `step_per` и `steps`

### Приём GO

Файл: `app_step_axis_dima/src/can_thr.c`, **`go_cmd_run()`**:

```c
set_dir_mot(p_go_cmd->dirs);
set_mot_per(p_go_cmd->step_per);
put_mot_nStep(p_go_cmd->steps);
```

### Период таймера шага

Файл: `app_step_axis_dima/src/motor_tsk.c`, **`set_mot_per(uint16_t per)`**:

```c
if (per > MAX_PER) per = MAX_PER;      // MAX_PER = 64000, dima_board.h
if (per < MIN_PER) per = MIN_PER;      // MIN_PER = 10

MOT_STEP_TIM->ARR  = per * 2;
MOT_STEP_TIM->CCR1 = per;
```

Таймер: **TIM1**, предделитель при инициализации `DEF_MOT_TIM_PRESC = 64` (`dima_board.h`).

Связь с master (комментарий в `can_stepper.h`):

```
period_timer_ticks ≈ step_per * CAN_STEP_PER_PRESCALE   // PRESCALE = 64
```

В логе slave `per` печатается **в hex** (`printk("…%x…", per)`), в CAN-логе master — **в decimal**.  
Пример: `per=750` на slave = `0x750` = **1872** decimal — это одно и то же значение `step_per`.

### Число шагов на slave

Файл: `motor_tsk.c`, **`put_mot_nStep(uint32_t nstep)`**:

```c
num_Step = nstep;
TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, ENABLE);
TIM_Cmd(MOT_STEP_TIM, ENABLE);
```

В **`MOT_STEP_TIM_IRQHandler`** при каждом импульсе `num_Step` уменьшается; при `num_Step == 0` движение останавливается, slave шлёт статус master.

---

## Настройки batch/CAN (master)

Файл: `common_stm32/grbl/config.h`

| Макрос | По умолчанию | Смысл |
|--------|--------------|--------|
| `CAN_STEP_PER_PRESCALE` | 64 | делитель при упаковке периода в CAN |
| `CAN_STEP_PER_MIN` | 500 | минимальный `step_per` (ограничение max частоты) |
| `CAN_STEP_PER_QUANT` | 8 | квантование скорости для batch |
| `CAN_SPEED_ZONE_SHIFT` | 8 | грубая «зона скорости» для flush |
| `CAN_BATCH_MAX_STEPS` | 65535 | макс. шагов в одном GO |
| `CAN_PIPELINE_GO` | 1 | не ждать конца движения между batch |
| `CAN_WAIT_AXIS_MASK` | — | какие оси идут через CAN |

---

## Ключевые файлы

| Роль | Файл | Функции |
|------|------|---------|
| Период и сегменты | `common_stm32/grbl/can_stepper.c` | `st_prep_buffer`, `st_can_step_per_from_segment`, batch |
| Структуры | `common_stm32/grbl/can_stepper.h` | `segment_t`, `st_block_t`, `CAN_STEP_PER_PRESCALE` |
| CAN пакет | `common/can/can_cmds.h` | `go_cmd_t` |
| Отправка CAN | `common_stm32/grbl/can_stepper.c` | `can_send_axis_go` |
| Приём GO | `app_step_axis_dima/src/can_thr.c` | `go_cmd_run` |
| Таймер мотора | `app_step_axis_dima/src/motor_tsk.c` | `set_mot_per`, `put_mot_nStep` |
| Лимиты периода | `common_stm32/board/dima_board.h` | `MIN_PER`, `MAX_PER`, `DEF_MOT_TIM_PRESC` |

---

## Пример (одноосевой jog)

`$J=G21G91X100Y0Z0F2000`, ось X на CAN:

1. Planner: ~40000 шагов X (зависит от `$100` steps/mm).
2. `st_prep_buffer`: десятки сегментов с разным `can_step_per` (ACCEL → короткий CRUISE → DECEL).
3. Batch: несколько GO (по зонам скорости), не сотни GO по 2 шага.
4. Типичный CRUISE: `step_per ≈ 1872` (0x750 на slave), тысячи шагов в одном GO.
5. Slave: `ARR = 3744`, `CCR1 = 1872`, `num_Step` = значение из пакета.

Для отладки числа GO на master: сборка с `CAN_SEND_DEBUG` — счётчик в `can_send_axis_go()`.
