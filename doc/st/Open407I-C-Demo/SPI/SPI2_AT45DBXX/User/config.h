#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for connected to I2C1
 */
/* SPIx Communication boards Interface */
// SPI1 MISO (PA6)	MOSI(PA7)  CLK(PA5)  NSS(PA4)

#define Open_SPIx                           SPI2
#define Open_SPIx_CLK                       RCC_APB1Periph_SPI2
#define Open_SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd
#define Open_SPIx_IRQn                      SPI2_IRQn
#define Open_SPIx_IRQHANDLER                SPI2_IRQHandler

#define Open_SPIx_SCK_PIN                   GPIO_Pin_13
#define Open_SPIx_SCK_GPIO_PORT             GPIOB
#define Open_SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define Open_SPIx_SCK_SOURCE                GPIO_PinSource13
#define Open_SPIx_SCK_AF                    GPIO_AF_SPI2

#define Open_SPIx_MISO_PIN                  GPIO_Pin_14
#define Open_SPIx_MISO_GPIO_PORT            GPIOB
#define Open_SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define Open_SPIx_MISO_SOURCE               GPIO_PinSource14
#define Open_SPIx_MISO_AF                   GPIO_AF_SPI2

#define Open_SPIx_MOSI_PIN                  GPIO_Pin_15
#define Open_SPIx_MOSI_GPIO_PORT            GPIOB
#define Open_SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define Open_SPIx_MOSI_SOURCE               GPIO_PinSource15
#define Open_SPIx_MOSI_AF                   GPIO_AF_SPI2

#endif
