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
  Example routine to emulate a custom USB device (CH372 device).
  This routine demonstrates the use of a USBHS Device to emulate a custom device, the CH372, 
  with endpoints 1/3/5 downlinking data and uploading via endpoints 1/4/6 respectively
  Endpoint 1 uploads and downlinks via ring buffer with no data reversal, endpoints 3/4, and endpoints 5/6 copy and upload.
  The device can be operated using Bushund or other upper computer software.
  Note: This routine needs to be demonstrated in conjunction with the host software.
*/

#include "ch32v30x_usbhs_device.h"
#include "debug.h"
////============= ON_DV ==================================
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
    uint8_t ret=0;
	Delay_Init();
	USART_Printf_Init(115200);
	printf( "SystemClk:%d\r\n",SystemCoreClock) ;
////	printf( "CH372Device Running On USBHS Controller\n" );
    /* USB20 device init */
    USBHS_RCC_Init( );
    USBHS_Device_Init( ENABLE );
    NVIC_EnableIRQ( USBHS_IRQn );
    init_led();
    set_led(1);
#if 0
for(;;)
{
    set_led(ret) ;
    ret++;
    Delay_Ms(500);
}
#endif
	while(1)
	{
        /* Determine if enumeration is complete, perform data transfer if completed */
    if(USBHS_DevEnumStatus)
        {
#if 0
            /* Data Transfer */
            if(RingBuffer_Comm.RemainPack)
            {
 ///               ret = USBHS_Endp_DataUp(DEF_UEP1, &Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_HS_PACK_SIZE], RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr], DEF_UEP_DMA_LOAD);
  ////              ret = USBHS_Endp_DataUp(DEF_UEP1, dataBuffer, RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr], DEF_UEP_DMA_LOAD);
                ret = USBHS_Endp_DataUp(DEF_UEP1, dataBuffer, 4, DEF_UEP_CPY_LOAD);
              if(ret == 0)
                {
                    NVIC_DisableIRQ(USBHS_IRQn);
                    RingBuffer_Comm.RemainPack--;
                    RingBuffer_Comm.DealPtr++;
                    if(RingBuffer_Comm.DealPtr == DEF_Ring_Buffer_Max_Blks)
                    {
                        RingBuffer_Comm.DealPtr = 0;
                    }
                    NVIC_EnableIRQ(USBHS_IRQn);
                }
            }

            /* Monitor whether the remaining space is available for further downloads */
            if(RingBuffer_Comm.RemainPack < (DEF_Ring_Buffer_Max_Blks - DEF_RING_BUFFER_RESTART))
            {
                if(RingBuffer_Comm.StopFlag)
                {
                    RingBuffer_Comm.StopFlag = 0;
                    USBHSD->UEP1_RX_CTRL = (USBHSD->UEP1_RX_CTRL & ~USBHS_UEP_R_RES_MASK) | USBHS_UEP_R_RES_ACK;
                }
            }
#endif
            ;
        }

	}
}
