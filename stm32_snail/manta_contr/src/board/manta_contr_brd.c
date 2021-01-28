#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
///#include "stm32f2xx_gpio.h"
///#include "stm32f2xx_rcc.h"

#include "manta_contr_brd.h"
#include "_hdlc.h"
#include "printk.h"

extern void uDelay (const uint32_t usec);
extern void  put_tst_pin(uint8_t idat);
extern int BMC150_init(void);

dp_dat_t cur_dp_dat;
int send_char_dbg (int c) 
{ 
while (!(UART_DBG->SR & USART_FLAG_TXE));
UART_DBG->DR = (c & 0x1FF);
return (c);
}
int send_char_bt (int c) 
{ 
while (!(UART_BT->SR & USART_FLAG_TXE));
UART_BT->DR = (c & 0x1FF);
return (c);
}

///=============================

int sendchar6 (int c) 
{ 
while (!(USART6->SR & USART_FLAG_TXE));
USART6->DR = (c & 0x1FF);
return (c);
}

int get_byte6 (void) 
{
while (!(USART6->SR & USART_FLAG_RXNE));
return (USART6->DR);
}

void _putk(char ch)
{
//sendchar_hdlc(ch);
sendchar6(ch);
}
void set_led0(uint8_t i_dat)
{
if(i_dat&0x1)
  GPIO_SetBits(LED0_GPIO, LED0_PIN);
else
  GPIO_ResetBits(LED0_GPIO, LED0_PIN);
}
void set_led1(uint8_t i_dat)
{
if(i_dat&0x1)
  GPIO_SetBits(LED1_GPIO, LED1_PIN);
else
  GPIO_ResetBits(LED1_GPIO, LED1_PIN);
}


uint8_t  get_dpx_r0(void)
{
return  GPIO_ReadInputDataBit(DPX_R0_GPIO, DPX_R0_PIN) ;
}
uint8_t  get_dpy_r0(void)
{
return  GPIO_ReadInputDataBit(DPY_R0_GPIO, DPY_R0_PIN) ;
}

void init_gpio(void)
{
  
////RCC_AHBPeriphClockCmd(XEN_PIN_RCC_AHB,ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
////============= DPX_RA ========================
RCC_AHB1PeriphClockCmd(DPX_RA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPX_RA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPX_RA_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPX_RA_GPIO, DPX_RA_PIN_NPIN, DPX_RA_AF);
////============= DPX_RB ========================
RCC_AHB1PeriphClockCmd(DPX_RA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPX_RB_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPX_RB_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPX_RB_GPIO, DPX_RB_PIN_NPIN, DPX_RB_AF);
///=============DPX_R0 =========================
RCC_AHB1PeriphClockCmd(DPX_R0_RCC,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Pin   = DPX_R0_PIN;
GPIO_Init(DPX_R0_GPIO, &GPIO_InitStructure);

////============= DPX_LA ========================
RCC_AHB1PeriphClockCmd(DPX_LA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPX_LA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPX_LA_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPX_LA_GPIO, DPX_LA_PIN_NPIN, DPX_LA_AF);
////============= DPX_LB ========================
RCC_AHB1PeriphClockCmd(DPX_LA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPX_LB_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPX_LB_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPX_LB_GPIO, DPX_LB_PIN_NPIN, DPX_LB_AF);
////============= DPY_RA ========================
RCC_AHB1PeriphClockCmd(DPY_RA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPY_RA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPY_RA_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPY_RA_GPIO, DPY_RA_PIN_NPIN, DPY_RA_AF);
////============= DPY_RB ========================
RCC_AHB1PeriphClockCmd(DPY_RA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPY_RB_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPY_RB_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPY_RB_GPIO, DPY_RB_PIN_NPIN, DPY_RB_AF);
////=============DPY_R0 =========================
RCC_AHB1PeriphClockCmd(DPY_R0_RCC,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Pin   = DPY_R0_PIN;
GPIO_Init(DPY_R0_GPIO, &GPIO_InitStructure);

////============= DPY_LA ========================
RCC_AHB1PeriphClockCmd(DPY_LA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPY_LA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPY_LA_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPY_LA_GPIO, DPY_LA_PIN_NPIN, DPY_LA_AF);
////============= DPY_LB ========================
RCC_AHB1PeriphClockCmd(DPY_LA_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = DPY_LB_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
////GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( DPY_LB_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(DPY_LB_GPIO, DPY_LB_PIN_NPIN, DPY_LB_AF);
  
////=========== DBG_UART =================================================== 
RCC_AHB1PeriphClockCmd(UART_DBG_TX_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = UART_DBG_TX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( UART_DBG_TX_GPIO, &GPIO_InitStructure );

RCC_AHB1PeriphClockCmd(UART_DBG_RX_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = UART_DBG_RX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( UART_DBG_RX_GPIO, &GPIO_InitStructure );
  
GPIO_PinAFConfig(UART_DBG_TX_GPIO, UART_DBG_TX_PIN_NPIN, UART_DBG_TX_AF);
GPIO_PinAFConfig(UART_DBG_RX_GPIO, UART_DBG_RX_PIN_NPIN, UART_DBG_RX_AF);
////===================================================================
////=========== BT_UART =================================================== 
RCC_AHB1PeriphClockCmd(UART_BT_TX_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = UART_BT_TX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( UART_BT_TX_GPIO, &GPIO_InitStructure );

RCC_AHB1PeriphClockCmd(UART_BT_RX_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = UART_BT_RX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( UART_BT_RX_GPIO, &GPIO_InitStructure );
  
GPIO_PinAFConfig(UART_BT_TX_GPIO, UART_BT_TX_PIN_NPIN, UART_BT_TX_AF);
GPIO_PinAFConfig(UART_BT_RX_GPIO, UART_BT_RX_PIN_NPIN, UART_BT_RX_AF);
////================ LED0 ===========================
RCC_AHB1PeriphClockCmd(LED0_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = LED0_PIN;
GPIO_Init(LED0_GPIO, &GPIO_InitStructure);
GPIO_SetBits(LED0_GPIO, LED0_PIN);
////================ LED1 ===========================
RCC_AHB1PeriphClockCmd(LED1_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = LED1_PIN;
GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
GPIO_SetBits(LED1_GPIO, LED1_PIN);

}
////=============================================
void UART_DBG_Init(void)
{
////GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
UART_DBG_CLK_INIT(UART_DBG_CLK, ENABLE);
USART_DeInit(UART_DBG);
USART_InitStructure.USART_BaudRate = 115200;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(UART_DBG, &USART_InitStructure);
UART_DBG->CR1 |= USART_CR1_RXNEIE;
USART_Cmd(UART_DBG, ENABLE);
}

////==================================================
extern hdlc_stat_t g_hdlc_bt;

////===========================================================
void USART2_IRQHandler(void)
{
///int cnt;  
u8 ch;
uint32_t tmp_sr;
signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
////signed portBASE_TYPE xTaskWoken= pdFALSE;

tmp_sr=UART_BT->SR;  
if((tmp_sr&USART_FLAG_RXNE) != 0)
  {
  UART_BT->SR &= ~USART_FLAG_RXNE;              ///  USART_ClearITPendingBit(UART_BT, USART_IT_RXNE);
  ch = (u8)(UART_BT->DR & 0x0FF);
  if (hdlc1_on_bytein(&g_hdlc_bt, ch) > 0)
    {
    xQueueSendFromISR(g_hdlc_bt.ev_rsv_frame, &ch, &xHigherPriorityTaskWoken);
  }
  }
else if((tmp_sr&USART_FLAG_ORE) != 0)
  {
  ch = (u8)(UART_BT->DR & 0x0FF);
  USART_ClearITPendingBit(UART_BT, USART_FLAG_ORE);
  }
#if 0
if ((tmp_sr&USART_FLAG_TXE) != 0)
    {
    UART_BT->SR &= ~USART_IT_TXE;              ///  USART_ClearITPendingBit(UART_BT, USART_IT_TXE);
    if (xQueueReceiveFromISR(g_hdlc_bt.ua_snd_dat, &ch, &xTaskWoken ) == pdPASS)
      {
      UART_BT->DR = ch & 0x1FF;
      }
    if (xQueueIsQueueEmptyFromISR(g_hdlc_bt.ua_snd_dat))
      {
      UART_BT->CR1 &= ~USART_CR1_TXEIE;		      // disable TX interrupt if nothing to send
      }
    }
#endif
}

void init_irq_bt(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_InitStructure.NVIC_IRQChannel = UART_BT_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;///0x6;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;////7;	//1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}

void UART_BT_Init(void)
{
  int i;
////GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
UART_BT_CLK_INIT(UART_BT_CLK, ENABLE);
USART_DeInit(UART_BT);
USART_InitStructure.USART_BaudRate = 115200;////19200;////115200;////9600;////38400;////115200;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(UART_BT, &USART_InitStructure);
UART_BT->CR1 |= USART_CR1_RXNEIE;
USART_Cmd(UART_BT, ENABLE);
for (i = 0; i < 0x1000; i++)
  {
  __NOP();   //avoid unwanted output
  }
////UART_BT->CR1 = 0x202C;

UART_BT->SR = 0;
init_irq_bt();

}

void init_timers(void)
{
////NVIC_InitTypeDef NVIC_InitStructure; 
////============= DPX_R ========================
RCC->APB2ENR |= DPX_R_TIM_RCC;
DPX_R_TIM ->CCER = TIM_CCER_CC1P | TIM_CCER_CC2P;
DPX_R_TIM ->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
DPX_R_TIM->SMCR = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
DPX_R_TIM ->ARR = DPX_R_TIM_PERIOD;////
DPX_R_TIM->CR1 = TIM_CR1_CEN;
////============= DPX_L ========================
RCC->APB1ENR |= DPX_L_TIM_RCC;
DPX_L_TIM ->CCER = TIM_CCER_CC1P | TIM_CCER_CC2P;
DPX_L_TIM ->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
DPX_L_TIM->SMCR = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
DPX_L_TIM ->ARR = DPX_R_TIM_PERIOD;////
DPX_L_TIM->CR1 = TIM_CR1_CEN;
////============= DPY_R ========================
RCC->APB1ENR |= DPY_R_TIM_RCC;
DPY_R_TIM ->CCER = TIM_CCER_CC1P | TIM_CCER_CC2P;
DPY_R_TIM ->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
DPY_R_TIM->SMCR = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
DPY_R_TIM ->ARR = DPX_R_TIM_PERIOD;////
DPY_R_TIM->CR1 = TIM_CR1_CEN;
////============= DPY_L ========================
RCC->APB1ENR |= DPY_L_TIM_RCC;
DPY_L_TIM ->CCER = TIM_CCER_CC1P | TIM_CCER_CC2P;
DPY_L_TIM ->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
DPY_L_TIM->SMCR = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
DPY_L_TIM ->ARR = DPX_R_TIM_PERIOD;////
DPY_L_TIM->CR1 = TIM_CR1_CEN;

}
////==================================
void on_int_tx_uart_bt(void)
{
UART_BT->CR1 |= USART_CR1_TXEIE;  // enable TX interrupt
}

////==================================================

volatile uint32_t num_step=0;

volatile uint32_t gsr;
uint8_t flg_xr_ok=0;
uint8_t flg_yr_ok=0;
////=======================================================
#if 0
uint8_t get_conc(void)
{
return GPIO_ReadInputDataBit(CONC_PIN_GPIO, CONC_PIN);
}
#endif

void clr_all_dp(void)
{
DPX_R_TIM->CNT=0; 
DPX_L_TIM->CNT=0; 
DPY_R_TIM->CNT=0; 
DPY_L_TIM->CNT=0; 
}
void clr_dpx_r0(void)
{
DPX_R_TIM->CNT=0; 
flg_xr_ok=1;
}
void clr_dpy_r0(void)
{
DPY_R_TIM->CNT=0;
flg_yr_ok=1;
}

void init_r0int(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_AHB1PeriphClockCmd(DPX_R0_RCC, ENABLE);
RCC_AHB1PeriphClockCmd(DPY_R0_RCC, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
////============= DPX_R0 ==========================
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;///GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Pin = DPX_R0_PIN;
GPIO_Init(DPX_R0_GPIO, &GPIO_InitStructure);
/* Connect  EXTI Line to GPIO Pin */
SYSCFG_EXTILineConfig(DPX_R0_EXTI_PORT, DPX_R0_EXTI_PIN);
/* Configure  EXTI line */
EXTI_InitStructure.EXTI_Line = DPX_R0_EXTI_LINE;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);

/* Enable and set EXTI Interrupt to the lowest priority */
NVIC_InitStructure.NVIC_IRQChannel = DPX_R0_EXTI_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure); 
////============= DPY_R0 ==========================
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;///GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Pin = DPY_R0_PIN;
GPIO_Init(DPY_R0_GPIO, &GPIO_InitStructure);
/* Connect  EXTI Line to GPIO Pin */
SYSCFG_EXTILineConfig(DPY_R0_EXTI_PORT, DPY_R0_EXTI_PIN);
/* Configure  EXTI line */
EXTI_InitStructure.EXTI_Line = DPY_R0_EXTI_LINE;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);
/* Enable and set EXTI Interrupt to the lowest priority */
NVIC_InitStructure.NVIC_IRQChannel = DPY_R0_EXTI_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure); 

}
////=============================================
void hw_board_init(void)
{
init_gpio();
UART_DBG_Init(); 
UART_BT_Init(); 
/////init_i2c();
////BMC150_init();
 
init_timers();
init_r0int();
clr_all_dp();
flg_xr_ok=0;
flg_yr_ok=0;

}
#define POR_P 2
////============================================
void tst_task( void *pvParameters )
{
uint8_t btst=0; 
int16_t tst=0;
 for(;;)
  {
  if(flg_xr_ok)
  {
    tst=(int)(DPX_R_TIM->CNT);
    if(tst>0)
      {
        if(tst<POR_P)
          btst=1;
        else
          btst=0;
      }
    else if(tst<0)
      {
        if(tst> -POR_P)
          btst=1;
        else
          btst=0;
      }
     else
       btst=1;
    set_led0(btst); 
  }
  else
     set_led0(0); 
   if(flg_yr_ok)
  {
  
///  btst= get_dpy_r0();
    tst=(int)DPY_R_TIM->CNT;
    if(tst>0)
      {
        if(tst<POR_P)
          btst=1;
        else
          btst=0;
      }
    else if(tst<0)
      {
        if(tst> -POR_P)
          btst=1;
        else
          btst=0;
      }
     else
       btst=1;

   set_led1(btst); 
  }
  else
    set_led1(0); 
   
    msleep(200);
  ////key=dbg_get_byte() ;  
  ////printk("\n\r nstep[%d] dir[%x] Mot_rej[%x]",nstep,dir,mot_rej); 
  } 
}
////============================================
////======================================
void task_dp(void *pvParameters) 
{
int16_t tmp;
int16_t prev_r=0;
int16_t prev_l=0;
int16_t prev_yr=0;
int16_t prev_yl=0;

for (;;) 
  {
  if(flg_xr_ok)
      {
      tmp=DPX_R_TIM->CNT; 
      cur_dp_dat.dp_ar=tmp;
      if(prev_r!= tmp)
        {
        prev_r= tmp;
        printk("\r\n DPX_R[%d] ",tmp);
        }
      }                                  
#if 1   
   tmp=DPX_L_TIM->CNT; 
   cur_dp_dat.dp_al=tmp;
   if(prev_l!= tmp)
      {
      prev_l= tmp;
      printk("\r\n DPX_L[%d] ",tmp);
      }
#endif   
  if(flg_yr_ok)
   {
   tmp=DPY_R_TIM->CNT; 
   cur_dp_dat.dp_br=tmp;
   if(prev_yr!= tmp)
      {
      prev_yr= tmp;
      printk("\r\n DPY_R[%d] ",tmp);
      }
    }
   tmp=DPY_L_TIM->CNT; 
   cur_dp_dat.dp_bl=tmp;
   if(prev_yl!= tmp)
      {
      prev_yl= tmp;
      printk("\r\n DPY_L[%d] ",tmp);
      }
   
////    vTaskDelay(500);
    }
}

	
