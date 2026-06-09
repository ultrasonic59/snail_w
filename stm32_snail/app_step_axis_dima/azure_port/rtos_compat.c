#include <string.h>
#include "rtos_compat.h"

typedef struct {
    TX_QUEUE queue;
    ULONG msg_size;
    ULONG capacity;
    UCHAR *storage;
} rtos_queue_t;

static TX_BYTE_POOL g_rtos_byte_pool;
static UCHAR g_rtos_byte_pool_mem[32 * 1024];

static void rtos_byte_pool_init(void)
{
    static UCHAR ready;
    if (!ready) {
        tx_byte_pool_create(&g_rtos_byte_pool, "rtos_pool", g_rtos_byte_pool_mem, sizeof(g_rtos_byte_pool_mem));
        ready = 1;
    }
}

UINT fr_to_tx_priority(UBaseType_t priority)
{
    if (priority >= (UBaseType_t)configMAX_PRIORITIES)
        priority = (UBaseType_t)configMAX_PRIORITIES - 1U;
    return (UINT)(TX_MAX_PRIORITIES - 1U - priority);
}

BaseType_t xTaskCreate(void (*task)(void *), const char *name,
                       uint16_t stack_depth, void *param,
                       UBaseType_t priority, TaskHandle_t *handle)
{
    TX_THREAD *thread;
    UCHAR *stack;
    ULONG stack_bytes;
    UINT tx_prio = fr_to_tx_priority(priority);

    rtos_byte_pool_init();
    stack_bytes = (ULONG)stack_depth * sizeof(ULONG);
    if (stack_bytes < TX_MINIMUM_STACK)
        stack_bytes = TX_MINIMUM_STACK;

    if (tx_byte_allocate(&g_rtos_byte_pool, (VOID **)&thread, sizeof(TX_THREAD), TX_NO_WAIT) != TX_SUCCESS)
        return pdFAIL;
    if (tx_byte_allocate(&g_rtos_byte_pool, (VOID **)&stack, stack_bytes, TX_NO_WAIT) != TX_SUCCESS) {
        tx_byte_release(thread);
        return pdFAIL;
    }

    if (tx_thread_create(thread, (CHAR *)name, (VOID (*)(ULONG))task, (ULONG)param,
                         stack, stack_bytes, tx_prio, tx_prio, RTOS_TIME_SLICE_TICKS,
                         TX_AUTO_START) != TX_SUCCESS) {
        tx_byte_release(stack);
        tx_byte_release(thread);
        return pdFAIL;
    }

    if (handle)
        *handle = thread;
    return pdPASS;
}

void vTaskStartScheduler(void)
{
    tx_kernel_enter();
}

void vTaskSuspend(TaskHandle_t handle)
{
    if (handle)
        tx_thread_suspend(handle);
}

void vTaskResume(TaskHandle_t handle)
{
    if (handle)
        tx_thread_resume(handle);
}

xQueueHandle xQueueCreate(UBaseType_t length, UBaseType_t item_size)
{
    rtos_queue_t *rq;
    ULONG storage_bytes;
    ULONG ux_msg_size;

    rtos_byte_pool_init();
    if (tx_byte_allocate(&g_rtos_byte_pool, (VOID **)&rq, sizeof(rtos_queue_t), TX_NO_WAIT) != TX_SUCCESS)
        return 0;

    storage_bytes = length * item_size;
    if (tx_byte_allocate(&g_rtos_byte_pool, (VOID **)&rq->storage, storage_bytes, TX_NO_WAIT) != TX_SUCCESS)
        return 0;

    rq->msg_size = item_size;
    rq->capacity = length;
    ux_msg_size = (item_size + sizeof(ULONG) - 1) / sizeof(ULONG);
    if (ux_msg_size == 0)
        ux_msg_size = 1;
    if (tx_queue_create(&rq->queue, "rtos_q", ux_msg_size, rq->storage, storage_bytes) != TX_SUCCESS)
        return 0;

    return (xQueueHandle)rq;
}

static rtos_queue_t *rtos_queue(xQueueHandle queue)
{
    return (rtos_queue_t *)queue;
}

BaseType_t xQueueSend(xQueueHandle queue, const void *item, TickType_t timeout)
{
    rtos_queue_t *rq = rtos_queue(queue);
    UINT wait = (timeout == portMAX_DELAY) ? TX_WAIT_FOREVER : (UINT)timeout;
    return (tx_queue_send(&rq->queue, (VOID *)item, wait) == TX_SUCCESS) ? pdPASS : pdFAIL;
}

BaseType_t xQueueReceive(xQueueHandle queue, void *item, TickType_t timeout)
{
    rtos_queue_t *rq = rtos_queue(queue);
    UINT wait = (timeout == portMAX_DELAY) ? TX_WAIT_FOREVER : (UINT)timeout;
    return (tx_queue_receive(&rq->queue, item, wait) == TX_SUCCESS) ? pdPASS : pdFAIL;
}

BaseType_t xQueueSendFromISR(xQueueHandle queue, const void *item, BaseType_t *woken)
{
    (void)woken;
    return xQueueSend(queue, item, 0);
}

BaseType_t xQueueReceiveFromISR(xQueueHandle queue, void *item, BaseType_t *woken)
{
    (void)woken;
    return xQueueReceive(queue, item, 0);
}

BaseType_t xQueueIsQueueEmptyFromISR(xQueueHandle queue)
{
    rtos_queue_t *rq = rtos_queue(queue);
    ULONG enqueued;
    tx_queue_info_get(&rq->queue, TX_NULL, &enqueued, TX_NULL, TX_NULL, TX_NULL, TX_NULL);
    return (enqueued == 0) ? pdTRUE : pdFALSE;
}
