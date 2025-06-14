#ifndef __UART_H__
#define __UART_H_
#include "stdint.h"
////#include "stm8s_conf.h"
////======== cmds =====================
#define PUT_VIBRO       'V'
#define PUT_LEDS        'L'
#define PUT_GLED        'G'
#define PUT_POW_GEN     'P'
#define GET_BAT         'B'
#define GET_TEMP        'T'
#define GET_VERS        'v'

////===================================

#define LEN_RX_BUFF 16

typedef struct rx_cmd_s
{
uint8_t len;
uint8_t buff[LEN_RX_BUFF];
}uart_cmd_t;

extern uart_cmd_t rx_cmd;
extern uart_cmd_t tx_cmd;

///extern uint8_t rx_buff[LEN_RX_BUFF];
////extern void uart1_rx_handler(void);
extern volatile uint8_t rx_buff_ready;
extern void uart_init(void);
extern int rx_receive(void* dat,uint16_t len_rx);
extern void obr_uart_cmd(uart_cmd_t *cmd);
extern void tx_send(uart_cmd_t *cmd);


#endif
