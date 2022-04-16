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

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;///0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;///0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

}
#if 0
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
#endif
void CAN_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
////=============== CAN1_INH ============================
RCC_AHB1PeriphClockCmd(CAN1_INH_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CAN1_INH_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( CAN1_INH_PIN_GPIO, &GPIO_InitStructure );
GPIO_ResetBits(CAN1_INH_PIN_GPIO, CAN1_INH_PIN);
 /* CAN GPIOs configuration **************************************************/
  /* Enable GPIO clock */
RCC_AHB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_RX_SOURCE, CAN1_AF_PORT);
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_TX_SOURCE, CAN1_AF_PORT);

  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);
  /* CAN configuration ********************************************************/
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN1_CLK, ENABLE);
  NVIC_can_Config();

  /* CAN register init */
  CAN_DeInit(CAN1);

  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = ENABLE;          ////off autoresend
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

  /* CAN Baudrate = 1MBps (CAN clocked at 30 MHz) */
  
   /* Baudrate = 500 Kbps */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CAN1, &CAN_InitStructure);

  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;////CAN_Filter_FIFO0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  //CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
#if 0
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO1;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  //CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
#endif
//  CAN2TxMessage.StdId = 0x321;
//  CAN2TxMessage.ExtId = 0x01;
//  CAN2TxMessage.RTR = CAN_RTR_DATA;
//  CAN2TxMessage.IDE = CAN_ID_STD;
//  CAN2TxMessage.DLC = 8;

  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

}
#if 0
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
#endif
#if 0
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
#endif
///=============================================
#define CAN_MAX_NUM_BYTES 8
#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1
#if 0
typedef struct  CAN_msg_s_{
  unsigned int   id;                 // 29 bit identifier
  unsigned char  data[CAN_MAX_NUM_BYTES];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} can_msg_t;
#endif

can_msg_t       CAN_RxMsg;                  /* CAN message for receiving        */                        
/*----------------------------------------------------------------------------
  write a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
void CAN_wrMsg (can_msg_t *msg)  {

  CAN1->sTxMailBox[0].TIR  = 0;           /* Reset TIR register               */
                                          /* Setup identifier information     */
  if (msg->format == STANDARD_FORMAT) {   /*    Standard ID                   */
    CAN1->sTxMailBox[0].TIR |= (uint32_t)(msg->id << 21) | CAN_ID_STD;
  } else {                                /* Extended ID                      */
    CAN1->sTxMailBox[0].TIR |= (uint32_t)(msg->id <<  3) | CAN_ID_EXT;
  }
                                          /* Setup type information           */
  if (msg->type == DATA_FRAME)  {         /* DATA FRAME                       */
    CAN1->sTxMailBox[0].TIR |= CAN_RTR_DATA;
  } else {                                /* REMOTE FRAME                     */
    CAN1->sTxMailBox[0].TIR |= CAN_RTR_REMOTE;
  }
                                          /* Setup data bytes                 */
  CAN1->sTxMailBox[0].TDLR = (((uint32_t)msg->data[3] << 24) | 
                              ((uint32_t)msg->data[2] << 16) |
                              ((uint32_t)msg->data[1] <<  8) | 
                              ((uint32_t)msg->data[0])        );
  CAN1->sTxMailBox[0].TDHR = (((uint32_t)msg->data[7] << 24) | 
                              ((uint32_t)msg->data[6] << 16) |
                              ((uint32_t)msg->data[5] <<  8) |
                              ((uint32_t)msg->data[4])        );
                                          /* Setup length                     */
  CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
  CAN1->sTxMailBox[0].TDTR |=  (msg->len & CAN_TDT0R_DLC);

  CAN1->IER |= CAN_IER_TMEIE;                 /* enable  TME interrupt        */
  CAN1->sTxMailBox[0].TIR |=  CAN_TI0R_TXRQ;  /* transmit message             */
}


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
void CAN1_RX1_IRQHandler (void)
{
if (CAN1->RF1R & CAN_RF0R_FMP0)
  {			/* message pending ?              */
  CAN_rdMsg (&CAN_RxMsg);                 /* read the message               */
  CAN_RxRdy = 1;                          // set receive flag
  }
}

#if 0
////==================================================================
void CAN_wrFilter (unsigned int id, unsigned char format)  {
  static unsigned short CAN_filterIdx = 0;
         unsigned int   CAN_msgId     = 0;
  
  if (CAN_filterIdx > 13) {                 /* check if Filter Memory is full*/
    return;
  }
                                            /* Setup identifier information  */
  if (format == STANDARD_FORMAT)  {         /*   Standard ID                 */
      CAN_msgId |= (uint32_t)(id << 21) | CAN_ID_STD;
  }  else  {                                /*   Extended ID                 */
      CAN_msgId |= (uint32_t)(id <<  3) | CAN_ID_EXT;
  }

  CAN1->FMR  |=   CAN_FMR_FINIT;            /* set initMode for filter banks */
  CAN1->FA1R &=  ~(1UL << CAN_filterIdx);   /* deactivate filter             */

                                            /* initialize filter             */
  CAN1->FS1R |= (unsigned int)(1 << CAN_filterIdx);     /* set 32-bit scale configuration    */
  CAN1->FM1R |= (unsigned int)(1 << CAN_filterIdx);     /* set 2 32-bit identifier list mode */

  CAN1->sFilterRegister[CAN_filterIdx].FR1 = CAN_msgId; /*  32-bit identifier                */
  CAN1->sFilterRegister[CAN_filterIdx].FR2 = CAN_msgId; /*  32-bit identifier                */
    													   
  CAN1->FFA1R &= ~(unsigned int)(1 << CAN_filterIdx);   /* assign filter to FIFO 0           */
  CAN1->FA1R  |=  (unsigned int)(1 << CAN_filterIdx);   /* activate filter                   */

  CAN1->FMR &= ~CAN_FMR_FINIT;              /* reset initMode for filterBanks*/

  CAN_filterIdx += 1;                       /* increase filter index         */
}

void CAN_waitReady (void)  
{
while ((CAN1->TSR & CAN_TSR_TME0) == 0);  /* Transmit mailbox 0 is empty    */
CAN_TxRdy = 1;
 
}
void CAN_setup (void)  
{
unsigned int brp;

  RCC->APB1ENR |= ( 1UL << 25);           /* enable clock for CAN             */
  NVIC_EnableIRQ(CAN1_TX_IRQn);    /* enable CAN TX interrupt          */
  NVIC_EnableIRQ(CAN1_RX0_IRQn);   /* enable CAN RX interrupt          */

  CAN1->MCR = (CAN_MCR_INRQ   |           /* initialisation request           */
               CAN_MCR_NART    );         /* no automatic retransmission      */
                                          /* only FIFO 0, tx mailbox 0 used!  */
  CAN1->IER = (CAN_IER_FMPIE0 |           /* enable FIFO 0 msg pending IRQ    */
               CAN_IER_TMEIE    );        /* enable Transmit mbx empty IRQ    */

brp = 4;//4;
                                                                          
CAN1->BTR &= ~(((        0x03) << 24) | ((        0x07) << 20) | ((         0x0F) << 16) | (          0x1FF)); 
CAN1->BTR |=  ((((1-1) & 0x03) << 24) | (((8-1) & 0x07) << 20) | (((6-1) & 0x0F) << 16) | ((brp-1) & 0x1FF));
}
void CAN_start (void)  
{
CAN1->MCR &= ~CAN_MCR_INRQ;             /* normal operating mode, reset INRQ*/
while (CAN1->MSR & CAN_MCR_INRQ);

}
#endif
////================================================================================
void CAN1_Init (void)
{
////CAN_setup ();                                   /* setup CAN Controller     */

////CAN_wrFilter (0x0, STANDARD_FORMAT);
////CAN_wrFilter (0x080 + NODE, STANDARD_FORMAT);
////CAN_wrFilter (0x700 + NODE, STANDARD_FORMAT);
	
////CAN_start ();                                   /* start CAN Controller   */
	
////CAN_waitReady ();                               /* wait til tx mbx is empty */
}
/*----------------------------------------------------------------------------
  CAN transmit interrupt handler
 *----------------------------------------------------------------------------*/
void CAN1_TX_IRQHandler (void) {

  if (CAN1->TSR & CAN_TSR_RQCP0) {          /* request completed mbx 0        */
    CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */
    CAN1->IER &= ~CAN_IER_TMEIE;            /* disable  TME interrupt         */
	
	CAN_TxRdy = 1;
//	sendchar2(0x34);
  }
}
