
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
#include "can_cmds.h"
///=======================================================================
extern void tst1_task( void *pvParameters );
extern void tst_task( void *pvParameters );
extern void can_rsv_task( void *pvParameters );
extern void can_send_thread(void* pp);

////extern int can_main(void);
extern void CAN1_Init (void);
TaskHandle_t  can_send_thread_handle;
uint8_t boot_state;

extern uint8_t check_ks_app(void);
////extern uint8_t eeprom_format(void);
uint16_t VirtAddVarTab[NB_OF_VAR]={0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xf,
                                   0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
                                   0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1f }; 

////============================================
int main( void )
{
////uint8_t btst=0; 
////uint32_t tst=0;
uint16_t tmp=0;

#ifdef DEBUG
////  debug();
#endif
  
__disable_irq();
hw_board_init();
#if STEP_X
  printk("\n\r=== [boot_step_x_axis] ==="); 
#elif STEP_Y
  printk("\n\r=== [boot_step_y_axis] ==="); 
#elif STEP_Z
  printk("\n\r=== [boot_step_z_axis] ==="); 
#else 
  #error "\n\r=== boot STEP_... nodefined ==="; 
#endif
////=================================================
boot_state=BOOTER_STATE_IDLE;
////eeprom_init();
///  FLASH_Unlock();
 /// EE_Init();
///  FLASH_Lock();
  
#if 0
////eeprom_init();
if(EE_ReadVariable(ADDR_EEPROM_BOOT_WORK, &tmp)==0)
  {
    if((tmp==VAL_EEPROM_WORK)&&(check_ks_app())) 
      {
       goto_app();
      }
  }
else
   {
    printk("\n\r=== [eeprom error!!!] ==="); 
 ////   eeprom_format();
    }
#endif
#if STEP_X
  printk("\n\r=== [wait boot_step_x_axis!!!] ==="); 
#elif STEP_Y
  printk("\n\r=== [wait boot_step_y_axis!!!] ==="); 
#elif STEP_Z
  printk("\n\r=== [wait boot_step_z_axis!!!] ==="); 
#else 
  #error "\n\r=== boot STEP_... nodefined ==="; 
#endif

////=================================================
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
////xTaskCreate( motor_task, "tst_task", MOTOR_TASK_STACK_SIZE, NULL, MOTOR_TASK_PRIORITY, NULL );
xTaskCreate(can_send_thread, (const char*)"can_send_thread",CAN_SEND_STACK_SIZE/2, 0, APP_PRIORITY, &can_send_thread_handle);
xTaskCreate( can_rsv_task, "can_rsv_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL );
////xTaskCreate( tst1_task, "tst_task", TST_TASK_STACK_SIZE, NULL, TST_TASK_PRIORITY, NULL );
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
#if 0
void assert_param(unsigned long iVal)
{
  if(iVal==0)
    {
    for( ;; )
	{
	}
    }
  
}
#endif
#endif
////=======================================================

////=======================================================