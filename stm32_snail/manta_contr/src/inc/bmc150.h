/*
 * Copyright (c) 2015, Intel Corporation
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the Intel Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL CORPORATION OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BMC150_H__
#define __BMC150_H__

#include <stdint.h>
////#include "../i2c/i2c.h"
///#include "bmc150_config.h"

typedef enum {
	BMC150_OK = (uint8_t) 0,
	BMC150_ERROR = !BMC150_OK
} BMC150_error_t;

///static uint16_t accel_addr = 0x10;
///static uint16_t magneto_addr = 0x12;
#define ACC_ADDR        10
#define MAGN_ADDR       12
/**
 * Range of the accelerometer measures.
 */
typedef enum {
	BMC150_MODE_2G = 0x3,
	BMC150_MODE_4G = 0x5,
	BMC150_MODE_8G = 0x8,
	BMC150_MODE_16G = 0xC,
} BMC150_accel_mode_t;

/**
 * Size of the data filter.
 */
typedef enum {
	BMC150_BANDWIDTH_64MS = 0x8,
	BMC150_BANDWIDTH_32MS = 0x9,
	BMC150_BANDWIDTH_16MS = 0xA,
	BMC150_BANDWIDTH_8MS = 0xB,
	BMC150_BANDWIDTH_4MS = 0xC,
	BMC150_BANDWIDTH_2MS = 0xD,
	BMC150_BANDWIDTH_1MS = 0xE,
	BMC150_BANDWIDTH_500US = 0xF,
} BMC150_bandwidth_t;

typedef enum {
	BMC150_MAG_POWER_SUSPEND = 0x0,
	BMC150_MAG_POWER_ACTIVE = 0x1,
} BMC150_mag_power_t;

typedef enum {
	BMC150_MAG_PRESET_REGULAR,
	BMC150_MAG_PRESET_LOW_POWER,
	BMC150_MAG_PRESET_ENHANCED,
	BMC150_MAG_PRESET_HIGH_ACCURACY,
} BMC150_mag_preset_t;

typedef struct {
	int16_t x, y, z;
} BMC150_accel_t;

typedef struct {
	int x, y, z;
} BMC150_mag_t;

////=============================
#define AIR_BMC150_MAG_PRESET   BMC150_MAG_PRESET_HIGH_ACCURACY
#define AIR_BMC150_ACCEL_MODE   BMC150_MODE_2G
#define AIR_BMC150_BANDWIDTH    BMC150_BANDWIDTH_500US
////=============================

#define BMC150_REG_ACCEL_CHIPID 0x00
#define BMC150_REG_ACCEL_X_LSB 0x02
#define BMC150_REG_ACCEL_X_MSB 0x03
#define BMC150_REG_ACCEL_Y_LSB 0x04
#define BMC150_REG_ACCEL_Y_MSB 0x05
#define BMC150_REG_ACCEL_Z_LSB 0x06
#define BMC150_REG_ACCEL_Z_MSB 0x07
#define BMC150_REG_ACCEL_PMU_RANGE 0x0F
#define BMC150_REG_ACCEL_PMU_BW 0x10

#define BMC150_ACCEL_CHIPID 0xFA
///=================================
#define BMC150_REG_MAG_CHIPID 0x40
#define BMC150_REG_MAG_X_LSB 0x42
#define BMC150_REG_MAG_X_MSB 0x43
#define BMC150_REG_MAG_Y_LSB 0x44
#define BMC150_REG_MAG_Y_MSB 0x45
#define BMC150_REG_MAG_Z_LSB 0x46
#define BMC150_REG_MAG_Z_MSB 0x47
#define BMC150_REG_MAG_RHALL_LSB 0x48
#define BMC150_REG_MAG_RHALL_MSB 0x49
#define BMC150_REG_MAG_POWER_MODES 0x4B
#define BMC150_REG_MAG_OPERATION_MODES 0x4C
#define BMC150_REG_MAG_REPETION_XY 0x51
#define BMC150_REG_MAG_REPETION_Z 0x52

#define BMC150_MAG_CHIPID 0x32
///=======================================
/* Undocumented registers necessary for temperature compensation. */
#define BMC150_REG_MAG_DIG_X1 0x5d
#define BMC150_REG_MAG_DIG_Y1 0x5e
#define BMC150_REG_MAG_DIG_Z4_LSB 0x62
#define BMC150_REG_MAG_DIG_Z4_MSB 0x63
#define BMC150_REG_MAG_DIG_X2 0x64
#define BMC150_REG_MAG_DIG_Y2 0x65
#define BMC150_REG_MAG_DIG_Z2_LSB 0x68
#define BMC150_REG_MAG_DIG_Z2_MSB 0x69
#define BMC150_REG_MAG_DIG_Z1_LSB 0x6a
#define BMC150_REG_MAG_DIG_Z1_MSB 0x6b
#define BMC150_REG_MAG_DIG_XYZ1_LSB 0x6c
#define BMC150_REG_MAG_DIG_XYZ1_MSB 0x6d
#define BMC150_REG_MAG_DIG_Z3_LSB 0x6e
#define BMC150_REG_MAG_DIG_Z3_MSB 0x6f
#define BMC150_REG_MAG_DIG_XY2 0x70
#define BMC150_REG_MAG_DIG_XY1 0x71

/* Overflow */
#define BMC150_FLIP_OVERFLOW_ADCVAL (-4096)
#define BMC150_HALL_OVERFLOW_ADCVAL (-16384)
#define BMC150_OVERFLOW_OUTPUT (0x8000)

#define EXTRACT_ACCEL(msb, lsb) ((int16_t)((lsb) | (msb) << 8) >> 4)

#define EXTRACT_MAG_XY(msb, lsb) ((int16_t)((lsb) | (msb) << 8) >> 3)
#define EXTRACT_MAG_Z(msb, lsb) ((int16_t)((lsb) | (msb) << 8) >> 1)
#define EXTRACT_RHALL(msb, lsb) ((int16_t)((lsb) | (msb) << 8) >> 2)
#define EXTRACT_UINT16(msb, lsb) ((uint16_t)((lsb) | (msb) << 8))

static struct compensation {
	int8_t x1, y1, x2, y2, xy1, xy2;
	uint16_t z1, z2, z3, z4, xyz1;
	uint8_t init;
} digital_comp;

int BMC150_init(void);

BMC150_error_t BMC150_read_accel(BMC150_accel_t *const accel);

BMC150_error_t BMC150_set_accel_mode(BMC150_accel_mode_t mode);

BMC150_error_t BMC150_set_bandwidth(BMC150_bandwidth_t bw);

BMC150_error_t BMC150_read_mag(BMC150_mag_t *const mag);

BMC150_error_t BMC150_mag_set_power(BMC150_mag_power_t power);

BMC150_error_t BMC150_mag_set_preset(BMC150_mag_preset_t preset);

#endif /* __BMC150_H__ */
