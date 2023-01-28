#include "board.h"
#include <string.h>
#include <stdio.h>
///============================================
xQueueHandle q_can_rd = 0;
uint8_t cur_can_br=DEF_CAN_BR;

can_br_coef_t can_br32[]=
{
  {160,CAN_BS1_15tq,CAN_BS2_5tq},  ////10 kb
  {80,CAN_BS1_15tq,CAN_BS2_5tq},  ////20 kb
  {32,CAN_BS1_15tq,CAN_BS2_5tq},  ////50 kb
  {32,CAN_BS1_8tq,CAN_BS2_2tq},  ////100 kb
  {16,CAN_BS1_14tq,CAN_BS2_2tq},  ////125 kb
  {8,CAN_BS1_14tq,CAN_BS2_2tq},  ////250 kb
  {8,CAN_BS1_6tq,CAN_BS2_1tq},  ////500 kb
  {4,CAN_BS1_8tq,CAN_BS2_2tq},  ////800 kb
  {2,CAN_BS1_12tq,CAN_BS2_3tq}  ////1000 kb
};
can_br_coef_t can_br30[]=
{
  {150,CAN_BS1_15tq,CAN_BS2_5tq},  ////10 kb
  {75,CAN_BS1_15tq,CAN_BS2_5tq},  ////20 kb
  {30,CAN_BS1_15tq,CAN_BS2_5tq},  ////50 kb
  {30,CAN_BS1_8tq,CAN_BS2_2tq},  ////100 kb
  {15,CAN_BS1_14tq,CAN_BS2_2tq},  ////125 kb
  {15,CAN_BS1_7tq,CAN_BS2_1tq},  ////250 kb
  {6,CAN_BS1_8tq,CAN_BS2_2tq},  ////500 kb
  {3,CAN_BS1_11tq,CAN_BS2_2tq},  ////800 kb
  {2,CAN_BS1_13tq,CAN_BS2_2tq}  ////1000 kb
};

///============================================
void	canfilter_init(void);
void nvic_can(void)
{
NVIC_InitTypeDef  NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
NVIC_InitStructure.NVIC_IRQChannel =USB_LP_CAN1_RX0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}
int can_init( FunctionalState ttcm, FunctionalState abom, FunctionalState awum, FunctionalState nart,
	     FunctionalState rflm, FunctionalState txfp, uint32_t sjw, uint32_t ts1, uint32_t ts2,
	     uint32_t brp, uint8_t loopback, uint8_t silent)
{
  uint8_t tmp=0;
CAN_InitTypeDef   CAN_InitStructure;
CAN_DeInit(CAN1);				// CAN register deinit
CAN_StructInit(&CAN_InitStructure);
CAN_InitStructure.CAN_TTCM = ttcm;
CAN_InitStructure.CAN_ABOM = abom;
CAN_InitStructure.CAN_AWUM = awum;
CAN_InitStructure.CAN_NART = nart;
CAN_InitStructure.CAN_RFLM = rflm;
CAN_InitStructure.CAN_TXFP = txfp;
if(loopback)
  tmp|=CAN_Mode_LoopBack;
if(silent)
  tmp|=CAN_Mode_Silent;
CAN_InitStructure.CAN_Mode = tmp;
////CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;

CAN_InitStructure.CAN_SJW = sjw;
CAN_InitStructure.CAN_Prescaler = brp;
CAN_InitStructure.CAN_BS1 = ts1;
CAN_InitStructure.CAN_BS2 = ts2;

if(CAN_Init(CAN1, &CAN_InitStructure) == CAN_InitStatus_Success)
  return 0;
else
  return -1;
}
int _can_init(uint32_t sjw, uint32_t ts1, uint32_t ts2,
	     uint32_t brp)
{
return can_init(DISABLE,DISABLE,DISABLE, ENABLE,
	     DISABLE, DISABLE, sjw, ts1, ts2,
	     brp, _FALSE, _FALSE);
  
}
void init_can(void)
{
RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
#if 1
can_init(DISABLE,DISABLE,DISABLE, ENABLE,
	     DISABLE, DISABLE, CAN_SJW_1tq, CAN_BS1_6tq, CAN_BS2_8tq,
	     4, _FALSE, _FALSE);
#endif
can_speed(cur_can_br);
nvic_can();

CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
CAN_ITConfig(CAN1,CAN_IT_FMP1,ENABLE);
canfilter_init();
}

///int	can1_resive0=0;
////int	can1_resive1=0;
CanRxMsg can_msg_buf1;
CanRxMsg can_msg_buf2;

void USB_LP_CAN1_RX0_IRQHandler(void)
{
uint8_t flg=0;  
signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
if (CAN_GetITStatus(CAN1,CAN_IT_FMP0))
  {
  CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
  CAN_Receive( CAN1,CAN_FIFO0, &can_msg_buf1);
  CAN_FIFORelease(CAN1,CAN_FIFO0);
  flg=1;
  xQueueSendFromISR(q_can_rd, &flg, &xHigherPriorityTaskWoken);
////  can1_resive0=1;
  }
}
void CAN1_RX1_IRQHandler(void)
{
uint8_t flg=0;  
signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
if (CAN_GetITStatus(CAN1,CAN_IT_FMP1))
  {
  CAN_ClearITPendingBit( CAN1,CAN_IT_FMP1);
  CAN_Receive( CAN1,CAN_FIFO1, &can_msg_buf2);
  CAN_FIFORelease(CAN1,CAN_FIFO1);
  flg=2;
  xQueueSendFromISR(q_can_rd, &flg, &xHigherPriorityTaskWoken);
////  can1_resive1=1;
  }
}

//	CAN Master filter init
void	canfilter_init(void)
{
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode 	= CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh 	= 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow 	= 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation 	= ENABLE;		////
	CAN_FilterInit(&CAN_FilterInitStructure);
}
#if 0
void CanWriteData(uint16_t ID,uint8_t *idata,uint8_t len)
{
uint8_t ii;
CanTxMsg TxMessage;
if(len>MAX_CAN_LEN)
  len=MAX_CAN_LEN;
  /* transmit */
  TxMessage.StdId = ID;  
  TxMessage.RTR = CAN_RTR_DATA; 
  TxMessage.IDE = CAN_ID_STD;   
  TxMessage.DLC = len;
 for(ii=0;ii<len;ii++)
  {
  TxMessage.Data[ii]=idata[ii];
  }
CAN_Transmit(CAN1,&TxMessage);  	
}
#endif
////==================================================================
int can_transmit( uint32_t id, uint8_t ext, uint8_t rtr,
		 uint8_t length, uint8_t *data)
{
uint8_t ii;
CanTxMsg TxMessage;
if(length>MAX_CAN_LEN)
  length=MAX_CAN_LEN;
  /* transmit */
if(ext)
  TxMessage.ExtId = id;
else  
  TxMessage.StdId = id; 
  TxMessage.RTR = CAN_RTR_DATA; 
if(ext)
  TxMessage.IDE = CAN_ID_EXT;   
else  
  TxMessage.IDE = CAN_ID_STD;   

  TxMessage.DLC = length;
 for(ii=0;ii<length;ii++)
  {
  TxMessage.Data[ii]=data[ii];
  }
return CAN_Transmit(CAN1,&TxMessage);  	
}

int can_speed(uint8_t index) {
if(index>=MAX_NUM_BR )
  return -1;
else
  return _can_init(CAN_SJW_1tq, can_br32[index].ts1,can_br32[index].ts2,can_br32[index].pre);
}
extern void on_led(void);

void can_read_task( void *pvParameters )
{
uint8_t flg=0;
char t_buf[32];
uint8_t num_bytes=0;
uint32_t cur_time;
CanRxMsg *p_msg_buf;
q_can_rd  = xQueueCreate(LEN_CAN_RD_Q,sizeof(uint8_t));

for( ;; )
  {
  xQueueReceive(q_can_rd,&flg,portMAX_DELAY);
  switch(flg){
    case 0x1:
      p_msg_buf=&can_msg_buf1;
      break;
    case 0x2:
       p_msg_buf=&can_msg_buf2;
     break;
    default:
      break;
   }
  if(flg)  {
    on_led();
    cur_time=xTaskGetTickCount();
#if 0
    num_bytes = sprintf(t_buf,"t%3.3X%1.1X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%4.4X\r",
///   num_bytes = sprintf(t_buf,"t%3.3X%1.1X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X\r",
            p_msg_buf->StdId,
            p_msg_buf->DLC,
            p_msg_buf->Data[0],
            p_msg_buf->Data[1],
            p_msg_buf->Data[2],
            p_msg_buf->Data[3],
            p_msg_buf->Data[4],
            p_msg_buf->Data[5],
            p_msg_buf->Data[6],
            p_msg_buf->Data[7] ,
            cur_time);
#else
num_bytes = 0;
t_buf[num_bytes++] = 't';
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->StdId)>>8);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->StdId)>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->StdId));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->DLC));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[0])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[0]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[1])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[1]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[2])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[2]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[3])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[3]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[4])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[4]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[5])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[5]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[6])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[6]));
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[7])>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((p_msg_buf->Data[7]));
t_buf[num_bytes++] = halfbyte_to_hexascii((cur_time)>>12);
t_buf[num_bytes++] = halfbyte_to_hexascii((cur_time)>>8);
t_buf[num_bytes++] = halfbyte_to_hexascii((cur_time)>>4);
t_buf[num_bytes++] = halfbyte_to_hexascii((cur_time)>>0);
t_buf[num_bytes++] = '\r';
#endif
   
        if(num_bytes)
          {
          write_my_uart(t_buf,num_bytes); 
          }
      }
  }
  
}
