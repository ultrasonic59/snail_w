
#include "board.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "queue.h"
   
void I2C_Eeprom_Init(void) {
  GPIO_InitTypeDef  GPIO_InitStructure;
  I2C_InitTypeDef   I2C_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C_EEPROM, ENABLE);
  //Reset the Peripheral
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C_EEPROM, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C_EEPROM, DISABLE);
  RCC_AHB1PeriphClockCmd(SDA_EEPROM_PIN_RCC, ENABLE);
  RCC_AHB1PeriphClockCmd(SCL_EEPROM_PIN_RCC, ENABLE);
  //Configure and initialize the GPIOs
  GPIO_InitStructure.GPIO_Pin = SDA_EEPROM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //PP; 
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; //UP; 
  GPIO_Init(SDA_EEPROM_PIN_GPIO, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = SCL_EEPROM_PIN;
  GPIO_Init(SCL_EEPROM_PIN_GPIO, &GPIO_InitStructure);
  GPIO_PinAFConfig(SCL_EEPROM_PIN_GPIO, SCL_EEPROM_NPIN, GPIO_AF_I2C_EEPROM);
  GPIO_PinAFConfig(SDA_EEPROM_PIN_GPIO, SDA_EEPROM_NPIN, GPIO_AF_I2C_EEPROM);
  //Configure and Initialize the I2C
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00; //We are the master. We don't need this
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 100000;  //
  
  //Initialize the Peripheral
  I2C_Init(I2C_EEPROM, &I2C_InitStructure);
  // I2C Peripheral Enable
  I2C_Cmd(I2C_EEPROM, ENABLE);
  

#if 0 
  
  //Enable the GPIOs for the SCL/SDA Pins
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIO_SCL | RCC_AHB1Periph_GPIO_SDA, ENABLE);
  
  //Configure and initialize the GPIOs
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SCL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //PP; 
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; //UP; 
  GPIO_Init(GPIO_SCL, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SDA;
  GPIO_Init(GPIO_SDA, &GPIO_InitStructure);
  
  //Connect GPIO pins to peripheral
  GPIO_PinAFConfig(GPIO_SCL, GPIO_PinSource_SCL, GPIO_AF_I2Cx);
	GPIO_PinAFConfig(GPIO_SDA, GPIO_PinSource_SDA, GPIO_AF_I2Cx);
  
#endif
///  return; 
}
   
   
#if 0
void i2c_init(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; //enable gpiob clock
RCC->APB1ENR|=RCC_APB1ENR_I2CxEN; //enable i2c1 clock
GPIOB->MODER|=0xA0000; //set pb8and9 to alternative function
GPIOB->AFR[1]|=0x44;
////???GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9; //set pb8 and pb9 as open drain
I2Cx->CR1=I2C_CR1_SWRST;
I2Cx->CR1&=~I2C_CR1_SWRST;	
I2Cx->CR2|=50;
I2Cx->CCR|=0x2|(1<<15)|(1<<14); 
I2Cx->TRISE=20; //output max rise 
I2Cx->CR1|=I2C_CR1_PE;
}
#endif
volatile uint32_t wait_time;
int i2c_readByte(I2C_TypeDef* I2Cx,uint8_t haddr,uint16_t addr, uint8_t *data)
{
#if 1
uint16_t tmp;
wait_time=0;
while(I2Cx->SR2&I2C_SR2_BUSY){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -1;
I2Cx->CR1|=I2C_CR1_START;
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_SB)){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -2;
tmp=addr>>8;
tmp&=0x3;
tmp<<=1;
I2Cx->DR=haddr|tmp;
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_ADDR)){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -3;
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
I2Cx->DR=addr&0xff;
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_TXE)){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -5;
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
I2Cx->DR=haddr|0x1;
wait_time=0;

while(!(I2Cx->SR1&I2C_SR1_ADDR)){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -7;
I2Cx->CR1&=~I2C_CR1_ACK;
tmp =I2Cx->SR2;
I2Cx->CR1|=I2C_CR1_STOP;
wait_time=0;

while(!(I2Cx->SR1&I2C_SR1_RXNE)){
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -8;

*data = I2Cx->DR;
#endif
return 0;
}

int i2c_writeByte(I2C_TypeDef* I2Cx,uint8_t haddr,uint16_t addr,uint8_t data)
{
#if 1
volatile uint16_t tmp;
wait_time=0;

while(I2Cx->SR2&I2C_SR2_BUSY){          /*wait until bus not busy*/
 wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
  
}
if(wait_time>=MAX_WAIT)
     return -1;
I2Cx->CR1|=I2C_CR1_START;                 /*generate start*/
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_SB)){           /*wait until start bit is set*/
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -2;

tmp=addr>>8;
tmp&=0x3;
tmp<<=1;
I2Cx->DR=haddr|tmp;
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_ADDR)){      /*wait until address flag is set*/
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -3;
tmp = I2Cx->SR2; 
wait_time=0;

/*clear SR2 by reading it */
while(!(I2Cx->SR1&I2C_SR1_TXE)){      /*Wait until Data register empty*/
   wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -4;
I2Cx->DR=addr&0xff;
wait_time=0;
while(!(I2Cx->SR1&I2C_SR1_TXE)){       /*wait until data register empty*/
  wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -5;
I2Cx->DR = data; 
wait_time=0;
while (!(I2Cx->SR1 & I2C_SR1_BTF)){     /*wait until transfer finished*/
   wait_time++;
  if(wait_time>=MAX_WAIT){
    break;
  }
}
if(wait_time>=MAX_WAIT)
     return -6;
I2Cx->CR1 |=I2C_CR1_STOP;	/*Generate Stop*/
return 0;	
#endif	
}

void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length){
#if 0
while (I2Cx->SR2 & I2C_SR2_BUSY);           //wait until bus not busy
I2Cx->CR1 |= I2C_CR1_START;                   //generate start
while (!(I2Cx->SR1 & I2C_SR1_SB)){;}					//wait until start is generated
volatile int Temp;														
I2Cx->DR = saddr<< 1;                 	 			// Send slave address
while (!(I2Cx->SR1 & I2C_SR1_ADDR)){;}        //wait until address flag is set
Temp = I2Cx->SR2; 						      //Clear SR2
while (!(I2Cx->SR1 & I2C_SR1_TXE));           //Wait until Data register empty
I2Cx->DR = maddr;                      				// send memory address
while (!(I2Cx->SR1 & I2C_SR1_TXE));           //wait until data register empty
//sending the data
for (uint8_t i=0;i<length;i++)
 { 
 I2Cx->DR=buffer[i]; 													//filling buffer with command or data
	while (!(I2Cx->SR1 & I2C_SR1_BTF));
 }	
                             
I2Cx->CR1 |= I2C_CR1_STOP;										//wait until transfer finished
#endif
}
int i2c_readByteEEprom(uint16_t addr, uint8_t *data)
{
return   i2c_readByte(I2C_EEPROM ,EEPROM_ADDR ,addr, data);
}
int i2c_writeByteEEprom(uint16_t addr,uint8_t data){
return  i2c_writeByte(I2C_EEPROM ,EEPROM_ADDR ,addr,data);
}

int i2c_readHwordEEprom(uint16_t addr, uint16_t *data)
{
uint8_t btmp;
uint16_t tmp;
int rez;
rez= i2c_readByte(I2C_EEPROM ,EEPROM_ADDR ,addr*2, &btmp);
if(rez<0)
   return rez;
tmp=btmp;
rez= i2c_readByte(I2C_EEPROM ,EEPROM_ADDR ,addr*2+1, &btmp);
if(rez<0)
   return rez;
tmp|= btmp<<8;
*data=tmp;
return 0;
}
int i2c_writeHwordEEprom(uint16_t addr,uint16_t data){
 int rez;
 
rez=  i2c_writeByte(I2C_EEPROM ,EEPROM_ADDR ,addr*2,data&0xff);
if(rez<0)
   return rez;
taskENTER_CRITICAL();
uDelay (2000);

rez=  i2c_writeByte(I2C_EEPROM ,EEPROM_ADDR ,addr*2+1,(data>>8)&0xff);
uDelay (2000);
taskEXIT_CRITICAL();

return rez;
}



