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
void serial_reset_read_buffer()
{
///  serial_rx_buffer_tail = serial_rx_buffer_head;
}


void spindle_init(){}
void coolant_init(){}
///void limits_init(){}
void probe_init(){}
///void plan_reset(){} // Clear block buffer and planner variables
void st_reset(){}// Clear stepper subsystem variables.

	    // Sync cleared gcode and planner positions to current system position.
///void plan_sync_position(){}

///void report_init_message(){}

	    // Start Grbl main loop. Processes program inputs and executes them.
///void protocol_main_loop(){}
uint32_t get_count(){
  return 0;
}

int read_parameter_setting(char * line, int * counter, float * parameters, int *id){
return 0;
}
uint8_t serial_read(){
  return 0;
}
void  __disable_irq(){}
void  __enable_irq(){}
// Wait end of motion
void mc_wait_end_of_motion(){}
uint8_t settings_read_coord_data(uint8_t coord_select, float *coord_data){
  return 0;
}
uint32_t plc_output_set_state(uint8_t number, uint8_t state){
  return 0;
}
uint32_t plc_wait_input_event(uint32_t pin, uint32_t edge, uint32_t timeout){
  return 0;
}
void spindle_sync(uint8_t state, float rpm){}
void coolant_sync(uint8_t mode){}
void mc_dwell(float seconds){}
void settings_write_coord_data(uint8_t coord_select, float *coord_data){}
void mc_line(float *target, plan_line_data_t *pl_data){}


void CDC_send_str(char *str_report, uint32_t len){}
