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
#include "config.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "my_types.h"
///#include "_hdlc.h"
#include "printk.h"
#include "min_max.h"
#include "ring_buff.h"
#include "can.h"
extern int send_char_dbg(int ch); 

extern uint8_t serial_rx_buffer[];
extern uint8_t serial_rx_buffer_head ;

#if (USB_CLASS == CDC_VCP)|| (USB_CLASS == MSC_CDC)    ///================================

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED 
#pragma     data_alignment = 4 
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

#include "usbd_cdc_vcp.h"
///hdlc_stat_t g_hdlc_vcp;
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
////static uint16_t VCP_DataTx   (uint8_t* Buf, uint32_t Len);
////static 
////uint16_t VCP_DataRx   (uint8_t* Buf, uint32_t Len);

///static uint16_t VCP_COMConfig(uint8_t Conf);

CDC_IF_Prop_TypeDef VCP_fops = 
{
  VCP_Init,
  VCP_DeInit,
  VCP_Ctrl,
  0,
  0
///  VCP_DataTx,
///  VCP_DataRx
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
#if 0
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
#endif
///=========================================
/*
 * VCP data Rx/Tx API
 */

void VCP_MarkRead(unsigned sz)
{
	atomic_t a = atomic_begin();
	USB_Rx_buff_tail = ring_wrap(USB_Rx_buff_size, USB_Rx_buff_tail + sz);
	atomic_end(a);
}

void VCP_MarkWritten(unsigned sz)
{
	atomic_t a = atomic_begin();
	USB_Tx_buff_head = ring_wrap(USB_TX_BUFF_SIZE, USB_Tx_buff_head + sz);
	atomic_end(a);
}

unsigned VCP_DataAvail(void)
{
	atomic_t a = atomic_begin();
	unsigned sz = ring_data_avail(USB_Rx_buff_size, USB_Rx_buff_head, USB_Rx_buff_tail);
	atomic_end(a);
	return sz;
}

unsigned VCP_SpaceAvail(void)
{
	atomic_t a = atomic_begin();
	unsigned sz = ring_space_avail(USB_TX_BUFF_SIZE, USB_Tx_buff_head, USB_Tx_buff_tail);
	atomic_end(a);
	return sz;
}

unsigned VCP_DataAvailContig(void)
{
	atomic_t a = atomic_begin();
	unsigned sz = ring_data_contig(USB_Rx_buff_size, USB_Rx_buff_head, USB_Rx_buff_tail);
	atomic_end(a);
	return sz;
}

unsigned VCP_SpaceAvailContig(void)
{
	atomic_t a = atomic_begin();
	unsigned sz = ring_space_contig(USB_TX_BUFF_SIZE, USB_Tx_buff_head, USB_Tx_buff_tail);
	atomic_end(a);
	return sz;
}

unsigned VCP_GetContig(void* buff, unsigned max_len)
{
	unsigned avail = VCP_DataAvailContig();
	unsigned sz = MIN_(avail, max_len);
	if (sz) {
		memcpy(buff, VCP_DataPtr(), sz);
		VCP_MarkRead(sz);
	}
	return sz;
}

unsigned VCP_PutContig(void const* buff, unsigned len)
{
unsigned avail = VCP_SpaceAvailContig();
unsigned sz = MIN_(avail, len);
if (sz) 
  {
  memcpy(VCP_SpacePtr(), buff, sz);
  VCP_MarkWritten(sz);
  }
return sz;
}

void CDC_send_str(char *str_report, uint32_t len){
  VCP_PutContig(str_report,len);
}

///==========================================

#if 0
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
#else
void hdlc_vcp_send_byte(u8 val)
{
int num;  
u8 btmp=val;
for(;;)
{
 num= VCP_PutContig(&btmp,1);
 if(num)
   break;
 msleep(1);
}
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

////TaskHandle_t  vcp_rx_thread_handle;
///TaskHandle_t  vcp_tx_thread_handle;
TaskHandle_t  vcp_thread_handle;
#if 0
////static 
uint16_t _VCP_DataRx (uint8_t* Buf, uint32_t Len)
{
///signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
uint8_t ch;
int ii;
///VCP_MarkRead(Len);
for(ii=0;ii<Len;ii++)
  {
  ch = Buf[ii];
  if (hdlc1_on_bytein(&g_hdlc_vcp, ch) > 0)
    {
    xQueueSend(g_hdlc_vcp.ev_rsv_frame, &ch,TIMEOUT_SEND);
///    xQueueSendFromISR(g_hdlc_vcp.ev_rsv_frame, &ch, &xHigherPriorityTaskWoken);
    }
  }
////VCP_MarkRead(Len);
return USBD_OK;
}
#endif

///extern int serial_read_tx(void);
extern uint8_t serial_get_tx_buffer_count(void);


void   OnUsbDataRx(uint8_t *rd_dat,uint32_t sz){
///  printk("\n\r OnUsbDataRx [%x:%x]\n\r",rd_dat[0],sz); 
volatile uint8_t data; 
volatile uint8_t *ptdata;
ptdata=rd_dat;
data = *ptdata;
volatile uint8_t RxBufferCount;
RxBufferCount = sz;

/// CDC_led_rx_on(1);
  // Pick off realtime command characters directly from the serial stream. These characters are
  // not passed into the main buffer, but these set system state flag bits for realtime execution.
  switch (data) {
      case CMD_RESET:	
        mc_reset();
      	 //report_init_message();
      	 break; // Call motion control reset routine.
      case CMD_STATUS_REPORT: 
        system_set_exec_state_flag(EXEC_STATUS_REPORT); 
        break; // Set as true
      case CMD_CYCLE_START:   
        system_set_exec_state_flag(EXEC_CYCLE_START); 
        break; // Set as true
      case CMD_FEED_HOLD:     
        system_set_exec_state_flag(EXEC_FEED_HOLD); 
        break; // Set as true
      default :
        if (data > 0x7F) { // Real-time control characters are extended ACSII only.
          switch(data) {
            case CMD_SAFETY_DOOR:   
              system_set_exec_state_flag(EXEC_SAFETY_DOOR); 
              break; // Set as true
            case CMD_JOG_CANCEL:
              if (sys.state & STATE_JOG) { // Block all other states from invoking motion cancel.
                system_set_exec_state_flag(EXEC_MOTION_CANCEL);
              }
              break;
            #ifdef DEBUG
              case CMD_DEBUG_REPORT: {
                uint8_t sreg = SREG; 
                cli(); 
                bit_true(sys_rt_exec_debug,EXEC_DEBUG_REPORT); 
                SREG = sreg;
              } break;
            #endif
            case CMD_FEED_OVR_RESET           : 
              system_set_exec_motion_override_flag(EXEC_FEED_OVR_RESET); 
              break;
            case CMD_FEED_OVR_COARSE_PLUS     : 
              system_set_exec_motion_override_flag(EXEC_FEED_OVR_COARSE_PLUS); 
              break;
            case CMD_FEED_OVR_COARSE_MINUS    : 
              system_set_exec_motion_override_flag(EXEC_FEED_OVR_COARSE_MINUS); 
              break;
            case CMD_FEED_OVR_FINE_PLUS       : 
              system_set_exec_motion_override_flag(EXEC_FEED_OVR_FINE_PLUS); 
              break;
            case CMD_FEED_OVR_FINE_MINUS      : 
              system_set_exec_motion_override_flag(EXEC_FEED_OVR_FINE_MINUS); 
              break;
            case CMD_RAPID_OVR_RESET          : 
              system_set_exec_motion_override_flag(EXEC_RAPID_OVR_RESET); 
              break;
            case CMD_RAPID_OVR_MEDIUM         : 
              system_set_exec_motion_override_flag(EXEC_RAPID_OVR_MEDIUM); 
              break;
            case CMD_RAPID_OVR_LOW            : 
              system_set_exec_motion_override_flag(EXEC_RAPID_OVR_LOW); 
              break;
            case CMD_SPINDLE_OVR_RESET        : 
              system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_RESET); 
              break;
            case CMD_SPINDLE_OVR_COARSE_PLUS  : 
              system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_COARSE_PLUS); 
              break;
            case CMD_SPINDLE_OVR_COARSE_MINUS : 
              system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_COARSE_MINUS); 
              break;
            case CMD_SPINDLE_OVR_FINE_PLUS    : 
              system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_FINE_PLUS); 
              break;
            case CMD_SPINDLE_OVR_FINE_MINUS   : 
              system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_FINE_MINUS); 
              break;
            case CMD_SPINDLE_OVR_STOP         : 
              system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_STOP); 
              break;
            case CMD_COOLANT_FLOOD_OVR_TOGGLE : 
              system_set_exec_accessory_override_flag(EXEC_COOLANT_FLOOD_OVR_TOGGLE); 
              break;

            #ifdef ENABLE_M7
              case CMD_COOLANT_MIST_OVR_TOGGLE: 
                system_set_exec_accessory_override_flag(EXEC_COOLANT_MIST_OVR_TOGGLE); 
                break;
            #endif

          }
          // Throw away any unfound extended-ASCII character by not passing it to the serial buffer.
        } else { // Write character to buffer
          // Write data to buffer unless it is full.
        	do {
        		serial_rx_buffer[serial_rx_buffer_head++] = *ptdata++;
        	}
        	while(--RxBufferCount);
        }
  }
 }





#define MAX_LEN_RD_DAT 256
////===================================
void vcp_thread(void *pdata)
{
///uint8_t on_sleep=0;
uint8_t rd_dat[MAX_LEN_RD_DAT];  
//uint32_t ii; 
uint32_t sz; 
//int t_dat;
//uint8_t rd_tdat;
printk("\n\r vcp_Thread\n\r"); 

#if 1  
for (;;) 
{
sz  = VCP_DataAvailContig();
while (sz)
  {
  if (sz > MAX_LEN_RD_DAT)
    {
    VCP_GetContig(rd_dat,MAX_LEN_RD_DAT);
    OnUsbDataRx(rd_dat,MAX_LEN_RD_DAT); 
    sz-=MAX_LEN_RD_DAT;
    }
  else
    {
    VCP_GetContig(rd_dat,sz);
    OnUsbDataRx(rd_dat,sz); 
    sz=0;
    }
#if 0  
  for(ii=0;ii<sz;ii++)
    {
    VCP_GetContig(&rd_dat,1);
 ////   rd_dat++;
    ////=====================================
    send_char_dbg(rd_dat);
    ////==========================================
   VCP_PutContig(&rd_dat,1);
    }
#endif  
//// on_sleep=0;
  }
  msleep(20);

/*
sz  =  serial_get_tx_buffer_count();
if(sz)
{
for(ii=0;ii<sz;ii++)
  {
  t_dat=serial_read_tx();  
  if(t_dat>0)
    {
    rd_tdat=t_dat;
    VCP_PutContig(&rd_tdat,1);
    }
    
  }
}
*/
#if 0
if(CAN_RxRdy)
  {
    
  on_sleep=0;  
  }
if(on_sleep)
  {
  msleep(1);
  }
#endif
}
#endif
}

////===================================

extern u16	pc_get_req_dat(u8 num_req,u16 offs,u8 *buf);
extern int      pc_set_rec_dat(u8 cmd,void *in_buf);
///u8 addr= *((u8*)pdata);
volatile int vtmp;
///=======================
#if 0
void init_hdlc_vcp(void)
{
BaseType_t rez;  
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

rez=xTaskCreate(vcp_thread, (const char*)"vcp_thread",VCP_TX_STACK_SIZE/2, 0, APP_PRIORITY, &vcp_thread_handle);

rez=xTaskCreate(hdlc1_obr_frame, (const char*)"HDLC_vcp_rx",VCP_RX_STACK_SIZE, (void*)&g_hdlc_vcp, APP_PRIORITY, &vcp_rx_thread_handle);
rez=xTaskCreate(hdlc1_snd_task, (const char*)"HDLC_vcp_tx", VCP_TX_STACK_SIZE, (void*)&g_hdlc_vcp, APP_PRIORITY, &vcp_tx_thread_handle);
vtmp=rez;
///put_tst1(0);
}
#endif
///======================================  
////static uint8_t flg_usb_on=0;
///======================================  
void on_off_usb_thr(uint8_t on_off)
{

#if 0  
if(on_off&0x1)
  {
  if(flg_usb_on)
    return;
  flg_usb_on=1;
////  put_tst1(1);
 vTaskResume(vcp_rx_thread_handle);
 vTaskResume(vcp_tx_thread_handle);
 vTaskResume(vcp_thread_handle);

  }
else
  {
  if(!flg_usb_on)
    return;
  flg_usb_on=0;
  vTaskSuspend(vcp_rx_thread_handle);
  vTaskSuspend(vcp_tx_thread_handle);
  vTaskSuspend(vcp_thread_handle);
///  put_tst1(0);
  }
#endif
}
///======================================  
#endif ///(USB_CLASS == CDC_VCP)
///======================================  
