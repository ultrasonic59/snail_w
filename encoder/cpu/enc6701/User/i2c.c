
#include "i2c.h"
///====================================================================
/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void IIC_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitTSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_OwnAddress1 = 0;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture );
}
volatile uint32_t wait_time=0;
int _i2c_readByteEncoder(uint16_t addr,uint8_t *o_data)
{
    while( I2C_GetFlagStatus( I2C1, I2C_FLAG_BUSY ) != RESET );
    I2C_GenerateSTART( I2C1, ENABLE );

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress( I2C1, ENCODER_ID, I2C_Direction_Transmitter );

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );


    return 0;
}

int i2c_readByteEncoder(uint16_t addr,uint8_t *o_data)
{
uint8_t temp=0;
////uint16_t tmp;

wait_time=0;
while( I2C_GetFlagStatus( I2C1, I2C_FLAG_BUSY ) != RESET ){
    wait_time++;
    if(wait_time>=MAX_WAIT){
      break;
    }
};
if(wait_time>=MAX_WAIT)
     return -1;
I2C_GenerateSTART( I2C1, ENABLE );
wait_time=0;
while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) ){
    wait_time++;
    if(wait_time>=MAX_WAIT){
      break;
    }
    };
if(wait_time>=MAX_WAIT)
   return -2;

I2C1->DATAR =ENCODER_ID;
wait_time=0;
while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ){
    wait_time++;
    if(wait_time>=MAX_WAIT){
      break;
   }
};
if(wait_time>=MAX_WAIT)
   return -3;
/*
tmp=I2Cx->SR2;
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_TXE)){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -4;
*/
    I2C_SendData( I2C1, (uint8_t)(addr&0xFF) );
    wait_time=0;
    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ){
        wait_time++;
        if(wait_time>=MAX_WAIT){
          break;
        }
    }
    if(wait_time>=MAX_WAIT)
         return -5;
/*
    I2Cx->CR1|=I2C_CR1_START;
    wait_time=0;

    while(!(I2Cx->SR1&I2C_SR1_SB)){
       wait_time++;
      if(wait_time>=MAX_WAIT){
        break;
      }
    }
    if(wait_time>=MAX_WAIT)
         return -6;
*/

    I2C_GenerateSTART( I2C1, ENABLE );
   while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) ){
       wait_time++;
       if(wait_time>=MAX_WAIT){
         break;
       }
     }
   if(wait_time>=MAX_WAIT)
        return -6;
   I2C1->DATAR =ENCODER_ID|0x1;
   wait_time=0;
   while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ){
       wait_time++;
       if(wait_time>=MAX_WAIT){
         break;
      }
   };
   if(wait_time>=MAX_WAIT)
      return -7;
   I2C_GenerateSTOP( I2C1, ENABLE );

 ////   I2C_Send7bitAddress( I2C1, 0XA0, I2C_Direction_Receiver );
 ////   while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) );
  while( I2C_GetFlagStatus( I2C1, I2C_FLAG_RXNE ) ==  RESET ){
      wait_time++;
      if(wait_time>=MAX_WAIT){
        break;
      }
   };
////    I2C_AcknowledgeConfig( I2C1, DISABLE );
  if(wait_time>=MAX_WAIT)
       return -8;

    temp = I2C_ReceiveData( I2C1 );
  I2C_GenerateSTOP( I2C1, ENABLE );
if(o_data)
    *o_data=temp;
return 0;
}

int read_encoder_val(uint16_t *oval)
   {
   int rez;
   uint16_t htmp;
   uint8_t btmp;
   rez=i2c_readByteEncoder(ENCODER_HVAL,&btmp);
   if(rez==0)
      {
        htmp=btmp;
        rez=i2c_readByteEncoder(ENCODER_LVAL,&btmp);
       if(rez==0)
         {
         htmp<<=8;
         htmp|=btmp;
         htmp>>=2;
         if(oval)
           *oval=htmp;
     ///    printk(": data[%x] ",htmp);
         }
      }
   ////  else
   ////     printk(": error[%d] ",rez);
   ////    }
   return rez;
   }




