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

/* Demo app includes. */
#include "board.h"

#if 0
#include "usb_lib.h"
#ifdef USEUSB
#include "usb_desc.h"
#endif
#include "hw_config.h"
#ifdef USEUSB
#include "usb_pwr.h"
#endif
#include "stm32eeprom.h"
///#include "eeprom.h"
#endif

#include "misc.h"
#include "printk.h"
#include "_hdlc.h"
///=======================================================================
#define TST_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 50 )
#define TST_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
extern void tst_task( void *pvParameters );
extern void task_dp(void *pvParameters); 
extern void init_hdlc_bt(void);

///=======================================================================

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
extern int LSM6DS3_Detect(void);
extern int bmc150_detect(void);

extern int send_char_bt (int c) ;
extern hdlc_stat_t g_hdlc_bt;

void bt_snd_task(void *pdata)
{
////t_frametx frame_tx;
uint8_t byte_send;
///hdlc_stat_t *p_hdlc=(hdlc_stat_t *)pdata;
///==================================
for(;;)
  {
  if(xQueueReceive(g_hdlc_bt.ua_snd_dat,&byte_send,portMAX_DELAY))
    send_char_bt(byte_send);	
  }
}
///====================================
   
////============================================
int main( void )
{
////uint8_t btst=0; 
uint32_t tst=0;
  
#ifdef DEBUG
  debug();
#endif
__disable_irq();

NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
hw_board_init();
#if 0
for(;;)
{
 if(LSM6DS3_Detect()>=0)
   break;
 uDelay(10000);
}
#endif
#if 0
for(;;)
{
 if(bmc150_detect()>=0)
   break;
 uDelay(10000);
}
#endif

printk("\n\r == init_hdlc_bt ==");  
init_hdlc_bt();

tst=    xTaskCreate(bt_snd_task, (const char*)"BT_tx", BT_TX_STACK_SIZE, NULL, 6, NULL);
printk("\n\r == bt_snd_task[%x] ==",tst);  

    xTaskCreate( tst_task, "tst_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );
tst=    xTaskCreate(task_dp, "DP", configMINIMAL_STACK_SIZE, NULL, 2, ( TaskHandle_t * ) NULL);
////xTaskCreate(bt_snd_task, (const char*)"BT_tx", BT_TX_STACK_SIZE, NULL, 6, NULL);
printk("\n\r == task_dp[%x] ==",tst);  

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Will only get here if there was not enough heap space to create the
	idle task. */
return 0;
}
////============================================================
/*-----------------------------------------------------------*/


#ifdef  DEBUG
/* Keep the linker happy. */
void assert_failed( unsigned char* pcFile, unsigned long ulLine )
{
	for( ;; )
	{
	}
}
#endif
////=======================================================

////=======================================================