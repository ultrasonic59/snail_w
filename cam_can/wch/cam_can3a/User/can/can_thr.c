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
extern TimerHandle_t timer_doza;

int put_doza(doza_cmd_t *p_cmd)
{
    printf("\n\rput_doza[%x] ",p_cmd->time);
    on_off_dv(0x1) ;
    xTimerChangePeriod(timer_doza,p_cmd->time,0);
    xTimerStart(timer_doza, 0);
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

