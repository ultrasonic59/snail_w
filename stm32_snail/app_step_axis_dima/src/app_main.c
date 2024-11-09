
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
#include "emul_eeprom.h"
#define VERS          "snail_axis_v1.0"

///=======================================================================
////extern void tst_task( void *pvParameters );
extern void tst_task( void *pvParameters );
extern void can_rsv_task( void *pvParameters );
extern void can_send_thread(void* pp);

////extern void CAN1_Init (void);
TaskHandle_t  can_send_thread_handle;

////============================================
int main( void )
{
uint16_t tmp=0;
#ifdef DEBUG
  debug();
#endif
__disable_irq();
hw_board_init();
#if STEP_X
  printk("\r\n[app_step_x_axis][%s]%s:%s] ",VERS, __DATE__, __TIME__);
#elif STEP_Y
  printk("\r\n[app_step_y_axis][%s]%s:%s] ",VERS, __DATE__, __TIME__);
#elif STEP_Z
  printk("\r\n[app_step_z_axis][%s]%s:%s] ",VERS, __DATE__, __TIME__);
#else 
  #error "\n\r=== app STEP_... nodefined ==="; 
#endif
////=================================================
eeprom_init();
if(EE_Read(ADDR_EEPROM_BOOT_WORK, &tmp)==0)
  {
    if(tmp!=VAL_EEPROM_WORK) ///
      {
       EE_Write(ADDR_EEPROM_BOOT_WORK, VAL_EEPROM_WORK);
      }
  }
else
  {
  EE_Write(ADDR_EEPROM_BOOT_WORK, VAL_EEPROM_WORK);
  }
////=================================================
////CAN1_Init();
////goto_app();
////goto_booter();
////=================================================
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
 xTaskCreate( motor_task, "motor_task", MOTOR_TASK_STACK_SIZE, NULL, MOTOR_TASK_PRIORITY, NULL );
xTaskCreate(can_send_thread, (const char*)"can_send_thread",CAN_SEND_STACK_SIZE/2, 0, APP_PRIORITY, &can_send_thread_handle);
xTaskCreate( can_rsv_task, "can_rsv_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
xTaskCreate( tst_task, "tst_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );
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