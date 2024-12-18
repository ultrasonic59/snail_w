/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/08/20
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/* @Note
 * Compatibility HID Example:
 * This program provides examples of the pass-through of USB-HID data and serial port
 *  data based on compatibility HID device. And the data returned by Get_Report request is
 *  the data sent by the last Set_Report request.Speed of UART1/2 is 115200bps.
 *
 * Interrupt Transfers:
 *   UART2_RX   ---> Endpoint1
 *   Endpoint2  ---> UART2_TX
 *
 *   Note that the first byte is the valid data length and the remaining bytes are
 *   the transmission data for interrupt Transfers.
 *
 * Control Transfers:
 *   Set_Report ---> UART1_TX
 *   Get_Report <--- last Set_Report packet
 *
 *  */

#include "ch32v30x_usbhs_device.h"
#include "usbd_compatibility_hid.h"
/******************************************************************************/
/* Global define */

/******************************************************************************/
/* Global Variables */

/*********************************************************************
 * @fn      Var_Init
 *
 * @brief   Software parameter initialization
 *
 * @return  none
 */
void Var_Init(void)
{
    uint16_t i;
    RingBuffer_Comm.LoadPtr = 0;
    RingBuffer_Comm.StopFlag = 0;
    RingBuffer_Comm.DealPtr = 0;
    RingBuffer_Comm._RemainPack = 0;
    for(i=0; i<DEF_Ring_Buffer_Max_Blks; i++)
    {
        RingBuffer_Comm.PackLen[i] = 0;
    }
}
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
////    uint8_t btst=0;
	Delay_Init();
	USART_Printf_Init(115200);
	printf( "SystemClk:%d\r\n",SystemCoreClock) ;
	printf( "Compatibility HID Running On USBHS Controller\n" );

	 /* Variables init */
    Var_Init();

    /* UART2 init */
 ///   UART2_Init();
 ///   UART2_DMA_Init();

    /* USB20 device init */
    USBHS_RCC_Init( );
   USBHS_Device_Init( ENABLE );
    init_led();
#if 0
 for(;;)
 {
     set_led(btst);
     printf( "Compatibility HID Running On USBHS Controller\n" );

     btst++;
     Delay_Ms(500);
 }
#endif
    /* Timer init */
    TIM2_Init();

    while(1)
    {
        ;
 /*
        if (USBHS_DevEnumStatus)
        {
          UART2_Rx_Service();
            UART2_Tx_Service();
            HID_Set_Report_Deal();
        }
        */
    }
}
