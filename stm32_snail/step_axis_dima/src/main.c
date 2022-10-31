
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Library includes. */
////#include "stm32f2xx_it.h"
#include "stm32f2xx_rcc.h"

/* Demo app includes. */
#include "board.h"

#include "misc.h"
#include "printk.h"
///=======================================================================
////extern void tst_task( void *pvParameters );
extern void tst1_task( void *pvParameters );
extern void can_rsv_task( void *pvParameters );
extern void can_send_thread(void* pp);

extern int can_main(void);
extern void CAN1_Init (void);
TaskHandle_t  can_send_thread_handle;

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
#if STEP_X
  printk("\n\r=== [step_x_axis] ==="); 
#elif STEP_Y
  printk("\n\r=== [step_y_axis] ==="); 
#elif STEP_Z
  printk("\n\r=== [step_z_axis] ==="); 
#else 
  #error "\n\r=== STEP_... nodefined ==="; 
#endif
////=================================================
CAN1_Init();

////=================================================
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
xTaskCreate( motor_task, "tst_task", MOTOR_TASK_STACK_SIZE, NULL, MOTOR_TASK_PRIORITY, NULL );
xTaskCreate(can_send_thread, (const char*)"can_send_thread",CAN_SEND_STACK_SIZE/2, 0, APP_PRIORITY, &can_send_thread_handle);
xTaskCreate( can_rsv_task, "can_rsv_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
////xTaskCreate( tst1_task, "tst1_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );
/* Start the scheduler. */
vTaskStartScheduler();
return 0;
}

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