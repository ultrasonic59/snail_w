#include <stdint.h>
#include <string.h>
///#include "ch32v30x.h"
#include "ch32v30x_can.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"


#include "cam_can_brd.h"
#include "can.h"
#include "can_cmds.h"
#include "debug.h"
#include "can_thr.h"

////=======================================================
////#define CANx CAN1

#ifndef TMIDxR_TXRQ
/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ         ((uint32_t)0x00000001)
#endif

////=======================================================
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

volatile TestStatus TestRx;
__IO uint32_t ret=0;
uint8_t         CAN_TxRdy = 0;              /* CAN HW ready to transmit message */
/////uint8_t         CAN_RxRdy = 0;              /* CAN HW received a message        */
can_msg_t       CAN_RxMsg;                  /* CAN message for receiving        */


#if 0
can_br_coef_t can_br30[]=
{
  {150,CAN_BS1_15tq,CAN_BS2_5tq},  ////10 kb
  {75,CAN_BS1_15tq,CAN_BS2_5tq},  ////20 kb
  {30,CAN_BS1_15tq,CAN_BS2_5tq},  ////50 kb
  {30,CAN_BS1_8tq,CAN_BS2_2tq},  ////100 kb
  {15,CAN_BS1_14tq,CAN_BS2_2tq},  ////125 kb
  {15,CAN_BS1_7tq,CAN_BS2_1tq},  ////250 kb
  {6,CAN_BS1_7tq,CAN_BS2_2tq},  ////500 kb
  {3,CAN_BS1_11tq,CAN_BS2_2tq},  ////800 kb
  {2,CAN_BS1_13tq,CAN_BS2_2tq}  ////1000 kb
};

#endif
can_br_coef_t can_br36[]=
{
  {150,CAN_BS1_15tq,CAN_BS2_5tq},  ////0:10 kb
  {75,CAN_BS1_15tq,CAN_BS2_5tq},  ////1:20 kb
  {30,CAN_BS1_15tq,CAN_BS2_5tq},  ////2:50 kb
  {30,CAN_BS1_8tq,CAN_BS2_2tq},  ////3:100 kb
  {15,CAN_BS1_14tq,CAN_BS2_2tq},  ////4:125 kb
  {12,CAN_BS1_6tq,CAN_BS2_5tq},  ////5:250 kb
  {12,CAN_BS1_6tq,CAN_BS2_5tq},  ////6:500 kb
  {3,CAN_BS1_11tq,CAN_BS2_2tq},  ////7:800 kb
  {3,CAN_BS1_6tq,CAN_BS2_5tq}  ////8:1000 kb
};

CanRxMsg RxMessage;

////=============================================================
void NVIC_can_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;///0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;///0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

}
#if 1
/*----------------------------------------------------------------------------
  write a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
void CAN_wrMsg (can_msg_t *msg)  {

  CANx->sTxMailBox[0].TXMIR = 0;           /* Reset TIR register               */
                                          /* Setup identifier information     */
  if (msg->format == STANDARD_FORMAT) {   /*    Standard ID                   */
    CANx->sTxMailBox[0].TXMIR |= (uint32_t)(msg->id << 21) | CAN_ID_STD;
  } else {                                /* Extended ID                      */
    CANx->sTxMailBox[0].TXMIR |= (uint32_t)(msg->id <<  3) | CAN_ID_EXT;
  }
                                          /* Setup type information           */
  if (msg->type == DATA_FRAME)  {         /* DATA FRAME                       */
    CANx->sTxMailBox[0].TXMIR |= CAN_RTR_DATA;
  } else {                                /* REMOTE FRAME                     */
    CANx->sTxMailBox[0].TXMIR |= CAN_RTR_REMOTE;
  }
                                          /* Setup data bytes                 */
  CANx->sTxMailBox[0].TXMDLR = (((uint32_t)msg->data[3] << 24) |
                              ((uint32_t)msg->data[2] << 16) |
                              ((uint32_t)msg->data[1] <<  8) | 
                              ((uint32_t)msg->data[0])        );
  CANx->sTxMailBox[0].TXMDHR = (((uint32_t)msg->data[7] << 24) |
                              ((uint32_t)msg->data[6] << 16) |
                              ((uint32_t)msg->data[5] <<  8) |
                              ((uint32_t)msg->data[4])        );
                                          /* Setup length                     */
  CANx->sTxMailBox[0].TXMDTR &= ~CAN_TDT0R_DLC;
  CANx->sTxMailBox[0].TXMDTR |=  (msg->len & CAN_TDT0R_DLC);

  CANx->INTENR |= CAN_INTENR_TMEIE;                 /* enable  TME interrupt        */
  CANx->sTxMailBox[0].TXMIR |=  TMIDxR_TXRQ;  /* transmit message             */
}

#if 0
/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
void CAN_rdMsg (can_msg_t *msg)  {
                                              /* Read identifier information  */
  if ((CANx->sFIFOMailBox[0].RXMIR & CAN_ID_EXT) == 0) {
    msg->format = STANDARD_FORMAT;
    msg->id     = 0x000007FF & (CANx->sFIFOMailBox[0].RXMIR >> 21);
  } else {
    msg->format = EXTENDED_FORMAT;
    msg->id     = 0x1FFFFFFF & (CANx->sFIFOMailBox[0].RXMIR >> 3);
  }
                                              /* Read type information        */
  if ((CANx->sFIFOMailBox[0].RXMIR & CAN_RTR_REMOTE) == 0) {
    msg->type =   DATA_FRAME;
  } else {
    msg->type = REMOTE_FRAME;
  }
                                              /* Read number of rec. bytes    */
  msg->len     = (CANx->sFIFOMailBox[0].RXMDTR      ) & 0x0F;
                                              /* Read data bytes              */
  msg->data[0] = (CANx->sFIFOMailBox[0].RXMDLR      ) & 0xFF;
  msg->data[1] = (CANx->sFIFOMailBox[0].RXMDLR >>  8) & 0xFF;
  msg->data[2] = (CANx->sFIFOMailBox[0].RXMDLR >> 16) & 0xFF;
  msg->data[3] = (CANx->sFIFOMailBox[0].RXMDLR >> 24) & 0xFF;

  msg->data[4] = (CANx->sFIFOMailBox[0].RXMDHR      ) & 0xFF;
  msg->data[5] = (CANx->sFIFOMailBox[0].RXMDHR >>  8) & 0xFF;
  msg->data[6] = (CANx->sFIFOMailBox[0].RXMDHR >> 16) & 0xFF;
  msg->data[7] = (CANx->sFIFOMailBox[0].RXMDHR >> 24) & 0xFF;

  CANx->RFIFO0 |= CAN_RFIFO0_RFOM0;             /* Release FIFO 0 output mailbox */
}
#endif
void CAN2_RX0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void CAN2_RX0_IRQHandler (void)
{
CanRxMsg t_msg;

if (CAN2->RFIFO0 & CAN_RFIFO0_FMP0)
  {			/* message pending ?              */
 //// CAN_rdMsg (&CAN_RxMsg);                 /* read the message               */
  CAN_Receive( CAN2, CAN_FIFO0, &t_msg);
  CAN_RxMsg.id=t_msg.StdId;
  memcpy(CAN_RxMsg.data,t_msg.Data,t_msg.DLC);
  CAN_RxMsg.len= t_msg.DLC;
  CAN_RxMsg.format= 0;
  CAN_RxMsg.type= t_msg.RTR;

  CAN_RxRdy = 1;                          // set receive flag
  }
}
void CAN2_RX1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
volatile uint32_t vtst;
void CAN2_RX1_IRQHandler (void)
{
CanRxMsg t_msg;
if (CAN2->RFIFO1 & CAN_RFIFO1_FMP1)
  {			/* message pending ?              */
  CAN_Receive( CAN2, CAN_FIFO1, &t_msg);
  CAN_RxMsg.id=t_msg.StdId;
  memcpy(CAN_RxMsg.data,t_msg.Data,t_msg.DLC);
  CAN_RxMsg.len= t_msg.DLC;
  CAN_RxMsg.format= 0;
  CAN_RxMsg.type= t_msg.RTR;

///  CAN_RxRdy = 1;                          // set receive flag
 /// CAN_ClearFlag(CAN2, CAN_IT_FF1) ;
////  CAN_ClearFlag(CAN2, CAN_IT_FOV1) ;
////  vtst=CAN2->RFIFO1;
  CAN_RxRdy = 1;                          // set receive flag

  }
}
////================================================================================
/*----------------------------------------------------------------------------
  CAN transmit interrupt handler
 *----------------------------------------------------------------------------*/
void CAN2_TX_IRQHandler (void) {
////???
#if 0
  if (CAN2-> >TSR & CAN_TSR_RQCP0) {          /* request completed mbx 0        */
    CAN2->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */
    CAN2->IER &= ~CAN_IER_TMEIE;            /* disable  TME interrupt         */
	
	CAN_TxRdy = 1;
//	sendchar2(0x34);
  }
#endif
}
#endif
////==============================================================
void CAN_FilterConfig(uint8_t num,uint32_t id,uint32_t mask)
{
 CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 #if 1
  CAN_FilterInitStructure.CAN_FilterNumber = num;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;////CAN_Filter_FIFO0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = (id>>16)&0xffff;
  CAN_FilterInitStructure.CAN_FilterIdLow = id&0xffff;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (mask>>16)&0xffff;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow =  mask&0xffff;
  //CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
#endif
}
void canfilter_init(void)
{
uint32_t id;
uint32_t mask= ID_MASK << 21; ///5+16;

id=ID_BRD<<21; ///5+16
printf("id=%x[%x]\n\r ",ID_BRD,id);

CAN_FilterConfig(0,id,mask);	
}
////=============================================================================================



////==============================================================
int can_init( FunctionalState ttcm, FunctionalState abom, FunctionalState awum, FunctionalState nart,
         FunctionalState rflm, FunctionalState txfp, uint32_t sjw, uint32_t ts1, uint32_t ts2,
         uint32_t brp, uint8_t loopback, uint8_t silent)
{
  uint8_t tmp=0;
CAN_InitTypeDef   CAN_InitStructure;
RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN2, ENABLE );
CAN_DeInit(CANx);               // CAN register deinit

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

if(CAN_Init(CANx, &CAN_InitStructure) == CAN_InitStatus_Success)
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
int can_speed(uint8_t index) {
if(index>=MAX_NUM_BR )
  return -1;
else
  return _can_init(CAN_SJW_1tq, can_br36[index].ts1,can_br36[index].ts2,can_br36[index].pre);
}


void init_can(void)
{
#if 1
/////RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

can_init(DISABLE,DISABLE,DISABLE, ENABLE,
         DISABLE, DISABLE, CAN_SJW_1tq, CAN_BS1_6tq, CAN_BS2_8tq,
         4, _FALSE, _FALSE);
can_speed(DEF_CAN_BR);
////nvic_can();
  NVIC_can_Config();

CAN_ITConfig(CANx,CAN_IT_FMP0,ENABLE);
CAN_ITConfig(CANx,CAN_IT_FMP1,ENABLE);
canfilter_init();
#endif
}
