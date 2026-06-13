#ifndef THREADX_APP_H
#define THREADX_APP_H

#include "tx_api.h"

#ifndef TX_APP_FR_MAX
#define TX_APP_FR_MAX  8U
#endif

#ifndef TX_APP_TIME_SLICE
#define TX_APP_TIME_SLICE  10U
#endif

#define TX_APP_NO_WAIT       ((ULONG)0U)
#define TX_APP_WAIT_FOREVER  TX_WAIT_FOREVER

typedef struct tx_app_queue tx_app_queue_t;

void tx_app_byte_pool_init(void);
UINT tx_app_priority_from_fr(UINT fr_priority);

UINT tx_app_thread_create(TX_THREAD *thread, const char *name,
                          VOID (*entry)(ULONG), ULONG entry_input,
                          VOID *stack, ULONG stack_size_bytes,
                          UINT fr_priority);

UINT tx_app_queue_create(tx_app_queue_t **out_queue, ULONG item_size, ULONG capacity);
void tx_app_queue_delete(tx_app_queue_t *queue);
UINT tx_app_queue_send(tx_app_queue_t *queue, const void *item, ULONG wait_ticks);
UINT tx_app_queue_receive(tx_app_queue_t *queue, void *item, ULONG wait_ticks);

#define tx_app_yield()              tx_thread_relinquish()
#define tx_app_critical_enter()     (void)tx_interrupt_control(TX_INT_DISABLE)
#define tx_app_critical_exit()      (void)tx_interrupt_control(TX_INT_ENABLE)

#endif /* THREADX_APP_H */
