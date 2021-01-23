#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for connected to I2C3
 */
#define Open_I2Cx                        	I2C2
#define Open_I2Cx_CLK                    	RCC_APB1Periph_I2C2

#define Open_I2Cx_SDA_PIN                 	GPIO_Pin_5
#define Open_I2Cx_SDA_GPIO_PORT           	GPIOH
#define Open_I2Cx_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOH
#define Open_I2Cx_SDA_SOURCE              	GPIO_PinSource5
#define Open_I2Cx_SDA_AF                  	GPIO_AF_I2C2

#define Open_I2Cx_SCL_PIN                 	GPIO_Pin_1
#define Open_I2Cx_SCL_GPIO_PORT           	GPIOF
#define Open_I2Cx_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOF
#define Open_I2Cx_SCL_SOURCE              	GPIO_PinSource1
#define Open_I2Cx_SCL_AF                  	GPIO_AF_I2C2

#define I2Cx_SPEED               100000
#define I2Cx_SLAVE_ADDRESS7      0x30

#endif
