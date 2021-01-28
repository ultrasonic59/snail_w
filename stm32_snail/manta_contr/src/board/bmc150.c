#include "manta_contr_brd.h"
#include "bmc150.h"

extern int I2C_Mem_Read(I2C_TypeDef* I2Cx, uint8_t sl_addr,uint8_t *buff,uint8_t rd_addr,uint16_t num);
extern int I2C_Memory_Write(I2C_TypeDef* I2Cx, uint8_t sl_addr,uint8_t *buff,uint8_t wr_addr,uint16_t num);
////===============================================================================
/*
 * From the BMC150 datasheet, page 125:
 * "The register address is automatically incremented and, therefore, more
 * than one byte can be sequentially read out. Once a new data read
 * transmission starts, the start address will be set to the register address
 * specified in the latest I2C write command."
 */
static BMC150_error_t read_register(uint16_t addr, uint8_t reg, uint8_t *const data,
			     uint32_t len)
{
 ///	AIR_I2C_ComboRead(addr,&reg,1,data,len);
if(I2C_Mem_Read(MAGN_I2C, addr,data,(0x00FF & reg),len)<0)  
return BMC150_ERROR;
        
return BMC150_OK;
}

static BMC150_error_t write_register(uint16_t addr, uint8_t reg, uint8_t data)
{
///	uint8_t writeData[2] = {reg, data};
///	AIR_I2C_Write(addr,writeData,2);
uint8_t tdata=data;
if(I2C_Memory_Write(MAGN_I2C,addr,&tdata,(0x00FF & reg),1)<0)
  return BMC150_ERROR;
return BMC150_OK;
}

BMC150_error_t BMC150_read_accel(BMC150_accel_t *const accel)
{
	BMC150_error_t rc;
	uint8_t raw_accel[6];

	/* Reading the 6 registers at once. */
	rc = read_register(ACC_ADDR, BMC150_REG_ACCEL_X_LSB, raw_accel,
			   sizeof(raw_accel));
	if (BMC150_OK != rc) {
		return rc;
	}

	accel->x = EXTRACT_ACCEL(raw_accel[1], raw_accel[0]);
	accel->y = EXTRACT_ACCEL(raw_accel[3], raw_accel[2]);
	accel->z = EXTRACT_ACCEL(raw_accel[5], raw_accel[4]);

	return BMC150_OK;
}

BMC150_error_t BMC150_set_accel_mode(BMC150_accel_mode_t mode)
{
	return write_register(ACC_ADDR, BMC150_REG_ACCEL_PMU_RANGE, mode);
}

BMC150_error_t BMC150_set_bandwidth(BMC150_bandwidth_t bw)
{
	return write_register(ACC_ADDR, BMC150_REG_ACCEL_PMU_BW, bw);
}

static BMC150_error_t read_dig_comp(struct compensation *const comp)
{
	uint8_t raw_comp[21];
	BMC150_error_t rc;

	rc = read_register(MAGN_ADDR, BMC150_REG_MAG_DIG_X1, raw_comp,
			   sizeof(raw_comp));
	if (BMC150_OK != rc) {
		return rc;
	}

	comp->x1 = raw_comp[0];
	comp->y1 = raw_comp[1];
	comp->z4 = EXTRACT_UINT16(raw_comp[6], raw_comp[5]);
	comp->x2 = raw_comp[7];
	comp->y2 = raw_comp[8];
	comp->z2 = EXTRACT_UINT16(raw_comp[12], raw_comp[11]);
	comp->z1 = EXTRACT_UINT16(raw_comp[14], raw_comp[13]);
	comp->xyz1 = EXTRACT_UINT16(raw_comp[16], raw_comp[15]);
	comp->z3 = EXTRACT_UINT16(raw_comp[18], raw_comp[17]);
	comp->xy2 = raw_comp[19];
	comp->xy1 = raw_comp[20];

	return BMC150_OK;
}

typedef enum {
	AXIS_X,
	AXIS_Y,
} axis_t;

static int compensate_xy(struct compensation *const comp, int16_t rhall,
			 int16_t raw, axis_t axis)
{
	int inter = 0;
	int value;

	if (rhall != 0) {
		inter = ((int)comp->xyz1 << 14) / rhall - (1 << 14);
	}

	if (BMC150_FLIP_OVERFLOW_ADCVAL == raw) {
		return BMC150_OVERFLOW_OUTPUT;
	}

	value = comp->xy2 * ((inter * inter) >> 7);
	value += inter * ((int)comp->xy1 << 7);
	value >>= 9;
	value += 1 << (8 + 12);
	value *= (int)(AXIS_X == axis ? comp->x2 : comp->y2) + 160;
	value >>= 12;
	value *= raw;
	value >>= 13;
	value += (int)(AXIS_X == axis ? comp->x1 : comp->y1) << 3;

	return value;
}

static int compensate_z(struct compensation *const comp, int rhall, int16_t raw)
{
	int dividend, divisor;
	int value;

	if (BMC150_HALL_OVERFLOW_ADCVAL == raw) {
		return BMC150_OVERFLOW_OUTPUT;
	}

	dividend = (raw - (int)comp->z4) << 15;
	dividend -= (comp->z3 * (rhall - (int)comp->xyz1)) >> 2;
	/* add 1 << 15 to round to next integer. */
	divisor = (int)comp->z1 * (rhall << 1) + (1 << 15);
	divisor >>= 16;
	divisor += (int)comp->z2;
	value = dividend / divisor;
	if (value > (1 << 15) || value < -(1 << 15)) {
		value = BMC150_OVERFLOW_OUTPUT;
	}

	return value;
}

BMC150_error_t BMC150_read_mag(BMC150_mag_t *const mag)
{
	BMC150_error_t rc = BMC150_OK;
	uint8_t raw_mag[8];
	int16_t x, y, z, rhall;

	if (!digital_comp.init) {
		rc = read_dig_comp(&digital_comp);
		if (BMC150_OK == rc) {
			digital_comp.init = 1;
		}
	}

	if (BMC150_OK != rc) {
		return rc;
	}

	rc = read_register(MAGN_ADDR, BMC150_REG_MAG_X_LSB, raw_mag,
			   sizeof(raw_mag));
	if (BMC150_OK != rc) {
		return rc;
	}

	x = EXTRACT_MAG_XY(raw_mag[1], raw_mag[0]);
	y = EXTRACT_MAG_XY(raw_mag[3], raw_mag[2]);
	z = EXTRACT_MAG_Z(raw_mag[5], raw_mag[4]);
	rhall = EXTRACT_RHALL(raw_mag[7], raw_mag[6]);

	mag->x = compensate_xy(&digital_comp, rhall, x, AXIS_X);
	mag->y = compensate_xy(&digital_comp, rhall, y, AXIS_Y);
	mag->z = compensate_z(&digital_comp, rhall, z);

	return BMC150_OK;
}

BMC150_error_t BMC150_mag_set_power(BMC150_mag_power_t power)
{
	return write_register(MAGN_ADDR, BMC150_REG_MAG_POWER_MODES, power);
}

/*
 * These values used for the presets are from Table 6 (page 24) of the
 * BMC150 datasheet.
 */
static const uint8_t operation_modes[] = {
    0,      /* 10 Hz */
    0,      /* 10 Hz */
    0,      /* 10 Hz */
    5 << 3, /* 20 Hz */
};

/* The formula here is repetions = 1 + 2*(mode) */
static const uint8_t repetion_modes_xy[] = {
    1, 3, 7, 23,
};

/* The formula here is repetions = 1 + (mode) */
static const uint8_t repetion_modes_z[] = {
    2, 14, 26, 82,
};

BMC150_error_t BMC150_mag_set_preset(BMC150_mag_preset_t preset)
{
BMC150_error_t rc;

rc = write_register(MAGN_ADDR, BMC150_REG_MAG_OPERATION_MODES,
			    operation_modes[preset]);
if (BMC150_OK != rc) 
  {
		return rc;
  }

	rc = write_register(MAGN_ADDR, BMC150_REG_MAG_REPETION_XY,
			    repetion_modes_xy[preset]);
	if (BMC150_OK != rc) {
		return rc;
	}

	rc = write_register(MAGN_ADDR, BMC150_REG_MAG_REPETION_Z,
			    repetion_modes_z[preset]);
	if (BMC150_OK != rc) {
		return rc;
	}

	return BMC150_OK;
}

int bmc150_detect(void)
{
int rez=0;  
uint8_t btmp;
rez= I2C_Mem_Read(MAGN_I2C, ACC_ADDR,&btmp,BMC150_REG_ACCEL_CHIPID,1);
if(rez<0)
  return rez;
if(btmp==BMC150_ACCEL_CHIPID)
  return 0;
else 
  return -12;
}


#if 1
int BMC150_init(void)
{
//Setup Magnometer
BMC150_mag_set_power(BMC150_MAG_POWER_ACTIVE);
BMC150_mag_set_preset(AIR_BMC150_MAG_PRESET);
//Setup Accelerometer
BMC150_set_accel_mode(AIR_BMC150_ACCEL_MODE);
BMC150_set_bandwidth(AIR_BMC150_BANDWIDTH);
	
return 0;
}
#endif