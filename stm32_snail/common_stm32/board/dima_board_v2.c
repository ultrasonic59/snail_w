#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"

#include "can.h"
#include "can_cmds.h"
#include "board.h"
#include "printk.h"
#include "i2c.h"

extern void uDelay (const uint32_t usec);
extern void  put_tst_pin(uint8_t idat);

int32_t cur_coord=0;
uint8_t cur_state=0;  /// .5-.4 conc, .3 - .0 status
uint8_t ena_check_conc=0;
void CAN_Config(void);

///=============================
int send_char_dbg (int c) 
{ 
while (!(UART_DBG->SR & 0x0080));
UART_DBG->DR = (c & 0x1FF);
return (c);
}
void _putk(char ch)
{
send_char_dbg(ch);
}

int get_byte_dbg (void) 
{
while (!(UART_DBG->SR & USART_SR_RXNE));
return (UART_DBG->DR);
}
int check_push_key_dbg(void)
{
return  (UART_DBG->SR & USART_SR_RXNE); 
}

void init_gpio(void)
{
////RCC_AHBPeriphClockCmd(XEN_PIN_RCC_AHB,ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
////=============== TST1 ============================
RCC_AHB1PeriphClockCmd(TST2_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST1_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST1_PIN_GPIO, &GPIO_InitStructure );
////=============== TST2 ============================
RCC_AHB1PeriphClockCmd(TST2_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST2_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST2_PIN_GPIO, &GPIO_InitStructure );
////=============== TST3 ============================
RCC_AHB1PeriphClockCmd(TST3_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST3_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
///GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST3_PIN_GPIO, &GPIO_InitStructure );
///GPIO_PinAFConfig(TST3_PIN_GPIO, TST3_PIN_NPIN, GPIO_AF_TIM1);
////=============== TST4 ============================
RCC_AHB1PeriphClockCmd(TST4_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST4_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST4_PIN_GPIO, &GPIO_InitStructure );
////=============== TST5 ============================
RCC_AHB1PeriphClockCmd(TST5_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST5_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST5_PIN_GPIO, &GPIO_InitStructure );
////=============== TST6 ============================
RCC_AHB1PeriphClockCmd(TST6_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST6_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST6_PIN_GPIO, &GPIO_InitStructure );
////=============== TST7 ============================
RCC_AHB1PeriphClockCmd(TST7_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST7_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
///GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( TST7_PIN_GPIO, &GPIO_InitStructure );
///GPIO_PinAFConfig(TST7_PIN_GPIO, TST7_PIN_NPIN, GPIO_AF_TIM8);

////=============== TST8 ============================
RCC_AHB1PeriphClockCmd(TST7_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST8_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
///GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( TST7_PIN_GPIO, &GPIO_InitStructure );
///GPIO_PinAFConfig(TST8_PIN_GPIO, TST7_PIN_NPIN, GPIO_AF_TIM8);
  
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
////=============== MOT_ENA ============================
RCC_AHB1PeriphClockCmd(MOT_ENA_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_ENA_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Init( MOT_ENA_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_MS1 ============================
RCC_AHB1PeriphClockCmd(MOT_MS1_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_MS1_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Init( MOT_MS1_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_MS2 ============================
RCC_AHB1PeriphClockCmd(MOT_MS2_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_MS2_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Init( MOT_MS2_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_MS3 ============================
RCC_AHB1PeriphClockCmd(MOT_MS3_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_MS3_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Init( MOT_MS3_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_RESET ============================
RCC_AHB1PeriphClockCmd(MOT_RESET_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_RESET_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( MOT_RESET_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_SLEEP NC============================
RCC_AHB1PeriphClockCmd(MOT_SLEEP_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_SLEEP_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( MOT_SLEEP_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_STEP ============================
RCC_AHB1PeriphClockCmd(MOT_STEP_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_STEP_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( MOT_STEP_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_DIR ============================
RCC_AHB1PeriphClockCmd(MOT_DIR_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_DIR_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( MOT_DIR_PIN_GPIO, &GPIO_InitStructure );
////=============== CONC1 ============================
RCC_AHB1PeriphClockCmd(CONC1_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CONC1_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_Init( CONC1_PIN_GPIO, &GPIO_InitStructure );
////=============== CONC0 ============================
RCC_AHB1PeriphClockCmd(CONC0_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CONC0_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_Init( CONC0_PIN_GPIO, &GPIO_InitStructure );
////=============== CAN1_INH ============================
RCC_AHB1PeriphClockCmd(CAN1_INH_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CAN1_INH_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( CAN1_INH_PIN_GPIO, &GPIO_InitStructure );
GPIO_ResetBits(CAN1_INH_PIN_GPIO, CAN1_INH_PIN);
 /* CAN GPIOs configuration **************************************************/
  /* Enable GPIO clock */
RCC_AHB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_RX_SOURCE, CAN1_AF_PORT);
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_TX_SOURCE, CAN1_AF_PORT);

  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);

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


///===========================================================
volatile uint32_t gsr;

////===============================================
uint8_t get_conc0(void)
{
return GPIO_ReadInputDataBit(CONC0_PIN_GPIO, CONC0_PIN);
}
uint8_t get_conc1(void)
{
return GPIO_ReadInputDataBit(CONC1_PIN_GPIO, CONC1_PIN);
}
uint8_t get_conc_n(void)
{
uint8_t rez=0;
if(get_conc0())
  rez|=(0x1<<0);
if(get_conc1())
  rez|=(0x1<<1);
return rez;
}
////=============================================
void hw_board_init(void)
{
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
init_gpio();
UART_DBG_Init(); 
init_can();
I2C_Eeprom_Init();
/*
#ifndef BOOTER
   motor_init();
#endif
cur_stat=STATE_READY;
*/
}
////============================================

////============================================
extern uint8_t can1_send(uint16_t id,uint8_t data_len,uint8_t *data);
extern uint8_t  CAN_TxRdy;              /* CAN HW ready to transmit message */
extern uint8_t  CAN_RxRdy;              /* CAN HW received a message        */
///=========================================================
void _CAN1_Init (void)
{
uint32_t id;
 uint32_t mask;
CAN_Config();

mask= ID_MASK << 21; ///5+16

id=ID_BRD<<21; ///5+16

CAN_FilterConfig(0,id,mask);	
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

extern can_msg_t CAN_RxMsg;
uint8_t cnt_led=0;
uint8_t t_led=0;
#define NUM_CNT_LED 20

void state_task( void *pvParameters )
{
  uint8_t tmp; 
int32_t prev_coord=0xffffffff;  
uint8_t prev_state=0xff; 
printk("\n\r state_task"); 
for(;;)
  {
  tmp=get_conc_n();  
  tmp<<=4;
  cur_state&= ~CONC_MASK;
  cur_state |= tmp;
    if((prev_state!=cur_state)||(prev_coord!=cur_coord))
    {
      prev_state=cur_state;
      prev_coord=cur_coord;
      put_can_cmd_stat(cur_state,cur_coord);
     }
   else
   {
      msleep(50);
      cnt_led++;
      if(cnt_led>NUM_CNT_LED)
      {
        cnt_led=0;
        t_led++;
        on_led(t_led);
      }
   }
  }

}
////========================================================  
void tst1_task( void *pvParameters )
{
////uint8_t btst=0; 
uint32_t t_coord=0;  
uint8_t t_stat=0x8; 

////uint8_t ii=0; 
printk("\n\r tst1_task"); 
///=======================================
#if 0
can_msg_t  send_msg;
go_cmd_t t_go_cmd;
t_go_cmd.cmd=GO_CMD ;
t_go_cmd.dirs=1;
t_go_cmd.step_per=1000;
send_msg.len=CAN_MAX_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
t_go_cmd.steps=10;
memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
send_msg.id=ID_BRD; 
#endif
///============================================
#if 0
for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
    printk("\n\r can_rx"); 
    printk("\n\r ExtId[%x]",CAN_RxMsg.id);
    printk("\n\r DLC[%x]\n\r ",CAN_RxMsg.len);
    for(ii=0;ii<8;ii++)
      {
      printk("[%x] ",CAN_RxMsg.data[ii]);
      }
    }
  else
  {
////   CAN_wrMsg (&send_msg);
    msleep(20);
  }
  }
#endif
for(;;)
  {
  put_can_cmd_stat(t_stat,t_coord);
   
   t_coord++; 
    msleep(20);
  }
}
////=======================================================
void tst_task( void *pvParameters )
{
///uint8_t btst=0; 
char key=0;
printk("\n\r tst_task"); 
 
for(;;)
{
if(check_push_key_dbg())
  {
  key=get_byte_dbg() ; 
      printk("\n\r [%]", key); 
  } 
msleep(10);
}
}
	
void  set_ms1(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_MS1_PIN_GPIO, MOT_MS1_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_MS1_PIN_GPIO, MOT_MS1_PIN);
  }
}
void  set_ms2(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_MS2_PIN_GPIO, MOT_MS2_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_MS2_PIN_GPIO, MOT_MS2_PIN);
  }
}
void  set_ms3(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_MS3_PIN_GPIO, MOT_MS3_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_MS3_PIN_GPIO, MOT_MS3_PIN);
  }
}
void  set_mot_ms(uint8_t idat)
{
 set_ms1(idat&0x1) ;
 idat>>=1;
 set_ms2(idat&0x1) ;
 idat>>=1;
 set_ms3(idat&0x1) ;
}
void  set_ena_mot(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(MOT_ENA_PIN_GPIO, MOT_ENA_PIN);
  }
else
  {
   GPIO_ResetBits(MOT_ENA_PIN_GPIO, MOT_ENA_PIN);
  }
}
void  set_dir_mot(uint8_t idat)
{
if(idat&0x1)
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
void  set_tst1(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST1_PIN_GPIO, TST1_PIN);
  }
else
  {
   GPIO_ResetBits(TST1_PIN_GPIO, TST1_PIN);
  }
}
void  set_tst2(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST2_PIN_GPIO, TST2_PIN);
  }
else
  {
   GPIO_ResetBits(TST2_PIN_GPIO, TST2_PIN);
  }
}
void  set_tst3(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST3_PIN_GPIO, TST3_PIN);
  }
else
  {
   GPIO_ResetBits(TST3_PIN_GPIO, TST3_PIN);
  }
}
void  set_tst4(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST4_PIN_GPIO, TST4_PIN);
  }
else
  {
   GPIO_ResetBits(TST4_PIN_GPIO, TST4_PIN);
  }
}
void  set_tst5(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST5_PIN_GPIO, TST5_PIN);
  }
else
  {
   GPIO_ResetBits(TST5_PIN_GPIO, TST5_PIN);
  }
}
void  set_tst6(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST6_PIN_GPIO, TST6_PIN);
  }
else
  {
   GPIO_ResetBits(TST6_PIN_GPIO, TST6_PIN);
  }
}
void  set_tst7(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST7_PIN_GPIO, TST7_PIN);
  }
else
  {
   GPIO_ResetBits(TST7_PIN_GPIO, TST7_PIN);
  }
}
void  set_tst8(uint8_t idat)
{
if(idat&0x1)
  {
  GPIO_SetBits(TST8_PIN_GPIO, TST8_PIN);
  }
else
  {
   GPIO_ResetBits(TST8_PIN_GPIO, TST8_PIN);
  }
}

void  on_led(uint8_t idat)
{
  set_tst7(idat);
}
