#ifndef _CAN_H_
#define _CAN_H_

#define MAX_CAN_LEN  8
#define LEN_CAN_RD_Q 8
#define MAX_NUM_BR   9

#define DEF_CAN_BR   6

typedef struct can_br_coef_s
{
uint16_t pre;
uint8_t ts1;
uint8_t ts2;
}can_br_coef_t;

extern can_br_coef_t can_br32[MAX_NUM_BR];

extern CanRxMsg can_msg_buf1;
extern CanRxMsg can_msg_buf2;

///extern void CanWriteData(uint16_t ID,uint8_t *idata,uint8_t len);
extern int can_speed(uint8_t index);
extern int can_transmit( uint32_t id, uint8_t ext, uint8_t rtr,
		 uint8_t length, uint8_t *data);
extern int _can_init(uint32_t sjw, uint32_t ts1, uint32_t ts2,
	     uint32_t brp);
extern void can_read_task( void *pvParameters );
extern void init_can(void);
extern uint8_t cur_can_br;

#endif