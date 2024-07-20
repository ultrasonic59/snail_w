#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "cam_can_brd.h"
#include "can.h"
#include "can_cmds.h"
#include "debug.h"
#include "can_thr.h"

QueueHandle_t queu_to_send;
uint8_t         CAN_RxRdy = 0;              /* CAN HW received a message        */

int stop_mot_cmd(void)
{
cur_stat=STATE_IDLE;
printf("\n\rSTATE_IDLE ");
///put_mot_nstep(0);
return 0;
}
int go_cmd(go_cmd_t *p_go_cmd)
{
///cur_stat=STATE_MOVE;
//// printf("\n\rGo [dir=%x:per=%x:steps=%x] ",p_go_cmd->dirs,p_go_cmd->step_per,p_go_cmd->steps);

///set_dir_mot(p_go_cmd->dirs);
////set_step_per(p_go_cmd->step_per);
///set_mot_per(p_go_cmd->step_per);
////put_mot_nstep(p_go_cmd->steps);
return 0;
}

void can_rsv_thr( void *pvParameters )
{
uint8_t ii=0;
printf(" can_rsv_task \n\r");
#if 1
 for(;;)
  {
  if(CAN_RxRdy)
    {
    CAN_RxRdy=0;
    obr_can_cmd(CAN_RxMsg.data);
#if 1
    printf("\n\r can_rx");
    printf("\n\r ExtId[%x]",CAN_RxMsg.id);
    printf("\n\r DLC[%x]\n\r ",CAN_RxMsg.len);
    for(ii=0;ii<CAN_RxMsg.len;ii++)
      {
      printf("[%x] ",CAN_RxMsg.data[ii]);
      }
    printf("\n\r ");
#endif
    }
  else
  {
    msleep(20);
  }
  }
#endif
}

void can_send_thr(void* pp)
{
can_msg_t  snd_msg;

printf(" can_send_thr\n\r");

////goto_app();
#if 1
queu_to_send=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
if(queu_to_send==NULL)
   {
    printf(" error queu_to_send\n\r");
    }
for(;;)
  {
  xQueueReceive(queu_to_send,&snd_msg,portMAX_DELAY);
////  can_wait_ready(READY_X);             //// wait ready X,Y,Z
  CAN_wrMsg (&snd_msg);

  }
#endif
}

