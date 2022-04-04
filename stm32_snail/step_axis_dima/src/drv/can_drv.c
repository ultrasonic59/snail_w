#include "stdint.h"
#include "stm32f2xx.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_can.h"
#include "misc.h"
#include "board.h"
#include "snail_can_cmds.h"
#include "printk.h"
////=======================================================
////#define CANx CAN1
#define MAX_CAN_DATA_LEN 8

////=======================================================
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
volatile TestStatus TestRx;
__IO uint32_t ret=0;
uint8_t  CAN_TxRdy = 0;              /* CAN HW ready to transmit message */
uint8_t  CAN_RxRdy = 0;              /* CAN HW received a message        */
CanRxMsg RxMessage;

////=============================================================
void NVIC_can_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}

void can1_init(void)
{
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  
GPIO_InitTypeDef GPIO_InitStructure;
////============== CAN1_INH ============================
RCC_AHB1PeriphClockCmd(CAN1_INH_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CAN1_INH_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( CAN1_INH_PIN_GPIO, &GPIO_InitStructure );
GPIO_ResetBits(CAN1_INH_PIN_GPIO, CAN1_INH_PIN);

////============== CAN1_RX ============================
RCC_AHB1PeriphClockCmd(CAN1_RX_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init(CAN1_RX_PIN_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(CAN1_RX_PIN_GPIO, CAN1_RX_PIN_SOURCE, GPIO_AF_CAN1);
////============== CAN1_TX ============================
RCC_AHB1PeriphClockCmd(CAN1_TX_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CAN1_TX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init(CAN1_TX_PIN_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(CAN1_TX_PIN_GPIO, CAN1_TX_PIN_SOURCE, GPIO_AF_CAN1);
////================================================================
RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
NVIC_can_Config();

  /* CAN register init */
  CAN_DeInit(CAN1);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;///CAN_Mode_LoopBack;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  
  /* Baudrate = 500 Kbps */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 4;
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  
/////  CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_FILTR_ID<<5;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0;
 CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
/////  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = CAN_FILTR_MASK<<5;///0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

  /* CAN FIFO0 message pending interrupt enable */ 
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

}
////==================================================================
uint8_t can1_send(uint16_t id,uint8_t data_len,uint8_t *data)
{
CanTxMsg TxMessage;
uint8_t ii ;
  /* transmit 1 message */
  TxMessage.StdId = 0;
  TxMessage.ExtId = id;
  TxMessage.IDE = CAN_ID_EXT;
  TxMessage.RTR = CAN_RTR_DATA;
  if(data_len>MAX_CAN_DATA_LEN)
    {
    data_len=MAX_CAN_DATA_LEN ; 
    }
  TxMessage.DLC = data_len;
  for(ii=0;ii<data_len;ii++)
    {
    TxMessage.Data[ii] = data[ii];
    }
  CAN_Transmit(CAN1, &TxMessage);
  return data_len;
}

TestStatus CAN_Interrupt(void)
{
  CanTxMsg TxMessage;
  uint32_t i = 0;


  /* transmit 1 message */
  TxMessage.StdId = 0;
  TxMessage.ExtId = 0x1234;
  TxMessage.IDE = CAN_ID_EXT;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.DLC = 2;
  TxMessage.Data[0] = 0xDE;
  TxMessage.Data[1] = 0xCA;
  CAN_Transmit(CAN1, &TxMessage);

  /* initialize the value that will be returned */
  ret = 0xFF;
       
  /* receive message with interrupt handling */
  i = 0;
  while((ret ==  0xFF) && (i < 0xFFF))
  {
    i++;
  }
  
  if (i ==  0xFFF)
  {
    ret = 0;  
  }

  /* disable interrupt handling */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);

  return (TestStatus)ret;
}

////==================================================================
int can_main1(void)
{
RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
NVIC_can_Config();
////=========================================
__enable_irq();
////========================================
#if 0
TestRx = CAN_Polling();
if (TestRx !=  FAILED)
  { /* OK */
  printk("\r\n CAN_Polling OK");
  }
  else
  { /* KO */
  printk("\r\n CAN_Polling BAD");
  }
#endif
  TestRx = CAN_Interrupt();
if (TestRx !=  FAILED)
  { /* OK */

   printk("\r\n Interrupt OK");
  }
  else
  { /* KO */
   printk("\r\n Interrupt BAD");
  }

  /* Infinite loop */
  while (1)
  {
    
  }

return 0;
}
///=============================================
#define CAN_MAX_NUM_BYTES 8
#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

typedef struct  CAN_msg_s_{
  unsigned int   id;                 // 29 bit identifier
  unsigned char  data[CAN_MAX_NUM_BYTES];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} can_msg_t;
can_msg_t       CAN_RxMsg;                  /* CAN message for receiving        */                        

/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
void CAN_rdMsg (can_msg_t *msg)  {
                                              /* Read identifier information  */
  if ((CAN1->sFIFOMailBox[0].RIR & CAN_ID_EXT) == 0) {
    msg->format = STANDARD_FORMAT;
    msg->id     = 0x000007FF & (CAN1->sFIFOMailBox[0].RIR >> 21);
  } else {
    msg->format = EXTENDED_FORMAT;
    msg->id     = 0x1FFFFFFF & (CAN1->sFIFOMailBox[0].RIR >> 3);
  }
                                              /* Read type information        */
  if ((CAN1->sFIFOMailBox[0].RIR & CAN_RTR_REMOTE) == 0) {
    msg->type =   DATA_FRAME;
  } else {
    msg->type = REMOTE_FRAME;
  }
                                              /* Read number of rec. bytes    */
  msg->len     = (CAN1->sFIFOMailBox[0].RDTR      ) & 0x0F;
                                              /* Read data bytes              */
  msg->data[0] = (CAN1->sFIFOMailBox[0].RDLR      ) & 0xFF;
  msg->data[1] = (CAN1->sFIFOMailBox[0].RDLR >>  8) & 0xFF;
  msg->data[2] = (CAN1->sFIFOMailBox[0].RDLR >> 16) & 0xFF;
  msg->data[3] = (CAN1->sFIFOMailBox[0].RDLR >> 24) & 0xFF;

  msg->data[4] = (CAN1->sFIFOMailBox[0].RDHR      ) & 0xFF;
  msg->data[5] = (CAN1->sFIFOMailBox[0].RDHR >>  8) & 0xFF;
  msg->data[6] = (CAN1->sFIFOMailBox[0].RDHR >> 16) & 0xFF;
  msg->data[7] = (CAN1->sFIFOMailBox[0].RDHR >> 24) & 0xFF;

  CAN1->RF0R |= CAN_RF0R_RFOM0;             /* Release FIFO 0 output mailbox */
}


void CAN1_RX0_IRQHandler (void)
{
if (CAN1->RF0R & CAN_RF0R_FMP0)
  {			/* message pending ?              */
  CAN_rdMsg (&CAN_RxMsg);                 /* read the message               */
  CAN_RxRdy = 1;                          // set receive flag
  }
}


////==================================================================