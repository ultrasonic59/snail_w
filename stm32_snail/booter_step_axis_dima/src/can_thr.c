#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
///#include "stm32f2xx_gpio.h"
///#include "stm32f2xx_rcc.h"

#include "can.h"
#include "can_cmds.h"
#include "board.h"
#include "printk.h"

extern can_msg_t CAN_RxMsg;

xQueueHandle queu_to_send;

int go_cmd(go_cmd_t *p_go_cmd)
{
#ifndef BOOTER  
cur_stat=STATE_MOVE;  
printk("\n\rGo [dir=%x:per=%x:steps=%x] ",p_go_cmd->dirs,p_go_cmd->step_per,p_go_cmd->steps);

set_dir_mot(p_go_cmd->dirs);
////set_step_per(p_go_cmd->step_per);
set_mot_per(p_go_cmd->step_per);
put_mot_nstep(p_go_cmd->steps);
#endif
return 0;
}

void can_rsv_task( void *pvParameters )
{
////  uint8_t ii;
printk("\n\r can_rsv_task"); 
 for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
 ////=============================== 
#if 0    
    printk("\n\r can_rx"); 
    printk(" ExtId[%x]",CAN_RxMsg.id);
    printk(" DLC[%x] \n\r ",CAN_RxMsg.len);
    for(ii=0;ii<CAN_RxMsg.len;ii++)
      {
      printk("[%x] ",CAN_RxMsg.data[ii]);
      }
#endif 
 ////===============================   
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
}

void can_send_thread(void* pp)
{
can_msg_t  snd_msg;

printk("\n\r can_send_thread");

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
}
