#include <string.h>
#include "rtos_compat.h"
#include "board.h"
#include "can.h"
#include "can_master.h"
#include "printk.h"
#include "can_stepper.h"
#include "config.h"

xQueueHandle queu_to_send;

#define CAN_PUT_STAT_CMD   0x3U
#define CAN_PUT_ACK        0x4U

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

  taskENTER_CRITICAL();
  if (!CAN_RxRdy) {
    taskEXIT_CRITICAL();
    return;
  }
  CAN_RxRdy = 0;
  memcpy(&rx, &CAN_RxMsg, sizeof(rx));
  taskEXIT_CRITICAL();

  can_master_rx_print(&rx);
  st_can_on_master_rx(&rx);
}

static void can_send_thread(void *pp)
{
  can_msg_t snd_msg;

  (void)pp;
  printk("\r\n can_send_thread");

  for (;;) {
    if (xQueueReceive(queu_to_send, &snd_msg, portMAX_DELAY) == pdPASS) {
      CAN_wrMsg(&snd_msg);
    }
  }
}

static void can_rsv_task(void *pvParameters)
{
  (void)pvParameters;
  printk("\r\ncan_rsv_task rx_log=no_STAT,no_ACK %s %s", __DATE__, __TIME__);

  for (;;) {
    st_can_master_service_rx();
    msleep(1);
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

  if (xQueueSend(queu_to_send, &msg, CAN_TIMEOUT_SEND) != pdPASS) {
    return -1;
  }
  return 0;
}

#if CAN_BACKGROUND_STAT_POLL
static void can_poll_task(void *pvParameters)
{
  (void)pvParameters;
  printk("\r\n can_poll_task");

  for (;;) {
    st_can_master_poll_stat();
    msleep(CAN_STAT_POLL_PERIOD_MS);
  }
}
#endif

void can_threads_start(void)
{
  BaseType_t rez;

  queu_to_send = xQueueCreate(CAN_MAX_LEN_QUEU, sizeof(can_msg_t));
  if (queu_to_send == NULL) {
    printk("\r\n can_threads_start: queue create failed");
    return;
  }

  rez = xTaskCreate(can_send_thread, "can_send_thread",
                    CAN_SEND_STACK_SIZE, NULL, CAN_SEND_TASK_PRIORITY, NULL);
  printk("\r\n can_send_thread[%u]", (unsigned)rez);

  rez = xTaskCreate(can_rsv_task, "can_rsv_task",
                    CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL);
  printk("\r\n can_rsv_task[%u]", (unsigned)rez);

#if CAN_BACKGROUND_STAT_POLL
  rez = xTaskCreate(can_poll_task, "can_poll_task",
                    CAN_POLL_STACK_SIZE, NULL, CAN_POLL_TASK_PRIORITY, NULL);
  printk("\r\n can_poll_task[%u]", (unsigned)rez);
#endif
}
