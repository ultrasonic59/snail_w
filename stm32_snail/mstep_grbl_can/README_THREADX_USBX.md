# mstep_grbl_can: ThreadX (без FreeRTOS)

RTOS: **ThreadX**. Ядро **FreeRTOS не используется** — прослойка `rtos_compat` удалена.

## Архитектура потоков

| Компонент | Файлы |
|-----------|--------|
| Точка входа | `azure_port/tx_application.c` → `tx_kernel_enter()` |
| Потоки/очереди | `common_stm32/threadx_app/` (`tx_app_thread_create`, `tx_app_queue_*`) |
| CAN master | `src/drv/can_thr.c` |
| GRBL / VCP | `grbl_tsk.c`, `common_stm32/usb/cdc_vcp/usbd_cdc_vcp.c` |

**Не добавляйте** группу `FreeRTOS`, `rtos_compat`, пути `common/freertos/...` и shim-заголовки в include paths.

## Сборка

```powershell
python D:\proj\grbl_can\mstep_grbl_can\patch_ewp_threadx.py
```

Открыть **`mstep_grbl_can_threadx.ewp`**:
- RTOS plugin: **ThreadX**
- Linker: **`mstep_threadx.icf`**
- Группа **FreeRTOS** — отсутствует
- **`src/main.c`** — excluded (точка входа: `azure_port/tx_application.c`)

Slave: **`app_step_axis_dima.ewp`**, точка входа `azure_port/tx_application.c`.

После изменений: **Project → Clean → Rebuild**.

## USB

ST USB Device Library (`common_stm32/usb/`), StdPeriph, без HAL.
