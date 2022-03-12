#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "my_grbl.h"
#include "my_stepper.h"

#include "printk.h"
extern void  set_curr_dir(uint8_t dirs);
////extern uint16_t dir_port_invert_mask;
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
         ,st_block_buffer[st.exec_segment->st_block_index].steps[0]
         ,st_block_buffer[st.exec_segment->st_block_index].steps[1]
         ,st_block_buffer[st.exec_segment->st_block_index].steps[2]
         ,st_block_buffer[st.exec_segment->st_block_index].step_event_count  );
 ////==============================================
}

extern void obr_segment(void);

void can_send_thread(void* pp)
{
uint8_t  res_byte;
printk("\n\r can_send_thread");

rdy_to_send=xQueueCreate(1,1);
for(;;)
  {
  xQueueReceive(rdy_to_send,&res_byte,portMAX_DELAY);
////   tst_print();
///  set_curr_dir(st.dir_outbits);
  obr_segment();

///=================================================

///=================================================
  sys.state &= ~STATE_CYCLE;

  }
}

