#include <string.h>
#include "board.h"
#include "printk.h"

#include "snail_can_cmds.h"
#include "can.h"
#include "can_cmds.h"
#include "emul_eeprom.h"
#include "hdlc.h"

extern volatile uint8_t can_go_step_done;
extern uint8_t cur_state;
extern UINT mot_go_try_chain_isr(void);

volatile uint32_t num_Step = 0U;
static void stop_mot_step_tim(void);

uint8_t cur_mot_rej=DEF_MOT_REJ;
static uint8_t cur_mot_dir=0;
int32_t next_coord=0;

cmd_t cur_cmd={0};
void mot_spi_wr(uint8_t addr,uint16_t idata);
uint16_t mot_spi_rd(uint8_t addr);
void mot_spi_init(void);

void motor_task( void *pvParameters )
{
///  int ii=0;
 /// uint16_t t_len=0;
uint8_t btst=0;
uint8_t psk=0;
///uint16_t tst;
char key=0;
int nstep=300;
uint8_t dir=0;
uint8_t mot_rej=0;
printk("\n\r motor_task");
motor_init();

#if 0
set_sleep_mot(1);
////set_ena_mot(1);
set_reset_mot(1);
uDelay(1000);
set_reset_mot(0);
uDelay(20000);
init_step_mot();
////set_ena_mot(0);
///tst=mot_spi_rd(0x0);
///tst|=0x1;
///mot_spi_wr(0x0,tst);
 ena_mot(0) ;
#endif

for(;;)
{
/*
  if( g_hdlc.len_obr_dat){
    t_len=g_hdlc.len_obr_dat;
    g_hdlc.len_obr_dat=0;
        printk("\n\r len[%x]",t_len);

    for(ii=0;ii<t_len;ii++){
         printk("%x=[%x] ",ii,g_hdlc.obr_buff[ii]   );

    }

  }
*/
if(check_push_key_dbg())
  {
  key=get_byte_dbg() ;
  switch(key)
    {
    case 'a':
      nstep += 100;
      break;
    case 's':
      if(nstep)
        nstep-= 100;
        break;
    case 'd':
      dir ++;
      dir&=0x1;
      break;
    case 'm':
      mot_rej ++;
      if(mot_rej>8)
        mot_rej=0;
 ////     mot_rej&=0x7;
      break;
    case 'p':
      ena_check_conc=0;
     psk=1;
      break;
    case 'P':
          ena_check_conc=1;

     psk=1;
      break;
   case 'z':
     print_mot_reg();
      break;

   }
  btst = get_conc_n();

  printk("\n\r nstep[%d] dir[%x] Mot_rej[%x] chk_conc[%x] conc=[%x]",nstep,dir,mot_rej,ena_check_conc,btst);
  set_dir_mot(dir);
  set_mot_rej(mot_rej);
  if(psk)
    {
    put_mot_nStep(nstep);
    psk=0;
    }

  }
}
}

///=============================================
////==============================================
void mot_spi_init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;
  MOT_SPI_PeriphClockCmd(MOT_SPI_RCC, ENABLE);

RCC_AHB1PeriphClockCmd(MOT_SPI_SCK_PIN_RCC,ENABLE);
RCC_AHB1PeriphClockCmd(MOT_SPI_MISO_PIN_RCC,ENABLE);
RCC_AHB1PeriphClockCmd(MOT_SPI_MOSI_PIN_RCC,ENABLE);
////RCC_AHB1PeriphClockCmd(MOT_SPI_SCS_PIN_RCC,ENABLE);

GPIO_PinAFConfig(MOT_SPI_SCK_PIN_GPIO, MOT_SPI_SCK_PIN_NPIN, MOT_SPI_AF);
GPIO_PinAFConfig(MOT_SPI_MISO_PIN_GPIO, MOT_SPI_MISO_PIN_NPIN, MOT_SPI_AF);
GPIO_PinAFConfig(MOT_SPI_MOSI_PIN_GPIO, MOT_SPI_MOSI_PIN_NPIN, MOT_SPI_AF);
////GPIO_PinAFConfig(MOT_SPI_SCS_PIN_GPIO, MOT_SPI_SCS_PIN_NPIN, MOT_SPI_AF);

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
///GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Pin = MOT_SPI_MISO_PIN;
GPIO_Init(MOT_SPI_MISO_PIN_GPIO, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Pin = MOT_SPI_SCK_PIN;
GPIO_Init(MOT_SPI_SCK_PIN_GPIO, &GPIO_InitStructure);
////GPIO_InitStructure.GPIO_Pin = MOT_SPI_MISO_PIN;
/////GPIO_Init(MOT_SPI_MISO_PIN_GPIO, &GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = MOT_SPI_MOSI_PIN;
GPIO_Init(MOT_SPI_MOSI_PIN_GPIO, &GPIO_InitStructure);

////GPIO_InitStructure.GPIO_Pin = MOT_SPI_SCS_PIN;
/////GPIO_Init(MOT_SPI_SCS_PIN_GPIO, &GPIO_InitStructure);

SPI_I2S_DeInit(MOT_SPI);
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;///SPI_NSS_Hard;///SPI_NSS_Soft;///SPI_NSS_Hard;
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_InitStructure.SPI_CRCPolynomial = 7;
SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
SPI_Init(MOT_SPI, &SPI_InitStructure);
SPI_Cmd(MOT_SPI, ENABLE);
}
uint16_t mot_spi_transfer(uint16_t i_data)
{
uint16_t rez=0;
GPIO_SetBits(MOT_SPI_SCS_PIN_GPIO, MOT_SPI_SCS_PIN);

while (SPI_I2S_GetFlagStatus(MOT_SPI, SPI_I2S_FLAG_TXE) == RESET);
SPI_I2S_SendData(MOT_SPI, i_data);
while (SPI_I2S_GetFlagStatus(MOT_SPI, SPI_I2S_FLAG_RXNE) == RESET);
while (SPI_I2S_GetFlagStatus(MOT_SPI, SPI_I2S_FLAG_TXE) == RESET);
rez=SPI_I2S_ReceiveData(MOT_SPI);
GPIO_ResetBits(MOT_SPI_SCS_PIN_GPIO, MOT_SPI_SCS_PIN);
return rez;
}
////==============================================
void mot_spi_set_br(uint16_t br)
{
uint16_t tmpreg = 0;
tmpreg = MOT_SPI->CR1& ~(0x7<<3);
tmpreg |=	br&(0x7<<3);
MOT_SPI->CR1=tmpreg;
}

void mot_spi_wr(uint8_t addr,uint16_t idata)
{
uint16_t tmp;
tmp=(addr&0x7)<<12;
tmp|= idata&0xfff;
mot_spi_transfer(tmp);
///printk("\n\r mot_spi_wr[%x:%x]",addr,idata);
}
void mot_spi_wrp(uint8_t addr,uint16_t *pdata)
{
uint16_t tmp;
memcpy(&tmp,pdata,sizeof(uint16_t));
mot_spi_wr(addr,tmp);
}
uint16_t mot_spi_rd(uint8_t addr)
{
uint16_t rez;
uint16_t tmp;
tmp=(addr&0x7)<<12;
tmp|= 0x8000;
rez=mot_spi_transfer(tmp);
return rez&0xfff;
}
////========================================================

CTRL_Register_t 	G_CTRL_REG;
TORQUE_Register_t 	G_TORQUE_REG;
 OFF_Register_t 	G_OFF_REG;
BLANK_Register_t	G_BLANK_REG;
DECAY_Register_t 	G_DECAY_REG;
STALL_Register_t 	G_STALL_REG;
DRIVE_Register_t 	G_DRIVE_REG;
STATUS_Register_t 	G_STATUS_REG;

void init_step_mot(void)
{
uint16_t tmp;
// CTRL Register

G_CTRL_REG.DTIME 	= 0;///0x03;
G_CTRL_REG.ISGAIN 	=0x3;/// 0;///0x03;
G_CTRL_REG.EXSTALL 	= 0x00;
G_CTRL_REG.MODE 	= 0x8;///0x03;
G_CTRL_REG.RSTEP 	= 0x00;
G_CTRL_REG.RDIR 	= 0x00;
G_CTRL_REG.ENBL 	= 0x01;

// TORQUE Register
G_TORQUE_REG.SIMPLTH = 0x00;
G_TORQUE_REG.TORQUE  = 0x8;///0xBA;

// OFF Register
G_OFF_REG.PWMMODE 	= 0x00;
G_OFF_REG.TOFF 		= 0x30;

// BLANK Register
G_BLANK_REG.ABT 	= 0x01;
G_BLANK_REG.TBLANK 	= 0x08;

// DECAY Register.
G_DECAY_REG.DECMOD  = 0x03;
G_DECAY_REG.TDECAY 	= 0x10;

// STALL Register
G_STALL_REG.VDIV 	= 0x03;
G_STALL_REG.SDCNT 	= 0x03;
G_STALL_REG.SDTHR 	= 0x40;

// DRIVE Register
G_DRIVE_REG.OCPTH 	= 0x01;
G_DRIVE_REG.IDRIVEP = 0x00;
G_DRIVE_REG.IDRIVEN = 0x00;
G_DRIVE_REG.TDRIVEP = 0x01;
G_DRIVE_REG.TDRIVEN = 0x01;
G_DRIVE_REG.OCPDEG 	= 0x01;

if(EE_Rd(ADDR_EEPROM_MOT_CTRL,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_CTRL_REG,sizeof(uint16_t)); ///error read
  }
mot_spi_wrp(ADDR_MOT_CTRL,(uint16_t*)&tmp);

if(EE_Rd(ADDR_EEPROM_MOT_TORQUE,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_TORQUE_REG,sizeof(uint16_t));
  }
mot_spi_wrp(ADDR_MOT_TORQUE,(uint16_t*)&tmp);
printk("\n\r _TORQUE_ [%d]",tmp);

if(EE_Rd(ADDR_EEPROM_MOT_OFF,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_OFF_REG,sizeof(uint16_t));
  }
mot_spi_wrp(ADDR_MOT_OFF,(uint16_t*)&tmp);

if(EE_Rd(ADDR_EEPROM_MOT_BLANK,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_BLANK_REG,sizeof(uint16_t));
  }
mot_spi_wrp(ADDR_MOT_BLANK,(uint16_t*)&tmp);

if(EE_Rd(ADDR_EEPROM_MOT_DECAY,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_DECAY_REG,sizeof(uint16_t));
  }
mot_spi_wrp(ADDR_MOT_DECAY,(uint16_t*)&tmp);

if(EE_Rd(ADDR_EEPROM_MOT_DECAY,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_STALL_REG,sizeof(uint16_t));
  }
mot_spi_wrp(ADDR_MOT_STALL,(uint16_t*)&tmp);
if(EE_Rd(ADDR_EEPROM_MOT_DECAY,&tmp)!=0)
  {
  memcpy(&tmp,(uint16_t*)&G_DRIVE_REG,sizeof(uint16_t));
  }
mot_spi_wrp(ADDR_MOT_DRIVE,(uint16_t*)&tmp);

mot_spi_wr(ADDR_MOT_STATUS,0);

}
////========================================================
void set_mot_rej(uint8_t rej)
{
uint16_t tmp;
CTRL_Register_t *t_ctrl_reg=(CTRL_Register_t*)&tmp;
tmp=mot_spi_rd(ADDR_MOT_CTRL);

t_ctrl_reg->MODE=rej;
mot_spi_wr(ADDR_MOT_CTRL,tmp);

printk("\n\r set_mot_rej[%x]",rej);

tmp=mot_spi_rd(ADDR_MOT_CTRL);
}

void set_mot_trq(uint8_t trq)
{
uint16_t tmp;
///uint16_t htmp;
TORQUE_Register_t *t_trq_reg=(TORQUE_Register_t*)&tmp;
tmp=mot_spi_rd(ADDR_MOT_TORQUE);

t_trq_reg->TORQUE=trq;
mot_spi_wr(ADDR_MOT_TORQUE,tmp);

tmp=mot_spi_rd(ADDR_MOT_TORQUE);
EE_Wr(ADDR_EEPROM_MOT_TORQUE,tmp);
printk("\n\r set_mot_trq[%x]",tmp);

}

void print_mot_reg(void)
{
uint16_t tmp;
tmp=mot_spi_rd(ADDR_MOT_CTRL);
printk("\n\r CTRL[%x]",tmp);

tmp=mot_spi_rd(ADDR_MOT_TORQUE);
printk("\n\r TORQUE[%x]",tmp);
tmp=mot_spi_rd(ADDR_MOT_OFF);
printk("\n\r OFF[%x]",tmp);
tmp=mot_spi_rd(ADDR_MOT_BLANK);
printk("\n\r BLANK[%x]",tmp);
tmp=mot_spi_rd(ADDR_MOT_STALL);
printk("\n\r STALL[%x]",tmp);
tmp=mot_spi_rd(ADDR_MOT_DRIVE);
printk("\n\r DRIVE[%x]",tmp);
tmp=mot_spi_rd(ADDR_MOT_STATUS);
printk("\n\r STATUS[%x]",tmp);

}
////extern CanRxMsg RxMessage;
void reset_mot_step(void)
{

}

static void set_mot_per_hw(uint16_t per)
{
  MOT_STEP_TIM->ARR = (uint32_t)per * 2U;
  MOT_STEP_TIM->CCR1 = per;
}

static uint16_t mot_clamp_per(uint16_t per)
{
  if (per > MAX_PER) {
    return MAX_PER;
  }
  if (per < MIN_PER) {
    return MIN_PER;
  }
  return per;
}

static struct {
  uint16_t start_per;
  uint16_t end_per;
  uint16_t ramp_steps;
  uint16_t ramp_left;
  uint16_t active_per;
} mot_ramp;

static uint16_t mot_ramp_pick_steps(uint16_t from, uint16_t to, uint32_t move_steps,
                                    uint8_t enforce_min16)
{
  uint32_t delta;
  uint32_t steps;

  if (from == to || move_steps == 0U) {
    return 0U;
  }
  delta = (from > to) ? (uint32_t)(from - to) : (uint32_t)(to - from);
  steps = (uint32_t)MOT_PER_RAMP_STEPS;
  if (delta > (uint32_t)MOT_PER_RAMP_DELTA_REF) {
    steps = (delta * (uint32_t)MOT_PER_RAMP_STEPS) / (uint32_t)MOT_PER_RAMP_DELTA_REF;
  }
  if (steps > (uint32_t)MOT_PER_RAMP_STEPS_MAX) {
    steps = (uint32_t)MOT_PER_RAMP_STEPS_MAX;
  }
  if (steps > move_steps) {
    steps = move_steps;
  }
  if (enforce_min16 && steps < 16U && move_steps >= 16U) {
    steps = 16U;
  }
  return (uint16_t)steps;
}

static void mot_ramp_begin_chain(uint16_t target_per, uint32_t move_steps)
{
  uint16_t from;
  uint16_t to;
  uint16_t steps;

  to = mot_clamp_per(target_per);
  from = mot_ramp.active_per;
  if (from < MIN_PER) {
    from = MIN_PER;
  }
  mot_ramp.start_per = from;
  mot_ramp.end_per = to;
  steps = mot_ramp_pick_steps(from, to, move_steps, 0U);
  if (steps > (uint16_t)MOT_PER_RAMP_CHAIN_STEPS) {
    steps = (uint16_t)MOT_PER_RAMP_CHAIN_STEPS;
  }
  if (from == to || steps == 0U) {
    mot_ramp.ramp_steps = 0U;
    mot_ramp.ramp_left = 0U;
    mot_ramp.active_per = to;
    return;
  }
  mot_ramp.ramp_steps = steps;
  mot_ramp.ramp_left = steps;
  mot_ramp.active_per = from;
}

static void mot_ramp_begin(uint16_t target_per, uint32_t move_steps)
{
  uint16_t from;
  uint16_t to;
  uint16_t steps;

  to = mot_clamp_per(target_per);
  from = mot_ramp.active_per;
  if (from < MIN_PER) {
    from = MIN_PER;
  }
  mot_ramp.start_per = from;
  mot_ramp.end_per = to;
  steps = mot_ramp_pick_steps(from, to, move_steps, 1U);
  if (from == to || steps == 0U) {
    mot_ramp.ramp_steps = 0U;
    mot_ramp.ramp_left = 0U;
    mot_ramp.active_per = to;
    set_mot_per_hw(to);
    return;
  }
  mot_ramp.ramp_steps = steps;
  mot_ramp.ramp_left = steps;
  mot_ramp.active_per = from;
  set_mot_per_hw(from);
}

static void mot_ramp_on_step(void)
{
  uint16_t done;
  int32_t delta;
  uint16_t per;

  if (mot_ramp.ramp_left == 0U) {
    return;
  }
  mot_ramp.ramp_left--;
  done = (uint16_t)(mot_ramp.ramp_steps - mot_ramp.ramp_left);
  delta = (int32_t)mot_ramp.end_per - (int32_t)mot_ramp.start_per;
  per = (uint16_t)((int32_t)mot_ramp.start_per +
                   (delta * (int32_t)done) / (int32_t)mot_ramp.ramp_steps);
  per = mot_clamp_per(per);
  mot_ramp.active_per = per;
  set_mot_per_hw(per);
  if (mot_ramp.ramp_left == 0U) {
    mot_ramp.active_per = mot_ramp.end_per;
    set_mot_per_hw(mot_ramp.end_per);
  }
}

static uint8_t mot_finish_stepping(void)
{
  if (mot_go_try_chain_isr() != 0U) {
    return 1U;
  }
  stop_mot_step_tim();
  can_go_step_done = 1U;
  return 0U;
}

void mot_go_start(uint8_t dirs, uint16_t per, uint32_t steps)
{
  if (steps == 0U) {
    put_mot_nStep(0U);
    return;
  }
  printk("\n\rGo [dir=%x:per=%x:steps=%x] ", dirs, per, (unsigned)steps);
  set_dir_mot(dirs);
  mot_ramp_begin(per, steps);
  ena_mot(1);
  num_Step = steps;
  TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, ENABLE);
  TIM_Cmd(MOT_STEP_TIM, ENABLE);
}

void mot_go_chain(uint8_t dirs, uint16_t per, uint32_t steps)
{
  if (steps == 0U) {
    return;
  }
  set_dir_mot(dirs);
  mot_ramp_begin_chain(per, steps);
  num_Step = steps;
  TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, ENABLE);
  TIM_Cmd(MOT_STEP_TIM, ENABLE);
}

void set_mot_per(uint16_t per)
{
  per = mot_clamp_per(per);
  mot_ramp.ramp_left = 0U;
  mot_ramp.active_per = per;
  set_mot_per_hw(per);
  printk("\n\r set_mot_per[%x]", per);
}

////=======================================================
static void stop_mot_step_tim(void)
{
TIM_Cmd(MOT_STEP_TIM, DISABLE);

}

void  set_dir_mot(uint8_t idat)
{
uint8_t tdat=idat&0x1;
cur_mot_dir= tdat;
#if 0
#if STEP_X
  tdat=idat&DIR_X;
#elif STEP_Y
  tdat=idat&DIR_Y;
#elif STEP_Z
  tdat=idat&DIR_Z;
#endif
#endif

if(tdat)
  {
  GPIO_SetBits(MOT_DIR_PIN_GPIO, MOT_DIR_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_DIR_PIN_GPIO, MOT_DIR_PIN);
  }
}
void  set_reset_mot(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_RESET_PIN_GPIO, MOT_RESET_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_RESET_PIN_GPIO, MOT_RESET_PIN);
  }
}
void  set_step_mot(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_STEP_PIN_GPIO, MOT_STEP_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_STEP_PIN_GPIO, MOT_STEP_PIN);
  }
}

void  set_sleep_mot(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_SLEEP_PIN_GPIO, MOT_SLEEP_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_SLEEP_PIN_GPIO, MOT_SLEEP_PIN);
  }
}
///==================================================
void mot_step_tim_init(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

RCC->APB2ENR |= MOT_STEP_TIM_RCC;
MOT_STEP_TIM ->PSC = DEF_MOT_TIM_PRESC;
MOT_STEP_TIM ->ARR = DEF_MOT_TIM_PERIOD;////
MOT_STEP_TIM ->CCR1 = DEF_MOT_TIM_PERIOD/2;////30;
TIM_ARRPreloadConfig(MOT_STEP_TIM, ENABLE);
TIM_OC1PreloadConfig(MOT_STEP_TIM, TIM_OCPreload_Enable);
MOT_STEP_TIM->CCER |= TIM_CCER_CC1E;////TIM_CCER_CC2NE;////| TIM_CCER_CC3NP;
MOT_STEP_TIM->BDTR |= TIM_BDTR_MOE;
MOT_STEP_TIM->CCMR1 = TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;
MOT_STEP_TIM->CR1 &= ~TIM_CR1_DIR;
MOT_STEP_TIM->CR1 &= ~TIM_CR1_CMS;

MOT_STEP_TIM ->DIER = TIM_DIER_CC1IE;
TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC1);

NVIC_InitStructure.NVIC_IRQChannel = MOT_TIM_IRQN;
//// highest priority
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;

NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//// highest priority
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

mot_ramp.active_per = MIN_PER;
mot_ramp.ramp_left = 0U;
}

///===========================================================
void ena_mot(uint8_t ena_dis)
{
uint16_t tmp;
////return ;
tmp=mot_spi_rd(ADDR_MOT_CTRL);
if(ena_dis&0x1)
{
tmp|=0x1;
}
else
{
tmp&= ~0x1;
}
mot_spi_wr(ADDR_MOT_CTRL,tmp);
}

void put_mot_nStep(uint32_t nstep)
{
  if(nstep){
     ena_mot(1) ;
     num_Step=nstep;
     TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, ENABLE);
     TIM_Cmd(MOT_STEP_TIM, ENABLE);
  }
  else{
  ///    ena_mot(0) ;
      num_Step=nstep;
      TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, DISABLE);
      TIM_Cmd(MOT_STEP_TIM, DISABLE);
  }
}

static uint8_t cur_step_out=0;
uint8_t use_enc=0;///1;

int32_t step_coord=0;

void MOT_STEP_TIM_IRQHandler(void)
{
///uint8_t end_step=0;
uint8_t tconc;
tconc=  get_conc_n();
#if 0
if(ena_check_conc)
{
///tconc=  get_conc_n();
if(tconc & MASK_CON !=0x0)
  num_step=0;
}
#endif
if(cur_step_out)
  {
   cur_step_out=0;
   set_step_mot(cur_step_out);
  }
else
{
  ///=====check conc =========
  if((cur_mot_dir&0x1)==0)
    {
      if((tconc & MASK_CON1) !=0x0)
           num_Step=0;
    }
  else
     {
     if((tconc & MASK_CON0) !=0x0)
           num_Step=0;
     }
  if(num_Step==0){
    mot_finish_stepping();
   }
  else{
  if(use_enc){
   cur_step_out=1;
   set_step_mot(cur_step_out);
    if((cur_mot_dir&0x1)==0){
      if(curr_coord>=next_coord)
        num_Step=0;
      else
        num_Step=1;
    }
    else{
      if(curr_coord<=next_coord)
        num_Step=0;
      else
        num_Step=1;
    }
  }
  else {
   cur_step_out=1;
   set_step_mot(cur_step_out);
  num_Step--;
  if((cur_mot_dir&0x1)==0)
    step_coord++;
  else
    step_coord--;
  mot_ramp_on_step();
  if (num_Step == 0U) {
    mot_finish_stepping();
  }
  }
  }
}
TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC1);
}

///=============================================
void motor_init(void)
{
///uint16_t tmp;
mot_step_tim_init();
mot_spi_init();

set_sleep_mot(1);
////set_ena_mot(1);
set_reset_mot(1);
uDelay(1000);
set_reset_mot(0);
uDelay(20000);
init_step_mot();
ena_mot(0) ;
/*
if(EE_ReadVariable(ADDR_EEPROM_MOT_REJ, &tmp)==0)
  {
    if(tmp>MAX_MOT_REJ)
      tmp=MAX_MOT_REJ;
   set_mot_rej(tmp);
  }
else
*/
 ///  set_mot_rej(DEF_MOT_REJ);

}
///==============================================
///spi_mot_cmd_t  req_spi_mot_cmd;

int wr_spi_mot(spi_mot_cmd_t *i_cmd)
{
mot_spi_wr(i_cmd->addr&0x7, i_cmd->w_val&0xffff);
///printk("\n\r wr_spi_mot[%x:%x:%x]",i_cmd->addr,i_cmd->len_dat,odat);

if(i_cmd->len_dat==4){
  mot_spi_wr((i_cmd->addr+1)&0x7, (i_cmd->w_val>>16)&0xffff);
///  printk("\n\r wr_spi_mot[%x:%x:%x]",i_cmd->addr+1,i_cmd->len_dat,odat);

}
return 0;
}

int rd_spi_mot(spi_mot_cmd_t *i_cmd)
{
uint32_t odat=0;
uint32_t odat1=0;

odat=mot_spi_rd(i_cmd->addr&0x7);
if(i_cmd->len_dat==4)
{
odat1= mot_spi_rd((i_cmd->addr+1)&0x7);
odat|= odat1<<16;
}
i_cmd->w_val=odat;
i_cmd->len_dat=5;    ///send all dat
printk("\n\r rd_spi_mot[%x:%x:%x]",i_cmd->addr,i_cmd->len_dat,odat);

 return 0;
}
