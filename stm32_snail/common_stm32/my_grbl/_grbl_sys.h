#ifndef _GRBL_SYS_H_
#define _GRBL_SYS_H_
////======================================
// Alarm executor codes. Valid values (1-255). Zero is reserved.
#define EXEC_ALARM_HARD_LIMIT           1
#define EXEC_ALARM_SOFT_LIMIT           2
#define EXEC_ALARM_ABORT_CYCLE          3
#define EXEC_ALARM_PROBE_FAIL_INITIAL   4
#define EXEC_ALARM_PROBE_FAIL_CONTACT   5
#define EXEC_ALARM_HOMING_FAIL_RESET    6
#define EXEC_ALARM_HOMING_FAIL_DOOR     7
#define EXEC_ALARM_HOMING_FAIL_PULLOFF  8
#define EXEC_ALARM_HOMING_FAIL_APPROACH 9
// Define system suspend flags. Used in various ways to manage suspend states and procedures.
#define SUSPEND_DISABLE           0      // Must be zero.
#define SUSPEND_HOLD_COMPLETE     bit(0) // Indicates initial feed hold is complete.
#define SUSPEND_RESTART_RETRACT   bit(1) // Flag to indicate a retract from a restore parking motion.
#define SUSPEND_RETRACT_COMPLETE  bit(2) // (Safety door only) Indicates retraction and de-energizing is complete.
#define SUSPEND_INITIATE_RESTORE  bit(3) // (Safety door only) Flag to initiate resume procedures from a cycle start.
#define SUSPEND_RESTORE_COMPLETE  bit(4) // (Safety door only) Indicates ready to resume normal operation.
#define SUSPEND_SAFETY_DOOR_AJAR  bit(5) // Tracks safety door state for resuming.
#define SUSPEND_MOTION_CANCEL     bit(6) // Indicates a canceled resume motion. Currently used by probing routine.
#define SUSPEND_JOG_CANCEL        bit(7) // Indicates a jog cancel in process and to reset buffers when complete.
// Define step segment generator state flags.
#define STEP_CONTROL_NORMAL_OP            0  // Must be zero.
#define STEP_CONTROL_END_MOTION           bit(0)
#define STEP_CONTROL_EXECUTE_HOLD         bit(1)
#define STEP_CONTROL_EXECUTE_SYS_MOTION   bit(2)
#define STEP_CONTROL_UPDATE_SPINDLE_PWM   bit(3)

// Define control pin index for Grbl internal use. Pin maps may change, but these values don't.
#ifdef ENABLE_SAFETY_DOOR_INPUT_PIN
  #define N_CONTROL_PIN 4
  #define CONTROL_PIN_INDEX_SAFETY_DOOR   bit(0)
  #define CONTROL_PIN_INDEX_RESET         bit(1)
  #define CONTROL_PIN_INDEX_FEED_HOLD     bit(2)
  #define CONTROL_PIN_INDEX_CYCLE_START   bit(3)
#else
  #define N_CONTROL_PIN 3
  #define CONTROL_PIN_INDEX_RESET         bit(0)
  #define CONTROL_PIN_INDEX_FEED_HOLD     bit(1)
  #define CONTROL_PIN_INDEX_CYCLE_START   bit(2)
#endif
// Define spindle stop override control states.
#define SPINDLE_STOP_OVR_DISABLED       0  // Must be zero.
#define SPINDLE_STOP_OVR_ENABLED        bit(0)
#define SPINDLE_STOP_OVR_INITIATE       bit(1)
#define SPINDLE_STOP_OVR_RESTORE        bit(2)
#define SPINDLE_STOP_OVR_RESTORE_CYCLE  bit(3)

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
extern int32_t sys_position[N_AXIS];      // Real-time machine (aka home) position vector in steps.
extern int32_t sys_probe_position[N_AXIS];
extern volatile uint8_t sys_probe_state;   // Probing state value.  Used to coordinate the probing cycle with stepper ISR.
extern volatile uint8_t sys_rt_exec_state;   // Global realtime executor bitflag variable for state management. See EXEC bitmasks.
extern volatile uint8_t sys_rt_exec_alarm;   // Global realtime executor bitflag variable for setting various alarms.
extern volatile uint8_t sys_rt_exec_motion_override; // Global realtime executor bitflag variable for motion-based overrides.
extern volatile uint8_t sys_rt_exec_accessory_override; // Global realtime executor bitflag variable for spindle/coolant overrides.

extern void system_set_exec_state_flag(uint8_t mask) ;
extern void system_set_exec_motion_override_flag(uint8_t mask);
extern void system_set_exec_accessory_override_flag(uint8_t mask);
extern void system_set_exec_alarm(uint8_t code);
extern void system_flag_wco_change(void);
extern uint8_t system_check_travel_limits(float *target);
extern void system_clear_exec_state_flag(uint8_t mask) ;
extern uint8_t system_check_safety_door_ajar(void);
extern void system_execute_startup(char *line);

////=================================================================
extern void system_convert_array_steps_to_mpos(float *position, int32_t *steps);
////======================================
#endif  ////_GRBL_SYS_H_

