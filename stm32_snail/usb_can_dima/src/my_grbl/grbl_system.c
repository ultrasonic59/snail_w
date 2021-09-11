#include <stdint.h>
#include "my_grbl.h"

system_t sys;
int32_t sys_position[N_AXIS];      // Real-time machine (aka home) position vector in steps.
int32_t sys_probe_position[N_AXIS]; // Last probe position in machine coordinates and steps.
volatile uint8_t sys_probe_state;   // Probing state value.  Used to coordinate the probing cycle with stepper ISR.
volatile uint8_t sys_rt_exec_state;   // Global realtime executor bitflag variable for state management. See EXEC bitmasks.
volatile uint8_t sys_rt_exec_alarm;   // Global realtime executor bitflag variable for setting various alarms.
volatile uint8_t sys_rt_exec_motion_override; // Global realtime executor bitflag variable for motion-based overrides.
volatile uint8_t sys_rt_exec_accessory_override; // Global realtime executor bitflag variable for spindle/coolant overrides.

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
void system_set_exec_alarm(uint8_t code) {
////  __disable_irq();
  sys_rt_exec_alarm |= (code);
////  __enable_irq();
}
void system_clear_exec_state_flag(uint8_t mask) {
///  __disable_irq();
  sys_rt_exec_state &= ~(mask);
///  __enable_irq();
}
// Returns if safety door is ajar(T) or closed(F), based on pin state.
uint8_t system_check_safety_door_ajar(void)
{
  #ifdef ENABLE_SAFETY_DOOR_INPUT_PIN
    return(system_control_get_state() & CONTROL_PIN_INDEX_SAFETY_DOOR);
  #else
    return(false); // Input pin not enabled, so just return that it's closed.
  #endif
}
// Executes user startup script, if stored.
void system_execute_startup(char *line)
{
  uint8_t n;
  for (n=0; n < N_STARTUP_LINE; n++) {
    if (!(settings_read_startup_line(n, line))) {
      line[0] = 0;
      report_execute_startup_message(line,STATUS_SETTING_READ_FAIL);
    } else {
      if (line[0] != 0) {
        uint8_t status_code = gc_execute_line(line);
        report_execute_startup_message(line,status_code);
      }
    }
  }
}

