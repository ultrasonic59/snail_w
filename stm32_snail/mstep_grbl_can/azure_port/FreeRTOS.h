#ifndef FREERTOS_H
#define FREERTOS_H

/* Legacy header name only: maps xTaskCreate/vTaskDelay/... to ThreadX. */
#include "rtos_compat.h"

#define INCLUDE_vTaskDelay              1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_vTaskSuspend            1
#define configMINIMAL_STACK_SIZE        128

#endif /* FREERTOS_H */
