
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Library includes. */
////#include "stm32f2xx_it.h"
#include "stm32f2xx_rcc.h"

/* Demo app includes. */
#include "board.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"

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
///=======================================================================
#define TST_TASK_STACK_SIZE			1024            ////( configMINIMAL_STACK_SIZE + 50 )
#define TST_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define GRBL_TASK_STACK_SIZE			1024            ////( configMINIMAL_STACK_SIZE + 50 )
#define VCP_TASK_STACK_SIZE                     1024

#define GRBL_TASK_PRIORITY				( tskIDLE_PRIORITY + 4 )
#define VCP_TASK_PRIORITY				( tskIDLE_PRIORITY + 5 )

////extern void tst_task( void *pvParameters );
extern void tst1_task( void *pvParameters );
extern void grbl_task( void *pvParameters );
extern void vcp_thread(void *pdata);
extern TaskHandle_t  vcp_thread_handle;

extern int can_main(void);
#pragma data_alignment=8   
__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;

extern USBD_Usr_cb_TypeDef USR_cb;
extern USBD_Class_cb_TypeDef  USBD_CDC_VCP_cb;
#define USBD_Class_cb USBD_CDC_VCP_cb

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

///=================================  
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc, 
            &USBD_Class_cb, 
            &USR_cb);

printk("\n\r=== [test1] ==="); 

////=================================================
can1_init();
////can_main();
////=================================================
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
        
////    xTaskCreate( gbrl_thr, "gbrl", mainCHECK_TASK_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
         
	/* Start the tasks defined within this file/specific to this demo. */
 ////???   xTaskCreate( vCheckTask, "Check", mainCHECK_TASK_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
////???	xTaskCreate( vLCDTask, "LCD", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

	/* The suicide tasks must be created last as they need to know how many
	tasks were running prior to their creation in order to ascertain whether
	or not the correct/expected number of tasks are running at any given time. */
 ////????   vCreateSuicidalTasks( mainCREATOR_TASK_PRIORITY );

	/* Configure the timers used by the fast interrupt timer test. */
/////	vSetupTimerTest();
xTaskCreate( grbl_task, "tst_task", GRBL_TASK_STACK_SIZE, NULL, GRBL_TASK_PRIORITY, NULL );
xTaskCreate( tst1_task, "tst1_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );
BaseType_t rez;  
rez=xTaskCreate(vcp_thread, (const char*)"vcp_thread",VCP_TASK_STACK_SIZE, 0, VCP_TASK_PRIORITY, &vcp_thread_handle);
printk("\n\r vcp_thread[%x]",rez); 

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Will only get here if there was not enough heap space to create the
	idle task. */
return 0;
}
////============================================================
#if 0
static void vCheckTask( void *pvParameters )
{
TickType_t xLastExecutionTime;
xLCDMessage xMessage;
static signed char cPassMessage[ mainMAX_MSG_LEN ];
extern unsigned short usMaxJitter;

	xLastExecutionTime = xTaskGetTickCount();
	xMessage.pcMessage = cPassMessage;

    for( ;; )
	{
		/* Perform this check every mainCHECK_DELAY milliseconds. */
		vTaskDelayUntil( &xLastExecutionTime, mainCHECK_DELAY );

		/* Has an error been found in any task? */

        if( xAreBlockingQueuesStillRunning() != pdTRUE )
		{
			xMessage.pcMessage = "ERROR IN BLOCK Q\n";
		}
		else if( xAreBlockTimeTestTasksStillRunning() != pdTRUE )
		{
			xMessage.pcMessage = "ERROR IN BLOCK TIME\n";
		}
        else if( xAreSemaphoreTasksStillRunning() != pdTRUE )
        {
            xMessage.pcMessage = "ERROR IN SEMAPHORE\n";
        }
        else if( xArePollingQueuesStillRunning() != pdTRUE )
        {
            xMessage.pcMessage = "ERROR IN POLL Q\n";
        }
        else if( xIsCreateTaskStillRunning() != pdTRUE )
        {
            xMessage.pcMessage = "ERROR IN CREATE\n";
        }
        else if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
        {
            xMessage.pcMessage = "ERROR IN MATH\n";
        }
		else if( xAreComTestTasksStillRunning() != pdTRUE )
		{
			xMessage.pcMessage = "ERROR IN COM TEST\n";
		}
		else
		{
			sprintf( ( char * ) cPassMessage, "PASS [%uns]\n", ( ( unsigned long ) usMaxJitter ) * mainNS_PER_CLOCK );
		}

		/* Send the message to the LCD gatekeeper for display. */
		xQueueSend( xLCDQueue, &xMessage, portMAX_DELAY );
	}
}
#endif
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