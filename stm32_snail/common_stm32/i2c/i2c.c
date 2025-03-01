/**

 * original author: Husamuldeen <https://github.com/hussamaldean>

   ----------------------------------------------------------------------
   	Copyright (C) husamuldeen, 2020

    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */


#include "board.h"
#include "i2c.h"
   
void I2C_LowLevel_Init(void) {
  GPIO_InitTypeDef  GPIO_InitStructure;
  I2C_InitTypeDef   I2C_InitStructure;
  
  //Enable the i2c
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2Cx, ENABLE);
  //Reset the Peripheral
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2Cx, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2Cx, DISABLE);
  
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
  
  //Configure and Initialize the I2C
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00; //We are the master. We don't need this
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 100000;  //1e4-1e5 is ok
  
  //Initialize the Peripheral
  I2C_Init(I2Cx, &I2C_InitStructure);
  // I2C Peripheral Enable
  I2C_Cmd(I2Cx, ENABLE);
  
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
char i2c_readByte(char saddr,char maddr, char *data)
{

volatile int tmp;
while(I2Cx->SR2&I2C_SR2_BUSY){;}
I2Cx->CR1|=I2C_CR1_START;
while(!(I2Cx->SR1&I2C_SR1_SB)){;}
I2Cx->DR=saddr<<1;
while(!(I2Cx->SR1&I2C_SR1_ADDR)){;}
tmp=I2Cx->SR2;
while(!(I2Cx->SR1&I2C_SR1_TXE)){;}
I2Cx->DR=maddr;
while(!(I2Cx->SR1&I2C_SR1_TXE)){;}
I2Cx->CR1|=I2C_CR1_START;
while(!(I2Cx->SR1&I2C_SR1_SB)){;}	
I2Cx->DR=saddr<<1|1;
while(!(I2Cx->SR1&I2C_SR1_ADDR)){;}
I2Cx->CR1&=~I2C_CR1_ACK;
tmp =I2Cx->SR2;
I2Cx->CR1|=I2C_CR1_STOP;
while(!(I2Cx->SR1&I2C_SR1_RXNE)){;}
*data++=I2Cx->DR;
return 0;
}

void i2c_writeByte(char saddr,char maddr,char data){

volatile int Temp;
while(I2Cx->SR2&I2C_SR2_BUSY){;}          /*wait until bus not busy*/
I2Cx->CR1|=I2C_CR1_START;                 /*generate start*/
while(!(I2Cx->SR1&I2C_SR1_SB)){;}         /*wait until start bit is set*/
I2Cx->DR = saddr<< 1;                 	 /* Send slave address*/
while(!(I2Cx->SR1&I2C_SR1_ADDR)){;}      /*wait until address flag is set*/
Temp = I2Cx->SR2; 											 /*clear SR2 by reading it */
while(!(I2Cx->SR1&I2C_SR1_TXE)){;}       /*Wait until Data register empty*/
I2Cx->DR = maddr;                        /* send memory address*/
while(!(I2Cx->SR1&I2C_SR1_TXE)){;}       /*wait until data register empty*/
I2Cx->DR = data; 	
while (!(I2Cx->SR1 & I2C_SR1_BTF));      /*wait until transfer finished*/
I2Cx->CR1 |=I2C_CR1_STOP;								 /*Generate Stop*/	
	
}

void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length){

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



}