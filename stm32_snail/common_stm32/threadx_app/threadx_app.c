#include <string.h>
#include "threadx_app.h"

struct tx_app_queue {
  TX_QUEUE queue;
  ULONG item_size;
  ULONG capacity;
  UCHAR *storage;
};

static TX_BYTE_POOL g_tx_app_byte_pool;
static UCHAR g_tx_app_byte_pool_mem[32U * 1024U];
static UCHAR g_tx_app_byte_pool_ready;

void tx_app_byte_pool_init(void)
{
  if (!g_tx_app_byte_pool_ready) {
    tx_byte_pool_create(&g_tx_app_byte_pool, "tx_app_pool",
                        g_tx_app_byte_pool_mem, sizeof(g_tx_app_byte_pool_mem));
    g_tx_app_byte_pool_ready = 1U;
  }
}

UINT tx_app_priority_from_fr(UINT fr_priority)
{
  if (fr_priority >= (UINT)TX_APP_FR_MAX) {
    fr_priority = (UINT)TX_APP_FR_MAX - 1U;
  }
  return (UINT)(TX_MAX_PRIORITIES - 1U - fr_priority);
}

UINT tx_app_thread_create(TX_THREAD *thread, const char *name,
                          VOID (*entry)(ULONG), ULONG entry_input,
                          VOID *stack, ULONG stack_size_bytes,
                          UINT fr_priority)
{
  UINT tx_priority;

  if (thread == NULL || entry == NULL || stack == NULL) {
    return TX_PTR_ERROR;
  }
  if (stack_size_bytes < (ULONG)TX_MINIMUM_STACK) {
    stack_size_bytes = (ULONG)TX_MINIMUM_STACK;
  }

  tx_priority = tx_app_priority_from_fr(fr_priority);
  return tx_thread_create(thread, (CHAR *)name, entry, entry_input,
                          stack, stack_size_bytes, tx_priority, tx_priority,
                          TX_APP_TIME_SLICE, TX_AUTO_START);
}

UINT tx_app_queue_create(tx_app_queue_t **out_queue, ULONG item_size, ULONG capacity)
{
  tx_app_queue_t *queue;
  ULONG storage_bytes;
  ULONG msg_words;
  UINT status;

  if (out_queue == NULL || item_size == 0U || capacity == 0U) {
    return TX_PTR_ERROR;
  }

  tx_app_byte_pool_init();
  if (tx_byte_allocate(&g_tx_app_byte_pool, (VOID **)&queue, sizeof(tx_app_queue_t),
                       TX_NO_WAIT) != TX_SUCCESS) {
    return TX_NO_MEMORY;
  }

  storage_bytes = capacity * item_size;
  if (tx_byte_allocate(&g_tx_app_byte_pool, (VOID **)&queue->storage, storage_bytes,
                       TX_NO_WAIT) != TX_SUCCESS) {
    tx_byte_release(queue);
    return TX_NO_MEMORY;
  }

  queue->item_size = item_size;
  queue->capacity = capacity;
  msg_words = (item_size + sizeof(ULONG) - 1U) / sizeof(ULONG);
  if (msg_words == 0U) {
    msg_words = 1U;
  }

  status = tx_queue_create(&queue->queue, "tx_app_q", msg_words,
                           queue->storage, storage_bytes);
  if (status != TX_SUCCESS) {
    tx_byte_release(queue->storage);
    tx_byte_release(queue);
    return status;
  }

  *out_queue = queue;
  return TX_SUCCESS;
}

void tx_app_queue_delete(tx_app_queue_t *queue)
{
  if (queue == NULL) {
    return;
  }
  tx_queue_delete(&queue->queue);
  if (queue->storage != NULL) {
    tx_byte_release(queue->storage);
  }
  tx_byte_release(queue);
}

UINT tx_app_queue_send(tx_app_queue_t *queue, const void *item, ULONG wait_ticks)
{
  if (queue == NULL || item == NULL) {
    return TX_PTR_ERROR;
  }
  return tx_queue_send(&queue->queue, (VOID *)item, wait_ticks);
}

UINT tx_app_queue_receive(tx_app_queue_t *queue, void *item, ULONG wait_ticks)
{
  if (queue == NULL || item == NULL) {
    return TX_PTR_ERROR;
  }
  return tx_queue_receive(&queue->queue, item, wait_ticks);
}
