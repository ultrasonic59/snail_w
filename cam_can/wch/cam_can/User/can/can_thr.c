#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "cam_can_brd.h"
#include "can_cmds.h"
#include "debug.h"

#if 0
#include "can.h"
#include "can_cmds.h"
#include "board.h"
#include "printk.h"

extern can_msg_t CAN_RxMsg;

xQueueHandle queu_to_send;
int stop_mot_cmd(void)
{
cur_stat=STATE_IDLE;  
printk("\n\rSTATE_IDLE ");

put_mot_nstep(0);
return 0;
}

int go_cmd(go_cmd_t *p_go_cmd)
{
cur_stat=STATE_MOVE;  
printk("\n\rGo [dir=%x:per=%x:steps=%x] ",p_go_cmd->dirs,p_go_cmd->step_per,p_go_cmd->steps);

set_dir_mot(p_go_cmd->dirs);
////set_step_per(p_go_cmd->step_per);
set_mot_per(p_go_cmd->step_per);
put_mot_nstep(p_go_cmd->steps);
////msleep(1000);
////cur_stat=STATE_READY;  
return 0;
}
#endif

void can_rsv_task( void *pvParameters )
{
printf("\n\r can_rsv_task");
#if 0
 for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
    obr_can_cmd(CAN_RxMsg.data);
#if 0   
    switch(CAN_RxMsg.data[0]) {
      case GO_CMD:
        {
        put_can_ack(GO_CMD);
          
        go_cmd((go_cmd_t *)CAN_RxMsg.data);
  ////       printk("Go [dir=%x:per=%d:steps=%d] ",p_can_cmd->dirs,p_can_cmd->step_per,p_can_cmd->steps);
         
        }
        break;
      case GET_STAT_CMD:
        {
        put_can_cmd_stat(cur_stat,cur_coord);
         printk("[stat=%x] ",cur_stat);

         }
        break;
        
    default:
      break;
    }
#endif
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
#endif
}

void can_send_thread(void* pp)
{
#if 0
can_msg_t  snd_msg;

printk("\n\r can_send_thread");

////goto_app();

queu_to_send=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
for(;;)
  {
  xQueueReceive(queu_to_send,&snd_msg,portMAX_DELAY);
////  can_wait_ready(READY_X);             //// wait ready X,Y,Z
  CAN_wrMsg (&snd_msg);
  
 //// test_print(&snd_msg);
  
 ////  tst_print();
///  set_curr_dir(st.dir_outbits);
////  obr_segment();
///=================================================
////  sys.state &= ~STATE_CYCLE;

  }
#endif
}
