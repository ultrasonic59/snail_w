#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f2xx_conf.h"
#include "stm32f2xx_can.h"
#include "mstep_board.h"
#include "can.h"

#include "printk.h"
////=====================
CAN_msg       CAN_TxMsg;                  /* CAN messge for sending           */
CAN_msg       CAN_RxMsg;                  /* CAN message for receiving        */                        

unsigned int  CAN_TxRdy = 0;              /* CAN HW ready to transmit message */
unsigned int  CAN_RxRdy = 0;              /* CAN HW received a message        */
////=====================
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
void CAN_testmode (unsigned int testmode) {

  CAN1->BTR &= ~(CAN_BTR_SILM | CAN_BTR_LBKM);     /* set testmode            */
  CAN1->BTR |=  (testmode & (CAN_BTR_SILM | CAN_BTR_LBKM));
}
void CAN_waitReady (void)  
{
while ((CAN1->TSR & CAN_TSR_TME0) == 0);  /* Transmit mailbox 0 is empty    */
CAN_TxRdy = 1;
 
}
/*----------------------------------------------------------------------------
  write a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
void CAN_wrMsg (CAN_msg *msg)  {

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
void CAN_rdMsg (CAN_msg *msg)  {
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


/*----------------------------------------------------------------------------
  CAN write message filter
 *----------------------------------------------------------------------------*/
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


/*----------------------------------------------------------------------------
  CAN transmit interrupt handler
 *----------------------------------------------------------------------------*/
void _CAN1_TX_IRQHandler (void) {

  if (CAN1->TSR & CAN_TSR_RQCP0) {          /* request completed mbx 0        */
    CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */
    CAN1->IER &= ~CAN_IER_TMEIE;            /* disable  TME interrupt         */
	
	CAN_TxRdy = 1;
//	sendchar2(0x34);
  }
}

/*----------------------------------------------------------------------------
  CAN receive interrupt handler
 *----------------------------------------------------------------------------*/
void _CAN1_RX0_IRQHandler (void)
{
u32 *up;
	
if (CAN1->RF0R & CAN_RF0R_FMP0)
  {			/* message pending ?              */
  CAN_rdMsg (&CAN_RxMsg);                 /* read the message               */

  if (CAN_RxMsg.id == (0x080 + NODE))
    {
    up = (u32*)CAN_RxMsg.data;
////    stat_srv_y.fault &= 0xff000000;
////    stat_srv_y.fault |= ((*up) & 0x00ffffff);
////    stat_srv_y.flg |= STAT_SRV_FLG_ERR_REQ;
    }
  else
    {
    CAN_RxRdy = 1;                          // set receive flag
    }
  }
}

////================================================================================
void CAN1_Init (void)
{
CAN_setup ();                                   /* setup CAN Controller     */

CAN_wrFilter (0x580 + NODE, STANDARD_FORMAT);
CAN_wrFilter (0x080 + NODE, STANDARD_FORMAT);
CAN_wrFilter (0x700 + NODE, STANDARD_FORMAT);
	
CAN_start ();                                   /* start CAN Controller   */
	
CAN_waitReady ();                               /* wait til tx mbx is empty */
}
