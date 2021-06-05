#include <stdint.h>
#include "my_grbl.h"

system_t sys;

volatile uint8_t sys_rt_exec_state;   // Global realtime executor bitflag variable for state management. See EXEC bitmasks.
volatile uint8_t sys_rt_exec_motion_override; // Global realtime executor bitflag variable for motion-based overrides.
volatile uint8_t sys_rt_exec_accessory_override; // Global realtime executor bitflag variable for spindle/coolant overrides.

void system_set_exec_state_flag(uint8_t flag) {
///  __disable_irq();
  sys_rt_exec_state |= (flag);
///  __enable_irq();
}
void system_set_exec_motion_override_flag(uint8_t mask) {
////  __disable_irq();
  sys_rt_exec_motion_override |= (mask);
///  __enable_irq();
}
void system_set_exec_accessory_override_flag(uint8_t mask) {
///  __disable_irq();
  sys_rt_exec_accessory_override |= (mask);
///  __enable_irq();
}

void system_clear_exec_motion_overrides() {
//// __disable_irq();
  sys_rt_exec_motion_override = 0;
////  __enable_irq();
}
