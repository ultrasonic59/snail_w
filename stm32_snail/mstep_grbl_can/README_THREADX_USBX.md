# mstep_grbl_can: ThreadX (без FreeRTOS)

RTOS: **ThreadX**. Ядро **FreeRTOS не используется** и не должно быть в проекте.

## Совместимость API

Старый код с `#include "FreeRTOS.h"` и `xTaskCreate`/`vTaskDelay` работает через shim в `azure_port/`:

| Файл | Назначение |
|------|------------|
| `FreeRTOS.h`, `task.h`, `queue.h` | Только имена заголовков, внутри — `rtos_compat.h` |
| `rtos_compat.c/h` | Реализация на ThreadX |

**Не добавляйте** группу `FreeRTOS` и пути `common/freertos/...` в include paths.

## Сборка

```powershell
python D:\proj\grbl_can\mstep_grbl_can\patch_ewp_threadx.py
```

Открыть **`mstep_grbl_can_threadx.ewp`**:
- RTOS plugin: **ThreadX**
- Linker: **`mstep_threadx.icf`**
- Группа **FreeRTOS** — отсутствует (если есть — удалить)
- **`src/main.c`** — excluded (точка входа: `azure_port/tx_application.c`)

После изменений: **Project → Clean → Rebuild**.

## USB

ST USB Device Library (`common_stm32/usb/`), StdPeriph, без HAL.
