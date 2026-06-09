#ifndef RTOS_COMPAT_H
#define RTOS_COMPAT_H

#include <stdint.h>
#include "tx_api.h"

typedef TX_THREAD *TaskHandle_t;
typedef ULONG      TickType_t;
typedef UINT       BaseType_t;
typedef UINT       UBaseType_t;
typedef TX_QUEUE  *xQueueHandle;
typedef TX_QUEUE  *QueueHandle_t;

#define pdTRUE                  ((BaseType_t)1)
#define pdFALSE                 ((BaseType_t)0)
#define pdPASS                  ((BaseType_t)1)
#define pdFAIL                  ((BaseType_t)0)
#define portMAX_DELAY           TX_WAIT_FOREVER
#define tskIDLE_PRIORITY        0

#define configMAX_PRIORITIES    8
#define configTICK_RATE_HZ      1000
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY 15
#define RTOS_TIME_SLICE_TICKS   10U

UINT fr_to_tx_priority(UBaseType_t priority);

#define vTaskDelay(ticks)       tx_thread_sleep((ULONG)(ticks))
#define taskYIELD()             tx_thread_relinquish()

BaseType_t xTaskCreate(void (*task)(void *), const char *name,
                       uint16_t stack_depth, void *param,
                       UBaseType_t priority, TaskHandle_t *handle);

void vTaskStartScheduler(void);
void vTaskSuspend(TaskHandle_t handle);
void vTaskResume(TaskHandle_t handle);

xQueueHandle xQueueCreate(UBaseType_t length, UBaseType_t item_size);
BaseType_t xQueueSend(xQueueHandle queue, const void *item, TickType_t timeout);
BaseType_t xQueueReceive(xQueueHandle queue, void *item, TickType_t timeout);
BaseType_t xQueueSendFromISR(xQueueHandle queue, const void *item, BaseType_t *woken);
BaseType_t xQueueReceiveFromISR(xQueueHandle queue, void *item, BaseType_t *woken);
BaseType_t xQueueIsQueueEmptyFromISR(xQueueHandle queue);

#define taskENTER_CRITICAL()    (void)tx_interrupt_control(TX_INT_DISABLE)
#define taskEXIT_CRITICAL()     (void)tx_interrupt_control(TX_INT_ENABLE)

#endif /* RTOS_COMPAT_H */
