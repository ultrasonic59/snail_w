#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

////#include "board.h"
#include "board.h"
#include "printk.h"

#include "snail_can_cmds.h"
#include "can.h"
#include "can_cmds.h"

cmd_t cur_cmd={0};
void mot_spi_wr(uint8_t addr,uint16_t idata);
uint16_t mot_spi_rd(uint8_t addr);
void mot_spi_init(void);

void motor_task( void *pvParameters )
{
///uint8_t btst=0; 
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
if(check_push_key_dbg())
  {
  key=get_byte_dbg() ;  
  switch(key)
    {
    case 'a':
      nstep += 20;
      break;
    case 's':
      if(nstep)
        nstep-= 20;
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
     psk=1;
      break;
    case 'z':
     print_mot_reg();
      break;
    
   }
  printk("\n\r nstep[%d] dir[%x] Mot_rej[%x]",nstep,dir,mot_rej); 
  set_dir_mot(dir);
  set_mot_rej(mot_rej);
  if(psk)
    {
    put_mot_nstep(nstep);
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
  
// CTRL Register

G_CTRL_REG.DTIME 	= 0;///0x03;
G_CTRL_REG.ISGAIN 	= 0;///0x03;
G_CTRL_REG.EXSTALL 	= 0x00;
G_CTRL_REG.MODE 	= 0;///0x03;
G_CTRL_REG.RSTEP 	= 0x00;
G_CTRL_REG.RDIR 	= 0x00;
G_CTRL_REG.ENBL 	= 0x01;

// TORQUE Register
G_TORQUE_REG.SIMPLTH = 0x00;
G_TORQUE_REG.TORQUE  = 0xBA;

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

mot_spi_wrp(ADDR_MOT_CTRL,(uint16_t*)&G_CTRL_REG);
mot_spi_wrp(ADDR_MOT_TORQUE,(uint16_t*)&G_TORQUE_REG);
mot_spi_wrp(ADDR_MOT_OFF,(uint16_t*)&G_OFF_REG);
mot_spi_wrp(ADDR_MOT_BLANK,(uint16_t*)&G_BLANK_REG);
mot_spi_wrp(ADDR_MOT_DECAY,(uint16_t*)&G_DECAY_REG);
mot_spi_wrp(ADDR_MOT_STALL,(uint16_t*)&G_STALL_REG);
mot_spi_wrp(ADDR_MOT_DRIVE,(uint16_t*)&G_DRIVE_REG);
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

tmp=mot_spi_rd(ADDR_MOT_CTRL);
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
////void put_mot_nstep(uint32_t nstep)

void set_mot_per(uint16_t per)
{
if(per>MAX_PER)
  per=MAX_PER;
else if(per<MIN_PER)
  per=MIN_PER;
MOT_STEP_TIM ->ARR = per*2;////
MOT_STEP_TIM ->CCR1 = per;////
}

////=======================================================
void stop_mot_step_tim(void)
{
TIM_Cmd(MOT_STEP_TIM, DISABLE);

}
volatile uint32_t num_step=0;
void  set_dir_mot(uint8_t idat)
{
uint8_t tdat=0;
#if STEP_X
  tdat=idat&DIR_X;
#elif STEP_Y
  tdat=idat&DIR_Y;
#elif STEP_Z
  tdat=idat&DIR_Z;
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
////==================================================



void mot_step_tim_init(void)
{
NVIC_InitTypeDef NVIC_InitStructure; 

RCC->APB2ENR |= MOT_STEP_TIM_RCC;
MOT_STEP_TIM ->PSC = DEF_MOT_TIM_PRESC;
MOT_STEP_TIM ->ARR = DEF_MOT_TIM_PERIOD;////
MOT_STEP_TIM ->CCR1 = DEF_MOT_TIM_PERIOD/2;////30;
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

void put_mot_nstep(uint32_t nstep)
{
ena_mot(1) ;
num_step=nstep; 
TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, ENABLE);
TIM_Cmd(MOT_STEP_TIM, ENABLE);
}

void MOT_STEP_TIM_IRQHandler(void)
{ 
if(num_step)
  {
  num_step--;  
  if(num_step==0)
    {
    stop_mot_step_tim(); 
    cur_stat=STATE_READY;  

    ena_mot(0) ;
    }
  }
else
  {
   stop_mot_step_tim(); 
   ena_mot(0) ;
   }
////TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC2);
TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC1);
}

///=============================================
void motor_init(void)
{
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
set_mot_rej(DEF_MOT_REJ);
  
}
///==============================================