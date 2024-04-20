#ifndef __CAN_H__
#define __CAN_H__

#include <stdint.h>
////==============================================

#define CAN_TIMEOUT_SEND	100

#define CAN_MAX_NUM_BYTES 8
#define MAX_NUM_BR   9

#define DEF_CAN_BR   6  ///500

#ifndef _FALSE 
#define _FALSE 0
#endif

typedef struct can_br_coef_s
{
uint16_t pre;
uint8_t ts1;
uint8_t ts2;
}can_br_coef_t;

extern can_br_coef_t can_br30[MAX_NUM_BR];

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

////==============================================
extern void CAN1_Init (void);
extern uint8_t  CAN_RxRdy;              /* CAN HW received a message        */
extern uint8_t  CAN_TxRdy;              /* CAN HW ready to transmit message */
////extern CanRxMsg RxMessage;
extern void CAN_wrMsg (can_msg_t *msg);
extern void CAN_Config(void);
extern void CAN_FilterConfig(uint8_t num,uint32_t id,uint32_t mask);
extern void init_can(void);

#endif
