#ifndef __CAN_H__
#define __CAN_H__

////==============================================
////#define NODE	0x01	//0x03
////#define NODE2	0x01	//0x03

////#define ADDR_PDO_1	0x181
////#define ADDR_PDO_2	0x182

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

typedef struct  {
  unsigned int   id;                 // 29 bit identifier
  unsigned char  data[8];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

/* CAN identifier type */
///#define CAN_ID_STD            ((uint32_t)0x00000000)  /* Standard Id          */
///#define CAN_ID_EXT            ((uint32_t)0x00000004)  /* Extended Id          */

/* CAN remote transmission request */
////#define CAN_RTR_DATA          ((uint32_t)0x00000000)  /* Data frame           */
////#define CAN_RTR_REMOTE        ((uint32_t)0x00000002)  /* Remote frame         */
////==============================================
extern void CAN1_Init (void);
extern uint8_t  CAN_RxRdy;              /* CAN HW received a message        */
extern uint8_t  CAN_TxRdy;              /* CAN HW ready to transmit message */
////extern CanRxMsg RxMessage;

#endif