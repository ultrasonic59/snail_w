#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for COM port1, connected to USART3
 */  
#define Open_USART                        USART1
#define Open_USART_CLK                    RCC_APB2Periph_USART1

#define Open_USART_TX_PIN                 GPIO_Pin_9
#define Open_USART_TX_GPIO_PORT           GPIOA
#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define Open_USART_TX_SOURCE              GPIO_PinSource9
#define Open_USART_TX_AF                  GPIO_AF_USART1


#define Open_USART_RX_PIN                 GPIO_Pin_10
#define Open_USART_RX_GPIO_PORT           GPIOA
#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define Open_USART_RX_SOURCE              GPIO_PinSource10
#define Open_USART_RX_AF                  GPIO_AF_USART1

#define Open_USART_IRQn                   USART1_IRQn	 

void USART_Configuration(void);
void USART_NVIC_Config(void);

#endif /*_USART_H*/
