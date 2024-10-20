/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "ch32v20x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/pin.h"
#include "lcd.h"

/* Global typedef */

/* Global define */

/* LED0通过rt的pin驱动接口驱动  */
#define LED0_PIN  26   //PA15

/* Global Variable */

/*********************************************************************
 * @fn      LED1_BLINK_INIT
 *
 * @brief   LED1通过直接调用底层驱动
 *
 * @return  none
 */
void LED1_BLINK_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/* main只是一个线程之一，除此之外还有tshell,idle
   *    本main只是一个LED闪烁，main线程的注册在rtthread_startup
   *   中，tshell使用了串口接收中断，中断栈和线程栈使用分开，注意进中断时候
 * 16caller寄存器需要压入线程栈中
 * */
int main(void)
{
    rt_kprintf("\r\n MCU: CH32V20x\r\n");
	rt_kprintf(" SysClk: %dHz\r\n",SystemCoreClock);
    rt_kprintf(" www.wch.cn\r\n");
	LED1_BLINK_INIT();
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	   lcd_init();


	while(1)
	{
	    GPIO_SetBits(GPIOA,GPIO_Pin_15);
	    rt_thread_mdelay(500);
	    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	    rt_thread_mdelay(500);
	}
}


/* 测试使用驱动接口操作I/O口  */
int led(void)
{
    rt_uint8_t count;

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    printf("led_SP:%08x\r\n",__get_SP());
    for(count = 0 ; count < 10 ;count++)
    {
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_kprintf("led on, count : %d\r\n", count);
        rt_thread_mdelay(500);

        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_kprintf("led off\r\n");
        rt_thread_mdelay(500);
    }
    return 0;
}
MSH_CMD_EXPORT(led,  led sample by using I/O drivers);



