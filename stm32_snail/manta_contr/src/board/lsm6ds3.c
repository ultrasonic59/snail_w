#include "manta_contr_brd.h"
#include "lsm6ds3.h"

extern int I2C_Mem_Read(I2C_TypeDef* I2Cx, uint8_t sl_addr,uint8_t *buff,uint8_t rd_addr,uint16_t num);
extern int I2C_Memory_Write(I2C_TypeDef* I2Cx, uint8_t sl_addr,uint8_t *buff,uint8_t wr_addr,uint16_t num);
////===============================================================================
static int LSM6DS3_Verify_XL_Settings(uint8_t XL_Rate, uint8_t XL_Range, uint8_t XL_Filter) 
{
if((XL_Rate < XL_12_5Hz) || (XL_Rate > XL_6660Hz))
  return LSM6DS3_FAIL_PARAMETERS;
////else if((XL_Range < XL_RANGE_2G) || (XL_Range > XL_RANGE_8G))
else if((XL_Range > XL_RANGE_8G))
  return LSM6DS3_FAIL_PARAMETERS;
///else if((XL_Filter < XL_FILTER_400Hz) || (XL_Filter > XL_FILTER_50Hz))
else if( (XL_Filter > XL_FILTER_50Hz))
  return LSM6DS3_FAIL_PARAMETERS;
return LSM6DS3_OK;
}
static int LSM6DS3_Verify_GS_Settings(uint8_t GS_Rate, uint8_t GS_Range) 
{
if((GS_Rate < GS_12_5Hz) || (GS_Rate > GS_1666Hz))
  return LSM6DS3_FAIL_PARAMETERS;
////else if((GS_Range < GS_RANGE_250dps) || (GS_Range > GS_RANGE_2000dps) || (GS_Range == 3) || (GS_Range == 5))
else if( (GS_Range > GS_RANGE_2000dps) || (GS_Range == 3) || (GS_Range == 5))
  return LSM6DS3_FAIL_PARAMETERS;
return LSM6DS3_OK;
}
////==================================================

int LSM6DS3_Detect(void)
{
int rez=0;  
uint8_t btmp;
rez= I2C_Mem_Read(GYRO_I2C, LSM6DS3_I2C_ADDRESS,&btmp,LSM6DS3_XL_GS_WHO_AM_I_REG,1);
if(rez<0)
  return rez;
if(btmp==LSM6DS3_WHO_I_AM_RESPONSE)
  return 0;
else 
  return -11;
}
////===============================================================================
int LSM6DS3_rd_reg(uint16_t reg,uint8_t *data,uint16_t size)
{
return I2C_Mem_Read(GYRO_I2C, LSM6DS3_I2C_ADDRESS,data,(0x00FF & reg),size);  
}
int LSM6DS3_wr_and_verify(uint16_t reg, uint8_t* data, uint16_t size) 
{
uint8_t ii=0;  
uint8_t compare[32] = {0xFF};
if(size > sizeof(compare))
  return -1;
if(I2C_Memory_Write(GYRO_I2C,LSM6DS3_I2C_ADDRESS,data,(0x00FF & reg),size)<0)
  return -2;
if(I2C_Mem_Read(GYRO_I2C, LSM6DS3_I2C_ADDRESS,compare,(0x00FF & reg),size)<0)
  return -3;
for(ii=0; ii < size; ii++) 
  {
  if(compare[ii] != data[ii])
    return -4;
  }
return 0;
}
////===================================================================
int LSM6DS3_XL_Start(uint8_t XL_Rate, uint8_t XL_Scale, uint8_t XL_Filter) 
{
uint8_t byte = (XL_Rate << 4) | ((XL_Scale << 2) & 0x0F) | (XL_Filter & 0x03);

if(LSM6DS3_Verify_XL_Settings(XL_Rate, XL_Scale, XL_Filter) !=  LSM6DS3_OK)
  return LSM6DS3_FAIL_PARAMETERS;
if(LSM6DS3_wr_and_verify(LSM6DS3_XL_GS_CTRL1_XL, &byte, sizeof(byte)) ==  LSM6DS3_OK)
  return LSM6DS3_OK;
return LSM6DS3_FAIL;
}
int LSM6DS3_XL_Stop(void) 
{
uint8_t byte = XL_POWER_DOWN;

if(LSM6DS3_wr_and_verify(LSM6DS3_XL_GS_CTRL1_XL, &byte, sizeof(byte)) ==  LSM6DS3_OK)
  return LSM6DS3_OK;
return LSM6DS3_FAIL;
}

////===================================================================
int LSM6DS3_XL_GetMeasurements(LSM6DS3_IMU_measurements *data) 
{
uint8_t bytes[6] = {0};

if(LSM6DS3_rd_reg(LSM6DS3_XL_GS_OUTX_L_XL, bytes, sizeof(bytes)) == LSM6DS3_OK) 
  {
  data->XL_x = (int16_t) (bytes[1]<<8 | bytes[0]);
  data->XL_y = (int16_t) (bytes[3]<<8 | bytes[2]);
  data->XL_z = (int16_t) (bytes[5]<<8 | bytes[4]);
  return LSM6DS3_OK;
  }
return LSM6DS3_FAIL;
}


/*
 * @brief  Start the gyroscope with desired settings
 * @param  GS_Rate: Output data rate
 * 					- GS_12_5Hz
 * 					- GS_26Hz
 * 					- GS_52Hz
 * 					- GS_104Hz
 * 					- GS_208Hz
 * 					- GS_416Hz
 * 					- GS_833Hz
 * 					- GS_1666Hz
 *		   GS_Range: Scale selection
 *		   			- GS_RANGE_125dps
 *		   			- GS_RANGE_250dps
 *		   			- GS_RANGE_500dps
 *		   			- GS_RANGE_1000dps
 *		   			- GS_RANGE_2000dps
 * @retval enum LSM6DS3_Result:
 * 					- LSM6DS3_OK    		   = 0,  Success
 * 					- LSM6DS3_FAIL  		   = 1,  Failed due to HAL
 * 					- LSM6DS3_FAIL_PARAMETERS  = 2,  Failed due to wrong parameters
*/
int LSM6DS3_GS_Start(uint8_t GS_Rate, uint8_t GS_Range) {
	uint8_t byte = (GS_Rate << 4) | ((GS_Range << 1) & 0x0F);

	byte &= 0xFE; /* Always secure the LSB is 0 */
	if(LSM6DS3_Verify_GS_Settings(GS_Rate, GS_Range) !=  LSM6DS3_OK)
		return LSM6DS3_FAIL_PARAMETERS;
	if(LSM6DS3_wr_and_verify(LSM6DS3_XL_GS_CTRL2_G, &byte, sizeof(byte)) ==  LSM6DS3_OK)
		return LSM6DS3_OK;
	return LSM6DS3_FAIL;
}

/*
 * @brief  Disable the gyroscope
 * @param  None
 * @retval enum LSM6DS3_Result:
 * 					- LSM6DS3_OK    		   = 0,  Success
 * 					- LSM6DS3_FAIL  		   = 1,  Failed due to HAL
*/
int LSM6DS3_GS_Stop(void) 
{
uint8_t byte = GS_POWER_DOWN;

if(LSM6DS3_wr_and_verify(LSM6DS3_XL_GS_CTRL2_G, &byte, sizeof(byte)) ==  LSM6DS3_OK)
  return LSM6DS3_OK;
return LSM6DS3_FAIL;
}
/*
 * @brief  Refresh the Gyroscope data
 * @param  None
 * @retval enum LSM6DS3_Result:
* 					- LSM6DS3_OK    		   = 0,  Success
 * 					- LSM6DS3_FAIL  		   = 1,  Failed due to HAL
*/
int LSM6DS3_GS_GetMeasurements(LSM6DS3_IMU_measurements *data) 
{
uint8_t bytes[6] = {0};

if(LSM6DS3_rd_reg(LSM6DS3_XL_GS_OUTX_L_GS, bytes, sizeof(bytes)) == LSM6DS3_OK) 
  {
  data->GS_x = (int16_t) (bytes[1]<<8 | bytes[0]);
  data->GS_y = (int16_t) (bytes[3]<<8 | bytes[2]);
  data->GS_z = (int16_t) (bytes[5]<<8 | bytes[4]);
  return LSM6DS3_OK;
  }
return LSM6DS3_FAIL;
}

/*
 * @brief  Refresh the IMU values
 * @param  None
 * @retval enum LSM6DS3_Result:
* 					- LSM6DS3_OK    		   = 0,  Success
 * 					- LSM6DS3_FAIL  		   = 1,  Failed due to HAL
*/
int LSM6DS3_IMU_GetMeasurements(LSM6DS3_IMU_measurements *data) 
{
uint8_t bytes[14] = {0};

if(LSM6DS3_rd_reg(LSM6DS3_XL_GS_OUT_TEMP_L, bytes, sizeof(bytes)) == LSM6DS3_OK) 
  {
  data->Temperature = (int16_t) (bytes[1]<<8  | bytes[0]);
  data->GS_x 		 = (int16_t) (bytes[3]<<8  | bytes[2]);
  data->GS_y 		 = (int16_t) (bytes[5]<<8  | bytes[4]);
  data->GS_z 		 = (int16_t) (bytes[7]<<8  | bytes[6]);
  data->XL_x 		 = (int16_t) (bytes[9]<<8  | bytes[8]);
  data->XL_y 		 = (int16_t) (bytes[11]<<8 | bytes[10]);
  data->XL_z 		 = (int16_t) (bytes[13]<<8 | bytes[12]);
  return LSM6DS3_OK;
  }
return LSM6DS3_FAIL;
}

uint8_t LSM6DS3_check_chng(LSM6DS3_IMU_measurements *data_a
                           ,LSM6DS3_IMU_measurements *data_b)
{
uint8_t rez=0; 
if(data_a->XL_x != data_b->XL_x)
  rez|=(0x1<<0);
if(data_a->XL_y != data_b->XL_y)
  rez|=(0x1<<1);
if(data_a->XL_z != data_b->XL_z)
  rez|=(0x1<<2);
if(data_a->GS_x != data_b->GS_x)
  rez|=(0x1<<3);
if(data_a->GS_y != data_b->GS_y)
  rez|=(0x1<<4);
if(data_a->GS_z != data_b->GS_z)
  rez|=(0x1<<5);
if(data_a->Temperature != data_b->Temperature)
  rez|=(0x1<<6);
return rez;
}
#if 0
/*
 * @brief  Get the value of X axe (Accelerometer)
 * @param  units: Select the units to be returned
 * 					- 0:  Selected units are g
 * 					- 1:  Selected units are mg
 * 					- >1: Invalid. Will return zero
 * @retval float: Value of X axe on g or mg
*/
float LSM6DS3_GetXL_X_Float(uint8_t units) {
	float mg_lsb = 0;
	switch(LSM6DS3_parameters.XL_range)
	{
		case XL_RANGE_2G:
			mg_lsb = 0.061f;
			break;
		case XL_RANGE_4G:
			mg_lsb = 0.122f;
			break;
		case XL_RANGE_8G:
			mg_lsb = 0.244f;
			break;
		case XL_RANGE_16G:
			mg_lsb = 0.488f;
			break;
		default:
			mg_lsb = 0.000f; /* Should never comes here */
			break;
	}
	if(units == LSM6DS3_UNITS_G)
		return (LSM6DS3_data.XL_x * mg_lsb / 1000.0f);
	else
		return (LSM6DS3_data.XL_x * mg_lsb);
}

/*
 * @brief  Get the value of Y axe (Accelerometer)
 * @param  units: Select the units to be returned
 * 					- 0:  Selected units are g
 * 					- 1:  Selected units are mg
 * 					- >1: Invalid. Will return zero
 * @retval float: Value of Y axe on g or mg
*/
float LSM6DS3_GetXL_Y_Float(uint8_t units) {
	float mg_lsb = 0;

	switch(LSM6DS3_parameters.XL_range)
	{
		case XL_RANGE_2G:
			mg_lsb = 0.061f;
			break;
		case XL_RANGE_4G:
			mg_lsb = 0.122f;
			break;
		case XL_RANGE_8G:
			mg_lsb = 0.244f;
			break;
		case XL_RANGE_16G:
			mg_lsb = 0.488f;
			break;
		default:
			mg_lsb = 0.000f; /* Should never comes here */
			break;
	}
	if(units == LSM6DS3_UNITS_G)
		return (LSM6DS3_data.XL_y * mg_lsb / 1000.0f);
	else
		return (LSM6DS3_data.XL_y * mg_lsb);
}

/*
 * @brief  Get the value of Z axe (Accelerometer)
 * @param  units: Select the units to be returned
 * 					- 0:  Selected units are g
 * 					- 1:  Selected units are mg
 * 					- >1: Invalid. Will return zero
 * @retval float: Value of Z axe on g or mg
*/
float LSM6DS3_GetXL_Z_Float(uint8_t units) {
	float mg_lsb = 0;

	switch(LSM6DS3_parameters.XL_range)
	{
		case XL_RANGE_2G:
			mg_lsb = 0.061f;
			break;
		case XL_RANGE_4G:
			mg_lsb = 0.122f;
			break;
		case XL_RANGE_8G:
			mg_lsb = 0.244f;
			break;
		case XL_RANGE_16G:
			mg_lsb = 0.488f;
			break;
		default:
			mg_lsb = 0.000f; /* Should never comes here */
			break;
	}
	if(units == LSM6DS3_UNITS_G)
		return (LSM6DS3_data.XL_z * mg_lsb / 1000.0f);
	else
		return (LSM6DS3_data.XL_z * mg_lsb);
}

/*
 * @brief  Get the raw data of X axe (Gyroscope)
 * @param  None
 * @retval int16_t: Raw data of X axe
*/
int16_t LSM6DS3_GetGS_X_Int16(void) {
	return LSM6DS3_data.GS_x;
}

/*
 * @brief  Get the raw data of Y axe (Gyroscope)
 * @param  None
 * @retval int16_t: Raw data of Y axe
*/
int16_t LSM6DS3_GetGS_Y_Int16(void) {
	return LSM6DS3_data.GS_y;
}

/*
 * @brief  Get the raw data of Z axe (Gyroscope)
 * @param  None
 * @retval int16_t: Raw data of Z axe
*/
int16_t LSM6DS3_GetGS_Z_Int16(void) {
	return LSM6DS3_data.GS_z;
}

/*
 * @brief  Get the raw data of temperature
 * @param  None
 * @retval int16_t: Raw data of temperature
*/
int16_t LSM6DS3_Temperature_Int16(void) {
	return LSM6DS3_data.Temperature;
}

/*
 * @brief  Get the temperature
 * @param  None
 * @retval float: Temperature in C (Celsius)
*/
float LSM6DS3_Temperature_Celsius(void) {
	return ((float)LSM6DS3_data.Temperature / 16.0f + 25.0f);
}

/*
 * @brief  Get the value of X axe (Gyroscope)
 * @param  units: Select the units to be returned
 * 					- 0: Selected units are dps
 * 					- 1: Selected units are mdps
 * 					- >1: Invalid. Will return zero
 * @retval float: Value of X axe on dps or mdps
*/
float LSM6DS3_GetGS_X_Float(uint8_t units) {
	float mdps_lsb = 0;

	switch(LSM6DS3_parameters.GS_range)
	{
		case GS_RANGE_125dps:
			mdps_lsb = 4.375f;
			break;
		case GS_RANGE_250dps:
			mdps_lsb = 8.75f;
			break;
		case GS_RANGE_500dps:
			mdps_lsb = 17.50f;
			break;
		case GS_RANGE_1000dps:
			mdps_lsb = 35.0f;
			break;
		case GS_RANGE_2000dps:
			mdps_lsb = 70.f;
			break;
		default:
			mdps_lsb = 0.000f; /* Should never comes here */
			break;
	}
	if(units == LSM6DS3_UNITS_G)
		return (LSM6DS3_data.GS_x * mdps_lsb / 1000.0f);
	else
		return (LSM6DS3_data.GS_x * mdps_lsb);
}

/*
 * @brief  Get the value of Y axe (Gyroscope)
 * @param  units: Select the units to be returned
 * 					- 0: Selected units are dps
 * 					- 1: Selected units are mdps
 * 					- >1: Invalid. Will return zero
 * @retval float: Value of Y axe on dps or mdps
*/
float LSM6DS3_GetGS_Y_Float(uint8_t units) {
	float mdps_lsb = 0;

	switch(LSM6DS3_parameters.GS_range)
	{
		case GS_RANGE_125dps:
			mdps_lsb = 4.375f;
			break;
		case GS_RANGE_250dps:
			mdps_lsb = 8.75f;
			break;
		case GS_RANGE_500dps:
			mdps_lsb = 17.50f;
			break;
		case GS_RANGE_1000dps:
			mdps_lsb = 35.0f;
			break;
		case GS_RANGE_2000dps:
			mdps_lsb = 70.f;
			break;
		default:
			mdps_lsb = 0.000f; /* Should never comes here */
			break;
	}
	if(units == LSM6DS3_UNITS_G)
		return (LSM6DS3_data.GS_y * mdps_lsb / 1000.0f);
	else
		return (LSM6DS3_data.GS_y * mdps_lsb);
}

/*
 * @brief  Get the value of Z axe (Gyroscope)
 * @param  units: Select the units to be returned
 * 					- 0: Selected units are dps
 * 					- 1: Selected units are mdps
 * 					- >1: Invalid. Will return zero
 * @retval float: Value of Z axe on dps or mdps
*/
float LSM6DS3_GetGS_Z_Float(uint8_t units) {
	float mdps_lsb = 0;

	switch(LSM6DS3_parameters.GS_range)
	{
		case GS_RANGE_125dps:
			mdps_lsb = 4.375f;
			break;
		case GS_RANGE_250dps:
			mdps_lsb = 8.75f;
			break;
		case GS_RANGE_500dps:
			mdps_lsb = 17.50f;
			break;
		case GS_RANGE_1000dps:
			mdps_lsb = 35.0f;
			break;
		case GS_RANGE_2000dps:
			mdps_lsb = 70.f;
			break;
		default:
			mdps_lsb = 0.000f; /* Should never comes here */
			break;
	}
	if(units == LSM6DS3_UNITS_G)
		return (LSM6DS3_data.GS_z * mdps_lsb / 1000.0f);
	else
		return (LSM6DS3_data.GS_z * mdps_lsb);
}
#endif
