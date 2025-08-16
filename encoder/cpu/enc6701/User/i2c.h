#ifndef __I2C_H__
#define __I2C_H__
#include <string.h>
#include <stdlib.h>
#include "debug.h"

#include "../brd/enc6701_brd.h"
#define MAX_WAIT  500000
///========= MT6701 ======================
#define ENCODER_ID   0x0c
#define ENCODER_HVAL 0x03
#define ENCODER_LVAL 0x04

extern void IIC_Init(u32 bound);
extern int read_encoder_val(uint16_t *oval);

#endif ///__I2C_H__
