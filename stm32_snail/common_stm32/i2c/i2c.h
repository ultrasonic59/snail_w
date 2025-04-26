
#ifndef __I2C_H__
#define __I2C_H__
//#include "stm32f7xx.h"                  // Device header

#include "stm32f2xx.h"                  // Device header
///#include "delay.h"
#include <stdint.h>
#include "stm32f2xx_conf.h"
#include "stm32f2xx_i2c.h"
#include "stm32f2xx_rcc.h"
#define MAX_WAIT  500000
#define EEPROM_ADDR 0xa0
#define DELAY_WRITE  4000  ///~6ms

extern void I2C_Eeprom_Init(void) ;
extern int i2c_readByte(I2C_TypeDef* I2Cx,uint8_t haddr,uint16_t addr, uint8_t *data);
extern int i2c_writeByte(I2C_TypeDef* I2Cx,uint8_t haddr,uint16_t addr,uint8_t data);
extern int i2c_readByteEEprom(uint16_t addr, uint8_t *data);
extern int i2c_writeByteEEprom(uint16_t addr,uint8_t data);
extern int i2c_readHwordEEprom(uint16_t addr, uint16_t *data);
extern int i2c_writeHwordEEprom(uint16_t addr,uint16_t data);

#endif

