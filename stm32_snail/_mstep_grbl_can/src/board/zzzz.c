#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

////#include "stm32f2xx_gpio.h"
#include "board.h"
#include "zzzz.h"

/// uint32_t SystemCoreClock = 120000000;


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
///settings_t settings;

uint32_t HAL_GetTick(void){
  return 0;
}
///============= eeprom ===================================
///void Eeprom_Read_Page(uint16_t BufferOffset){}
///void memcpy_to_eeprom_with_checksum(unsigned int destination, char *source, unsigned int size){}
///int memcpy_from_eeprom_with_checksum(char *destination, unsigned int source, unsigned int size){
 /// return 0;
///}

void spindle_init(){}
void coolant_init(){}
void probe_init(){}
uint32_t get_count(){
  return 0;
}
 void spindle_set_state(uint8_t state, float rpm)
 {
 }
  uint8_t spindle_compute_pwm_value(float rpm) // 328p PWM register is 8-bit.
    {
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
///void mc_dwell(float seconds){}
///void mc_line(float *target, plan_line_data_t *pl_data){}
void probe_configure_invert_mask(uint8_t is_probe_away)
{
///  probe_invert_mask = 0; // Initialize as zero.
///  if (bit_isfalse(settings.flags,BITFLAG_INVERT_PROBE_PIN)) { probe_invert_mask ^= PROBE_MASK; }
 /// if (is_probe_away) { probe_invert_mask ^= PROBE_MASK; }
}
uint8_t probe_get_state(){
  return 0;
}
void spindle_stop(){}

void coolant_stop()
{
}

uint8_t coolant_get_state( )
{ 
 return 0;
}
  
 void st_update_plan_block_parameters()
 {
 }
 uint8_t spindle_get_state()
{
  return 0;
}

void coolant_set_state(uint8_t mode){}


///void CDC_send_str(char *str_report, uint32_t len){}
