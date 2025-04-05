
#ifndef __I2C_H__
#define __I2C_H__
//#include "stm32f7xx.h"                  // Device header

#include "stm32f2xx.h"                  // Device header
///#include "delay.h"
#include <stdint.h>
#include "stm32f2xx_conf.h"
#include "stm32f2xx_i2c.h"
#include "stm32f2xx_rcc.h"

extern void I2C_Eeprom_Init(void) ;
///void i2c_init(void);
///char i2c_readByte(char saddr,char maddr,char *data);
///void i2c_writeByte(char saddr,char maddr,char data);
///void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length);
#endif

