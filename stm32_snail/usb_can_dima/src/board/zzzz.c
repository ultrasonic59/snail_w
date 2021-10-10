#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

////#include "stm32f2xx_gpio.h"
#include "board.h"
#include "my_grbl.h"

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
////===============================================================
// Method to store coord data parameters into EEPROM
void settings_write_coord_data(uint8_t coord_select, float *coord_data)
{
}
// Read selected coordinate data from EEPROM. Updates pointed coord_data value.
  
uint8_t settings_read_coord_data(uint8_t coord_select, float *coord_data)
{
#if 0
  uint32_t addr = coord_select*(sizeof(float)*N_AXIS+1) + EEPROM_ADDR_PARAMETERS;
  if (!(memcpy_from_eeprom_with_checksum((char*)coord_data, addr, sizeof(float)*N_AXIS))) {
    // Reset with default zero vector
		coord_data[X_AXIS] = 0.0f;
		coord_data[Y_AXIS] = 0.0f;
		coord_data[Z_AXIS] = 0.0f;
		settings_write_coord_data(coord_select,coord_data);
    return(false);
  }
#endif
  return(true);
}
// Reads startup line from EEPROM. Updated pointed line string data.
uint8_t settings_read_build_info(char *line)
{
#if 0
  if (!(memcpy_from_eeprom_with_checksum((char*)line, EEPROM_ADDR_BUILD_INFO, LINE_BUFFER_SIZE))) {
    // Reset line with default value
    line[0] = 0; // Empty line
    settings_store_build_info(line);
    return(false);
  }
#endif
  return(true);
}
// Method to store build info into EEPROM
// NOTE: This function can only be called in IDLE state.
void settings_store_build_info(char *line)
{
  // Build info can only be stored when state is IDLE.
////  memcpy_to_eeprom_with_checksum(EEPROM_ADDR_BUILD_INFO,(char*)line, LINE_BUFFER_SIZE);
}

void settings_restore(uint8_t restore_flag) {
}
 // Reads startup line from EEPROM. Updated pointed line string data.
uint8_t settings_read_startup_line(uint8_t n, char *line)
{
#if 0
  uint32_t addr = n*(LINE_BUFFER_SIZE+1)+EEPROM_ADDR_STARTUP_BLOCK;
  if (!(memcpy_from_eeprom_with_checksum((char*)line, addr, LINE_BUFFER_SIZE))) {
    // Reset line with default value
    line[0] = 0; // Empty line
    settings_store_startup_line(n, line);
    return(false);
  }
#endif
  return(true);
}
uint8_t settings_store_global_setting(uint8_t parameter, float value) {
  return(true);
}
  // Method to store startup lines into EEPROM
void settings_store_startup_line(uint8_t n, char *line)
{
#if 0
  #ifdef FORCE_BUFFER_SYNC_DURING_EEPROM_WRITE
    protocol_buffer_synchronize(); // A startup line may contain a motion and be executing. 
  #endif
  uint32_t addr = n*(LINE_BUFFER_SIZE+1)+EEPROM_ADDR_STARTUP_BLOCK;
  memcpy_to_eeprom_with_checksum(addr,(char*)line, LINE_BUFFER_SIZE);
#endif
}


////========================================================================
void coolant_sync(uint8_t mode)
{
}
void coolant_set_state(uint8_t mode)
{
}
uint8_t coolant_get_state()
{
return 0;
}
  
void  SetSpindleEnablebit(void)
{
}

void  ResetSpindleEnablebit(void)
{
}
void __spindle_set_state(uint8_t state)
  {
  }
void spindle_set_state(uint8_t state, float rpm)
  {
  }

void spindle_sync(uint8_t state, float rpm)
{
}

void spindle_stop()
{
}
uint8_t spindle_get_state()
{
return 0;
}

// Reset and clear stepper subsystem variables
void st_reset()
{
#if 0  
  // Initialize stepper driver idle state.
  st_go_idle();

  // Initialize stepper algorithm variables.
  memset(&prep, 0, sizeof(st_prep_t));
  memset(&st, 0, sizeof(stepper_t));
  st.exec_segment = NULL;
  pl_block = NULL;  // Planner block pointer used by segment buffer
  segment_buffer_tail = 0;
  segment_buffer_head = 0; // empty = tail
  segment_next_head = 1;
  busy = false;

  st_generate_step_dir_invert_masks();
  st.dir_outbits = dir_port_invert_mask; // Initialize direction bits to default.

  // Initialize step and direction port pins.
  GPIO_Write(STEP_PORT, (GPIO_ReadOutputData(STEP_PORT) & ~STEP_MASK) | (step_port_invert_mask & STEP_MASK));
  GPIO_Write(DIRECTION_PORT, (GPIO_ReadOutputData(DIRECTION_PORT) & ~DIRECTION_MASK) | (dir_port_invert_mask & DIRECTION_MASK));
#endif
}

// Called by planner_recalculate() when the executing block is updated by the new plan.
void st_update_plan_block_parameters()
{
#if 0  
  if (pl_block != NULL) { // Ignore if at start of a new block.
    prep.recalculate_flag |= PREP_FLAG_RECALCULATE;
    pl_block->entry_speed_sqr = prep.current_speed*prep.current_speed; // Update entry speed.
    pl_block = NULL; // Flag st_prep_segment() to load and check active velocity profile.
  }
#endif
}
void st_wake_up()
{
}
void st_prep_buffer()
{
}

// Called by realtime status reporting to fetch the current speed being executed. This value
// however is not exactly the current speed, but the speed computed in the last step segment
// in the segment buffer. It will always be behind by up to the number of segment blocks (-1)
// divided by the ACCELERATION TICKS PER SECOND in seconds.
float st_get_realtime_rate()
{
#if 0
  if (sys.state & (STATE_CYCLE | STATE_HOMING | STATE_HOLD | STATE_JOG | STATE_SAFETY_DOOR)){
    return prep.current_speed;
  }
#endif   
  return 0.0f;
}

