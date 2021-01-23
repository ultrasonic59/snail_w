/**
  ******************************************************************************
  * @file    usbd_cdc_vcp.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    09-November-2015
  * @brief   Generic media access Layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 
#include <stdlib.h>
#include <string.h>
#include "usbd_conf.h"
#include "usbd_desc.h"
#if VERS_PL==5
#include "rook_v5a.h"
#else
#include "rook_v4e.h"
#endif

////#include "rook_v5a.h"
#include "rook_rtos.h"
#include "my_misc.h"
#include "_hdlc.h"
#include "printk.h"

#if (USB_CLASS == CDC_VCP)|| (USB_CLASS == MSC_CDC)    ///================================

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED 
#pragma     data_alignment = 4 
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

#include "usbd_cdc_vcp.h"
hdlc_stat_t g_hdlc_vcp;
#if 0
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
LINE_CODING linecoding =
  {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* nb. of bits 8*/
  };


USART_InitTypeDef USART_InitStructure;
#endif

/* These are external variables imported from CDC core to be used for IN 
   transfer management. */
extern uint8_t  APP_Rx_Buffer []; /* Write CDC received data in this buffer.
                                     These data will be sent over USB IN endpoint
                                     in the CDC core functions. */
extern uint32_t APP_Rx_ptr_in;    /* Increment this pointer or roll it back to
                                     start address when writing received data
                                     in the buffer APP_Rx_Buffer. */

/* Private function prototypes -----------------------------------------------*/
static uint16_t VCP_Init     (void);
static uint16_t VCP_DeInit   (void);
static uint16_t VCP_Ctrl     (uint32_t Cmd, uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataTx   (uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataRx   (uint8_t* Buf, uint32_t Len);

///static uint16_t VCP_COMConfig(uint8_t Conf);

CDC_IF_Prop_TypeDef VCP_fops = 
{
  VCP_Init,
  VCP_DeInit,
  VCP_Ctrl,
  VCP_DataTx,
  VCP_DataRx
};

static uint16_t VCP_Init(void)
{
  return USBD_OK;
}
static uint16_t VCP_DeInit(void)
{
  return USBD_OK;
}

static uint16_t VCP_Ctrl (uint32_t Cmd, uint8_t* Buf, uint32_t Len)
{ 
  return USBD_OK;
}

/**
  * @brief  VCP_DataTx
  *         CDC received data to be send over USB IN endpoint are managed in 
  *         this function.
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else VCP_FAIL
  */
static uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len)
{
  return USBD_OK;
}
///=========================================
#if 1
void hdlc_vcp_send_byte(u8 val)
{
///u8 btmp = val;
APP_Rx_Buffer[APP_Rx_ptr_in]=val;
APP_Rx_ptr_in++;
if(APP_Rx_ptr_in == APP_RX_DATA_SIZE)
  {
  APP_Rx_ptr_in = 0;
  }  
////xQueueSend(g_hdlc_bt.ua_snd_dat, &btmp, portMAX_DELAY);
/////on_int_tx_uart_bt();
///_printk("[%x]",APP_Rx_ptr_in);

}
#endif

#if 0
uint8_t hdlc_vcp_send_frame(uint8_t *buff,uint16_t len)
{
#if 1
uint16_t ii;

for(ii=0;ii<len;ii++)
{
APP_Rx_Buffer[APP_Rx_ptr_in]=buff[ii]; 
if(APP_Rx_ptr_in == APP_RX_DATA_SIZE)
  {
  APP_Rx_ptr_in = 0;
  }  

}
///memcpy(APP_Rx_Buffer,buff,len);  
#endif
return 0;
}
#endif
///==========================================
////extern u16     hdlc_bt_get_req_dat(u8 num_req,u8 *buf);
////extern int hdlc_bt_set_rec_dat(u8 cmd, void *in_buf);
////extern int hdlc_bt_get_rez(u8 type_rez,void *obuf);
////extern TaskHandle_t  my_system_monitor_thread_handle;

TaskHandle_t  vcp_rx_thread_handle;
TaskHandle_t  vcp_tx_thread_handle;

static uint16_t VCP_DataRx (uint8_t* Buf, uint32_t Len)
{
///signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
uint8_t ch;
int ii;
for(ii=0;ii<Len;ii++)
  {
  ch = Buf[ii];
  if (hdlc1_on_bytein(&g_hdlc_vcp, ch) > 0)
    {
    xQueueSend(g_hdlc_vcp.ev_rsv_frame, &ch,TIMEOUT_SEND);
///    xQueueSendFromISR(g_hdlc_vcp.ev_rsv_frame, &ch, &xHigherPriorityTaskWoken);
    }
  }
return USBD_OK;
}
extern u16	pc_get_req_dat(u8 num_req,u16 offs,u8 *buf);
extern int      pc_set_rec_dat(u8 cmd,void *in_buf);

///=======================
void init_hdlc_vcp(void)
{
g_hdlc_vcp.fn_send_byte=hdlc_vcp_send_byte;
////g_hdlc_vcp.fn_send_frame=hdlc_vcp_send_frame;
g_hdlc_vcp.fn_set_rec_dat=pc_set_rec_dat;////hdlc_bt_set_rec_dat;
g_hdlc_vcp.fn_get_req_dat=pc_get_req_dat;////hdlc_bt_get_req_dat;
g_hdlc_vcp.ua_snd_dat=xQueueCreate(512,sizeof(unsigned char));		//8192
g_hdlc_vcp.ev_rsv_ack=xQueueCreate(1,1);
g_hdlc_vcp.ev_rsv_dat=xQueueCreate(1,1);
g_hdlc_vcp.ev_rsv_frame=xQueueCreate(1,1);
g_hdlc_vcp.ev_snd_frame=xQueueCreate(16, sizeof(uint32_t));
hdlc1_init(&g_hdlc_vcp);

xTaskCreate(hdlc1_obr_frame, (const char*)"HDLC_vcp_rx",VCP_RX_STACK_SIZE, (void*)&g_hdlc_vcp, APP_PRIORITY, &vcp_rx_thread_handle);
xTaskCreate(hdlc1_snd_task, (const char*)"HDLC_vcp_tx", VCP_TX_STACK_SIZE, (void*)&g_hdlc_vcp, APP_PRIORITY, &vcp_tx_thread_handle);
vTaskSuspend(vcp_rx_thread_handle);
vTaskSuspend(vcp_tx_thread_handle);
///put_tst1(0);
}

///======================================  
static uint8_t flg_usb_on=0;
///======================================  
void on_off_usb_thr(uint8_t on_off)
{
///BaseType_t xYieldRequired;  
if(on_off&0x1)
  {
  if(flg_usb_on)
    return;
  flg_usb_on=1;
////  put_tst1(1);
 vTaskResume(vcp_rx_thread_handle);
 vTaskResume(vcp_tx_thread_handle);
#if 0  
 xYieldRequired=xTaskResumeFromISR(&vcp_rx_thread_handle);
 if( xYieldRequired == pdTRUE )
    {
    portYIELD_FROM_ISR(1); 
    }
#endif
/// xTaskResumeFromISR(&vcp_tx_thread_handle);

  }
else
  {
  if(!flg_usb_on)
    return;
  flg_usb_on=0;
  vTaskSuspend(vcp_rx_thread_handle);
  vTaskSuspend(vcp_tx_thread_handle);
///  put_tst1(0);
  }
}
///======================================  
#endif ///(USB_CLASS == CDC_VCP)
///======================================  
