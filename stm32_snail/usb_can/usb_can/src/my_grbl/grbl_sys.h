#ifndef _GRBL_SYS_H_
#define _GRBL_SYS_H_
////======================================
// Define global system variables
typedef struct {
  uint8_t state;               // Tracks the current system state of Grbl.
  uint8_t abort;               // System abort flag. Forces exit back to main loop for reset.             
  uint8_t suspend;             // System suspend bitflag variable that manages holds, cancels, and safety door.
  uint8_t soft_limit;          // Tracks soft limit errors for the state machine. (boolean)
  uint8_t step_control;        // Governs the step segment generator depending on system state.
  uint8_t probe_succeeded;     // Tracks if last probing cycle was successful.
  uint8_t homing_axis_lock;    // Locks axes when limits engage. Used as an axis motion mask in the stepper ISR.
  uint8_t f_override;          // Feed rate override value in percent
  uint8_t r_override;          // Rapids override value in percent
  uint8_t spindle_speed_ovr;   // Spindle speed value in percent
  uint8_t spindle_stop_ovr;    // Tracks spindle stop override states
  uint8_t report_ovr_counter;  // Tracks when to add override data to status reports.
  uint8_t report_wco_counter;  // Tracks when to add work coordinate offset data to status reports.
	#ifdef ENABLE_PARKING_OVERRIDE_CONTROL
		uint8_t override_ctrl;     // Tracks override control states.
	#endif
	#ifdef VARIABLE_SPINDLE
    float spindle_speed;
  #endif
} system_t;
extern system_t sys;
extern void system_set_exec_state_flag(uint8_t mask) ;
extern void system_set_exec_motion_override_flag(uint8_t mask);
extern void system_set_exec_accessory_override_flag(uint8_t mask);

////======================================
#endif  ////_GRBL_SYS_H_

