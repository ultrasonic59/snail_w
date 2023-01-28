#ifndef __SERIAL_H__
#define __SERIAL_H__
///==================================================
#include "ring_buffer.h"

#define XON 0x11
#define XOFF 0x13
#if 0
typedef int32_t ring_size_t;

typedef struct ring {
    uint8_t *data;
    ring_size_t size;
    ring_size_t begin;
    ring_size_t end;
}ring_t;
#endif

#define RB_SIZE	512
#define TB_SIZE	64

#define MY_USART_SPEED	115200  //// 500000  ///115200  ////1000000 ////2000000

#if 0
#define RING_SIZE(RING)  ((RING)->size - 1)
#define RING_DATA(RING)  (RING)->data
#define RING_EMPTY(RING) ((RING)->begin == (RING)->end)
#endif

extern xQueueHandle q_uart_rd ;
extern ringbuffer_t uart_rx_buffer;
extern ringbuffer_t uart_tx_buffer;

////============================================================
extern void usart_setup(void);
///extern int32_t ring_write_ch(ring_t *ring, uint8_t ch);
////extern int32_t ring_write(ring_t *ring, uint8_t * data, ring_size_t size);
extern int32_t ring_write(ringbuffer_t*ring, uint8_t * data, uint32_t size);
///extern int32_t ring_read_ch(ring_t *ring, uint8_t * ch);
///extern int32_t ring_bytes_free(const ring_t *ring);
extern uint8_t uart_read_blocking(void);
extern void init_dma_read(void);
extern int write_my_uart( char *ptr, int len) ;

extern int sendchar_my_uart (int c) ;
extern void MY_UART_IRQHandler(void);

#endif ///__SERIAL_H__

