
#ifndef _BOARD_H_
#define _BOARD_H_

////#include "stm32f10x_lib.h"
#include "stm32f10x_can.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "can.h"
#include "serial.h"
#include "my_misc.h"

/* Baud rate used by the comtest tasks. */
#define DEF_BAUD_RATE		( 115200 )

#define MY_UART_GPIO_RCC       RCC_APB2Periph_GPIOA
#define RCC_APBPeriph_MY_UART  RCC_APB1Periph_USART2
#define MY_UART                USART2
#define MY_UART_TX_PIN        GPIO_Pin_2
#define MY_UART_TX_PIN_SOURCE  GPIO_PinSource2
#define MY_UART_RX_PIN        GPIO_Pin_3
#define MY_UART_RX_PIN_SOURCE  GPIO_PinSource3
#define MY_UART_RX_GPIO            GPIOA
#define MY_UART_TX_GPIO            GPIOA
#define MY_UART_RX_AF           GPIO_AF_USART2
#define MY_UART_TX_AF           GPIO_AF_USART2
#define MY_UART_IRQn            USART2_IRQn
#define MY_UART_IRQHandler            USART2_IRQHandler

#define CAN_GPIO_PORT_RCC       RCC_APB2Periph_GPIOB
#define CAN_CLK           RCC_APB1Periph_CAN1
#define CAN_RX_PIN        GPIO_Pin_8
#define CAN_TX_PIN        GPIO_Pin_9
#define CAN_GPIO_PORT     GPIOB
////=============== Led ============================
#define LED_PIN	    	        GPIO_Pin_0
#define LED_PIN_NPIN	    	0
#define LED_PIN_GPIO	    	GPIOA
////#define LED_PIN_RCC  	        RCC_AHB1Periph_GPIOA

#ifndef _TRUE
#define _TRUE   1
#endif

#ifndef _FALSE
#define _FALSE   0
#endif

extern void board_init(void);
extern void init_can(void);
extern void init_serial(void);
extern void init_gpio(void);
extern void testTask( void *pvParameters );
extern void  put_led(uint8_t idat);
extern void Delay(uint32_t nTime);
extern void uDelay (const uint32_t usec);
extern void on_led(void);

#endif ////_BOARD_H_

