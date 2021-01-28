#include "bt_cmd.h"
#include "_hdlc.h"
#include "board.h"
#include "printk.h"

hdlc_stat_t g_hdlc_bt;
void init_hdlc_bt(void);
////=================================================
extern void on_int_tx_uart_bt(void);
volatile int res_send;

void hdlc_bt_send_byte(uint8_t val)
{
uint8_t btmp = val;
#if 0
printk("[%x]",val);
if(val==0x7e)
  printk("\r\n");

if(UART_BT->SR & USART_FLAG_TXE)
  UART_BT->DR=val;
else
  {
  res_send = xQueueSend(g_hdlc_bt.ua_snd_dat, &btmp, portMAX_DELAY);
  on_int_tx_uart_bt();
  }
#endif
  res_send = xQueueSend(g_hdlc_bt.ua_snd_dat, &btmp, portMAX_DELAY);

}

extern uint16_t	pc_get_req_dat(uint8_t num_req,uint16_t offs,uint8_t *buf);
extern int      pc_set_rec_dat(uint8_t cmd,void *in_buf);

TaskHandle_t  bt_thr_rx;
TaskHandle_t  bt_thr_tx;
extern void bt_snd_task(void *pdata);

///=======================
void init_hdlc_bt(void)
{
g_hdlc_bt.fn_send_byte=hdlc_bt_send_byte;
////g_hdlc_bt.fn_send_frame=hdlc_bt_send_frame;
g_hdlc_bt.fn_set_rec_dat=pc_set_rec_dat;////hdlc_bt_set_rec_dat;
//// g_hdlc_bt.fn_get_rez=hdlc_bt_get_rez;
g_hdlc_bt.fn_get_req_dat=pc_get_req_dat;////hdlc_bt_get_req_dat;
///g_hdlc_bt.ua_snd_dat=xQueueCreate(512,sizeof(unsigned char));		//
g_hdlc_bt.ua_snd_dat=xQueueCreate(64,sizeof(unsigned char));		//
g_hdlc_bt.ev_rsv_ack=xQueueCreate(1,1);
g_hdlc_bt.ev_rsv_dat=xQueueCreate(1,1);
g_hdlc_bt.ev_rsv_frame=xQueueCreate(1,1);
g_hdlc_bt.ev_snd_frame=xQueueCreate(16, sizeof(uint32_t));

hdlc1_init(&g_hdlc_bt);

xTaskCreate(hdlc1_obr_frame, (const char*)"HDLC_BT_rx",BT_RX_STACK_SIZE, (void*)&g_hdlc_bt, APP_PRIORITY, &bt_thr_rx);
xTaskCreate(hdlc1_snd_task, (const char*)"HDLC_BT_tx", BT_TX_STACK_SIZE, (void*)&g_hdlc_bt, APP_PRIORITY, &bt_thr_tx);
////xTaskCreate(bt_snd_task, (const char*)"BT_tx", BT_TX_STACK_SIZE, (void*)&g_hdlc_bt, APP_PRIORITY, NULL);
///	task_queue_init();
}


////=================================================