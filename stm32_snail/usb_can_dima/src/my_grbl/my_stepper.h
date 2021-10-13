#ifndef __MY_STEPPER_H__
#define __MY_STEPPER_H__

#ifndef SEGMENT_BUFFER_SIZE
#define SEGMENT_BUFFER_SIZE 10
#endif

// Some useful constants.
#define DT_SEGMENT (1.0f/(ACCELERATION_TICKS_PER_SECOND*60.0f)) // min/segment
#define REQ_MM_INCREMENT_SCALAR 1.25f
#define RAMP_ACCEL 0
#define RAMP_CRUISE 1
#define RAMP_DECEL 2
#define RAMP_DECEL_OVERRIDE 3

#define PREP_FLAG_RECALCULATE bit(0)
#define PREP_FLAG_HOLD_PARTIAL_BLOCK bit(1)
#define PREP_FLAG_PARKING bit(2)
#define PREP_FLAG_DECEL_OVERRIDE bit(3)

#define X_DIRECTION_BIT 3
#define Y_DIRECTION_BIT 4
#define Z_DIRECTION_BIT 5

// Stores the planner block Bresenham algorithm execution data for the segments in the segment
// buffer. Normally, this buffer is partially in-use, but, for the worst case scenario, it will
// never exceed the number of accessible stepper buffer segments (SEGMENT_BUFFER_SIZE-1).
// NOTE: This data is copied from the prepped planner blocks so that the planner blocks may be
// discarded when entirely consumed and completed by the segment buffer. Also, AMASS alters this
// data for its own use.
typedef struct st_block_s_{
  uint32_t steps[N_AXIS];
  uint32_t step_event_count;
  uint8_t direction_bits;
  #ifdef VARIABLE_SPINDLE
    uint8_t is_pwm_rate_adjusted; // Tracks motions that require constant laser power/rate
  #endif
} st_block_t;

// Primary stepper segment ring buffer. Contains small, short line segments for the stepper
// algorithm to execute, which are "checked-out" incrementally from the first block in the
// planner buffer. Once "checked-out", the steps in the segments buffer cannot be modified by
// the planner, where the remaining planner block steps still can.
typedef struct segment_s_{
  uint16_t n_step;           // Number of step events to be executed for this segment
  uint16_t cycles_per_tick;  // Step distance traveled per ISR tick, aka step rate.
  uint8_t  st_block_index;   // Stepper block data index. Uses this information to execute this segment.
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    uint8_t amass_level;    // Indicates AMASS level for the ISR to execute this segment
  #else
    uint8_t prescaler;      // Without AMASS, a prescaler is required to adjust for slow timing.
  #endif
  #ifdef VARIABLE_SPINDLE
    uint8_t spindle_pwm;
  #endif
} segment_t;
// Stepper ISR data struct. Contains the running data for the main stepper ISR.
typedef struct stepper_s_{
  // Used by the bresenham line algorithm
  uint32_t counter_x,        // Counter variables for the bresenham line tracer
           counter_y,
           counter_z;
  #ifdef STEP_PULSE_DELAY
    uint8_t step_bits;  // Stores out_bits output to complete the step pulse delay
  #endif

  uint8_t execute_step;     // Flags step execution for each interrupt.
  uint8_t step_pulse_time;  // Step pulse reset time after step rise

  PORTPINDEF step_outbits;         // The next stepping-bits to be output
  PORTPINDEF dir_outbits;
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    uint32_t steps[N_AXIS];
  #endif

  uint16_t step_count;       // Steps remaining in line segment motion
  uint8_t exec_block_index; // Tracks the current st_block index. Change indicates new block.
  st_block_t *exec_block;   // Pointer to the block data for the segment being executed
  segment_t *exec_segment;  // Pointer to the segment being executed
} stepper_t;
#if 1
const uint16_t step_pin_mask[N_AXIS] =
{
	1 << X_STEP_BIT,
	1 << Y_STEP_BIT,
	1 << Z_STEP_BIT,

};
const uint16_t direction_pin_mask[N_AXIS] =
{
	1 << X_DIRECTION_BIT,
	1 << Y_DIRECTION_BIT,
	1 << Z_DIRECTION_BIT,
};
#endif

extern void stepper_init(void);

#endif  ////__MY_STEPPER_H__