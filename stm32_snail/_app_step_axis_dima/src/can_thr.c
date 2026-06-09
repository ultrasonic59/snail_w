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
#include "emul_eeprom.h"

extern can_msg_t CAN_RxMsg;

xQueueHandle queu_to_send;

int stop_mot_cmd(void)
{
cur_state &= ~STATE_MASK;
cur_state|=STATE_IDLE;  
printk("\n\rSTATE_IDLE ");
put_mot_nStep(0);
return 0;
}

int go_cmd(go_cmd_t *p_go_cmd)
{
cur_state &= ~STATE_MASK;
cur_state|=STATE_MOVE;  
printk("\n\rGo [dir=%x:per=%x:steps=%x] ",p_go_cmd->dirs,p_go_cmd->step_per,p_go_cmd->steps);

set_dir_mot(p_go_cmd->dirs);
////set_step_per(p_go_cmd->step_per);
set_mot_per(p_go_cmd->step_per);
if(use_enc){
  if(p_go_cmd->dirs==0){ ///up
    next_coord=curr_coord+p_go_cmd->steps;
  }
  else{
        next_coord=curr_coord-p_go_cmd->steps;
  }
put_mot_nStep(p_go_cmd->steps);
  
}
else{
put_mot_nStep(p_go_cmd->steps);
}
////msleep(1000);
////cur_stat=STATE_READY;  
return 0;
}
int go_cmd_conc(go_cmd_t *p_go_cmd)
{
cur_state &= ~STATE_MASK;
cur_state|=STATE_MOVE;  
///printk("\n\rGo [dir=%x:per=%x:steps=%x] ",p_go_cmd->dirs,p_go_cmd->step_per,p_go_cmd->steps);

set_dir_mot(p_go_cmd->dirs);
////set_step_per(p_go_cmd->step_per);
set_mot_per(p_go_cmd->step_per);
put_mot_nStep(p_go_cmd->steps);
return 0;
}
extern uint8_t cur_mot_rej;

int set_param(set_param_cmd_t *i_data)
{
uint8_t tmp;
uint16_t htmp;
switch(i_data->num_par)
   {
   case MOTOR_REJ:
     cur_mot_rej=i_data->par_val&0xf;
      set_mot_rej(cur_mot_rej);
      if(EE_Rd(ADDR_EEPROM_MOT_CTRL,&htmp)==0){
        htmp&= ~CTRL_MODE_MASK;
        htmp|= ((cur_mot_rej<<CTRL_MODE_OFFS)&CTRL_MODE_MASK);
        EE_Wr(ADDR_EEPROM_MOT_CTRL,htmp);
      }
      tmp= (i_data->par_val>>8)&0xff;
      set_mot_trq(tmp);
     if(EE_Rd(ADDR_EEPROM_MOT_TORQUE,&htmp)==0){
        htmp&= ~CTRL_TORQUE_MASK;
        htmp|= (tmp&CTRL_TORQUE_MASK);
        EE_Wr(ADDR_EEPROM_MOT_TORQUE,htmp);
      }
     printk("\n\r MOTOR_REJ[%d:%d]",cur_mot_rej,tmp);
    
     break;
   case SET_COORD:
     printk("\n\r SET_COORD[%x]",i_data->par_val);
    
     curr_coord=(int32_t)i_data->par_val;
     if(i_data->par_val==0){
       enc_obor=0;
       enc_offs=curr_enc;
     }
     break;
   }
return 0;
}
void    test_print(can_msg_t  *p_msg)
 {
uint8_t ii;
    printk("\n\r ExtId[%x]",p_msg->id);
    printk("\n\r DLC[%x]\n\r ",p_msg->len);
    for(ii=0;ii<p_msg->len;ii++)
      {
      printk("[%x] ",p_msg->data[ii]);
      }

 }
     
///===========================================
void can_rsv_task( void *pvParameters )
{
///  uint8_t ii=0;
printk("\n\r can_rsv_task"); 
 for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
    obr_can_cmd(CAN_RxMsg.data);
  
 ///   printk("\n\r can_rx"); 
 ///   test_print(&CAN_RxMsg);
#if 0
    printk("\n\r ExtId[%x]",CAN_RxMsg.id);
    printk("\n\r DLC[%x]\n\r ",CAN_RxMsg.len);
    for(ii=0;ii<CAN_RxMsg.len;ii++)
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

////goto_app();

queu_to_send=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
for(;;)
  {
  xQueueReceive(queu_to_send,&snd_msg,portMAX_DELAY);
////  can_wait_ready(READY_X);             //// wait ready X,Y,Z
  CAN_wrMsg (&snd_msg);
  ///  printk("\n\r can_tx"); 
  ///  test_print(&snd_msg);
  
///=================================================
////  sys.state &= ~STATE_CYCLE;

  }
}
