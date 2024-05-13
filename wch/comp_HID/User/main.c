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
#include "usb_can_brd.h"

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
    RingBuffer_Comm.RemainPack = 0;
    for(i=0; i<DEF_Ring_Buffer_Max_Blks; i++)
    {
        RingBuffer_Comm.PackLen[i] = 0;
    }
}
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
#define CNT_D_MAX 2000000
int main(void)
{
    uint32_t cnt_d=0;
   uint8_t tst=0;
	Delay_Init();
	USART_Printf_Init(115200);
	printf( "SystemClk:%d\r\n",SystemCoreClock) ;
	printf( "Compatibility HID Running On USBHS Controller\r\n" );

	 /* Variables init */
    Var_Init();
    board_init();
#if 0
for(;;)
{
 cnt_d++;
 if(cnt_d>=CNT_D_MAX)
    {
     cnt_d=0;
      set_rled(tst);
      tst++;
    }
///printf( "k\n" );
///Delay_Ms (100);
}
#endif
    /* UART2 init */
    UART2_Init();
    UART2_DMA_Init();

    /* USB20 device init */
    USBHS_RCC_Init( );
    USBHS_Device_Init( ENABLE );

    /* Timer init */
    TIM2_Init();

    while(1)
    {
        if (USBHS_DevEnumStatus)
        {
            UART2_Rx_Service();
            UART2_Tx_Service();
            HID_Set_Report_Deal();
        }
        ///====================================
        cnt_d++;
        if(cnt_d>=CNT_D_MAX)
           {
            cnt_d=0;
             set_rled(tst);
             tst++;
           }
  ///=========================================
    }
}
