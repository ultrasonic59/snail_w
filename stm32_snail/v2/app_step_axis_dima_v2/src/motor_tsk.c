#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "board.h"
#include "printk.h"

#include "snail_can_cmds.h"
#include "can.h"
#include "can_cmds.h"
#include "i2c.h"

uint8_t cur_mot_rej=DEF_MOT_REJ;
static uint8_t cur_mot_dir=0;

cmd_t cur_cmd={0};

////set_mot_per(p_go_cmd->step_per);

void motor_dbg_task( void *pvParameters )
{
uint8_t btst=0; 
uint8_t psk=0; 
///uint16_t tst;
char key=0;
int nstep=300;
uint8_t dir=0;
uint8_t t_ena=0;
uint8_t t_reset=0;
uint16_t t_enc_val=0;

uint8_t mot_rej=0;
printk("\n\r motor_task"); 
motor_init();

for(;;)
{
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
   case 'e':
      t_ena ++;
      t_ena&=0x1;
      break;
  case 'r':
      t_reset ++;
      t_reset&=0x1;
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
       break;
    
   }
  btst = get_conc_n();

  printk("\n\r nstep[%d] dir[%x] Mot_rej[%x] chk_conc[%x] conc=[%x]ena=[%x]reset=[%x]",nstep,dir,mot_rej,ena_check_conc,btst,t_ena,t_reset); 
 /*
  if(read_encoder_val(&t_enc_val)==0)
  {
  uint32_t gr;
  gr=t_enc_val*36000;
  gr>>=14;
  printk("\n\r encoder[%d][%x][%d]",t_enc_val,t_enc_val,gr); 
  }
  else
   printk("\n\r read encoder!!!"); 
 */     
  set_dir_mot(dir);
  set_mot_rej(mot_rej);
  set_ena_mot(t_ena);
  set_reset_mot(t_reset);
 if(psk)
    {
    put_mot_nstep(nstep);
    psk=0;
    }
  
  }  
}
}

////========================================================  
void set_mot_rej(uint8_t rej)
{
 set_mot_ms(rej&0x7); 
}


void reset_mot_step(void)
{
  
}
void set_mot_per(uint16_t per)
{
if(per>MAX_PER)
  per=MAX_PER;
else if(per<MIN_PER)
  per=MIN_PER;
MOT_STEP_TIM ->ARR = per*2;////
MOT_STEP_TIM ->CCR1 = per;////
printk("\n\r set_mot_per[%x]",per);

}
///=======================================================
void stop_mot_step_tim(void)
{
TIM_Cmd(MOT_STEP_TIM, DISABLE);

}
volatile uint32_t num_step=0;

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
///==================================================
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
void put_mot_nstep(uint32_t nstep)
{
////set_ena_mot(1) ;
num_step=nstep; 
TIM_ITConfig(MOT_STEP_TIM, TIM_IT_CC1, ENABLE);
TIM_Cmd(MOT_STEP_TIM, ENABLE);
}

static uint8_t cur_step_out=0;
void MOT_STEP_TIM_IRQHandler(void)
{ 
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
if(ena_check_conc)
{  
  if((cur_mot_dir&0x1)==0)
    {
      if((tconc & MASK_CON1) !=0x0)
           num_step=0;
    }
  else
     {
     if((tconc & MASK_CON0) !=0x0)
           num_step=0;
     }
} 
if(num_step)
  {
   cur_step_out=1;
   set_step_mot(cur_step_out);
  num_step--;
  if((cur_mot_dir&0x1)==0)
    cur_coord++;
  else
    cur_coord--;
   
  if(num_step==0)
    {
   cur_step_out=0;
   set_step_mot(cur_step_out);
   
    stop_mot_step_tim(); 
    cur_state &= ~STATE_MASK;
    cur_state|=STATE_READY;  

  ////  set_ena_mot(0) ;
    }
  }
else
  {
   stop_mot_step_tim(); 
 ///  set_ena_mot(0) ;
   }
}
////TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC2);
TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC1);
}

///=============================================
void motor_init(void)
{
mot_step_tim_init();

////set_ena_mot(1);
set_reset_mot(1);
uDelay(1000);
set_reset_mot(0);
uDelay(20000);
///init_step_mot();
////set_ena_mot(0) ;
/*
if(EE_ReadVariable(ADDR_EEPROM_MOT_REJ, &tmp)==0)
  {
    if(tmp>MAX_MOT_REJ)
      tmp=MAX_MOT_REJ;
   set_mot_rej(tmp);
  }
else
*/
   set_mot_rej(DEF_MOT_REJ);
  
}
///==============================================