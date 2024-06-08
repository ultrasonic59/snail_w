/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/*
 *@Note
 *Example routine to emulate a simulate USB-CDC Device, USE USART1(PA9/PA10)
 *Recommended to use UART2(PA2) as debug port, you can modify the debug port
 *by modifying the macro definition in debug.h
 *Merged HID devices, using endpoint 4 data downlink to fetch reverse upload;
*/

#include "ch32v30x_usbhs_device.h"
#include "debug.h"
////============= LED_PIN ==================================
  #define LED_PIN          GPIO_Pin_3
  #define LED_GPIO         GPIOA
volatile uint8_t leds=0;

void init_led(void)
{
GPIO_InitTypeDef GPIO_InitStructure = {0};
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
GPIO_InitStructure.GPIO_Pin = LED_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(LED_GPIO, &GPIO_InitStructure);

}
void set_led(uint8_t on_off)
{
if(on_off&0x1)
{
    leds|=0x1;
   GPIO_WriteBit(LED_GPIO,LED_PIN,Bit_RESET);
}
else
{
    leds&=~(0x1);
   GPIO_WriteBit(LED_GPIO,LED_PIN, Bit_SET);
}
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    RCC_Configuration( );

    /* Tim2 init */
    TIM2_Init( );

    /* Usart1 init */
    UART1_Init( 1, DEF_UARTx_BAUDRATE, DEF_UARTx_STOPBIT, DEF_UARTx_PARITY );

    /* USB20 device init */
    USBHS_RCC_Init( );
    USBHS_Device_Init( ENABLE );

    while(1)
    {
     ///   UART1_DataRx_Deal( );
     ////   UART1_DataTx_Deal( );
        ;
    }
}
