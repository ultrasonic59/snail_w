#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "threadx_app.h"
#include "board.h"
#include "can.h"
#include "can_cmds.h"
#include "printk.h"
#include "my_misc.h"
#include "emul_eeprom.h"

////=======================================
extern uint8_t boot_state;
extern void put_tst_pin(uint8_t idat);
extern void put_tst1_pin(uint8_t idat);

extern tx_app_queue_t *can_tx_queue(void);

#ifndef CAN_LOG_GO_RX
#define CAN_LOG_GO_RX  1
#endif

int put_can_cmd_reset_all(void)
{
  return 0;
}

void _mc_reset(void)
{
put_can_cmd_reset_all();
////report_init_message();
}
int put_can_cmd_go(uint8_t dirs,uint16_t per
                   ,uint32_t step_x
                   ,uint32_t step_y
                   ,uint32_t step_z)
{
///uint8_t btst=0;
can_msg_t  send_msg;
go_cmd_t t_go_cmd;
t_go_cmd.cmd=GO_CMD ;
t_go_cmd.dirs=dirs;
t_go_cmd.step_per=per;
send_msg.len=CAN_MAX_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
if(step_x)
  {
   t_go_cmd.steps=step_x;
   memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
   send_msg.id=ID_BRD;
   tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);
  }
if(step_y)
  {
   t_go_cmd.steps=step_y;
   memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
   send_msg.id=ID_BRD;
   tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);
  }
if(step_z)
  {
   t_go_cmd.steps=step_z;
   memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
   send_msg.id=ID_BRD;
   tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);
  }

////send_msg.data[1]=btst;
////tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

///go_cmd_t   go_cmd;
#if 0
        printk("\n\r tst_cnt[%d][%02x][%d][%d][%d]", per, dirs
            , step_x
            , step_y
            , step_z
        );
#endif

  return 0;
}
////================================================
#ifndef _MASTER_
int put_can_cmd_encoder(encoder_data_t idata)
{
///uint8_t btst=0;
can_msg_t  send_msg;
encoder_cmd_t t_put_encoder_cmd;
t_put_encoder_cmd.cmd=PUT_ENCODER_CMD ;
t_put_encoder_cmd.axis= AXIS_BRD;

t_put_encoder_cmd.coord=idata.Coord;
t_put_encoder_cmd.temp_val=idata.val;

////t_put_encoder_cmd.state=cur_state;
send_msg.len=CAN_MAX_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,&t_put_encoder_cmd,sizeof(encoder_cmd_t));
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}
int put_can_cmd_enc_coord(encoder_data_t idata)
{
///uint8_t btst=0;
can_msg_t  send_msg;
encoder_cmd_t t_put_encoder_cmd;
t_put_encoder_cmd.cmd=PUT_ENC_COORD_CMD ;
t_put_encoder_cmd.axis= AXIS_BRD;

t_put_encoder_cmd.coord=idata.Coord;
t_put_encoder_cmd.temp_val=idata.val;

////t_put_encoder_cmd.state=cur_state;
send_msg.len=CAN_MAX_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,&t_put_encoder_cmd,sizeof(encoder_cmd_t));
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}

int put_can_cmd_stat(uint8_t state
                   ,uint32_t coord)
{
///uint8_t btst=0;
can_msg_t  send_msg;
put_stat_cmd_t t_put_stat_cmd;
t_put_stat_cmd.cmd=PUT_STAT_CMD ;
t_put_stat_cmd.axis= AXIS_BRD;

////t_put_stat_cmd.coord=cur_coord;
///t_put_stat_cmd.state=cur_stat;
t_put_stat_cmd.coord=coord;
t_put_stat_cmd.state=state;
send_msg.len=CAN_MAX_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,&t_put_stat_cmd,sizeof(put_stat_cmd_t));
send_msg.id=ID_MASTER_CMD;
put_tst_pin(0U);
CAN_wrMsg(&send_msg);

  return 0;
}

volatile uint8_t can_stat_notify = 0;

void can_stat_notify_if_pending(void)
{
  if (can_stat_notify) {
    can_stat_notify = 0;
    put_can_cmd_stat(cur_state, (uint32_t)curr_coord);
  }
}

int put_can_boot_ans(uint8_t cmd,uint8_t state)
{
can_msg_t  send_msg;
put_boot_stat_cmd_t t_put_stat_cmd;
t_put_stat_cmd.cmd=cmd ;
t_put_stat_cmd.axis= AXIS_BRD;
t_put_stat_cmd.state=state;
send_msg.len=sizeof(put_boot_stat_cmd_t);
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,&t_put_stat_cmd,sizeof(put_boot_stat_cmd_t));
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}
int put_can_boot_cmd_stat(uint8_t state)
{
return put_can_boot_ans(PUT_BOOT_STAT,state);
}

int put_can_rd_eeprom_ans(rd_eeprom_ans_t *t_rd_eeprom_ans)
{
can_msg_t  send_msg;
can_cmd_t t_can_cmd;
t_can_cmd.data[0]=RD_EEPROM_ANS ;
t_can_cmd.data[1]=t_rd_eeprom_ans->num_dates;
t_can_cmd.data[2]=t_rd_eeprom_ans->addr;
memcpy(&t_can_cmd.data[3],t_rd_eeprom_ans->data,sizeof(uint16_t)*t_rd_eeprom_ans->num_dates);
send_msg.len= 3+sizeof(uint16_t)*t_rd_eeprom_ans->num_dates;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,t_can_cmd.data,3+sizeof(uint16_t)*t_rd_eeprom_ans->num_dates);
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}
int put_can_rd_spi_mot_ans(spi_mot_cmd_t *t_ans)
{
can_msg_t  send_msg;
can_cmd_t t_can_cmd;
memcpy(&t_can_cmd.data,t_ans,sizeof(spi_mot_cmd_t));

send_msg.len= 3+sizeof(uint8_t)*t_ans->len_dat;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,t_can_cmd.data,3+sizeof(uint8_t)*t_ans->len_dat);
///memcpy(send_msg.data,t_can_cmd.data,3+sizeof(uint8_t)*send_msg.len);
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);
return 0;
}

int put_can_wr_eeprom_ans(wr_eeprom_req_t *t_wr_eeprom_ans)
{
can_msg_t  send_msg;
can_cmd_t t_can_cmd;
t_can_cmd.data[0]=WR_EEPROM_ANS ;
t_can_cmd.data[1]=t_wr_eeprom_ans->num_dates;
t_can_cmd.data[2]=t_wr_eeprom_ans->addr;
send_msg.len= 3;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,t_can_cmd.data,3);
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}

int put_can_ack(uint8_t cmd )
{
///uint8_t btst=0;
can_msg_t  send_msg;

put_ack_t t_put_ack;

t_put_ack.cmd=PUT_ACK ;
t_put_ack.ack.axis= AXIS_BRD;

 t_put_ack.ack.ack_cmd=cmd;
send_msg.len= sizeof(put_ack_t);
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,&t_put_ack,sizeof(put_ack_t));
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}

#endif
int put_can_rd_flash_ans(rd_flash_ans_t *t_rd_flash_ans)
{
can_msg_t  send_msg;
can_cmd_t t_can_cmd;
t_can_cmd.data[0]=RD_FLASH_ANS ;

memcpy(&t_can_cmd.data[1],&t_rd_flash_ans->addr,sizeof(uint32_t));

memcpy(&t_can_cmd.data[5],&t_rd_flash_ans->data,sizeof(uint16_t));
send_msg.len= 7;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
memcpy(send_msg.data,t_can_cmd.data,5+sizeof(uint16_t));
send_msg.id=ID_MASTER_CMD;
tx_app_queue_send(can_tx_queue(), &send_msg, (ULONG)CAN_TIMEOUT_SEND);

  return 0;
}

void rd_flash_dat(rd_flash_ans_t *t_rd_flash_ans)
{
uint16_t t_data;
t_data= *(uint16_t*)(t_rd_flash_ans->addr);
t_rd_flash_ans->data=t_data;
///printk("\n\rflash [%x:%x] ===",t_rd_flash_ans->addr,t_rd_flash_ans->data);
}

void rd_eeprom_dat(rd_eeprom_ans_t *t_rd_eeprom_ans)
{

if(t_rd_eeprom_ans->num_dates==0)
  return;
if(EE_Rd(t_rd_eeprom_ans->addr,&t_rd_eeprom_ans->data[0])!=0)
  {

  t_rd_eeprom_ans->num_dates=0;
  return;
  }
  printk("\n\rdat0[%x] ===",t_rd_eeprom_ans->data[0]);
if(t_rd_eeprom_ans->num_dates==2)
  {
  if(EE_Rd(t_rd_eeprom_ans->addr+1,&t_rd_eeprom_ans->data[1])!=0)
    {
    t_rd_eeprom_ans->num_dates=1;
    return;
    }
  }
 //// printk(" dat1[%x] ===",t_rd_eeprom_ans->data[1]);

}

void wr_eeprom_dat(wr_eeprom_req_t *t_wr_eeprom_req)
{
  printk("\n\r wr dat0[%x:%x] ===",t_wr_eeprom_req->addr,t_wr_eeprom_req->data[0]);

if(t_wr_eeprom_req->num_dates==0)
  return;
if(EE_Wr(t_wr_eeprom_req->addr,t_wr_eeprom_req->data[0])!=0)
  {
  t_wr_eeprom_req->num_dates=0;
  return;
  }
if(t_wr_eeprom_req->num_dates==2)
  {
  if(EE_Wr(t_wr_eeprom_req->addr+1,t_wr_eeprom_req->data[1])!=0)
    {
    t_wr_eeprom_req->num_dates=1;
    return;
    }
  }
}

static uint8_t prev_state=0xff;
int obr_can_cmd(uint8_t *data)
{
////uint8_t tmp;
switch(data[0]) {
      case STOP_CMD:
        put_can_ack(STOP_CMD);
        stop_mot_cmd();
        break;
      case GO_CMD:
        {
        go_cmd_t *p_go_cmd = (go_cmd_t *)data;
#if CAN_LOG_GO_RX
        printk("\n\rRGO [dir=%x:per=%x:steps=%x] ",
               p_go_cmd->dirs, p_go_cmd->step_per, (unsigned)p_go_cmd->steps);
#endif
        if (go_cmd(p_go_cmd) >= 0) {
          put_can_ack(GO_CMD);
        }
        }
        break;
      case GET_STAT_CMD:
        {
        uint8_t tmp;
        put_tst_pin(1U);
        put_tst1_pin(0);
       tmp=get_conc_n();
        tmp<<=4;
        cur_state&= ~CONC_MASK;
        cur_state |= tmp;
        put_can_cmd_stat(cur_state,curr_coord);
        ///put_can_cmd_encoder(resiv_enc);
        if(prev_state!=cur_state){
         prev_state=cur_state;
        }
         }
        break;
      case GET_ENCODER_CMD:
        {
   ///     uint8_t tmp=get_conc_n();
   //     tmp<<=4;
    //    cur_state&= ~CONC_MASK;
    //    cur_state |= tmp;
 ///       put_can_cmd_encoder(resiv_enc);
 ///       printk("[enc=%x:%d] \n\r",resiv_enc.Coord,resiv_enc.Coord);
         }
        break;

      case SET_PARAM:
         put_can_ack(SET_PARAM);
         set_param((set_param_cmd_t *)(data));
        break;
       case WR_SPI_MOT:
         put_can_ack(WR_SPI_MOT);
         wr_spi_mot((spi_mot_cmd_t *)(data));
        break;
       case RD_SPI_MOT_REQ:
         {
         spi_mot_cmd_t  ans_spi_mot_cmd;
         memcpy((void*)&ans_spi_mot_cmd,data,sizeof(spi_mot_cmd_t));
         rd_spi_mot(&ans_spi_mot_cmd);
         put_can_rd_spi_mot_ans(&ans_spi_mot_cmd);
          }
        break;
       case GET_BOOT_STAT:
        put_can_boot_cmd_stat(boot_state);
        printk("[stat=%x] ",boot_state);
        break;
       case GO_TO_BOOTER:
 ////       EE_WriteVariable(ADDR_EEPROM_BOOT_WORK,0);  ///???
        goto_booter();
        break;
      case CHECK_CONN:
         put_can_ack(CHECK_CONN );
 ////   printk("CHECK_CONN[%x] ",cur_stat);
        break;
      case RD_EEPROM_REQ:
        {
        rd_eeprom_ans_t t_rd_eeprom_ans;
        t_rd_eeprom_ans.num_dates=data[1];
        t_rd_eeprom_ans.addr=data[2];
        rd_eeprom_dat(&t_rd_eeprom_ans);
        put_can_rd_eeprom_ans(&t_rd_eeprom_ans);
////     printk("RD_EEPROM_REQ ");
        }
        break;
      case WR_EEPROM_REQ:
        {
        wr_eeprom_req_t t_wr_eeprom_req;
        t_wr_eeprom_req.num_dates=data[1];
        t_wr_eeprom_req.addr=data[2];
        memcpy(t_wr_eeprom_req.data,&data[3],sizeof(uint16_t)*t_wr_eeprom_req.num_dates);
        wr_eeprom_dat(&t_wr_eeprom_req);
        put_can_wr_eeprom_ans(&t_wr_eeprom_req);
 ////    printk("WR_EEPROM_REQ ");
        }
        break;
      case RD_FLASH_REQ:
        {
        rd_flash_ans_t t_rd_flash_ans;
        memcpy(&t_rd_flash_ans.addr,&data[1],sizeof(uint32_t));
        rd_flash_dat(&t_rd_flash_ans);
        put_can_rd_flash_ans(&t_rd_flash_ans);
////     printk("RD_EEPROM_REQ ");
        }
        break;
     default:
      break;
    }
return 0;
}
////======================================================
