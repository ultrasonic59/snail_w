/*
 * enc6701_brd.c
 *
 *  Created on: Feb 27, 2025
 *      Author: vagol
 */
#include "enc6701_brd.h"
#include "adc.h"
#include "uart.h"
#include "timers.h"
#include "softuart.h"
#include "i2c.h"


void init_gpio(void)
{
GPIO_InitTypeDef  GPIO_InitStructure = {0};
///RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
///=============dbg_rx==================================
GPIO_InitStructure.GPIO_Pin = SOFT_RX_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;///GPIO_Speed_50MHz;
GPIO_Init(SOFT_RX_GPIO, &GPIO_InitStructure);
///============= dbg_tx ==================================
GPIO_InitStructure.GPIO_Pin = SOFT_TX_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;///GPIO_Speed_50MHz;
GPIO_Init(SOFT_TX_GPIO, &GPIO_InitStructure);
GPIO_WriteBit(SOFT_TX_GPIO,SOFT_TX_PIN,Bit_SET);
///=============led==================================
GPIO_InitStructure.GPIO_Pin = LED_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;///GPIO_Speed_50MHz;
GPIO_Init(LED_GPIO, &GPIO_InitStructure);
///=============RT==================================
GPIO_InitStructure.GPIO_Pin = RT_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;///GPIO_Speed_50MHz;
GPIO_Init(RT_GPIO, &GPIO_InitStructure);
}
///=============== led =======================================
void set_led(uint8_t on_off)
{
 if((on_off&0x1)==0)
     GPIO_WriteBit(LED_GPIO,LED_PIN,Bit_SET);
 else
     GPIO_WriteBit(LED_GPIO,LED_PIN, Bit_RESET);
}
////extern void IIC_Init(u32 bound, u16 address);

void init_hw(void)
{
init_gpio();
DMA_INIT();
USART1_CFG();

TIM1_Config(); ///for softuart
SoftUartInit(SOFT_TX_GPIO,SOFT_TX_PIN
                  ,SOFT_RX_GPIO,SOFT_RX_PIN);
SoftUartEnableRx();
///============================================
    IIC_Init( 400000); // 400Kbps
///    I2C1->CTLR1 |= 0x0080; // CTLR1_NOSTRETCH_Set - Disable clock stretching
///    I2C1->CTLR1 |= 0x0400; // CTLR1_ACK_Set - Enable ACK following each byte received - This also stops the clock stretching for each character received.
TIM2_Config(); ///for adc
adc_init();

}


