#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "board.h"
#include "printk.h"
////======================================
extern void set_mot_dir(uint8_t dir);
extern void set_mot_step(uint8_t step);
extern void reset_mot_step(void);

extern void system_set_exec_state_flag(uint8_t flag);
////======================================
system_t sys;
// Used to avoid ISR nesting of the "Stepper Driver Interrupt". Should never occur though.
static volatile uint8_t busy;
stepper_t st;
// Step segment ring buffer indices
static volatile uint8_t segment_buffer_tail;
static uint8_t segment_buffer_head;
static uint8_t segment_next_head;
int32_t sys_position[N_AXIS];      // Real-time machine (aka home) position vector in steps.

static segment_t segment_buffer[SEGMENT_BUFFER_SIZE];
static st_block_t st_block_buffer[SEGMENT_BUFFER_SIZE-1];
////============================================================
// Stepper shutdown
void st_go_idle()
{
  // Disable Stepper Driver Interrupt. Allow Stepper Port Reset Interrupt to finish, if active.
  NVIC_DisableIRQ(TIM2_IRQn);

  busy = 0;
#if 0
  // Set stepper driver idle state, disabled or enabled, depending on settings and circumstances.
////????  bool pin_state = false; // Keep enabled.
  if (((settings.stepper_idle_lock_time != 0xff) || sys_rt_exec_alarm || sys.state == STATE_SLEEP) && sys.state != STATE_HOMING) {
    // Force stepper dwell to lock axes for a defined amount of time to ensure the axes come to a complete
    // stop and not drift from residual inertial forces at the end of the last movement.
    delay__ms(settings.stepper_idle_lock_time);
    pin_state = true; // Override. Disable steppers.
  }
  if (bit_istrue(settings.flags,BITFLAG_INVERT_ST_ENABLE)) { pin_state = !pin_state; } // Apply pin invert.
  if (pin_state) 
  { 
	  SetStepperDisableBit();
  }
  else 
  { 
	  ResetStepperDisableBit();
  }
#endif  
}

////============================================================
void TIM2_IRQHandler(void)
{
if ((TIM2->SR & 0x0001) != 0)                  // check interrupt source
	{
	TIM2->SR &= ~(1 << 0);                          // clear UIF flag
	TIM2->CNT = 0;
	}
else
	{
	return;
	}

  if (busy) { return; } // The busy-flag is used to avoid reentering this interrupt
    set_mot_dir(st.dir_outbits);

////  GPIO_Write(DIRECTION_PORT, (GPIO_ReadOutputData(DIRECTION_PORT) & ~DIRECTION_MASK) | (st.dir_outbits & DIRECTION_MASK));
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

  // Then pulse the stepping pins
  #ifdef STEP_PULSE_DELAY
    st.step_bits = (STEP_PORT & ~STEP_MASK) | st.step_outbits; // Store out_bits to prevent overwriting.
  #else  // Normal operation
////	GPIO_Write(STEP_PORT, (GPIO_ReadOutputData(STEP_PORT) & ~STEP_MASK) | st.step_outbits);
        set_mot_step(st.step_outbits);

  #endif
  // Enable step pulse reset timer so that The Stepper Port Reset Interrupt can reset the signal after
  // exactly settings.pulse_microseconds microseconds, independent of the main Timer1 prescaler.
   NVIC_EnableIRQ(TIM3_IRQn);

  busy = 1;

  // If there is no step segment, attempt to pop one from the stepper buffer
  if (st.exec_segment == NULL) {
    // Anything in the buffer? If so, load and initialize next step segment.
    if (segment_buffer_head != segment_buffer_tail) {
      // Initialize new step segment and load number of steps to execute
      st.exec_segment = &segment_buffer[segment_buffer_tail];

      // Initialize step segment timing per step and load number of steps to execute.
	  TIM2->ARR = st.exec_segment->cycles_per_tick - 1;
	  /* Set the Autoreload value */
#ifndef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING        
	  TIM2->PSC = st.exec_segment->prescaler;
#endif
      st.step_count = st.exec_segment->n_step; // NOTE: Can sometimes be zero when moving slow.
      // If the new segment starts a new planner block, initialize stepper variables and counters.
      // NOTE: When the segment data index changes, this indicates a new planner block.
      if ( st.exec_block_index != st.exec_segment->st_block_index ) {
        st.exec_block_index = st.exec_segment->st_block_index;
        st.exec_block = &st_block_buffer[st.exec_block_index];

        // Initialize Bresenham line and distance counters
        st.counter_x = st.counter_y = st.counter_z = (st.exec_block->step_event_count >> 1);
      }
////???      st.dir_outbits = st.exec_block->direction_bits ^ dir_port_invert_mask;

      #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
        // With AMASS enabled, adjust Bresenham axis increment counters according to AMASS level.
        st.steps[X_AXIS] = st.exec_block->steps[X_AXIS] >> st.exec_segment->amass_level;
        st.steps[Y_AXIS] = st.exec_block->steps[Y_AXIS] >> st.exec_segment->amass_level;
        st.steps[Z_AXIS] = st.exec_block->steps[Z_AXIS] >> st.exec_segment->amass_level;
      #endif

      #ifdef VARIABLE_SPINDLE
        // Set real-time spindle output as segment is loaded, just prior to the first step.
        spindle_set_speed(st.exec_segment->spindle_pwm);
      #endif

    } else {
      // Segment buffer empty. Shutdown.
      st_go_idle();
      // Ensure pwm is set properly upon completion of rate-controlled motion.
      #ifdef VARIABLE_SPINDLE
      if (st.exec_block->is_pwm_rate_adjusted) { spindle_set_speed(SPINDLE_PWM_OFF_VALUE); }
      #endif
      system_set_exec_state_flag(EXEC_CYCLE_STOP); // Flag main program for cycle end
      return; // Nothing to do but exit.
    }
  }


  // Check probing state.
////????  if (sys_probe_state == PROBE_ACTIVE) { probe_state_monitor(); }

  // Reset step out bits.
  st.step_outbits = 0;

  // Execute step displacement profile by Bresenham line algorithm
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    st.counter_x += st.steps[X_AXIS];
  #else
    st.counter_x += st.exec_block->steps[X_AXIS];
  #endif
  if (st.counter_x > st.exec_block->step_event_count) {
    st.step_outbits |= (1<<X_STEP_BIT);
    st.counter_x -= st.exec_block->step_event_count;
    if (st.exec_block->direction_bits & (1<<X_DIRECTION_BIT)) { sys_position[X_AXIS]--; }
    else { sys_position[X_AXIS]++; }
  }
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    st.counter_y += st.steps[Y_AXIS];
  #else
    st.counter_y += st.exec_block->steps[Y_AXIS];
  #endif
  if (st.counter_y > st.exec_block->step_event_count) {
    st.step_outbits |= (1<<Y_STEP_BIT);
    st.counter_y -= st.exec_block->step_event_count;
    if (st.exec_block->direction_bits & (1<<Y_DIRECTION_BIT)) { sys_position[Y_AXIS]--; }
    else { sys_position[Y_AXIS]++; }
  }
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    st.counter_z += st.steps[Z_AXIS];
  #else
    st.counter_z += st.exec_block->steps[Z_AXIS];
  #endif
  if (st.counter_z > st.exec_block->step_event_count) {
    st.step_outbits |= (1<<Z_STEP_BIT);
    st.counter_z -= st.exec_block->step_event_count;
    if (st.exec_block->direction_bits & (1<<Z_DIRECTION_BIT)) { sys_position[Z_AXIS]--; }
    else { sys_position[Z_AXIS]++; }
  }

  // During a homing cycle, lock out and prevent desired axes from moving.
  if (sys.state == STATE_HOMING) { st.step_outbits &= sys.homing_axis_lock; }

  st.step_count--; // Decrement step events count
  if (st.step_count == 0) {
    // Segment is complete. Discard current segment and advance segment indexing.
    st.exec_segment = NULL;
    uint8_t segment_tail_next = segment_buffer_tail + 1;
    if (segment_tail_next == SEGMENT_BUFFER_SIZE)
    {
      segment_tail_next = 0;
    }
    segment_buffer_tail = segment_tail_next;
  }

////  st.step_outbits ^= step_port_invert_mask;  // Apply step port invert mask
  busy = 0;////false;
}
void TIM3_IRQHandler(void)
{
	if ((TIM3->SR & 0x0001) != 0)                  // check interrupt source
	{
		TIM3->SR &= ~(1<<0);                          // clear UIF flag
		TIM3->CNT = 0;
 		NVIC_DisableIRQ(TIM3_IRQn);
    // Reset stepping pins (leave the direction pins)
/////		GPIO_Write(STEP_PORT, (GPIO_ReadOutputData(STEP_PORT) & ~STEP_MASK) | (step_port_invert_mask & STEP_MASK));
        reset_mot_step();
                
	}
}

////============================================================
