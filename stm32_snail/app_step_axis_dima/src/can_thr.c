#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "can.h"
#include "can_cmds.h"
#include "board.h"
#include "printk.h"
#include "emul_eeprom.h"

extern can_msg_t CAN_RxMsg;
extern volatile uint32_t num_Step;
extern uint16_t curr_enc;
extern int32_t enc_obor;
extern uint16_t enc_offs;

xQueueHandle queu_to_send;
static xQueueHandle go_cmd_queue;

volatile uint8_t can_go_step_done = 0;

void can_motion_done_if_pending(void);

static void go_cmd_run(go_cmd_t *p_go_cmd)
{
  cur_state &= ~STATE_MASK;
  cur_state|=STATE_MOVE;
  printk("\n\rGo [dir=%x:per=%x:steps=%x] ",p_go_cmd->dirs,p_go_cmd->step_per,p_go_cmd->steps);

  if(use_enc){
    set_dir_mot(p_go_cmd->dirs);
    if(p_go_cmd->dirs==0){
      next_coord=curr_coord+p_go_cmd->steps;
    }
    else{
      next_coord=curr_coord-p_go_cmd->steps;
    }
    mot_go_start(p_go_cmd->dirs, p_go_cmd->step_per, p_go_cmd->steps);
  }
  else{
    mot_go_start(p_go_cmd->dirs, p_go_cmd->step_per, p_go_cmd->steps);
  }
}

BaseType_t mot_go_try_chain_isr(BaseType_t *pxHigherPriorityTaskWoken)
{
  go_cmd_t next;

  if (go_cmd_queue == NULL) {
    return pdFALSE;
  }
  if (xQueueReceiveFromISR(go_cmd_queue, &next, pxHigherPriorityTaskWoken) != pdPASS) {
    return pdFALSE;
  }
  cur_state &= ~STATE_MASK;
  cur_state |= STATE_MOVE;
  if (use_enc) {
    set_dir_mot(next.dirs);
    if (next.dirs == 0U) {
      next_coord = curr_coord + (int32_t)next.steps;
    } else {
      next_coord = curr_coord - (int32_t)next.steps;
    }
  }
  mot_go_start(next.dirs, next.step_per, next.steps);
  return pdTRUE;
}

int go_cmd(go_cmd_t *p_go_cmd)
{
  if (num_Step == 0U && (cur_state & STATE_MASK) == STATE_IDLE) {
    go_cmd_run(p_go_cmd);
    return 0;
  }
  if (go_cmd_queue != NULL &&
      xQueueSend(go_cmd_queue, p_go_cmd, 0) == pdPASS) {
    if (num_Step == 0U && can_go_step_done) {
      can_motion_done_if_pending();
    }
    return 0;
  }
  if (num_Step == 0U) {
    can_go_step_done = 0U;
    go_cmd_run(p_go_cmd);
    return 0;
  }
  return -1;
}

int stop_mot_cmd(void)
{
  go_cmd_queue_clear();
  cur_state &= ~STATE_MASK;
  cur_state|=STATE_IDLE;
  put_can_cmd_stat(cur_state, (uint32_t)curr_coord);
  put_mot_nStep(0);
  return 0;
}

void go_cmd_queue_clear(void)
{
  go_cmd_t dummy;

  if (go_cmd_queue != NULL) {
    while (xQueueReceive(go_cmd_queue, &dummy, 0) == pdPASS) {
    }
  }
}

void can_motion_done_if_pending(void)
{
  go_cmd_t cmd;

  if (can_go_step_done) {
    can_go_step_done = 0;
    if (go_cmd_queue != NULL &&
        xQueueReceive(go_cmd_queue, &cmd, 0) == pdPASS) {
      go_cmd_run(&cmd);
      return;
    }
    cur_state &= ~STATE_MASK;
    cur_state |= STATE_IDLE;
    put_can_cmd_stat(cur_state, (uint32_t)curr_coord);
    return;
  }
  can_stat_notify_if_pending();
}

int go_cmd_conc(go_cmd_t *p_go_cmd)
{
  return go_cmd(p_go_cmd);
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
static void can_rx_log_go(const can_msg_t *p_msg)
{
  uint8_t ii;

  if (p_msg->data[0] != GO_CMD && p_msg->data[0] != STOP_CMD) {
    return;
  }
  printk("\r\nCAN rx id=0x%X len=%u data:", (unsigned)p_msg->id, (unsigned)p_msg->len);
  for (ii = 0; ii < p_msg->len; ii++) {
    printk(" %02X", p_msg->data[ii]);
  }
  if (p_msg->data[0] == GO_CMD && p_msg->len >= sizeof(go_cmd_t)) {
    go_cmd_t *g = (go_cmd_t *)p_msg->data;
    printk(" GO dir=%u per=%u steps=%lu",
           (unsigned)g->dirs, (unsigned)g->step_per, (unsigned long)g->steps);
  }
  printk("\r\n");
}

static int can_rx_snapshot(can_msg_t *dst)
{
  __disable_irq();
  if (!CAN_RxRdy) {
    __enable_irq();
    return 0;
  }
  CAN_RxRdy = 0;
  memcpy(dst, &CAN_RxMsg, sizeof(*dst));
  __enable_irq();
  return 1;
}

void can_rsv_task( void *pvParameters )
{
can_msg_t rx;
printk("\r\ncan_rsv_task rx_log=v4 %s %s", __DATE__, __TIME__);
 for(;;)
  {
  can_motion_done_if_pending();
  if( CAN_RxRdy)
    {
    if (can_rx_snapshot(&rx)) {
      can_rx_log_go(&rx);
      obr_can_cmd(rx.data);
    }
    }
  else
  {
    msleep(1);
  }
  }
}

void can_send_thread(void* pp)
{
can_msg_t  snd_msg;

(void)pp;
printk("\n\r can_send_thread");

queu_to_send=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
go_cmd_queue=xQueueCreate(8,sizeof(go_cmd_t));
for(;;)
  {
  can_motion_done_if_pending();
  if (xQueueReceive(queu_to_send,&snd_msg,1) == pdPASS) {
    CAN_wrMsg (&snd_msg);
  }
  }
}
