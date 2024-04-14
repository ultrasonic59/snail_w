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
 ����IAPʵ�����̣�
 ��֧�ִ�����USB����FLASH��¼
 ע��
 1. ��IAP���ع��ߣ�ʵ������ PA0����(Ĭ����������)
 2. ��������APP��PA0�ӵأ��͵�ƽ���룩������λ����������APP����
 3. �����谲װCH372������
 
 */

#include "debug.h"
#include "ch32v20x_usbotg_device.h"
#include "iap.h"
#include "usb_istr.h"
#include "usb_desc.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
extern u8 End_Flag;
/*********************************************************************
 * @fn      IAP_2_APP
 *
 * @brief   IAP_2_APP program.
 *
 * @return  none
 */
void IAP_2_APP(void) {
    USB_Port_Set(DISABLE, DISABLE);
    USBOTG_H_FS->HOST_CTRL = 0x00;
    USBOTG_FS->BASE_CTRL = 0x00;
    USBOTG_FS->INT_EN = 0x00;
    USBOTG_FS->UEP2_3_MOD = 0x00;
    USBOTG_FS->BASE_CTRL |= (1 << 1) | (1 << 2);
    Delay_Ms(50);
    printf("jump APP\r\n");
    Delay_Ms(10);
    NVIC_EnableIRQ(Software_IRQn);
    NVIC_SetPendingIRQ(Software_IRQn);
}
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    Set_USBConfig();
    USB_Init();
    USB_Port_Set(DISABLE, DISABLE);
    Delay_Ms(700);
    USB_Port_Set(ENABLE, ENABLE);
    USB_Interrupts_Config();

    USBOTG_Init();
    USART3_CFG(57600);
    while(1)
    {
        EP2_RecData_Deal();
        if( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET) {
            UART_Rx_Deal();
        }
        if (End_Flag)
        {
            Delay_Ms(10);
            IAP_2_APP();
            while(1);
        }
    }
}
