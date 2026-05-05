#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

////#include "stm32f2xx_gpio.h"
#include "board.h"
#include "zzzz.h"

////#define TEST_PIN ZSTP_PIN
////#define TEST_PIN_GPIO ZSTP_PIN_GPIO

void  put_tst_pin(uint8_t idat)
{
#if 1  
if(idat&0x1)
  {
  GPIO_SetBits(TST3_PIN_GPIO, TST3_PIN);
   GPIO_SetBits(TST2_PIN_GPIO, TST2_PIN);
  ////GPIO_SetBits(TST7_PIN_GPIO, TST7_PIN);
  }
else
  {
   GPIO_ResetBits(TST3_PIN_GPIO, TST3_PIN);
   GPIO_ResetBits(TST2_PIN_GPIO, TST2_PIN);
   ////GPIO_ResetBits(TST7_PIN_GPIO, TST7_PIN);
  }
#endif 
}
///=================================================================
settings_t settings;

uint32_t HAL_GetTick(void){
  return 0;
}
void settings_init() {
#if 0 
  if(!read_global_settings()) {
    report_status_message(STATUS_SETTING_READ_FAIL);
    settings_restore(SETTINGS_RESTORE_DEFAULTS); // Force restore all EEPROM data.
    report_grbl_settings();
  }
#endif
}
// Initialize and start the stepper motor subsystem
void stepper_init()
{

}
void system_init()
{
	//Eeprom_Write_CR();
}
void serial_reset_read_buffer()
{
///  serial_rx_buffer_tail = serial_rx_buffer_head;
}

void gc_init()
{
///  memset(&gc_state, 0, sizeof(parser_state_t));

  // Load default G54 coordinate system.
 /// if (!(settings_read_coord_data(gc_state.modal.coord_select,gc_state.coord_system))) {
 ///   report_status_message(STATUS_SETTING_READ_FAIL);
///  }
}

void spindle_init(){}
void coolant_init(){}
///void limits_init(){}
void probe_init(){}
void plan_reset(){} // Clear block buffer and planner variables
void st_reset(){}// Clear stepper subsystem variables.

	    // Sync cleared gcode and planner positions to current system position.
void plan_sync_position(){}
void gc_sync_position(){}

void report_init_message(){}

	    // Start Grbl main loop. Processes program inputs and executes them.
void protocol_main_loop(){}

