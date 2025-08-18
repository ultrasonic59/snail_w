#ifndef __I2C_H__
#define __I2C_H__
#include <string.h>
#include <stdlib.h>
#include "debug.h"

#include "../brd/enc6701_brd.h"
#define  I2C_CR1_START                       ((uint16_t)0x0100)            /*!<Start Generation */
#define  I2C_CR1_STOP                        ((uint16_t)0x0200)            /*!<Stop Generation */
#define  I2C_CR1_ACK                         ((uint16_t)0x0400)            /*!<Acknowledge Enable */
#
#define  I2C_SR1_SB                          ((uint16_t)0x0001)            /*!<Start Bit (Master mode) */
#define  I2C_SR1_ADDR                        ((uint16_t)0x0002)            /*!<Address sent (master mode)/matched (slave mode) */
#define  I2C_SR1_RXNE                        ((uint16_t)0x0040)            /*!<Data Register not Empty (receivers) */

#define  I2C_SR1_TXE                         ((uint16_t)0x0080)            /*!<Data Register Empty (transmitters) */

#define  I2C_SR2_BUSY                        ((uint16_t)(0x1<<1))            /*!<Bus Busy */



#define MAX_WAIT  50000
///========= MT6701 ======================
#define ENCODER_ID   0x0c
#define ENCODER_HVAL 0x03
#define ENCODER_LVAL 0x04

extern void IIC_Init(u32 bound);
extern int read_encoder_val(uint16_t *oval);

#endif ///__I2C_H__
