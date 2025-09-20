#ifndef __UART_H__
#define __UART_H__

typedef struct send_data_s{
uint16_t coord;
uint16_t val;
}send_data_t;

extern send_data_t resiv_enc;

extern void UART_ENC_IRQHandler(void);
extern uint8_t uart_send_buff(uint8_t *buff, uint16_t len);
extern void UART_ENC_Init(void);

#endif