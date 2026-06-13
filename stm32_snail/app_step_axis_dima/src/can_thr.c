#include <string.h>
#include "tx_api.h"
#include "threadx_app.h"

#include "can.h"
#include "can_cmds.h"
#include "board.h"
#include "printk.h"
#include "emul_eeprom.h"

extern volatile uint32_t num_Step;
extern uint16_t curr_enc;
extern int32_t enc_obor;
extern uint16_t enc_offs;

static tx_app_queue_t *queu_to_send;
static TX_SEMAPHORE can_rx_sem;
static UCHAR can_rx_sem_ready = 0U;

volatile uint8_t can_go_step_done = 0;

#define GO_CHAIN_CAP  128U
#define GO_IDLE_DEFER_TICKS  50U
static go_cmd_t go_chain_buf[GO_CHAIN_CAP];
static volatile uint8_t go_chain_rd;
static volatile uint8_t go_chain_wr;
static volatile uint8_t go_stream_active = 0U;
static volatile uint8_t go_idle_armed = 0U;
static ULONG go_idle_arm_tick = 0U;

void can_motion_done_if_pending(void);

void can_rx_signal_from_isr(void)
{
  if (can_rx_sem_ready) {
    tx_semaphore_put(&can_rx_sem);
  }
}

static void go_chain_reset(void)
{
  UINT interrupt_save;

  interrupt_save = tx_interrupt_control(TX_INT_DISABLE);
  go_chain_rd = 0U;
  go_chain_wr = 0U;
  tx_interrupt_control(interrupt_save);
}

static int go_chain_push(const go_cmd_t *cmd)
{
  uint8_t wr;
  uint8_t next;

  __disable_irq();
  wr = go_chain_wr;
  next = (uint8_t)(wr + 1U);
  if (next >= GO_CHAIN_CAP) {
    next = 0U;
  }
  if (next == go_chain_rd) {
    __enable_irq();
    return -1;
  }
  go_chain_buf[wr] = *cmd;
  go_chain_wr = next;
  __enable_irq();
  return 0;
}

static int go_chain_pop_thread(go_cmd_t *cmd)
{
  UINT interrupt_save;
  uint8_t rd;
  int rc = -1;

  interrupt_save = tx_interrupt_control(TX_INT_DISABLE);
  rd = go_chain_rd;
  if (rd != go_chain_wr) {
    *cmd = go_chain_buf[rd];
    go_chain_rd = (uint8_t)(rd + 1U);
    if (go_chain_rd >= GO_CHAIN_CAP) {
      go_chain_rd = 0U;
    }
    rc = 0;
  }
  tx_interrupt_control(interrupt_save);
  return rc;
}

static uint8_t go_chain_has_pending(void)
{
  uint8_t has_pending;

  __disable_irq();
  has_pending = (go_chain_rd != go_chain_wr) ? 1U : 0U;
  __enable_irq();
  return has_pending;
}

static int go_chain_pop_isr(go_cmd_t *cmd)
{
  uint8_t rd;

  __disable_irq();
  rd = go_chain_rd;
  if (rd == go_chain_wr) {
    __enable_irq();
    return -1;
  }
  *cmd = go_chain_buf[rd];
  go_chain_rd = (uint8_t)(rd + 1U);
  if (go_chain_rd >= GO_CHAIN_CAP) {
    go_chain_rd = 0U;
  }
  __enable_irq();
  return 0;
}

static void go_cmd_continue(go_cmd_t *p_go_cmd)
{
  go_idle_armed = 0U;
  go_stream_active = 1U;
  cur_state &= ~STATE_MASK;
  cur_state |= STATE_MOVE;

  if (use_enc) {
    set_dir_mot(p_go_cmd->dirs);
    if (p_go_cmd->dirs == 0U) {
      next_coord = curr_coord + (int32_t)p_go_cmd->steps;
    } else {
      next_coord = curr_coord - (int32_t)p_go_cmd->steps;
    }
  }
  mot_go_chain(p_go_cmd->dirs, p_go_cmd->step_per, p_go_cmd->steps);
}

static void go_idle_finalize(void)
{
  go_idle_armed = 0U;
  go_stream_active = 0U;
  cur_state &= ~STATE_MASK;
  cur_state |= STATE_IDLE;
  put_can_cmd_stat(cur_state, (uint32_t)curr_coord);
}

static void go_idle_arm(void)
{
  go_idle_armed = 1U;
  go_idle_arm_tick = tx_time_get();
}

static void go_idle_try_finalize(void)
{
  ULONG now;

  if (!go_idle_armed || num_Step != 0U) {
    return;
  }
  if (go_chain_rd != go_chain_wr) {
    return;
  }
  now = tx_time_get();
  if ((now - go_idle_arm_tick) < (ULONG)GO_IDLE_DEFER_TICKS) {
    return;
  }
  go_idle_finalize();
}

static void go_cmd_run(go_cmd_t *p_go_cmd)
{
  go_idle_armed = 0U;
  go_stream_active = 1U;
  cur_state &= ~STATE_MASK;
  cur_state|=STATE_MOVE;

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

UINT mot_go_try_chain_isr(void)
{
  go_cmd_t next;

  if (go_chain_pop_isr(&next) != 0) {
    return 0U;
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
  mot_go_chain(next.dirs, next.step_per, next.steps);
  return 1U;
}

static void go_cmd_apply(go_cmd_t *p_go_cmd)
{
  go_idle_armed = 0U;

  if (num_Step > 0U || go_chain_has_pending()) {
    if (go_chain_push(p_go_cmd) == 0) {
      if (num_Step == 0U && can_go_step_done) {
        can_motion_done_if_pending();
      }
      return;
    }
    return;
  }

  if (can_go_step_done || go_stream_active || go_idle_armed) {
    can_go_step_done = 0U;
    go_idle_armed = 0U;
    go_cmd_continue(p_go_cmd);
    return;
  }

  go_cmd_run(p_go_cmd);
}

int go_cmd(go_cmd_t *p_go_cmd)
{
  go_cmd_apply(p_go_cmd);
  return 0;
}

int stop_mot_cmd(void)
{
  go_cmd_queue_clear();
  go_idle_armed = 0U;
  go_stream_active = 0U;
  cur_state &= ~STATE_MASK;
  cur_state|=STATE_IDLE;
  put_can_cmd_stat(cur_state, (uint32_t)curr_coord);
  put_mot_nStep(0);
  return 0;
}

void go_cmd_queue_clear(void)
{
  go_chain_reset();
}

void can_motion_done_if_pending(void)
{
  go_cmd_t cmd;

  if (can_go_step_done) {
    can_go_step_done = 0U;
    if (go_chain_pop_thread(&cmd) == 0) {
      go_cmd_continue(&cmd);
      return;
    }
    if (go_stream_active) {
      go_idle_arm();
      return;
    }
    go_idle_finalize();
    return;
  }
  go_idle_try_finalize();
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
static int can_rx_snapshot(can_msg_t *dst)
{
  return CAN_rx_pop(dst);
}

void can_rsv_task( void *pvParameters )
{
can_msg_t rx;
(void)pvParameters;
printk("\r\ncan_rsv_task %s %s", __DATE__, __TIME__);
if (tx_semaphore_create(&can_rx_sem, "can_rx_sem", 0U) == TX_SUCCESS) {
  can_rx_sem_ready = 1U;
}
 for(;;)
  {
  can_motion_done_if_pending();
  if (can_rx_snapshot(&rx)) {
    do {
      obr_can_cmd(rx.data);
    } while (can_rx_snapshot(&rx));
  } else {
    tx_semaphore_get(&can_rx_sem, 1U);
  }
  }
}

void can_send_thread(void* pp)
{
can_msg_t  snd_msg;

(void)pp;
printk("\n\r can_send_thread");

if (tx_app_queue_create(&queu_to_send, sizeof(can_msg_t), CAN_MAX_LEN_QUEU) != TX_SUCCESS) {
  return;
}
for(;;)
  {
  can_motion_done_if_pending();
  if (tx_app_queue_receive(queu_to_send, &snd_msg, 1U) == TX_SUCCESS) {
    CAN_wrMsg (&snd_msg);
  }
  }
}

tx_app_queue_t *can_tx_queue(void)
{
  return queu_to_send;
}
