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
xQueueHandle queu_stat_rdy;
xQueueHandle queu_ack;
///---- send message with acknol ----------
int can_send_msg_ack(can_msg_t  *p_snd_msg){ 
int t_rez;
ack_t t_ack;
int rez=0;
CAN_wrMsg(p_snd_msg); 
t_rez=xQueueReceive(queu_ack,&t_ack,TIME_WAIT_ACK);   ////wait ready stat
if(t_rez==pdTRUE)
  {
//// check cmd ,axis    
  rez=0;  
  }
else
  rez= -1;
return rez;  
}
////===================================
int can_wait_ready(uint8_t flg_rdy){
can_msg_t  send_msg;
int t_rez;
uint8_t t_ready_stat=0;
uint8_t t_rdy=flg_rdy;
int rez=0;
printk("\n\r can_wait_ready");
for(;;){
////  send_msg.id=ID_X_CMD|ID_Y_CMD|ID_Z_CMD;
  send_msg.id=ID_X_CMD;
 send_msg.data[0]=GET_STAT_CMD;
  send_msg.len=CAN_REQ_STAT_NUM_BYTES;
  send_msg.format=STANDARD_FORMAT;
  send_msg.type=DATA_FRAME;
  CAN_wrMsg (&send_msg);
  t_rez=xQueueReceive(queu_stat_rdy,&t_ready_stat,TIME_WAIT_RDY);   ////wait ready stat
  if(t_rez==pdTRUE)
  {
  if(flg_rdy&READY_X){
    if(t_ready_stat&READY_X){
      if(curr_stat_x==STATE_READY){
        t_rdy&= ~READY_X;
        }
      }
    }
  if(flg_rdy&READY_Y){
    if(t_ready_stat&READY_Y){
      if(curr_stat_y==STATE_READY){
        t_rdy&= ~READY_Y;
        }
      }
    }
  if(flg_rdy&READY_Z){
    if(t_ready_stat&READY_Z){
      if(curr_stat_z==STATE_READY){
        t_rdy&= ~READY_Z;
        }
      }
    }
  }
  else{
    msleep(5);
  }
if(t_rdy==0)
  break;
}

return rez;
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
  can_wait_ready(READY_X);             //// wait ready X,Y,Z
 //// CAN_wrMsg (&snd_msg);
  can_send_msg_ack(&snd_msg); 
  test_print(&snd_msg);
  
  }
}
////xQueueHandle queu_can_resv;
////xQueueHandle queu_stat_rdy;

void can_rsv_task( void *pvParameters )
{
////uint8_t ii=0; 
///can_cmd_t *p_can_cmd=  (can_cmd_t *)CAN_RxMsg.data;
printk("\n\r can_rsv_task"); 
////queu_can_resv=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
queu_stat_rdy=xQueueCreate(1,sizeof(uint8_t));
queu_ack=xQueueCreate(LEN_ACK_QU,sizeof(ack_t));
 
for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
    switch(CAN_RxMsg.data[0]) {
    case PUT_ACK:
      {
      put_ack_t *p_p_ack=  (put_ack_t *)CAN_RxMsg.data;
      ack_t *p_ack=  (ack_t *)&p_p_ack->ack;
      xQueueSend(queu_ack,p_ack,CAN_TIMEOUT_SEND);   ///set stat ready 
      }
      break;
    case PUT_STAT_CMD:
        {
        put_stat_cmd_t *p_stat_cmd=  (put_stat_cmd_t *)CAN_RxMsg.data;
        if(p_stat_cmd->axis&AXIS_X)
          {
          stat_ready|= READY_X;
          curr_stat_x= p_stat_cmd->state;
          curr_x = p_stat_cmd->coord;
          printk("\r\ncurr_stat_x[%x]",curr_stat_x);
          }
         if(p_stat_cmd->axis&AXIS_Y)
          {
          stat_ready|= READY_Y;
          curr_stat_y= p_stat_cmd->state;
          curr_y = p_stat_cmd->coord;
          }
         if(p_stat_cmd->axis&AXIS_Z)
          {
          stat_ready|= READY_Z;
          curr_stat_z= p_stat_cmd->state;
          curr_z = p_stat_cmd->coord;
          }
         xQueueSend(queu_stat_rdy,&stat_ready,CAN_TIMEOUT_SEND);   ///set stat ready 
  
  /////     printk("put stat");
         
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
    msleep(5);
  }
  }
}
