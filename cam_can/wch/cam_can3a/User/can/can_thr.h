/*
 * can_thr.h
 *
 *  Created on: Apr 30, 2024
 *      Author: vova
 */

#ifndef __CAN_THR_H_
#define __CAN_THR_H_

#define MAX_CAN_DATA_LEN 8

#define  CAN_TDT0R_DLC                       ((uint32_t)0x0000000F)        /*!<Data Length Code */

extern QueueHandle_t queu_to_send;
extern can_msg_t   CAN_RxMsg;
extern uint8_t     cur_stat;
extern uint8_t     CAN_TxRdy ;              /* CAN HW ready to transmit message */
extern uint8_t     CAN_RxRdy ;              /* CAN HW received a message        */
extern void CAN_wrMsg (can_msg_t *msg);


extern void can_rsv_thr( void *pvParameters );
extern void can_send_thr(void* pp);
extern int obr_can_cmd(uint8_t *data);
extern int stop_mot_cmd(void);

#endif /* __CAN_THR_H_ */
