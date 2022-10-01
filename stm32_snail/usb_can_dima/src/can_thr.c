#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "my_grbl.h"
#include "my_stepper.h"
#include "can.h"
#include "board.h"

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
extern can_msg_t       CAN_RxMsg;                  /* CAN message for receiving        */                        


TaskHandle_t  can_send_thread_handle;
xQueueHandle queu_to_send;
xQueueHandle queu_can_resv;

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
  printk("\n\r [id=%x]  "
         ,snd_msg->id
          );
  printk(" [cmd=%x][dirs=%x][per=%x][steps=%lx]"
         ,p_go_cmd->cmd
         ,p_go_cmd->dirs
         ,p_go_cmd->step_per
         ,p_go_cmd->steps  );
 ////==============================================
}

////extern void obr_segment(void);
////===================================
void can_wait_ready(void){
can_msg_t  send_msg;
send_msg.id=ID_X_CMD|ID_Y_CMD|ID_Z_CMD;
send_msg.data[0]=GET_STAT_CMD;
send_msg.len=CAN_REQ_STAT_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
CAN_wrMsg (&send_msg);
}
///================================
void can_send_thread(void* pp)
{
can_msg_t  snd_msg;

printk("\n\r can_send_thread");

queu_to_send=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
for(;;)
  {
  xQueueReceive(queu_to_send,&snd_msg,portMAX_DELAY);
  can_wait_ready();             //// wait ready X,Y,Z
  CAN_wrMsg (&snd_msg);
  
  test_print(&snd_msg);
  
 ////  tst_print();
///  set_curr_dir(st.dir_outbits);
////  obr_segment();
///=================================================
////  sys.state &= ~STATE_CYCLE;

  }
}
xQueueHandle queu_can_resv;

void can_rsv_task( void *pvParameters )
{
uint8_t ii=0; 
///can_cmd_t *p_can_cmd=  (can_cmd_t *)CAN_RxMsg.data;
printk("\n\r can_rsv_task"); 
queu_can_resv=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
 
for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
    switch(CAN_RxMsg.data[0]) {
      case PUT_STAT_CMD:
        {
        put_stat_cmd_t *p_can_cmd=  (put_stat_cmd_t *)CAN_RxMsg.data;
         printk("put stat");
        }
        break;
    default:
      break;
    }
#if 0   
    printk("\n\r can_rx"); 
    printk("\n\r ExtId[%x]",CAN_RxMsg.id);
    printk("\n\r DLC[%x]\n\r ",CAN_RxMsg.len);
    for(ii=0;ii<8;ii++)
      {
      printk("[%x] ",CAN_RxMsg.data[ii]);
      }
#endif
    }
  else
  {
////   CAN_wrMsg (&send_msg);
    msleep(20);
  }
  }
}
