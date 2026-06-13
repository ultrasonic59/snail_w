#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "grbl.h"

#include "can_stepper.h"
#include "planner.h"
#include "settings.h"
#include "cpu_map.h"
#include "protocol.h"
#include "printk.h"
#include "serial.h"

extern void set_ena_mot(uint8_t idat);

#ifdef USE_THREADX
#include "tx_api.h"
#endif

#ifndef CAN_SEND_DEBUG
#include "can_master.h"
#endif

#define GO_CMD            0x1U
#define GET_STAT_CMD      0x2U

#ifndef CAN_SEND_DEBUG
#define ID_MASTER_CMD     (0x1U << 9)
#define PUT_STAT_CMD      0x3U
#define PUT_ACK           0x4U
#define ST_CAN_AXIS_STATE_MASK  0xFU
#define ST_CAN_STATE_IDLE  0U
#define ST_CAN_STATE_MOVE  2U

typedef struct {
  uint8_t cmd;
  uint8_t axis;
  uint8_t state;
  uint8_t rsv;
  int32_t coord;
} put_stat_cmd_t;

typedef struct {
  uint8_t ack_cmd;
  uint8_t axis;
} ack_body_t;

typedef struct {
  uint8_t cmd;
  ack_body_t ack;
} put_ack_t;

static volatile uint8_t st_can_axis_state[N_AXIS];
static volatile uint8_t st_can_go_ack_mask;
static volatile uint8_t st_can_axis_present_mask;
static volatile uint8_t st_can_axis_seen_mask;
static uint32_t st_can_axis_last_seen_ms[N_AXIS];
static uint32_t st_can_stat_req_ms[N_AXIS];
#endif

typedef struct {
  uint8_t  cmd;
  uint8_t  dirs;
  uint16_t step_per;
  uint32_t steps;
} go_cmd_t;

#ifdef CAN_SEND_DEBUG
static uint32_t can_send_count;
#endif

static void st_execute_can_segments(void);

static uint32_t can_batch_steps[N_AXIS];
static uint32_t can_batch_sent_steps[N_AXIS];
static uint16_t can_batch_step_per;
static uint16_t can_batch_step_per_max;
static uint16_t can_batch_cruise_step_per;
static uint16_t can_batch_target_cruise_per;
static uint8_t can_batch_ramp_type;
static uint8_t can_batch_block_index;
static uint8_t can_batch_dirs;
static uint8_t can_batch_direction_bits;
static uint8_t can_batch_active;
static st_block_t *can_batch_block;
static float st_can_block_accel;

static st_prep_t prep;
static stepper_t st;
static st_block_t st_block_buffer[SEGMENT_BUFFER_SIZE-1];
static segment_t segment_buffer[SEGMENT_BUFFER_SIZE];
// Pointers for the step segment being prepped from the planner buffer. Accessed only by the
// main program. Pointers may be planning segments or planner blocks ahead of what being executed.
static plan_block_t *pl_block;     // Pointer to the planner block being prepped
static st_block_t *st_prep_block;  // Pointer to the stepper block data being prepped
// Step segment ring buffer indices
static volatile uint8_t segment_buffer_tail;
static uint8_t segment_buffer_head;
static uint8_t segment_next_head;
static volatile uint8_t busy;
// Step and direction port invert masks.
static uint8_t step_port_invert_mask;
static uint8_t dir_port_invert_mask;

///==================================================
///======================================================
// Stepper state initialization. Cycle should only start if the st.cycle_start flag is
// enabled. Startup init and limits call this function but shouldn't start the cycle.
void st_wake_up()
{
  // Enable stepper drivers.
/*
  if (bit_istrue(settings.flags,BITFLAG_INVERT_ST_ENABLE)) {
    HAL_GPIO_WritePin(STEPPERS_DISABLE_PORT, STEPPERS_DISABLE_BIT_Pin, GPIO_PIN_RESET);
  }
  else {
    HAL_GPIO_WritePin(STEPPERS_DISABLE_PORT, STEPPERS_DISABLE_BIT_Pin, GPIO_PIN_SET);
  }
*/
  // Initialize stepper output bits to ensure first ISR call does not step.
  st.step_outbits = step_port_invert_mask;

  // Initialize step pulse timing from settings. Here to ensure updating after re-writing.
  #ifdef STEP_PULSE_DELAY
    // Set total step pulse time after direction pin set. Ad hoc computation from oscilloscope.
    st.step_pulse_time = -(((settings.pulse_microseconds+STEP_PULSE_DELAY-2)*TICKS_PER_MICROSECOND) >> 3);
    // Set delay between direction pin write and step command.
    OCR0A = -(((settings.pulse_microseconds)*TICKS_PER_MICROSECOND) >> 3);
  #else // Normal operation
    // Set step pulse time. Ad hoc computation from oscilloscope. Uses two's complement.
    st.step_pulse_time = (settings.pulse_microseconds);
  #endif

  // Enable Stepper Driver Interrupt

///???  TIM2->ARR = (uint32_t)st.exec_segment->cycles_per_tick - 1;
///???  TIM3->ARR = (((uint32_t)st.step_pulse_time*TICKS_PER_MICROSECOND) >> 1); //++
  // Set the Autoreload value
#ifndef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
///???  TIM2->PSC = st.exec_segment->prescaler;
#endif
///???  TIM2->EGR = TIM_EGR_UG;
///???  TIM3->EGR = TIM_EGR_UG; // ++

  busy = false;
}

static uint8_t st_next_block_index(uint8_t block_index)
{
  block_index++;
  if ( block_index == (SEGMENT_BUFFER_SIZE-1) ) {
    return(0);
  }
  return(block_index);
}

static uint32_t *st_axis_counter(uint8_t axis)
{
  switch (axis) {
    case X_AXIS: return &st.counter_x;
    case Y_AXIS: return &st.counter_y;
    case Z_AXIS: return &st.counter_z;
    default:     return &st.counter_z;
  }
}

static uint32_t st_axis_step_delta(uint8_t axis)
{
#ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
  return st.steps[axis];
#else
  return st.exec_block->steps[axis];
#endif
}

static void st_init_bresenham_counters(void)
{
  uint32_t half = st.exec_block->step_event_count >> 1;

  st.counter_x = st.counter_y = st.counter_z = half;
}

static void st_bresenham_one_step(uint32_t axis_steps[N_AXIS])
{
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    uint32_t *counter = st_axis_counter(idx);
    uint16_t step_mask = get_step_pin_mask(idx);

    *counter += st_axis_step_delta(idx);
    if (*counter > st.exec_block->step_event_count) {
      *counter -= st.exec_block->step_event_count;
      if (sys.state != STATE_HOMING || (sys.homing_axis_lock & step_mask)) {
        axis_steps[idx]++;
        if (st.exec_block->direction_bits & get_direction_pin_mask(idx)) {
          sys_position[idx]--;
        } else {
          sys_position[idx]++;
        }
      }
    }
  }
}

static uint8_t st_can_go_dirs_for_axis(uint8_t axis, uint8_t direction_bits)
{
  uint8_t dirs = (uint8_t)(direction_bits ^ dir_port_invert_mask);

  if (dirs & (uint8_t)get_direction_pin_mask(axis)) {
    return 1U;
  }
  return 0U;
}

static void can_send_axis_go(uint8_t axis, uint8_t dirs, uint16_t step_per, uint32_t steps)
{
  uint16_t id;

  if (steps == 0) {
    return;
  }

  id = (uint16_t)((1U << axis) << 5);
  dirs = st_can_go_dirs_for_axis(axis, dirs);

#ifdef CAN_SEND_DEBUG
  can_send_count++;
  printk("\r\nCAN GO #%lu axis=%u id=0x%X dirs=0x%02X step_per=%u steps=%lu",
         (unsigned long)can_send_count, (unsigned)axis, (unsigned)id, dirs,
         (unsigned)step_per, (unsigned long)steps);
#else
  go_cmd_t cmd;

  cmd.cmd = GO_CMD;
  cmd.dirs = dirs;
  cmd.step_per = step_per;
  cmd.steps = steps;
  can_master_tx(id, (const uint8_t *)&cmd, sizeof(cmd));
#endif
}

#ifdef CAN_SEND_DEBUG
void st_can_debug_begin_line(const char *line)
{
  can_send_count = 0;
  if (line != NULL && line[0] != 0) {
    printk("\r\n>>> %s", line);
  }
}

void st_can_send_count_report(void)
{
  printk("\r\nCAN total: %lu", (unsigned long)can_send_count);
}

void st_can_master_poll_stat(void)
{
}

uint8_t st_can_get_present_mask(void)
{
  return 0U;
}
#endif

#ifndef CAN_SEND_DEBUG
static uint8_t st_can_axis_bit(uint8_t axis)
{
  return (uint8_t)(1U << axis);
}

static uint8_t st_can_axis_idx_from_brd(uint8_t axis_brd)
{
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (axis_brd == (uint8_t)(1U << idx)) {
      return idx;
    }
  }
  return 0xFFU;
}

static void st_can_mark_axis_present(uint8_t idx)
{
  uint8_t axis_bit = st_can_axis_bit(idx);

  st_can_axis_seen_mask |= axis_bit;
  st_can_axis_present_mask |= axis_bit;
  st_can_axis_last_seen_ms[idx] = HAL_GetTick();
}

static void st_can_presence_tick(void)
{
  uint32_t now = HAL_GetTick();
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    uint8_t axis_bit = st_can_axis_bit(idx);

    if (!ST_CAN_AXIS_ENABLED(idx)) {
      continue;
    }
    if ((st_can_axis_present_mask & axis_bit) != 0U) {
      if ((now - st_can_axis_last_seen_ms[idx]) >= (uint32_t)CAN_AXIS_PRESENCE_MS) {
        st_can_axis_present_mask &= (uint8_t)~axis_bit;
        st_can_axis_state[idx] = ST_CAN_STATE_IDLE;
      }
      continue;
    }
    if ((st_can_axis_seen_mask & axis_bit) == 0U &&
        st_can_stat_req_ms[idx] != 0U &&
        (now - st_can_stat_req_ms[idx]) >= (uint32_t)CAN_AXIS_STAT_RSP_MS) {
      st_can_axis_seen_mask |= axis_bit;
    }
  }
}

uint8_t st_can_get_present_mask(void)
{
  return (uint8_t)(st_can_axis_present_mask & (uint8_t)CAN_WAIT_AXIS_MASK);
}

void st_can_master_poll_stat(void)
{
  uint8_t cmd[2];
  uint8_t brd_mask = (uint8_t)CAN_WAIT_AXIS_MASK;
  uint8_t idx;
  uint32_t now = HAL_GetTick();

  if (brd_mask == 0U) {
    return;
  }

  cmd[0] = GET_STAT_CMD;
  cmd[1] = brd_mask;
  for (idx = 0; idx < N_AXIS; idx++) {
    if ((brd_mask & (uint8_t)(1U << idx)) != 0U) {
      st_can_stat_req_ms[idx] = now;
    }
  }
  set_ena_mot(1U);
  can_master_tx((uint32_t)(brd_mask << 5), cmd, 2U);
  st_can_presence_tick();
}

static uint8_t st_can_filter_move_mask(uint8_t move_mask)
{
  uint8_t idx;
  uint8_t filtered = 0U;

  for (idx = 0; idx < N_AXIS; idx++) {
    uint8_t axis_bit = st_can_axis_bit(idx);

    if ((move_mask & axis_bit) == 0U) {
      continue;
    }
    if (!ST_CAN_AXIS_ENABLED(idx)) {
      continue;
    }
    if ((st_can_axis_seen_mask & axis_bit) != 0U &&
        (st_can_axis_present_mask & axis_bit) == 0U) {
      continue;
    }
    filtered |= axis_bit;
  }
  return filtered;
}

static uint8_t st_can_wait_move_mask(uint8_t move_mask)
{
  return (uint8_t)(st_can_filter_move_mask(move_mask) & st_can_axis_present_mask);
}

static int st_can_axis_should_send(uint8_t axis)
{
  uint8_t axis_bit = st_can_axis_bit(axis);

  if (!ST_CAN_AXIS_ENABLED(axis)) {
    return 0;
  }
  if ((st_can_axis_seen_mask & axis_bit) != 0U &&
      (st_can_axis_present_mask & axis_bit) == 0U) {
    return 0;
  }
  return 1;
}

static void st_can_rx_process_msg(const can_msg_t *msg)
{
  uint8_t idx;

  if (msg->format != STANDARD_FORMAT || msg->id != ID_MASTER_CMD) {
    return;
  }

  if (msg->data[0] == PUT_ACK && msg->len >= sizeof(put_ack_t)) {
    const put_ack_t *ack = (const put_ack_t *)msg->data;

    if (ack->ack.ack_cmd == GO_CMD) {
      idx = st_can_axis_idx_from_brd(ack->ack.axis);
      if (idx < N_AXIS) {
        st_can_mark_axis_present(idx);
        st_can_go_ack_mask |= st_can_axis_bit(idx);
        st_can_axis_state[idx] = ST_CAN_STATE_MOVE;
      }
    }
  } else if (msg->data[0] == PUT_STAT_CMD && msg->len >= 4U) {
    const put_stat_cmd_t *stat = (const put_stat_cmd_t *)msg->data;

    set_ena_mot(0U);
    idx = st_can_axis_idx_from_brd(stat->axis);
    if (idx < N_AXIS) {
      st_can_mark_axis_present(idx);
      st_can_axis_state[idx] = stat->state;
    }
  }
}
#endif

void st_can_on_master_rx(const can_msg_t *msg)
{
#ifndef CAN_SEND_DEBUG
  if (msg != NULL) {
    st_can_rx_process_msg(msg);
  }
#else
  (void)msg;
#endif
}

static uint32_t st_can_segment_time_ms(uint16_t step_per, uint32_t max_steps)
{
  uint64_t ticks;

  if (max_steps == 0 || step_per == 0) {
    return 0;
  }

  ticks = (uint64_t)max_steps * (uint64_t)step_per * (uint64_t)CAN_STEP_PER_PRESCALE;
  ticks = (ticks * 1000ULL + (uint64_t)F_TIM - 1ULL) / (uint64_t)F_TIM;
  if (ticks > 0xFFFFFFFFULL) {
    return 0xFFFFFFFFUL;
  }
  return (uint32_t)ticks;
}

static void st_can_yield_ms(void)
{
#ifndef CAN_SEND_DEBUG
  st_can_master_service_rx();
#endif
#ifdef USE_THREADX
  tx_thread_relinquish();
#endif
}

#ifdef CAN_SEGMENT_WAIT
#ifndef CAN_SEND_DEBUG
static int st_can_axis_is_idle(uint8_t axis)
{
  return (st_can_axis_state[axis] & ST_CAN_AXIS_STATE_MASK) == ST_CAN_STATE_IDLE;
}

#if CAN_PIPELINE_GO
static void st_can_send_go_fire(uint8_t move_mask, uint8_t dirs, uint16_t step_per,
                                const uint32_t axis_steps[N_AXIS])
{
  uint8_t idx;

  move_mask = st_can_filter_move_mask(move_mask);
  if (move_mask == 0U) {
    return;
  }

  for (idx = 0; idx < N_AXIS; idx++) {
    if ((move_mask & st_can_axis_bit(idx)) && st_can_axis_should_send(idx)) {
      st_can_axis_state[idx] = ST_CAN_STATE_MOVE;
      can_send_axis_go(idx, dirs, step_per, axis_steps[idx]);
    }
  }
}

#if CAN_PIPELINE_WAIT_ACK
static void st_can_wait_go_ack(uint8_t move_mask)
{
  uint32_t t0;
  uint8_t want;

  want = st_can_filter_move_mask(move_mask);
  if (want == 0U) {
    return;
  }

  t0 = HAL_GetTick();
  for (;;) {
    want = st_can_filter_move_mask(move_mask);
    if (want == 0U) {
      return;
    }

    st_can_master_service_rx();
    if ((st_can_go_ack_mask & want) == want) {
      return;
    }
    if (sys.abort) {
      return;
    }
    if ((HAL_GetTick() - t0) >= (uint32_t)CAN_CMD_RSP_TIMEOUT_MS) {
      return;
    }

    protocol_execute_realtime();
    st_can_yield_ms();
  }
}
#endif
#endif

#if !CAN_PIPELINE_GO
static void st_can_send_go_one_axis_with_retry(uint8_t axis, uint8_t dirs, uint16_t step_per,
                                             uint32_t steps)
{
  uint32_t last_send;
  uint8_t axis_bit = st_can_axis_bit(axis);
  uint8_t retries = 0;

  if (!st_can_axis_should_send(axis)) {
    return;
  }

  st_can_go_ack_mask &= (uint8_t)~axis_bit;
  st_can_axis_state[axis] = ST_CAN_STATE_MOVE;
  can_send_axis_go(axis, dirs, step_per, steps);
  last_send = HAL_GetTick();

  for (;;) {
    st_can_master_service_rx();
    if (st_can_go_ack_mask & axis_bit) {
      return;
    }
    if (sys.abort) {
      return;
    }

    if ((HAL_GetTick() - last_send) >= (uint32_t)CAN_CMD_RSP_TIMEOUT_MS) {
      if (++retries >= 3U) {
        return;
      }
      can_send_axis_go(axis, dirs, step_per, steps);
      last_send = HAL_GetTick();
    }

    protocol_execute_realtime();
    st_can_yield_ms();
  }
}

static void st_can_send_go_with_retry(uint8_t move_mask, uint8_t dirs, uint16_t step_per,
                                    const uint32_t axis_steps[N_AXIS])
{
  uint8_t idx;

  st_can_go_ack_mask = 0;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (!(move_mask & st_can_axis_bit(idx))) {
      continue;
    }
    st_can_send_go_one_axis_with_retry(idx, dirs, step_per, axis_steps[idx]);
    if (sys.abort) {
      return;
    }
  }
}
#endif

static int st_can_wait_axes_move_done(uint8_t move_mask, uint16_t step_per, uint32_t max_steps)
{
  uint32_t timeout_ms;
  uint32_t t0;
  uint32_t last_poll = 0;
  uint8_t wait_mask;

  wait_mask = st_can_wait_move_mask(move_mask);
  if (wait_mask == 0U) {
    return 1;
  }

  timeout_ms = st_can_segment_time_ms(step_per, max_steps);
  timeout_ms += (timeout_ms >> 2) + 50U;
  t0 = HAL_GetTick();
  last_poll = t0;

  for (;;) {
    uint8_t idx;
    uint8_t done = 1;

    st_can_master_service_rx();
    st_can_presence_tick();
    wait_mask = st_can_wait_move_mask(move_mask);
    if (wait_mask == 0U) {
      return 1;
    }
    if (sys.abort) {
      return 0;
    }
    if (sys_rt_exec_state & EXEC_RESET) {
      sys.abort = true;
      return 0;
    }

    for (idx = 0; idx < N_AXIS; idx++) {
      if ((wait_mask & st_can_axis_bit(idx)) && !st_can_axis_is_idle(idx)) {
        done = 0;
        break;
      }
    }
    if (done) {
      return 1;
    }

    if ((HAL_GetTick() - t0) >= timeout_ms) {
      return 0;
    }

    if ((HAL_GetTick() - last_poll) >= (uint32_t)CAN_STAT_WAIT_POLL_MS) {
      st_can_master_poll_stat();
      last_poll = HAL_GetTick();
    }

    st_can_yield_ms();
  }
}

static int st_can_wait_axes_idle(uint8_t move_mask)
{
  uint32_t t0 = HAL_GetTick();
  uint32_t last_poll = t0;
  uint8_t wait_mask;

  for (;;) {
    uint8_t idx;
    uint8_t done = 1;

    st_can_master_service_rx();
    st_can_presence_tick();
    wait_mask = st_can_wait_move_mask(move_mask);
    if (wait_mask == 0U) {
      return 1;
    }
    if (sys.abort) {
      return 0;
    }
    if (sys_rt_exec_state & EXEC_RESET) {
      sys.abort = true;
      return 0;
    }

    for (idx = 0; idx < N_AXIS; idx++) {
      if ((wait_mask & st_can_axis_bit(idx)) && !st_can_axis_is_idle(idx)) {
        done = 0;
        break;
      }
    }
    if (done) {
      return 1;
    }

    if ((HAL_GetTick() - t0) >= (uint32_t)CAN_AXIS_WAIT_IDLE_MS) {
      return 0;
    }

    if ((HAL_GetTick() - last_poll) >= (uint32_t)CAN_STAT_WAIT_POLL_MS) {
      st_can_master_poll_stat();
      last_poll = HAL_GetTick();
    }

    st_can_yield_ms();
  }
}

static uint8_t st_can_move_mask_from_steps(const uint32_t axis_steps[N_AXIS])
{
  uint8_t idx;
  uint8_t move_mask = 0U;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (axis_steps[idx] != 0U && ST_CAN_AXIS_ENABLED(idx)) {
      move_mask |= st_can_axis_bit(idx);
    }
  }
  return st_can_filter_move_mask(move_mask);
}
#endif
#endif

static uint16_t st_can_step_per_clamp(uint16_t step_per)
{
  if (step_per == 0U || step_per >= 65535U) {
    return step_per;
  }
  if (step_per < CAN_STEP_PER_MIN) {
    step_per = (uint16_t)CAN_STEP_PER_MIN;
  }
#if CAN_STEP_PER_SLAVE_MIN > 0U
  if (step_per < CAN_STEP_PER_SLAVE_MIN) {
    step_per = (uint16_t)CAN_STEP_PER_SLAVE_MIN;
  }
#endif
#if CAN_STEP_PER_MAX > 0U
  if (step_per > CAN_STEP_PER_MAX) {
    return (uint16_t)CAN_STEP_PER_MAX;
  }
#endif
  return step_per;
}

static uint16_t st_can_step_per_batch_key_ex(uint16_t step_per, uint16_t quant)
{
  uint32_t key;

  if (step_per == 0U || step_per >= 65535U) {
    return step_per;
  }
  if (quant < 1U) {
    quant = 1U;
  }
  key = step_per;
  if (quant > 1U) {
    key = (key + quant / 2U) / quant * quant;
  }
#if CAN_STEP_PER_SLAVE_MIN > 0U
  if (key < CAN_STEP_PER_SLAVE_MIN) {
    key = CAN_STEP_PER_SLAVE_MIN;
  }
#endif
  if (key > 65535U) {
    key = 65535U;
  }
  return (uint16_t)key;
}

static void st_send_segment_can(uint8_t dirs, uint16_t step_per,
                                const uint32_t axis_steps[N_AXIS], uint8_t wait_done)
{
  uint8_t idx;
  uint8_t move_mask = 0;
  uint32_t max_steps = 0;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (axis_steps[idx] == 0 || !ST_CAN_AXIS_ENABLED(idx)) {
      continue;
    }
    move_mask |= st_can_axis_bit(idx);
    if (axis_steps[idx] > max_steps) {
      max_steps = axis_steps[idx];
    }
  }

  move_mask = st_can_filter_move_mask(move_mask);
  if (move_mask == 0) {
    return;
  }

  step_per = st_can_step_per_clamp(step_per);

#ifdef CAN_SEGMENT_WAIT
#ifndef CAN_SEND_DEBUG
#if CAN_PIPELINE_GO
  {
    uint8_t send_mask = move_mask;

    send_mask = st_can_filter_move_mask(send_mask);
    st_can_go_ack_mask &= (uint8_t)~send_mask;
    st_can_send_go_fire(move_mask, dirs, step_per, axis_steps);
#if CAN_PIPELINE_WAIT_ACK
    st_can_wait_go_ack(move_mask);
#endif
    if (!wait_done) {
      st_can_yield_ms();
    }
    if (wait_done) {
      st_can_wait_axes_move_done(move_mask, step_per, max_steps);
    }
  }
#else
  st_can_send_go_with_retry(move_mask, dirs, step_per, axis_steps);
  if (wait_done) {
    st_can_wait_axes_move_done(move_mask, step_per, max_steps);
  }
#endif
#else
  for (idx = 0; idx < N_AXIS; idx++) {
    if (move_mask & st_can_axis_bit(idx)) {
      can_send_axis_go(idx, dirs, step_per, axis_steps[idx]);
    }
  }
#endif
#else
  for (idx = 0; idx < N_AXIS; idx++) {
    if (move_mask & st_can_axis_bit(idx)) {
      can_send_axis_go(idx, dirs, step_per, axis_steps[idx]);
    }
  }
#endif
}

static void st_discard_current_segment(void)
{
  st.exec_segment = NULL;
  segment_buffer_tail++;
  if (segment_buffer_tail == SEGMENT_BUFFER_SIZE) {
    segment_buffer_tail = 0;
  }
}

static uint16_t st_can_step_per_from_segment(const segment_t *seg)
{
  uint32_t cycles = seg->cycles_per_tick;

#ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
  cycles <<= seg->amass_level;
#else
  if (seg->prescaler == 2) {
    cycles <<= 3;
  } else if (seg->prescaler == 3) {
    cycles <<= 6;
  }
#endif
  if (cycles == 0) {
    return 65535;
  }
  cycles = (cycles + CAN_STEP_PER_PRESCALE - 1U) / CAN_STEP_PER_PRESCALE;
  if (cycles < 1) {
    cycles = 1;
  }
  if (cycles > 65535) {
    cycles = 65535;
  }
  return (uint16_t)cycles;
}

static uint8_t st_can_planner_starved(void)
{
  return (pl_block == NULL && plan_get_current_block() == NULL) ? 1U : 0U;
}

static uint32_t st_can_batch_max_axis_steps(void)
{
  uint32_t max_steps = 0;
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (ST_CAN_AXIS_ENABLED(idx) && can_batch_steps[idx] > max_steps) {
      max_steps = can_batch_steps[idx];
    }
  }
  return max_steps;
}

static uint8_t st_can_dir_key(uint8_t dirs)
{
  uint8_t key = 0;
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (ST_CAN_AXIS_ENABLED(idx)) {
      key |= (uint8_t)(dirs & get_direction_pin_mask(idx));
    }
  }
  return key;
}

static uint8_t st_can_ramp_zone(uint8_t ramp_type)
{
  if (ramp_type == RAMP_CRUISE) {
    return RAMP_CRUISE;
  }
  if (ramp_type == RAMP_ACCEL) {
    return RAMP_ACCEL;
  }
  return RAMP_DECEL;
}

static uint16_t st_can_block_target_cruise_per(uint8_t block_index)
{
  uint8_t idx = segment_buffer_tail;
  uint16_t cruise_per = 0U;
  uint8_t has_cruise = 0U;

  while (idx != segment_buffer_head) {
    const segment_t *seg = &segment_buffer[idx];

    if (seg->st_block_index == block_index) {
      uint16_t key = st_can_step_per_batch_key_ex(seg->can_step_per, CAN_STEP_PER_QUANT_RAMP);

      if (seg->ramp_type == RAMP_CRUISE) {
        has_cruise = 1U;
        if (cruise_per == 0U || key < cruise_per) {
          cruise_per = key;
        }
      }
    }
    idx++;
    if (idx == SEGMENT_BUFFER_SIZE) {
      idx = 0U;
    }
  }
  if (has_cruise) {
    return cruise_per;
  }
  return 0U;
}

static uint32_t st_can_batch_min_steps_for_zone(uint8_t seg_zone)
{
  if (seg_zone == RAMP_ACCEL) {
    return (uint32_t)CAN_BATCH_MIN_STEPS_ACCEL;
  }
  if (seg_zone == RAMP_DECEL) {
    return (uint32_t)CAN_BATCH_MIN_STEPS_DECEL;
  }
  return (uint32_t)CAN_BATCH_MIN_STEPS_RAMP;
}

static float st_can_mm_min_for_step_per(float steps_per_mm, uint16_t step_per)
{
  uint32_t cycles;

  if (step_per == 0U || steps_per_mm <= 0.0f) {
    return 0.0f;
  }
  cycles = (uint32_t)step_per * (uint32_t)CAN_STEP_PER_PRESCALE;
  if (cycles == 0U) {
    return 0.0f;
  }
  return (float)((uint64_t)F_TIM * 60ULL) / ((float)cycles * steps_per_mm);
}

static uint16_t st_can_cap_accel_slow_start(uint16_t step_per)
{
  uint32_t slow_limit = (uint32_t)CAN_STEP_PER_RAMP_START_MAX;

  if (can_batch_target_cruise_per != 0U) {
    uint32_t cruise_limit = (uint32_t)can_batch_target_cruise_per *
                            (uint32_t)CAN_STEP_PER_RAMP_START_RATIO;

    if (cruise_limit < slow_limit) {
      slow_limit = cruise_limit;
    }
  }
  if (slow_limit > 65535U) {
    slow_limit = 65535U;
  }
  if ((uint32_t)step_per > slow_limit) {
    return (uint16_t)slow_limit;
  }
  return step_per;
}

static void st_can_cap_prep_profile(plan_block_t *pb, st_prep_t *prep_p, float steps_per_mm,
                                    float block_accel)
{
  float cap;
  float cap_sqr;
  float exit_sqr;
  float entry_sqr;
  float inv_2_accel;
  float intersect_distance;
  float nominal_speed;

  if (CAN_STEP_PER_SLAVE_MIN == 0U) {
    return;
  }
  cap = st_can_mm_min_for_step_per(steps_per_mm, (uint16_t)CAN_STEP_PER_SLAVE_MIN);
  if (cap <= 0.0f || prep_p->maximum_speed <= cap) {
    return;
  }

  inv_2_accel = 0.5f / block_accel;
  exit_sqr = prep_p->exit_speed * prep_p->exit_speed;
  entry_sqr = pb->entry_speed_sqr;
  cap_sqr = cap * cap;
  nominal_speed = cap;
  prep_p->maximum_speed = nominal_speed;

  if (entry_sqr > cap_sqr) {
    prep_p->accelerate_until = pb->millimeters - inv_2_accel * (entry_sqr - cap_sqr);
    if (prep_p->accelerate_until <= 0.0f) {
      prep_p->ramp_type = RAMP_DECEL;
      prep_p->exit_speed = sqrtf(entry_sqr - 2.0f * block_accel * pb->millimeters);
      if (prep_p->exit_speed < 0.0f) {
        prep_p->exit_speed = 0.0f;
      }
      return;
    }
    prep_p->decelerate_after = inv_2_accel * (cap_sqr - exit_sqr);
    prep_p->ramp_type = RAMP_DECEL_OVERRIDE;
    return;
  }

  intersect_distance = 0.5f * (pb->millimeters + inv_2_accel * (entry_sqr - exit_sqr));
  if (intersect_distance > 0.0f) {
    if (intersect_distance < pb->millimeters) {
      prep_p->decelerate_after = inv_2_accel * (cap_sqr - exit_sqr);
      if (prep_p->decelerate_after < intersect_distance) {
        if (entry_sqr >= cap_sqr - 0.001f) {
          prep_p->ramp_type = RAMP_ACCEL;
          prep_p->accelerate_until = pb->millimeters - inv_2_accel * (cap_sqr - entry_sqr);
          if (prep_p->accelerate_until < 0.0f) {
            prep_p->accelerate_until = 0.0f;
          }
        } else {
          prep_p->ramp_type = RAMP_ACCEL;
          prep_p->accelerate_until = pb->millimeters - inv_2_accel * (cap_sqr - entry_sqr);
        }
      } else {
        prep_p->ramp_type = RAMP_ACCEL;
        prep_p->accelerate_until = intersect_distance;
        prep_p->decelerate_after = intersect_distance;
        prep_p->maximum_speed = sqrtf(2.0f * block_accel * intersect_distance + exit_sqr);
        if (prep_p->maximum_speed > cap) {
          prep_p->maximum_speed = cap;
        }
      }
    } else {
      prep_p->ramp_type = RAMP_DECEL;
    }
  } else {
    prep_p->ramp_type = RAMP_ACCEL;
    prep_p->accelerate_until = 0.0f;
    prep_p->maximum_speed = prep_p->exit_speed;
  }
}

#if !CAN_BATCH_ZONE_ONLY
static uint8_t st_can_batch_key_change_flush(uint8_t seg_zone, uint16_t seg_key)
{
  if (seg_zone == RAMP_CRUISE) {
    return 0U;
  }
  if (can_batch_ramp_type == RAMP_ACCEL && seg_key < can_batch_step_per) {
#if CAN_BATCH_MIN_STEPS_ACCEL > 0U
    if (st_can_batch_max_axis_steps() < (uint32_t)CAN_BATCH_MIN_STEPS_ACCEL) {
      return 0U;
    }
#endif
#if CAN_STEP_PER_RAMP_HYST > 0U
    if (((uint32_t)can_batch_step_per - (uint32_t)seg_key) < (uint32_t)CAN_STEP_PER_RAMP_HYST) {
      return 0U;
    }
#endif
    return 1U;
  }
  if (can_batch_ramp_type == RAMP_DECEL && seg_key > can_batch_step_per) {
#if CAN_BATCH_MIN_STEPS_DECEL > 0U
    if (st_can_batch_max_axis_steps() < (uint32_t)CAN_BATCH_MIN_STEPS_DECEL) {
      return 0U;
    }
#endif
#if CAN_STEP_PER_RAMP_HYST > 0U
    if (((uint32_t)seg_key - (uint32_t)can_batch_step_per) < (uint32_t)CAN_STEP_PER_RAMP_HYST) {
      return 0U;
    }
#endif
    return 1U;
  }
#if CAN_BATCH_MIN_STEPS_RAMP > 0U
  if (st_can_batch_max_axis_steps() >= (uint32_t)CAN_BATCH_MIN_STEPS_RAMP) {
    return 1U;
  }
#endif
  return 0U;
}
#endif

static uint8_t st_can_batch_need_flush(uint8_t seg_dirs, uint8_t seg_block_index)
{
  if (!can_batch_active) {
    return 0;
  }
  if (st_can_batch_max_axis_steps() >= CAN_BATCH_MAX_STEPS) {
    return 1U;
  }
  if (st_can_dir_key(seg_dirs) != can_batch_dirs) {
    return 1U;
  }
  if (seg_block_index != can_batch_block_index) {
    return 1U;
  }
  return 0U;
}

static void st_can_batch_peek_send(uint32_t send_steps[N_AXIS])
{
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    send_steps[idx] = can_batch_steps[idx];
  }
  if (can_batch_block == NULL) {
    return;
  }
  for (idx = 0; idx < N_AXIS; idx++) {
    uint32_t rem = can_batch_block->planner_steps[idx];

    if (rem > can_batch_sent_steps[idx]) {
      rem -= can_batch_sent_steps[idx];
    } else {
      rem = 0;
    }
    if (send_steps[idx] > rem) {
      send_steps[idx] = rem;
    }
  }
}

static void st_can_batch_note_sent(const uint32_t send_steps[N_AXIS])
{
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    can_batch_sent_steps[idx] += send_steps[idx];
  }
}

static void st_can_batch_commit_send(const uint32_t send_steps[N_AXIS])
{
  uint8_t idx;

  for (idx = 0; idx < N_AXIS; idx++) {
    if (send_steps[idx] != 0U && send_steps[idx] <= can_batch_steps[idx]) {
      can_batch_steps[idx] -= send_steps[idx];
    }
  }
  st_can_batch_note_sent(send_steps);
}

static uint16_t st_can_batch_send_step_per(void)
{
#if CAN_BATCH_ZONE_ONLY
  if (can_batch_ramp_type == RAMP_ACCEL || can_batch_ramp_type == RAMP_DECEL) {
    return can_batch_step_per_max;
  }
#endif
  return can_batch_step_per;
}

static void st_can_batch_reset(void)
{
  memset(can_batch_steps, 0, sizeof(can_batch_steps));
  can_batch_step_per = 0;
  can_batch_step_per_max = 0;
  can_batch_ramp_type = 0;
  can_batch_target_cruise_per = 0U;
  can_batch_dirs = 0;
  can_batch_direction_bits = 0;
  can_batch_active = 0;
  can_batch_block = NULL;
}

static void st_can_batch_flush(uint8_t wait_done);

#if CAN_PIPELINE_GO
static uint8_t st_can_batch_ramp_wait(uint8_t base_wait)
{
  /* Pipeline: slave queues GO in go_cmd_queue and chains in mot_go_try_chain_isr(). */
  return base_wait;
}
#else
static uint8_t st_can_batch_ramp_wait(uint8_t base_wait)
{
  (void)base_wait;
  return 1U;
}
#endif

static void st_can_batch_sync_block(uint8_t seg_block_index)
{
  if (seg_block_index == can_batch_block_index) {
    return;
  }
  if (can_batch_active) {
#if CAN_PIPELINE_GO
    st_can_batch_flush(st_can_batch_ramp_wait(0U));
#else
    st_can_batch_flush(1U);
#endif
  }
  if (can_batch_active && st_can_batch_max_axis_steps() > 0U) {
    st_can_batch_reset();
  }
  memset(can_batch_sent_steps, 0, sizeof(can_batch_sent_steps));
  can_batch_block_index = seg_block_index;
  can_batch_cruise_step_per = 0U;
  can_batch_target_cruise_per = st_can_block_target_cruise_per(seg_block_index);
}

static void st_can_batch_flush(uint8_t wait_done)
{
  uint32_t send_steps[N_AXIS];
  uint8_t idx;
  uint8_t has_send = 0U;
  uint8_t has_remain = 0U;
  uint8_t move_mask;
  uint32_t max_steps = 0U;
  uint16_t step_per;
  int move_ok = 1;

  if (!can_batch_active) {
    return;
  }

  memset(send_steps, 0, sizeof(send_steps));
  st_can_batch_peek_send(send_steps);
  for (idx = 0; idx < N_AXIS; idx++) {
    if (send_steps[idx] != 0U && ST_CAN_AXIS_ENABLED(idx)) {
      has_send = 1U;
      if (send_steps[idx] > max_steps) {
        max_steps = send_steps[idx];
      }
    }
  }
  if (!has_send) {
    return;
  }

  move_mask = st_can_move_mask_from_steps(send_steps);
  if (move_mask == 0U) {
    return;
  }

  step_per = st_can_batch_send_step_per();
  if (can_batch_ramp_type == RAMP_ACCEL) {
    if (can_batch_target_cruise_per != 0U && step_per < can_batch_target_cruise_per) {
      step_per = can_batch_target_cruise_per;
    }
    if (can_batch_cruise_step_per != 0U && step_per < can_batch_cruise_step_per) {
      step_per = can_batch_cruise_step_per;
    }
    step_per = st_can_cap_accel_slow_start(step_per);
  }
  st_send_segment_can(can_batch_direction_bits, step_per, send_steps, wait_done);

  if (wait_done) {
    move_ok = st_can_wait_axes_move_done(move_mask, step_per, max_steps);
    if (!move_ok && !st_can_wait_axes_idle(move_mask)) {
      return;
    }
  }

  st_can_batch_commit_send(send_steps);
  for (idx = 0; idx < N_AXIS; idx++) {
    if (can_batch_steps[idx] != 0U) {
      has_remain = 1U;
      break;
    }
  }
  if (!has_remain) {
    st_can_batch_reset();
  }
}

void st_can_batch_flush_if_pending(void)
{
  if (can_batch_active) {
#if CAN_PIPELINE_GO
    st_can_batch_flush(st_can_batch_ramp_wait(0U));
#else
    st_can_batch_flush(1U);
#endif
  }
}

/* Execute prepared segments: Bresenham -> GO_CMD on CAN (one packet per axis). */
static void st_execute_can_segments(void)
{
  uint32_t axis_steps[N_AXIS];

  if (busy) {
    return;
  }
  busy = true;

  while (segment_buffer_head != segment_buffer_tail) {
    uint8_t seg_dirs;
    uint16_t n;
    uint8_t idx;

    if (st.exec_segment == NULL) {
      st.exec_segment = &segment_buffer[segment_buffer_tail];
      st.step_count = st.exec_segment->n_step;
      if (st.step_count == 0) {
        st_discard_current_segment();
        continue;
      }

      if (st.exec_block_index != st.exec_segment->st_block_index) {
        st.exec_block_index = st.exec_segment->st_block_index;
        st.exec_block = &st_block_buffer[st.exec_block_index];
        st_init_bresenham_counters();
      }

#ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
      {
        uint8_t amass_idx;
        for (amass_idx = 0; amass_idx < N_AXIS; amass_idx++) {
          st.steps[amass_idx] = st.exec_block->steps[amass_idx] >> st.exec_segment->amass_level;
        }
      }
#endif

#ifdef VARIABLE_SPINDLE
      spindle_set_speed(st.exec_segment->spindle_pwm);
#endif
    }

    if (sys_probe_state == PROBE_ACTIVE) {
      probe_state_monitor();
    }

    memset(axis_steps, 0, sizeof(axis_steps));
    n = st.step_count;
    while (n--) {
      st_bresenham_one_step(axis_steps);
    }

    seg_dirs = st.exec_block->direction_bits;
    {
      uint16_t seg_step_per = st.exec_segment->can_step_per;
      uint8_t seg_ramp_type = st.exec_segment->ramp_type;
      uint8_t seg_zone = st_can_ramp_zone(seg_ramp_type);
      uint16_t seg_quant = (seg_zone == RAMP_CRUISE) ? CAN_STEP_PER_QUANT : CAN_STEP_PER_QUANT_RAMP;
      uint16_t seg_key = st_can_step_per_batch_key_ex(seg_step_per, seg_quant);
      uint8_t seg_block_index = st.exec_segment->st_block_index;
      uint8_t do_flush = 0U;
      uint8_t flush_cruise_follow = 0U;
#if CAN_PIPELINE_GO
      uint8_t flush_wait = 0U;
#else
      uint8_t flush_wait = 1U;
#endif

      st_can_batch_sync_block(seg_block_index);

      {
        uint16_t cruise_target = st_can_block_target_cruise_per(seg_block_index);
        if (cruise_target != 0U) {
          can_batch_target_cruise_per = cruise_target;
        }
      }
      if (seg_zone == RAMP_CRUISE) {
        can_batch_target_cruise_per = seg_key;
      }

#if CAN_STEP_PER_SLAVE_MIN > 0U
      if (seg_zone == RAMP_ACCEL) {
        uint16_t cap_key = st_can_step_per_batch_key_ex((uint16_t)CAN_STEP_PER_SLAVE_MIN,
                                                        CAN_STEP_PER_QUANT_RAMP);
        if (seg_key < cap_key) {
          seg_key = cap_key;
        }
      }
#endif
      if (seg_zone == RAMP_ACCEL && can_batch_cruise_step_per != 0U &&
          seg_key < can_batch_cruise_step_per) {
        seg_key = can_batch_cruise_step_per;
      }

      if (seg_zone == RAMP_DECEL) {
        if (can_batch_cruise_step_per != 0U && seg_key < can_batch_cruise_step_per) {
          seg_key = can_batch_cruise_step_per;
        }
        if (can_batch_active && can_batch_ramp_type == RAMP_DECEL &&
            seg_key < can_batch_step_per) {
          seg_key = can_batch_step_per;
        }
      }

      if (can_batch_active) {
        if (st_can_batch_need_flush(seg_dirs, seg_block_index)) {
          do_flush = 1U;
        } else if (seg_zone != can_batch_ramp_type) {
          do_flush = 1U;
          if (seg_zone == RAMP_DECEL && can_batch_ramp_type == RAMP_CRUISE) {
            flush_wait = 0U;
          }
#if CAN_PIPELINE_GO
          if (seg_zone == RAMP_CRUISE && can_batch_ramp_type == RAMP_ACCEL) {
            flush_wait = 0U;
          }
#endif
#if !CAN_BATCH_ZONE_ONLY
        } else if (seg_key != can_batch_step_per) {
          if (seg_zone == RAMP_DECEL && seg_key < can_batch_step_per) {
            /* ignore faster keys while slowing down */
          } else if (st_can_batch_key_change_flush(seg_zone, seg_key)) {
            do_flush = 1U;
          } else if (st_can_batch_max_axis_steps() > 0U &&
                     (seg_zone == RAMP_ACCEL || seg_zone == RAMP_DECEL)) {
            uint32_t min_ramp = st_can_batch_min_steps_for_zone(seg_zone);
            if (min_ramp == 0U || st_can_batch_max_axis_steps() >= min_ramp) {
              do_flush = 1U;
            }
          } else if (seg_zone == RAMP_DECEL && seg_key > can_batch_step_per_max) {
            can_batch_step_per_max = seg_key;
          }
#endif
        }
        if (do_flush) {
          if (can_batch_ramp_type == RAMP_ACCEL && seg_zone == RAMP_CRUISE) {
            can_batch_target_cruise_per = seg_key;
#if CAN_PIPELINE_GO
            flush_cruise_follow = 1U;
#endif
          }
          st_can_batch_flush(st_can_batch_ramp_wait(flush_wait));
        }
      }
      for (idx = 0; idx < N_AXIS; idx++) {
        if (ST_CAN_AXIS_ENABLED(idx)) {
          can_batch_steps[idx] += axis_steps[idx];
        }
      }
      if (!can_batch_active) {
        can_batch_block = st.exec_block;
        can_batch_step_per = seg_key;
        can_batch_step_per_max = seg_key;
        can_batch_ramp_type = seg_zone;
        can_batch_dirs = st_can_dir_key(seg_dirs);
        can_batch_direction_bits = seg_dirs;
        can_batch_active = 1;
        if (seg_zone == RAMP_CRUISE) {
          can_batch_cruise_step_per = seg_key;
        }
      } else if (can_batch_ramp_type == RAMP_CRUISE) {
        can_batch_cruise_step_per = can_batch_step_per;
      } else if (seg_zone == RAMP_ACCEL && seg_key < can_batch_step_per_max) {
        can_batch_step_per_max = seg_key;
      } else if (seg_zone == RAMP_DECEL && seg_key > can_batch_step_per_max) {
        can_batch_step_per_max = seg_key;
      }
#if CAN_PIPELINE_GO
      if (flush_cruise_follow && can_batch_active &&
          can_batch_ramp_type == RAMP_CRUISE &&
          st_can_batch_max_axis_steps() > 0U) {
        st_can_batch_flush(st_can_batch_ramp_wait(0U));
      }
#endif
    }

    st_discard_current_segment();
  }

  if (segment_buffer_head == segment_buffer_tail) {
#if !CAN_BATCH_ZONE_ONLY
    if (can_batch_active && st_can_batch_max_axis_steps() > 0U) {
      st_can_batch_flush(st_can_batch_ramp_wait(0U));
    }
#endif
    if (st_can_planner_starved()) {
      st_can_batch_flush_if_pending();
      can_batch_block_index = 0xFFU;
      can_batch_target_cruise_per = 0U;
      memset(can_batch_sent_steps, 0, sizeof(can_batch_sent_steps));
#ifdef CAN_SEGMENT_WAIT
#ifndef CAN_SEND_DEBUG
      st_can_wait_axes_idle((uint8_t)CAN_WAIT_AXIS_MASK);
#endif
#endif
      st_go_idle();
      system_set_exec_state_flag(EXEC_CYCLE_STOP);
    }
    busy = false;
  }
}

/* Prepares step segment buffer. Continuously called from main program.

   The segment buffer is an intermediary buffer interface between the execution of steps
   by the stepper algorithm and the velocity profiles generated by the planner. The stepper
   algorithm only executes steps within the segment buffer and is filled by the main program
   when steps are "checked-out" from the first block in the planner buffer. This keeps the
   step execution and planning optimization processes atomic and protected from each other.
   The number of steps "checked-out" from the planner buffer and the number of segments in
   the segment buffer is sized and computed such that no operation in the main program takes
   longer than the time it takes the stepper algorithm to empty it before refilling it.
   Currently, the segment buffer conservatively holds roughly up to 40-50 msec of steps.
   NOTE: Computation units are in steps, millimeters, and minutes.
*/
void st_prep_buffer()
{
  if (bit_istrue(sys.step_control,STEP_CONTROL_END_MOTION)) {
    goto can_execute_exit;
  }

  while (segment_buffer_tail != segment_next_head) { // Check if we need to fill the buffer.

    // Determine if we need to load a new planner block or if the block needs to be recomputed.
    if (pl_block == NULL) {

      // Query planner for a queued block
      if (sys.step_control & STEP_CONTROL_EXECUTE_SYS_MOTION) { pl_block = plan_get_system_motion_block(); }
      else { pl_block = plan_get_current_block(); }
      if (pl_block == NULL) { goto can_execute_exit; } // No planner blocks. Exit.

      // Check if we need to only recompute the velocity profile or load a new block.
      if (prep.recalculate_flag & PREP_FLAG_RECALCULATE) {

        #ifdef PARKING_ENABLE
          if (prep.recalculate_flag & PREP_FLAG_PARKING) { prep.recalculate_flag &= ~(PREP_FLAG_RECALCULATE); }
          else { prep.recalculate_flag = false; }
        #else
          prep.recalculate_flag = false;
        #endif

      } else {

        // Load the Bresenham stepping data for the block.
        prep.st_block_index = st_next_block_index(prep.st_block_index);

        // Prepare and copy Bresenham algorithm segment data from the new planner block, so that
        // when the segment buffer completes the planner block, it may be discarded when the
        // segment buffer finishes the prepped block, but the stepper ISR is still executing it.
        st_prep_block = &st_block_buffer[prep.st_block_index];
        st_prep_block->direction_bits = pl_block->direction_bits;
        #ifdef ENABLE_DUAL_AXIS
          #if (DUAL_AXIS_SELECT == X_AXIS)
            if (st_prep_block->direction_bits & (1<<X_DIRECTION_BIT)) {
          #elif (DUAL_AXIS_SELECT == Y_AXIS)
            if (st_prep_block->direction_bits & (1<<Y_DIRECTION_BIT)) {
          #endif
            st_prep_block->direction_bits_dual = (1<<DUAL_DIRECTION_BIT);
          }  else { st_prep_block->direction_bits_dual = 0; }
        #endif
        uint8_t idx;
        #ifndef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
          for (idx=0; idx<N_AXIS; idx++) { st_prep_block->steps[idx] = (pl_block->steps[idx] << 1); }
          st_prep_block->step_event_count = (pl_block->step_event_count << 1);
        #else
          // With AMASS enabled, simply bit-shift multiply all Bresenham data by the max AMASS
          // level, such that we never divide beyond the original data anywhere in the algorithm.
          // If the original data is divided, we can lose a step from integer roundoff.
          for (idx=0; idx<N_AXIS; idx++) { st_prep_block->steps[idx] = pl_block->steps[idx] << MAX_AMASS_LEVEL; }
          st_prep_block->step_event_count = pl_block->step_event_count << MAX_AMASS_LEVEL;
        #endif

        // Initialize segment buffer data for generating the segments.
        prep.steps_remaining = (float)pl_block->step_event_count;
        prep.step_per_mm = prep.steps_remaining/pl_block->millimeters;
        st_prep_block->feed_rate = pl_block->programmed_rate;
        st_prep_block->steps_per_mm = pl_block->step_event_count / pl_block->millimeters;
        for (idx=0; idx<N_AXIS; idx++) {
          st_prep_block->planner_steps[idx] = pl_block->steps[idx];
        }
        prep.req_mm_increment = REQ_MM_INCREMENT_SCALAR/prep.step_per_mm;
        prep.dt_remainder = 0.0; // Reset for new segment block

        if ((sys.step_control & STEP_CONTROL_EXECUTE_HOLD) || (prep.recalculate_flag & PREP_FLAG_DECEL_OVERRIDE)) {
          // New block loaded mid-hold. Override planner block entry speed to enforce deceleration.
          prep.current_speed = prep.exit_speed;
          pl_block->entry_speed_sqr = prep.exit_speed*prep.exit_speed;
          prep.recalculate_flag &= ~(PREP_FLAG_DECEL_OVERRIDE);
        } else {
          prep.current_speed = sqrt(pl_block->entry_speed_sqr);
        }

        #ifdef VARIABLE_SPINDLE
          // Setup laser mode variables. PWM rate adjusted motions will always complete a motion with the
          // spindle off.
          st_prep_block->is_pwm_rate_adjusted = false;
          if (settings.flags & BITFLAG_LASER_MODE) {
            if (pl_block->condition & PL_COND_FLAG_SPINDLE_CCW) {
              // Pre-compute inverse programmed rate to speed up PWM updating per step segment.
              prep.inv_rate = 1.0/pl_block->programmed_rate;
              st_prep_block->is_pwm_rate_adjusted = true;
            }
          }
        #endif
      }

			/* ---------------------------------------------------------------------------------
			 Compute the velocity profile of a new planner block based on its entry and exit
			 speeds, or recompute the profile of a partially-completed planner block if the
			 planner has updated it. For a commanded forced-deceleration, such as from a feed
			 hold, override the planner velocities and decelerate to the target exit speed.
			*/
			prep.mm_complete = 0.0; // Default velocity profile complete at 0.0mm from end of block.
			if (sys.step_control & STEP_CONTROL_EXECUTE_HOLD) {
        st_can_block_accel = pl_block->acceleration;
      } else {
        st_can_block_accel = pl_block->acceleration * CAN_RAMP_ACCEL_SCALE;
      }
			float inv_2_accel = 0.5f / st_can_block_accel;
			if (sys.step_control & STEP_CONTROL_EXECUTE_HOLD) { // [Forced Deceleration to Zero Velocity]
				// Compute velocity profile parameters for a feed hold in-progress. This profile overrides
				// the planner block profile, enforcing a deceleration to zero speed.
				prep.ramp_type = RAMP_DECEL;
				// Compute decelerate distance relative to end of block.
				float decel_dist = pl_block->millimeters - inv_2_accel*pl_block->entry_speed_sqr;
				if (decel_dist < 0.0) {
					// Deceleration through entire planner block. End of feed hold is not in this block.
					prep.exit_speed = sqrt(pl_block->entry_speed_sqr-2*pl_block->acceleration*pl_block->millimeters);
				} else {
					prep.mm_complete = decel_dist; // End of feed hold.
					prep.exit_speed = 0.0;
				}
			} else { // [Normal Operation]
				// Compute or recompute velocity profile parameters of the prepped planner block.
				prep.ramp_type = RAMP_ACCEL; // Initialize as acceleration ramp.
				prep.accelerate_until = pl_block->millimeters;

				float exit_speed_sqr;
				float nominal_speed;
        if (sys.step_control & STEP_CONTROL_EXECUTE_SYS_MOTION) {
          prep.exit_speed = exit_speed_sqr = 0.0; // Enforce stop at end of system motion.
        } else {
          exit_speed_sqr = plan_get_exec_block_exit_speed_sqr();
          prep.exit_speed = sqrt(exit_speed_sqr);
        }

        nominal_speed = plan_compute_profile_nominal_speed(pl_block);
				float nominal_speed_sqr = nominal_speed*nominal_speed;
				float intersect_distance =
								0.5*(pl_block->millimeters+inv_2_accel*(pl_block->entry_speed_sqr-exit_speed_sqr));

        if (pl_block->entry_speed_sqr > nominal_speed_sqr) { // Only occurs during override reductions.
          prep.accelerate_until = pl_block->millimeters - inv_2_accel*(pl_block->entry_speed_sqr-nominal_speed_sqr);
          if (prep.accelerate_until <= 0.0) { // Deceleration-only.
            prep.ramp_type = RAMP_DECEL;
            // prep.decelerate_after = pl_block->millimeters;
            // prep.maximum_speed = prep.current_speed;

            // Compute override block exit speed since it doesn't match the planner exit speed.
            prep.exit_speed = sqrt(pl_block->entry_speed_sqr - 2*pl_block->acceleration*pl_block->millimeters);
            prep.recalculate_flag |= PREP_FLAG_DECEL_OVERRIDE; // Flag to load next block as deceleration override.

            // TODO: Determine correct handling of parameters in deceleration-only.
            // Can be tricky since entry speed will be current speed, as in feed holds.
            // Also, look into near-zero speed handling issues with this.

          } else {
            // Decelerate to cruise or cruise-decelerate types. Guaranteed to intersect updated plan.
            prep.decelerate_after = inv_2_accel*(nominal_speed_sqr-exit_speed_sqr); // Should always be >= 0.0 due to planner reinit.
            prep.maximum_speed = nominal_speed;
            prep.ramp_type = RAMP_DECEL_OVERRIDE;
          }
				} else if (intersect_distance > 0.0) {
					if (intersect_distance < pl_block->millimeters) { // Either trapezoid or triangle types
						// NOTE: For acceleration-cruise and cruise-only types, following calculation will be 0.0.
						prep.decelerate_after = inv_2_accel*(nominal_speed_sqr-exit_speed_sqr);
						if (prep.decelerate_after < intersect_distance) { // Trapezoid type
							prep.maximum_speed = nominal_speed;
							if (pl_block->entry_speed_sqr == nominal_speed_sqr) {
								// Cruise-deceleration or cruise-only type.
								prep.ramp_type = RAMP_CRUISE;
							} else {
								// Full-trapezoid or acceleration-cruise types
								prep.accelerate_until -= inv_2_accel*(nominal_speed_sqr-pl_block->entry_speed_sqr);
							}
						} else { // Triangle type
							prep.accelerate_until = intersect_distance;
							prep.decelerate_after = intersect_distance;
							prep.maximum_speed = sqrtf(2.0f * st_can_block_accel * intersect_distance + exit_speed_sqr);
						}
					} else { // Deceleration-only type
            prep.ramp_type = RAMP_DECEL;
            // prep.decelerate_after = pl_block->millimeters;
            // prep.maximum_speed = prep.current_speed;
					}
				} else { // Acceleration-only type
					prep.accelerate_until = 0.0;
					// prep.decelerate_after = 0.0;
					prep.maximum_speed = prep.exit_speed;
				}
			}

      if (!(sys.step_control & STEP_CONTROL_EXECUTE_HOLD)) {
        st_prep_block = &st_block_buffer[prep.st_block_index];
        st_can_cap_prep_profile(pl_block, &prep, st_prep_block->steps_per_mm, st_can_block_accel);
      }

      #ifdef VARIABLE_SPINDLE
        bit_true(sys.step_control, STEP_CONTROL_UPDATE_SPINDLE_PWM); // Force update whenever updating block.
      #endif
    }

    // Initialize new segment
    segment_t *prep_segment = &segment_buffer[segment_buffer_head];

    // Set new segment to point to the current segment data block.
    prep_segment->st_block_index = prep.st_block_index;

    /*------------------------------------------------------------------------------------
        Compute the average velocity of this new segment by determining the total distance
      traveled over the segment time DT_SEGMENT. The following code first attempts to create
      a full segment based on the current ramp conditions. If the segment time is incomplete
      when terminating at a ramp state change, the code will continue to loop through the
      progressing ramp states to fill the remaining segment execution time. However, if
      an incomplete segment terminates at the end of the velocity profile, the segment is
      considered completed despite having a truncated execution time less than DT_SEGMENT.
        The velocity profile is always assumed to progress through the ramp sequence:
      acceleration ramp, cruising state, and deceleration ramp. Each ramp's travel distance
      may range from zero to the length of the block. Velocity profiles can end either at
      the end of planner block (typical) or mid-block at the end of a forced deceleration,
      such as from a feed hold.
    */
    float dt_max = DT_SEGMENT; // Maximum segment time
    float dt = 0.0; // Initialize segment time
    float time_var = dt_max; // Time worker variable
    float mm_var; // mm-Distance worker variable
    float speed_var; // Speed worker variable
    float mm_remaining = pl_block->millimeters; // New segment distance from end of block.
    float minimum_mm = mm_remaining-prep.req_mm_increment; // Guarantee at least one step.
    if (minimum_mm < 0.0) { minimum_mm = 0.0; }

    do {
      switch (prep.ramp_type) {
        case RAMP_DECEL_OVERRIDE:
          speed_var = st_can_block_accel * time_var;
          if (prep.current_speed-prep.maximum_speed <= speed_var) {
            // Cruise or cruise-deceleration types only for deceleration override.
            mm_remaining = prep.accelerate_until;
            time_var = 2.0*(pl_block->millimeters-mm_remaining)/(prep.current_speed+prep.maximum_speed);
            prep.ramp_type = RAMP_CRUISE;
            prep.current_speed = prep.maximum_speed;
          } else { // Mid-deceleration override ramp.
            mm_remaining -= time_var*(prep.current_speed - 0.5*speed_var);
            prep.current_speed -= speed_var;
          }
          break;
        case RAMP_ACCEL:
          // NOTE: Acceleration ramp only computes during first do-while loop.
        	// dT = A*dT
          speed_var = st_can_block_accel * time_var;
          // dX = dX - (0.5*A*dT? + V0*dT)
          mm_remaining -= time_var*(prep.current_speed + 0.5*speed_var);
          if (mm_remaining < prep.accelerate_until) { // End of acceleration ramp.
            // Acceleration-cruise, acceleration-deceleration ramp junction, or end of block.
            mm_remaining = prep.accelerate_until; // NOTE: 0.0 at EOB
            time_var = 2.0*(pl_block->millimeters-mm_remaining)/(prep.current_speed+prep.maximum_speed);
            if (mm_remaining == prep.decelerate_after) { prep.ramp_type = RAMP_DECEL; }
            else { prep.ramp_type = RAMP_CRUISE; }
            prep.current_speed = prep.maximum_speed;
          } else { // Acceleration only.
            prep.current_speed += speed_var;
          }
          break;
        case RAMP_CRUISE:
          // NOTE: mm_var used to retain the last mm_remaining for incomplete segment time_var calculations.
          // NOTE: If maximum_speed*time_var value is too low, round-off can cause mm_var to not change. To
          //   prevent this, simply enforce a minimum speed threshold in the planner.
          mm_var = mm_remaining - prep.maximum_speed*time_var;
          if (mm_var < prep.decelerate_after) { // End of cruise.
            // Cruise-deceleration junction or end of block.
            time_var = (mm_remaining - prep.decelerate_after)/prep.maximum_speed;
            mm_remaining = prep.decelerate_after; // NOTE: 0.0 at EOB
            prep.ramp_type = RAMP_DECEL;
          } else { // Cruising only.
            mm_remaining = mm_var;
          }
          break;
        default: // case RAMP_DECEL:
          // NOTE: mm_var used as a misc worker variable to prevent errors when near zero speed.
          speed_var = st_can_block_accel * time_var; // Used as delta speed (mm/min)
          if (prep.current_speed > speed_var) { // Check if at or below zero speed.
            // Compute distance from end of segment to end of block.
            mm_var = mm_remaining - time_var*(prep.current_speed - 0.5*speed_var); // (mm)
            if (mm_var > prep.mm_complete) { // Typical case. In deceleration ramp.
              mm_remaining = mm_var;
              prep.current_speed -= speed_var;
              break; // Segment complete. Exit switch-case statement. Continue do-while loop.
            }
          }
          // Otherwise, at end of block or end of forced-deceleration.
          time_var = 2.0*(mm_remaining-prep.mm_complete)/(prep.current_speed+prep.exit_speed);
          mm_remaining = prep.mm_complete;
          prep.current_speed = prep.exit_speed;
      }
      dt += time_var; // Add computed ramp time to total segment time.
      if (dt < dt_max) { time_var = dt_max - dt; } // **Incomplete** At ramp junction.
      else {
        if (mm_remaining > minimum_mm) { // Check for very slow segments with zero steps.
          // Increase segment time to ensure at least one step in segment. Override and loop
          // through distance calculations until minimum_mm or mm_complete.
          dt_max += DT_SEGMENT;
          time_var = dt_max - dt;
        } else {
          break; // **Complete** Exit loop. Segment execution time maxed.
        }
      }
    } while (mm_remaining > prep.mm_complete); // **Complete** Exit loop. Profile complete.

    #ifdef VARIABLE_SPINDLE
      /* -----------------------------------------------------------------------------------
        Compute spindle speed PWM output for step segment
      */

      if (st_prep_block->is_pwm_rate_adjusted || (sys.step_control & STEP_CONTROL_UPDATE_SPINDLE_PWM)) {
        if (pl_block->condition & (PL_COND_FLAG_SPINDLE_CW | PL_COND_FLAG_SPINDLE_CCW)) {
          float rpm = pl_block->spindle_speed;
          // NOTE: Feed and rapid overrides are independent of PWM value and do not alter laser power/rate.
          if (st_prep_block->is_pwm_rate_adjusted) { rpm *= (prep.current_speed * prep.inv_rate); }
          // If current_speed is zero, then may need to be rpm_min*(100/MAX_SPINDLE_SPEED_OVERRIDE)
          // but this would be instantaneous only and during a motion. May not matter at all.
          prep.current_spindle_pwm = spindle_compute_pwm_value(rpm);
        } else {
          sys.spindle_speed = 0.0;
          prep.current_spindle_pwm = SPINDLE_PWM_OFF_VALUE;
        }
        bit_false(sys.step_control,STEP_CONTROL_UPDATE_SPINDLE_PWM);
      }
      prep_segment->spindle_pwm = prep.current_spindle_pwm; // Reload segment PWM value

    #endif

    /* -----------------------------------------------------------------------------------
       Compute segment step rate, steps to execute, and apply necessary rate corrections.
       NOTE: Steps are computed by direct scalar conversion of the millimeter distance
       remaining in the block, rather than incrementally tallying the steps executed per
       segment. This helps in removing floating point round-off issues of several additions.
       However, since floats have only 7.2 significant digits, long moves with extremely
       high step counts can exceed the precision of floats, which can lead to lost steps.
       Fortunately, this scenario is highly unlikely and unrealistic in CNC machines
       supported by Grbl (i.e. exceeding 10 meters axis travel at 200 step/mm).
    */
    float step_dist_remaining = prep.step_per_mm*mm_remaining; // Convert mm_remaining to steps
    float n_steps_remaining = ceil(step_dist_remaining); // Round-up current steps remaining
    float last_n_steps_remaining = ceil(prep.steps_remaining); // Round-up last steps remaining
    prep_segment->n_step = (uint16_t)(last_n_steps_remaining-n_steps_remaining); // Compute number of steps to execute.

    // Bail if we are at the end of a feed hold and don't have a step to execute.
    if (prep_segment->n_step == 0) {
      if (sys.step_control & STEP_CONTROL_EXECUTE_HOLD) {
        // Less than one step to decelerate to zero speed, but already very close. AMASS
        // requires full steps to execute. So, just bail.
        bit_true(sys.step_control,STEP_CONTROL_END_MOTION);
        #ifdef PARKING_ENABLE
          if (!(prep.recalculate_flag & PREP_FLAG_PARKING)) { prep.recalculate_flag |= PREP_FLAG_HOLD_PARTIAL_BLOCK; }
        #endif
        goto can_execute_exit; // Segment not generated, but current step data still retained.
      }
    }

    // Compute segment step rate. Since steps are integers and mm distances traveled are not,
    // the end of every segment can have a partial step of varying magnitudes that are not
    // executed, because the stepper ISR requires whole steps due to the AMASS algorithm. To
    // compensate, we track the time to execute the previous segment's partial step and simply
    // apply it with the partial step distance to the current segment, so that it minutely
    // adjusts the whole segment rate to keep step output exact. These rate adjustments are
    // typically very small and do not adversely effect performance, but ensures that Grbl
    // outputs the exact acceleration and velocity profiles as computed by the planner.
    dt += prep.dt_remainder; // Apply previous segment partial step execute time
    float inv_rate = dt/(last_n_steps_remaining - step_dist_remaining); // Compute adjusted step rate inverse

    // Compute CPU cycles per step for the prepped segment.
   uint32_t cycles = (uint32_t)ceilf((TICKS_PER_MICROSECOND * 1000000) *inv_rate * 60); // (cycles/step)
///uint32_t cycles =10; ///???
    #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
      // Compute step timing and multi-axis smoothing level.
      // NOTE: AMASS overdrives the timer with each level, so only one prescalar is required.
      if (cycles < AMASS_LEVEL1) { prep_segment->amass_level = 0; }
      else {
        if (cycles < AMASS_LEVEL2) { prep_segment->amass_level = 1; }
        else if (cycles < AMASS_LEVEL3) { prep_segment->amass_level = 2; }
        else { prep_segment->amass_level = 3; }
        cycles >>= prep_segment->amass_level;
        prep_segment->n_step <<= prep_segment->amass_level;
      }
      if (cycles < (1UL << 16)) { prep_segment->cycles_per_tick = cycles; } // < 65536 (4.1ms @ 16MHz)
      else { prep_segment->cycles_per_tick = 0xffff; } // Just set the slowest speed possible.
    #else
      // Compute step timing and timer prescalar for normal step generation.
      if (cycles < (1UL << 16)) { // < 65536  (4.1ms @ 16MHz)
        prep_segment->prescaler = 1; // prescaler: 0
        prep_segment->cycles_per_tick = cycles;
      } else if (cycles < (1UL << 19)) { // < 524288 (32.8ms@16MHz)
        prep_segment->prescaler = 2; // prescaler: 8
        prep_segment->cycles_per_tick = cycles >> 3;
      } else {
        prep_segment->prescaler = 3; // prescaler: 64
        if (cycles < (1UL << 22)) { // < 4194304 (262ms@16MHz)
          prep_segment->cycles_per_tick =  cycles >> 6;
        } else { // Just set the slowest speed possible. (Around 4 step/sec.)
          prep_segment->cycles_per_tick = 0xffff;
        }
      }
    #endif

    prep_segment->can_step_per = st_can_step_per_from_segment(prep_segment);
    prep_segment->ramp_type = prep.ramp_type;

    // Segment complete! Increment segment buffer indices, so stepper ISR can immediately execute it.
    segment_buffer_head = segment_next_head;
    if ( ++segment_next_head == SEGMENT_BUFFER_SIZE ) { segment_next_head = 0; }

    // Update the appropriate planner and segment data.
    pl_block->millimeters = mm_remaining;
    prep.steps_remaining = n_steps_remaining;
    prep.dt_remainder = (n_steps_remaining - step_dist_remaining)*inv_rate;

    // Check for exit conditions and flag to load next planner block.
    if (mm_remaining == prep.mm_complete) {
      // End of planner block or forced-termination. No more distance to be executed.
      if (mm_remaining > 0.0) { // At end of forced-termination.
        // Reset prep parameters for resuming and then bail. Allow the stepper ISR to complete
        // the segment queue, where realtime protocol will set new state upon receiving the
        // cycle stop flag from the ISR. Prep_segment is blocked until then.
        bit_true(sys.step_control,STEP_CONTROL_END_MOTION);
        #ifdef PARKING_ENABLE
          if (!(prep.recalculate_flag & PREP_FLAG_PARKING)) { prep.recalculate_flag |= PREP_FLAG_HOLD_PARTIAL_BLOCK; }
        #endif
        goto can_execute_exit; // Bail!
      } else { // End of planner block
        // The planner block is complete. All steps are set to be executed in the segment buffer.
        if (sys.step_control & STEP_CONTROL_EXECUTE_SYS_MOTION) {
          bit_true(sys.step_control,STEP_CONTROL_END_MOTION);
          goto can_execute_exit;
        }
        pl_block = NULL; // Set pointer to indicate check and load next planner block.
        plan_discard_current_block();
      }
    }

  }

can_execute_exit:
  st_execute_can_segments();
}

void st_update_plan_block_parameters()
{
  if (pl_block != NULL) {
    prep.recalculate_flag |= PREP_FLAG_RECALCULATE;
    pl_block->entry_speed_sqr = prep.current_speed * prep.current_speed;
    pl_block = NULL;
  }
}

// Called by realtime status reporting to fetch the current speed being executed. This value
// however is not exactly the current speed, but the speed computed in the last step segment
// in the segment buffer. It will always be behind by up to the number of segment blocks (-1)
// divided by the ACCELERATION TICKS PER SECOND in seconds.
float st_get_realtime_rate()
{
  if (sys.state & (STATE_CYCLE | STATE_HOMING | STATE_HOLD | STATE_JOG | STATE_SAFETY_DOOR)){
    return prep.current_speed;
  }
  return 0.0f;
}

// Stepper shutdown
void st_go_idle()
{
  // Disable Stepper Driver Interrupt. Allow Stepper Port Reset Interrupt to finish, if active.
///  HAL_NVIC_DisableIRQ(TIM2_IRQn);
///  HAL_NVIC_DisableIRQ(TIM3_IRQn); // ++
  busy = false;

  // Set stepper driver idle state, disabled or enabled, depending on settings and circumstances.
  bool pin_state = false; // Keep enabled.
  if (((settings.stepper_idle_lock_time != 0xff) || sys_rt_exec_alarm || sys.state == STATE_SLEEP) && sys.state != STATE_HOMING) {
    // Force stepper dwell to lock axes for a defined amount of time to ensure the axes come to a complete
    // stop and not drift from residual inertial forces at the end of the last movement.
    delay_ms(settings.stepper_idle_lock_time);
    pin_state = true; // Override. Disable steppers.
  }
  if (bit_istrue(settings.flags,BITFLAG_INVERT_ST_ENABLE)) {
    pin_state = !pin_state;
  } // Apply pin invert.
///  if (pin_state) {
///    HAL_GPIO_WritePin(STEPPERS_DISABLE_PORT, STEPPERS_DISABLE_BIT_Pin, GPIO_PIN_SET);
///  }
 /// else {
 ///   HAL_GPIO_WritePin(STEPPERS_DISABLE_PORT, STEPPERS_DISABLE_BIT_Pin, GPIO_PIN_RESET);
///  }
}

// Initialize and start the stepper motor subsystem
void stepper_init()  ///nothing
{

}

// Generates the step and direction port invert masks used in the Stepper Interrupt Driver.
void st_generate_step_dir_invert_masks()
{
  uint8_t idx;
  step_port_invert_mask = 0;
  dir_port_invert_mask = 0;
  for (idx=0; idx<N_AXIS; idx++) {
    if (bit_istrue(settings.step_invert_mask,bit(idx))) {
      step_port_invert_mask |= get_step_pin_mask(idx);
    }
    if (bit_istrue(settings.dir_invert_mask,bit(idx))) {
      dir_port_invert_mask |= get_direction_pin_mask(idx);
    }
  }
  #ifdef ENABLE_DUAL_AXIS
    step_port_invert_mask_dual = 0;
    dir_port_invert_mask_dual = 0;
    // NOTE: Dual axis invert uses the N_AXIS bit to set step and direction invert pins.
    if (bit_istrue(settings.step_invert_mask,bit(N_AXIS))) { step_port_invert_mask_dual = (1<<DUAL_STEP_BIT); }
    if (bit_istrue(settings.dir_invert_mask,bit(N_AXIS))) { dir_port_invert_mask_dual = (1<<DUAL_DIRECTION_BIT); }
  #endif
}

void st_reset()
{
  // Initialize stepper driver idle state.
  st_go_idle();

  // Initialize stepper algorithm variables.
  memset(&prep, 0, sizeof(st_prep_t));
  memset(&st, 0, sizeof(stepper_t));
  st.exec_segment = NULL;
  pl_block = NULL;  // Planner block pointer used by segment buffer
  segment_buffer_tail = 0;
  segment_buffer_head = 0; // empty = tail
  segment_next_head = 1;
  busy = false;

  st_can_batch_reset();
  can_batch_block_index = 0xFFU;
  memset(can_batch_sent_steps, 0, sizeof(can_batch_sent_steps));

#ifndef CAN_SEND_DEBUG
  {
    uint8_t idx;
    for (idx = 0; idx < N_AXIS; idx++) {
      st_can_axis_state[idx] = ST_CAN_STATE_IDLE;
      st_can_axis_last_seen_ms[idx] = 0U;
      st_can_stat_req_ms[idx] = 0U;
    }
    st_can_go_ack_mask = 0;
    st_can_axis_present_mask = 0;
    st_can_axis_seen_mask = 0;
    st_can_master_poll_stat();
  }
#endif

#ifdef CAN_SEND_DEBUG
  can_send_count = 0;
#endif

  st_generate_step_dir_invert_masks();
  st.dir_outbits = dir_port_invert_mask; // Initialize direction bits to default.

  // Initialize step and direction port pins.
 /// GPIO_WritePort(STEP_PORT, (GPIO_ReadPort(STEP_PORT) & ~STEP_MASK) | (step_port_invert_mask & STEP_MASK));
 /// GPIO_WritePort(DIRECTION_PORT, (GPIO_ReadPort(DIRECTION_PORT) & ~DIRECTION_MASK) | (dir_port_invert_mask & DIRECTION_MASK));

  #ifdef ENABLE_DUAL_AXIS
    st.dir_outbits_dual = dir_port_invert_mask_dual;
    STEP_PORT_DUAL = (STEP_PORT_DUAL & ~STEP_MASK_DUAL) | step_port_invert_mask_dual;
    DIRECTION_PORT_DUAL = (DIRECTION_PORT_DUAL & ~DIRECTION_MASK_DUAL) | dir_port_invert_mask_dual;
  #endif
}
