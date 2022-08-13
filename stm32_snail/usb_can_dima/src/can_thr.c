#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "my_grbl.h"
#include "my_stepper.h"
#include "can.h"

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
xQueueHandle queu_to_send;

void _tst_print(void)
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
void test_print(can_msg_t  *snd_msg)
{
go_cmd_t *p_go_cmd=  (go_cmd_t *)snd_msg->data;
  ////==============================================
  printk("\n\r [id=%x]"
         ,snd_msg->id
          );
  printk("\n\r [cmd=%x][dirs=%x][per=%x][steps=%lx]"
         ,p_go_cmd->cmd
         ,p_go_cmd->dirs
         ,p_go_cmd->step_per
         ,p_go_cmd->steps  );
 ////==============================================
}

////extern void obr_segment(void);

void can_send_thread(void* pp)
{
can_msg_t  snd_msg;

printk("\n\r can_send_thread");

queu_to_send=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
for(;;)
  {
  xQueueReceive(queu_to_send,&snd_msg,portMAX_DELAY);
  CAN_wrMsg (&snd_msg);
  test_print(&snd_msg);
 ////  tst_print();
///  set_curr_dir(st.dir_outbits);
////  obr_segment();
///=================================================
////  sys.state &= ~STATE_CYCLE;

  }
}

