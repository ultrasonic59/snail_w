#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for connected to I2C3
 */
#define Open_I2Cx                        	I2C3
#define Open_I2Cx_CLK                    	RCC_APB1Periph_I2C3

#define Open_I2Cx_SDA_PIN                 	GPIO_Pin_9
#define Open_I2Cx_SDA_GPIO_PORT           	GPIOC
#define Open_I2Cx_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOC
#define Open_I2Cx_SDA_SOURCE              	GPIO_PinSource9
#define Open_I2Cx_SDA_AF                  	GPIO_AF_I2C3

#define Open_I2Cx_SCL_PIN                 	GPIO_Pin_7
#define Open_I2Cx_SCL_GPIO_PORT           	GPIOH
#define Open_I2Cx_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOH
#define Open_I2Cx_SCL_SOURCE              	GPIO_PinSource7
#define Open_I2Cx_SCL_AF                  	GPIO_AF_I2C3

#define I2Cx_SPEED               100000
#define I2Cx_SLAVE_ADDRESS7      0x30

#endif
