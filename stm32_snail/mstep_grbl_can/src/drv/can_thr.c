#include <string.h>
#include "tx_api.h"
#include "threadx_app.h"
#include "board.h"
#include "can.h"
#include "can_master.h"
#include "printk.h"
#include "can_stepper.h"
#include "config.h"

static tx_app_queue_t *queu_to_send;
static TX_SEMAPHORE can_rx_sem;
static UCHAR can_rx_sem_ready = 0U;

#define CAN_PUT_STAT_CMD   0x3U
#define CAN_PUT_ACK        0x4U
#define CAN_GET_STAT_CMD   0x2U

#ifndef CAN_START_TX_THREAD
#define CAN_START_TX_THREAD  1
#endif
#ifndef CAN_START_RX_THREAD
#define CAN_START_RX_THREAD  1
#endif

static int can_master_rx_should_print(const can_msg_t *msg)
{
  if (msg->data[0] == CAN_PUT_STAT_CMD || msg->data[0] == CAN_PUT_ACK) {
    return 0;
  }
  return 1;
}

static void can_master_rx_print(const can_msg_t *msg)
{
  uint8_t ii;

  if (!can_master_rx_should_print(msg)) {
    return;
  }

  printk("\r\nCAN rx id=0x%X fmt=%u len=%u data:",
         (unsigned)msg->id, (unsigned)msg->format, (unsigned)msg->len);
  for (ii = 0; ii < msg->len; ii++) {
    printk(" %02X", msg->data[ii]);
  }
  printk("\r\n");
}

void st_can_master_service_rx(void)
{
  can_msg_t rx;

  tx_app_critical_enter();
  if (!CAN_RxRdy) {
    tx_app_critical_exit();
    return;
  }
  CAN_RxRdy = 0;
  memcpy(&rx, &CAN_RxMsg, sizeof(rx));
  tx_app_critical_exit();

  can_master_rx_print(&rx);
  st_can_on_master_rx(&rx);
}

void can_master_rx_signal_from_isr(void)
{
  if (can_rx_sem_ready) {
    tx_semaphore_put(&can_rx_sem);
  }
}

static VOID can_send_thread_entry(ULONG param)
{
  can_msg_t snd_msg;

  (void)param;
  printk("\r\n can_send_thread");

  for (;;) {
    if (tx_app_queue_receive(queu_to_send, &snd_msg, TX_APP_WAIT_FOREVER) == TX_SUCCESS) {
      CAN_wrMsg(&snd_msg);
    }
  }
}

static VOID can_rsv_thread_entry(ULONG param)
{
  (void)param;
  printk("\r\ncan_rsv_task rx_log=no_STAT,no_ACK %s %s", __DATE__, __TIME__);

  for (;;) {
    tx_semaphore_get(&can_rx_sem, TX_WAIT_FOREVER);
    st_can_master_service_rx();
  }
}

int can_master_tx(uint32_t id, const uint8_t *data, uint8_t len)
{
  can_msg_t msg;

  if (queu_to_send == NULL || data == NULL || len == 0) {
    return -1;
  }
  if (len > CAN_MAX_NUM_BYTES) {
    len = CAN_MAX_NUM_BYTES;
  }

  msg.id = id;
  msg.len = len;
  msg.format = STANDARD_FORMAT;
  msg.type = DATA_FRAME;
  memcpy(msg.data, data, len);

  if (data[0] == CAN_GET_STAT_CMD) {
    CAN_wrMsg(&msg);
    return 0;
  }

  if (tx_app_queue_send(queu_to_send, &msg, (ULONG)CAN_TIMEOUT_SEND) != TX_SUCCESS) {
    return -1;
  }
  return 0;
}

#if CAN_BACKGROUND_STAT_POLL
static VOID can_poll_thread_entry(ULONG param)
{
  (void)param;
  printk("\r\n can_poll_task");

  for (;;) {
    st_can_master_poll_stat();
    msleep(CAN_STAT_POLL_PERIOD_MS);
  }
}
#endif

static TX_THREAD can_send_tx_thread;
static TX_THREAD can_rsv_tx_thread;
#if CAN_BACKGROUND_STAT_POLL
static TX_THREAD can_poll_tx_thread;
#endif
static ULONG can_send_stack[CAN_SEND_STACK_SIZE];
static ULONG can_rsv_stack[CAN_TASK_STACK_SIZE];
#if CAN_BACKGROUND_STAT_POLL
static ULONG can_poll_stack[CAN_POLL_STACK_SIZE];
#endif

void can_threads_start(void)
{
  UINT status;

  if (tx_app_queue_create(&queu_to_send, sizeof(can_msg_t), CAN_MAX_LEN_QUEU) != TX_SUCCESS) {
    printk("\r\n can_threads_start: queue create failed");
    return;
  }
  if (tx_semaphore_create(&can_rx_sem, "can_rx_sem", 0U) != TX_SUCCESS) {
    printk("\r\n can_threads_start: rx semaphore failed");
    return;
  }
  can_rx_sem_ready = 1U;

#if CAN_START_TX_THREAD
  status = tx_app_thread_create(&can_send_tx_thread, "can_send_thread", can_send_thread_entry, 0U,
                                can_send_stack, sizeof(can_send_stack), CAN_SEND_TASK_PRIORITY);
  printk("\r\n can_send_thread[%u]", (unsigned)status);
#endif

#if CAN_START_RX_THREAD
  status = tx_app_thread_create(&can_rsv_tx_thread, "can_rsv_task", can_rsv_thread_entry, 0U,
                                can_rsv_stack, sizeof(can_rsv_stack), CAN_TASK_PRIORITY);
  printk("\r\n can_rsv_task[%u]", (unsigned)status);
#endif

#if CAN_BACKGROUND_STAT_POLL
  status = tx_app_thread_create(&can_poll_tx_thread, "can_poll_task", can_poll_thread_entry, 0U,
                                  can_poll_stack, sizeof(can_poll_stack), CAN_POLL_TASK_PRIORITY);
  printk("\r\n can_poll_task[%u]", (unsigned)status);
#endif
}

tx_app_queue_t *can_tx_queue(void)
{
  return queu_to_send;
}
