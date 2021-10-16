/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks.
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Fast Interrupt Test" - A high frequency periodic interrupt is generated
 * using a free running timer to demonstrate the use of the
 * configKERNEL_INTERRUPT_PRIORITY configuration constant.  The interrupt
 * service routine measures the number of processor clocks that occur between
 * each interrupt - and in so doing measures the jitter in the interrupt timing.
 * The maximum measured jitter time is latched in the ulMaxJitter variable, and
 * displayed on the LCD by the 'Check' task as described below.  The
 * fast interrupt is configured and handled in the timertest.c source file.
 *
 * "LCD" task - the LCD task is a 'gatekeeper' task.  It is the only task that
 * is permitted to access the display directly.  Other tasks wishing to write a
 * message to the LCD send the message on a queue to the LCD task instead of
 * accessing the LCD themselves.  The LCD task just blocks on the queue waiting
 * for messages - waking and displaying the messages as they arrive.
 *
 * "Check" task -  This only executes every five seconds but has the highest
 * priority so is guaranteed to get processor time.  Its main function is to
 * check that all the standard demo tasks are still operational.  Should any
 * unexpected behaviour within a demo task be discovered the 'check' task will
 * write an error to the LCD (via the LCD task).  If all the demo tasks are
 * executing with their expected behaviour then the check task writes PASS
 * along with the max jitter time to the LCD (again via the LCD task), as
 * described above.
 *
 */

/* Standard includes. */
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Library includes. */
////#include "stm32f2xx_it.h"
#include "stm32f2xx_rcc.h"

#include "board.h"
#include "usbd_core.h"
#include "usbd_desc.h"

#include "can.h"

#include "misc.h"
#include "printk.h"
///=======================================================================
extern void vcp_thread(void *pdata);
extern void grbl_thread(void* pp);

extern TaskHandle_t  vcp_thread_handle;
extern TaskHandle_t  grbl_thread_handle;

///extern void usb_thread( void *arg );
///extern void init_hdlc_vcp(void);

#define TST_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 50 )
#define TST_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
void tst_task( void *pvParameters );
///==================================
TaskHandle_t  usb_thread_handle;
///==================================
///==================================
#pragma data_alignment=8   
__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;

extern USBD_Class_cb_TypeDef  USBD_CDC_VCP_cb;
#define USBD_Class_cb USBD_CDC_VCP_cb
extern USBD_Class_cb_TypeDef  USBD_CDC_cb;
////#define USBD_Class_cb USBD_CDC_cb

extern USBD_Usr_cb_TypeDef USR_cb;

////========================================================
void uDelay (const uint32_t usec)
{
uint32_t count = 0;
const uint32_t utime = 45*usec;////(120 * usec / 7);
do
  {
   if ( ++count > utime )
    {
    return ;
    }
  }
while (1);
}
   
////============================================
int main( void )
{
////uint8_t btst=0; 
////uint32_t tst=0;
#ifdef DEBUG
  debug();
#endif
__disable_irq();
hw_board_init();

printk("\n\r CAN1_Init"); 
CAN1_Init();
////================================
////=================================  
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc, 
            &USBD_Class_cb, 
            &USR_cb);
///=================================  
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
///  xTaskCreate( tst_task, "tst_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );
////rez=
xTaskCreate(vcp_thread, (const char*)"vcp_thread",VCP_TX_STACK_SIZE/2, 0, APP_PRIORITY, &vcp_thread_handle);
xTaskCreate(grbl_thread, (const char*)"grbl_thread",GRBL_STACK_SIZE/2, 0, APP_PRIORITY, &grbl_thread_handle);

  
////    xTaskCreate( usb_thread, "usb_thread", APPLICATION_STACK_SIZE/sizeof( portSTACK_TYPE ), NULL, APP_PRIORITY, &usb_thread_handle);

	/* Start the scheduler. */
vTaskStartScheduler();

	/* Will only get here if there was not enough heap space to create the
	idle task. */
return 0;
}
////============================================================
////=======================================================

////=======================================================