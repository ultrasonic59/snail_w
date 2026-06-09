
#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#ifdef MSTEP_BRD
#include "stm32f2xx.h"                  // Device header
#include "stm32f2xx_conf.h"
#include "stm32f2xx_i2c.h"
#include "stm32f2xx_rcc.h"

#else
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"
#endif
#define MAX_WAIT  500000
#define EEPROM_ADDR 0xa0
#define DELAY_WRITE  4000  ///~6ms
///========= MT6701 ======================
#define ENCODER_ID   0x0c
#define ENCODER_HVAL 0x03
#define ENCODER_LVAL 0x04

extern void I2C_Eeprom_Init(void) ;
extern int i2c_readByte(I2C_TypeDef* I2Cx,uint8_t haddr,uint16_t addr, uint8_t *data);
extern int i2c_writeByte(I2C_TypeDef* I2Cx,uint8_t haddr,uint16_t addr,uint8_t data);
extern int i2c_readByteEEprom(uint16_t addr, uint8_t *data);
extern int i2c_writeByteEEprom(uint16_t addr,uint8_t data);
extern int i2c_readHwordEEprom(uint16_t addr, uint16_t *data);
extern int i2c_writeHwordEEprom(uint16_t addr,uint16_t data);
extern void I2C_encoder_Init(void) ;
extern int read_encoder_val(uint16_t *oval);

#endif

