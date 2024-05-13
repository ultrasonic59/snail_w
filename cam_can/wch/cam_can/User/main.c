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
 task1 and task2 alternate printing
*/

#include "debug.h"
#include "cam_can_brd.h"
#include "ch32v30x_usbhs_device.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "task.h"
#include "can.h"
#include "can_thr.h"
#include "usb_hid_thr.h"
#include "usbd_compatibility_hid.h"

/* Global define */
#define TASK1_TASK_PRIO     5
#define TASK1_STK_SIZE      256
#define TASK2_TASK_PRIO     5
#define TASK2_STK_SIZE      256

/* Global Variable */
TaskHandle_t Task1Task_Handler;
TaskHandle_t Task2Task_Handler;
TaskHandle_t  can_send_thread_handle;

#if 0
/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0/1
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure={0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
#endif
////extern int put_can_ack(uint8_t cmd );
/*********************************************************************
 * @fn      task1_task
 *
 * @brief   task1 program.
 *
 * @param  *pvParameters - Parameters point of task1
 *
 * @return  none
 */
void task1_task(void *pvParameters)
{
 ////   int rez=0;
    while(1)
    {
     ////   printf("task1 entry\r\n");
    ///    set_led(1);
 ///       set_tst3(1);
 ///       on_off_dv(1);
    ////   GPIO_SetBits(GPIOA, GPIO_Pin_0);
        vTaskDelay(250);
  ////      GPIO_ResetBits(GPIOA, GPIO_Pin_0);
///        set_led(0);
 ///       set_tst3(0);
///        on_off_dv(0);
     vTaskDelay(250);
  //// put_can_ack(0x3 );

    }
}

/*********************************************************************
 * @fn      task2_task
 *
 * @brief   task2 program.
 *
 * @param  *pvParameters - Parameters point of task2
 *
 * @return  none
 */
void task2_task(void *pvParameters)
{
    while(1)
    {
        printf("task2 entry\r\n");
        set_tst1(0);
        set_tst2(0);
////       GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        vTaskDelay(100);
  ////      GPIO_SetBits(GPIOA, GPIO_Pin_1);
        set_tst1(1);
        set_tst2(1);
      vTaskDelay(100);
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
///int rez=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("FreeRTOS Kernel Version:%s\r\n",tskKERNEL_VERSION_NUMBER);
	board_init();
 /*
    for(;;)
    {
     USART_SendData(USART1, 0x35);
     Delay_Ms(100);
    }
*/
    UART2_Init();
    UART2_DMA_Init();

    /* USB20 device init */
    USBHS_RCC_Init( );
    USBHS_Device_Init( ENABLE );

    TIM2_Init();

 ////  xTaskCreate( motor_task, "motor_task", MOTOR_TASK_STACK_SIZE, NULL, MOTOR_TASK_PRIORITY, NULL );
  //// rez=
 ////          xTaskCreate( can_rsv_thr, "can_rsv_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
   ////printf("rez:%d\r\n",rez);
  ///rez=
 ////         xTaskCreate(can_send_thr, (const char*)"can_send_thr",CAN_SEND_STACK_SIZE/2, 0, CAN_TASK_PRIORITY, &can_send_thread_handle);
        xTaskCreate(usb_hid_thr, (const char*)"usb_hid_thr",USB_HID_STACK_SIZE/2, 0, USB_HID_TASK_PRIORITY, NULL);

  ////printf("rez1:%d\r\n",rez);
 ////  xTaskCreate( can_rsv_thr, "can_rsv_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
 ////  xTaskCreate( tst_task, "tst_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );

#if 0
////	GPIO_Toggle_INIT();
	/* create two task */
    xTaskCreate((TaskFunction_t )task2_task,
                        (const char*    )"task2",
                        (uint16_t       )TASK2_STK_SIZE,
                        (void*          )NULL,
                        (UBaseType_t    )TASK2_TASK_PRIO,
                        (TaskHandle_t*  )&Task2Task_Handler);
#endif
    xTaskCreate((TaskFunction_t )task1_task,
                    (const char*    )"task1",
                    (uint16_t       )TASK1_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )TASK1_TASK_PRIO,
                    (TaskHandle_t*  )&Task1Task_Handler);

    vTaskStartScheduler();

	while(1)
	{
	    printf("shouldn't run at here!!\n");
	}
}
