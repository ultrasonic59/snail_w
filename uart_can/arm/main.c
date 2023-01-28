#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "board.h"

/* Task priorities. */
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )
   
#define CAN_TASK_PRIORITY				( tskIDLE_PRIORITY + 4 )

#define CAN_TASK_STACK_SIZE			        ( configMINIMAL_STACK_SIZE + 50 )

extern void slc_task( void *pvParameters );
///======================================================
int main( void )
{
#ifdef DEBUG
  debug();
#endif
board_init();
////xTaskCreate( testTask, "Check", mainCHECK_TASK_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
xTaskCreate( slc_task, "slc_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
xTaskCreate( can_read_task, "can_read", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
/* Start the scheduler. */
vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the
	idle task. */
return 0;
}
/*-----------------------------------------------------------*/

int fputc( int ch, FILE *f )
{
return ch;
}
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
