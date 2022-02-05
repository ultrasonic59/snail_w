#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "my_grbl.h"
#include "my_stepper.h"

#include "printk.h"
extern void  set_curr_dir(uint8_t dirs);
extern uint16_t dir_port_invert_mask;
extern uint16_t step_port_invert_mask;
extern stepper_t st;
extern st_block_t st_block_buffer[];
extern segment_t segment_buffer[];

extern volatile uint8_t segment_buffer_tail;
///static 
extern uint8_t segment_buffer_head;

TaskHandle_t  can_send_thread_handle;
xQueueHandle rdy_to_send;

void tst_print(void)
{
  ////==============================================
  printk("\n\r [out=%x][n_step=%x,idx=%x]cycl=[%x]"
         ,st.step_outbits
         ,st.exec_segment->n_step
         ,st.exec_segment->st_block_index
         ,st.exec_segment->cycles_per_tick
          );
  printk("\n\r [steps0=%x][steps1=%x][steps2=%x][ev_cnt=%x]"
         ,st_block_buffer[st.exec_segment->st_block_index].steps_[0]
         ,st_block_buffer[st.exec_segment->st_block_index].steps_[1]
         ,st_block_buffer[st.exec_segment->st_block_index].steps_[2]
         ,st_block_buffer[st.exec_segment->st_block_index].step_event_count  );
 ////==============================================
}


void can_send_thread(void* pp)
{
uint8_t  res_byte;
rdy_to_send=xQueueCreate(1,1);
for(;;)
  {
  xQueueReceive(rdy_to_send,&res_byte,portMAX_DELAY);
   tst_print();
  set_curr_dir(st.dir_outbits);
///=================================================
do
{
  if (st.exec_segment == NULL) {
    // Anything in the buffer? If so, load and initialize next step segment.
    if (segment_buffer_head != segment_buffer_tail) {
      // Initialize new step segment and load number of steps to execute
      st.exec_segment = &segment_buffer[segment_buffer_tail];

      // Initialize step segment timing per step and load number of steps to execute.
////	  TIM2->ARR = st.exec_segment->cycles_per_tick - 1;
	  /* Set the Autoreload value */
      st.step_count = st.exec_segment->n_step; // NOTE: Can sometimes be zero when moving slow.
      // If the new segment starts a new planner block, initialize stepper variables and counters.
      // NOTE: When the segment data index changes, this indicates a new planner block.
      if ( st.exec_block_index != st.exec_segment->st_block_index ) {
        st.exec_block_index = st.exec_segment->st_block_index;
        st.exec_block = &st_block_buffer[st.exec_block_index];

        // Initialize Bresenham line and distance counters
        st.counter_x = st.counter_y = st.counter_z = (st.exec_block->step_event_count >> 1);
      }
      st.dir_outbits = st.exec_block->direction_bits ^ dir_port_invert_mask;

      #ifdef VARIABLE_SPINDLE
        // Set real-time spindle output as segment is loaded, just prior to the first step.
        spindle_set_speed(st.exec_segment->spindle_pwm);
      #endif

    } else {
      // Segment buffer empty. Shutdown.
      st_go_idle();
      // Ensure pwm is set properly upon completion of rate-controlled motion.
      #ifdef VARIABLE_SPINDLE
      if (st.exec_block->is_pwm_rate_adjusted) { 
        spindle_set_speed(SPINDLE_PWM_OFF_VALUE); 
          }
      #endif
      system_set_exec_state_flag(EXEC_CYCLE_STOP); // Flag main program for cycle end
  ////?????    return; // Nothing to do but exit.
    }
  }
  // Reset step out bits.
  st.step_outbits = 0;

  // Execute step displacement profile by Bresenham line algorithm
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    st.counter_x += st.steps[X_AXIS];
  #else
    st.counter_x += st.exec_block->steps_[X_AXIS];
  #endif
  if (st.counter_x > st.exec_block->step_event_count) {
    st.step_outbits |= (1<<X_STEP_BIT);
    st.counter_x -= st.exec_block->step_event_count;
    if (st.exec_block->direction_bits & (1<<X_DIRECTION_BIT)) { 
      sys_position[X_AXIS]--; 
      }
    else { 
      sys_position[X_AXIS]++; 
      }
  }
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    st.counter_y += st.steps[Y_AXIS];
  #else
    st.counter_y += st.exec_block->steps_[Y_AXIS];
  #endif
  if (st.counter_y > st.exec_block->step_event_count) {
    st.step_outbits |= (1<<Y_STEP_BIT);
    st.counter_y -= st.exec_block->step_event_count;
    if (st.exec_block->direction_bits & (1<<Y_DIRECTION_BIT)) { 
      sys_position[Y_AXIS]--; 
      }
    else { 
      sys_position[Y_AXIS]++; 
      }
  }
  #ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
    st.counter_z += st.steps[Z_AXIS];
  #else
    st.counter_z += st.exec_block->steps_[Z_AXIS];
  #endif
  if (st.counter_z > st.exec_block->step_event_count) {
    st.step_outbits |= (1<<Z_STEP_BIT);
    st.counter_z -= st.exec_block->step_event_count;
    if (st.exec_block->direction_bits & (1<<Z_DIRECTION_BIT)) { 
      sys_position[Z_AXIS]--; 
      }
    else { 
      sys_position[Z_AXIS]++; 
      }
  }

  // During a homing cycle, lock out and prevent desired axes from moving.
  if (sys.state == STATE_HOMING) { 
    st.step_outbits &= sys.homing_axis_lock; 
    }

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
 
  st.step_outbits ^= step_port_invert_mask;  // Apply step port invert mask
} while(st.step_count != 0);

///=================================================
    printk("\n\r can_send_thread");
 sys.state &= ~STATE_CYCLE;

  }
}

