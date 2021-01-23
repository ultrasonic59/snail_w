#ifndef __SNAIL_SPD_BRD_H__
#define __SNAIL_SPD_BRD_H__

#include "stm32f2xx_conf.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_rcc.h"

#define BAUD_RATE_115200	        115200

#define  DEF_DBG_BR                     BAUD_RATE_115200	///

////#include "serial_cnf.h"
////======= UART_DBG =======================
////==== A9 =====
#define UART_DBG_TX_PIN         GPIO_Pin_9
#define UART_DBG_TX_SOURCE      GPIO_PinSource9
#define UART_DBG_TX_GPIO_PORT   GPIOA
#define UART_DBG_TX_GPIO_CLK    RCC_AHB1Periph_GPIOA
////==== A10 =====
#define UART_DBG_RX_PIN         GPIO_Pin_10
#define UART_DBG_IRQ_PIN        10
#define UART_DBG_RX_SOURCE      GPIO_PinSource10
#define UART_DBG_RX_GPIO_PORT   GPIOA
#define UART_DBG_RX_GPIO_CLK    RCC_AHB1Periph_GPIOA

#define UART_DBG_CLK            RCC_APB2Periph_USART1
#define UART_DBG_CLK_INIT       RCC_APB2PeriphClockCmd
#define UART_DBG_RX_AF          GPIO_AF_USART1
#define UART_DBG_TX_AF          GPIO_AF_USART1

#define UART_DBG_IRQn           USART1_IRQn
#define UART_DBG                USART1
#define UART_DBG_IRQHandler     USART1_IRQHandler
////======= LEDS =======================
#define LED0_PIN	        GPIO_Pin_3
#define LED0_NPIN	        3
#define LED0_GPIO	        GPIOE
#define LED0_RCC_AHB      RCC_AHB1Periph_GPIOE

#define LED1_PIN	        GPIO_Pin_4
#define LED1_NPIN	        4
#define LED1_GPIO	        GPIOE
#define LED1_RCC_AHB      RCC_AHB1Periph_GPIOE

#define LED2_PIN	        GPIO_Pin_5
#define LED2_NPIN	        5
#define LED2_GPIO	        GPIOE
#define LED2_RCC_AHB      RCC_AHB1Periph_GPIOE

#define LED3_PIN	        GPIO_Pin_6
#define LED3_NPIN	        6
#define LED3_GPIO	        GPIOE
#define LED3_RCC_AHB      RCC_AHB1Periph_GPIOE
////=======================================================
#define CAN1_CLK                    RCC_APB1Periph_CAN1
#define CAN1_RX_PIN                 GPIO_Pin_0
#define CAN1_TX_PIN                 GPIO_Pin_1
#define CAN1_GPIO_PORT              GPIOD
#define CAN1_GPIO_CLK               RCC_AHB1Periph_GPIOD
#define CAN1_AF_PORT                GPIO_AF_CAN1
#define CAN1_RX_SOURCE              GPIO_PinSource0
#define CAN1_TX_SOURCE              GPIO_PinSource1

#define CAN2_CLK                    (RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2)
#define CAN2_RX_PIN                 GPIO_Pin_5
#define CAN2_TX_PIN                 GPIO_Pin_6
#define CAN2_GPIO_PORT              GPIOB
#define CAN2_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define CAN2_AF_PORT                GPIO_AF_CAN2
#define CAN2_RX_SOURCE              GPIO_PinSource5
#define CAN2_TX_SOURCE              GPIO_PinSource6

////=======================================================

extern void gpio_init(void);
extern void put_led0(uint8_t idata);
extern void put_led1(uint8_t idata);
extern void put_led2(uint8_t idata);
extern void put_led3(uint8_t idata);
extern void uDelay (const uint32_t usec);
extern void CAN_Config(void);

///======================================
#endif ///__SNAIL_SPD_BRD_H__
