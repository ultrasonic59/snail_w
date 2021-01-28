#include "manta_contr_brd.h"

I2C_InitTypeDef magn_i2c;
I2C_InitTypeDef gyro_i2c;


void init_i2c(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB1PeriphClockCmd(MAGN_RCC, ENABLE);
RCC_APB1PeriphClockCmd(GYRO_RCC, ENABLE);
RCC_AHB1PeriphClockCmd(MAGN_SDA_RCC_AHB, ENABLE);
RCC_AHB1PeriphClockCmd(GYRO_SDA_RCC_AHB, ENABLE);
////=========== MAGN ============================
#if 1
magn_i2c.I2C_ClockSpeed = 100000; 
magn_i2c.I2C_Mode = I2C_Mode_I2C;
magn_i2c.I2C_DutyCycle = I2C_DutyCycle_2;

magn_i2c.I2C_OwnAddress1 = H_MAGN_ADDR;
magn_i2c.I2C_Ack = I2C_Ack_Disable;
magn_i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
I2C_Init(MAGN_I2C, &magn_i2c);

GPIO_InitStructure.GPIO_Pin = MAGN_SCL_PIN|MAGN_SDA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
GPIO_Init( MAGN_SCL_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(MAGN_SCL_GPIO,MAGN_SCL_PIN_SRC,MAGN_SCL_AF);
GPIO_PinAFConfig(MAGN_SDA_GPIO,MAGN_SDA_PIN_SRC,MAGN_SCL_AF);
I2C_Cmd(MAGN_I2C, ENABLE);
#endif
////=========== GIRO ============================
gyro_i2c.I2C_ClockSpeed = 100000; 
gyro_i2c.I2C_Mode = I2C_Mode_I2C;
gyro_i2c.I2C_DutyCycle = I2C_DutyCycle_2;

gyro_i2c.I2C_OwnAddress1 = GYRO_ADDR;
gyro_i2c.I2C_Ack = I2C_Ack_Disable;
gyro_i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
I2C_DeInit(GYRO_I2C);
I2C_Init(GYRO_I2C, &gyro_i2c);

GPIO_InitStructure.GPIO_Pin = GYRO_SCL_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
GPIO_Init( GYRO_SCL_GPIO, &GPIO_InitStructure );

GPIO_InitStructure.GPIO_Pin = GYRO_SDA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
GPIO_Init( GYRO_SDA_GPIO, &GPIO_InitStructure );

GPIO_PinAFConfig(GYRO_SCL_GPIO,GYRO_SCL_PIN_SRC,GYRO_SCL_AF);
GPIO_PinAFConfig(GYRO_SDA_GPIO,GYRO_SDA_PIN_SRC,GYRO_SDA_AF);
I2C_Cmd(GYRO_I2C, ENABLE);

}

int I2C_Mem_Read(I2C_TypeDef* I2Cx, uint8_t sl_addr,uint8_t *buff,uint8_t rd_addr,uint16_t num)
{
uint32_t timeout = I2C_TIMEOUT_MAX;
timeout = I2C_TIMEOUT_MAX;
while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
  {
  if ((timeout--) == 0) 
    return -1;
  }
I2C_GenerateSTART(I2Cx, ENABLE);
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
  if ((timeout--) == 0) 
    return -2;
  }
I2C_Send7bitAddress(I2Cx, sl_addr<<1, I2C_Direction_Transmitter);
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
  if ((timeout--) == 0) 
    return -3;
  } 
I2C_SendData(I2Cx, rd_addr);
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
  if ((timeout--) == 0) 
    return -4;
  }
I2C_GenerateSTART(I2Cx, ENABLE);
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
  if ((timeout--) == 0) 
    return -5;
  }
I2C_Send7bitAddress(I2Cx, sl_addr<<1, I2C_Direction_Receiver);
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
  if ((timeout--) == 0) 
    return -6;
  }
while(num)
  {
  if(num==1)
    {
    I2C_AcknowledgeConfig(I2Cx, DISABLE);
    I2C_GenerateSTOP(I2Cx, ENABLE);
    }
////	I2C_AcknowledgeConfig(I2Cx, DISABLE);
    timeout = I2C_TIMEOUT_MAX;
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
      {
      if ((timeout--) == 0) 
        return -7;
      }
    *buff=I2C_ReceiveData(I2Cx);
    buff++;
    num--;
  }
I2C_AcknowledgeConfig(I2Cx, ENABLE);
return num;	
}
////===============================================================================
int I2C_Memory_Write(I2C_TypeDef* I2Cx, uint8_t sl_addr,uint8_t *buff,uint8_t wr_addr,uint16_t num)
{
uint32_t timeout = I2C_TIMEOUT_MAX;
timeout = I2C_TIMEOUT_MAX;
while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
  {
  if ((timeout--) == 0) 
    return -1;
  }
I2C_GenerateSTART(I2Cx, ENABLE);
	
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
  if ((timeout--) == 0) 
    return -2;
  }
I2C_Send7bitAddress(I2Cx, sl_addr<<1, I2C_Direction_Transmitter);
	
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
  if ((timeout--) == 0) 
    return -3;
  } 
I2C_SendData(I2Cx, wr_addr);
timeout = I2C_TIMEOUT_MAX;
while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
  if ((timeout--) == 0) 
    return -4;
  }
while(num)
  {
  I2C_SendData(I2Cx, *buff);
  timeout = I2C_TIMEOUT_MAX;
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
    if ((timeout--) == 0) 
      return -5;
    }
  num--;
  buff++;
  }
I2C_GenerateSTOP(I2Cx, ENABLE);
return 0;	
}

////I2C_GenerateSTOP(I2Cx, ENABLE)