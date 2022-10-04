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

extern void uDelay (const uint32_t usec);
extern void  put_tst_pin(uint8_t idat);

uint32_t cur_coord=0;
uint8_t cur_stat=0;

void mot_spi_wr(uint8_t addr,uint16_t idata);
uint16_t mot_spi_rd(uint8_t addr);
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
////=============== TST2 ============================
RCC_AHB1PeriphClockCmd(TST2_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST2_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST2_PIN_GPIO, &GPIO_InitStructure );
////=============== TST3 ============================
RCC_AHB1PeriphClockCmd(TST3_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST3_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( TST3_PIN_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(TST3_PIN_GPIO, TST3_PIN_NPIN, GPIO_AF_TIM1);

////=============== TST7 ============================
RCC_AHB1PeriphClockCmd(TST7_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = TST7_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( TST7_PIN_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(TST7_PIN_GPIO, TST7_PIN_NPIN, GPIO_AF_TIM8);
  
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
////=============== MOT_FAULT ============================
RCC_AHB1PeriphClockCmd(MOT_FAULT_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_FAULT_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_Init( MOT_FAULT_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_STALLN ============================
RCC_AHB1PeriphClockCmd(MOT_STALLN_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_STALLN_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_Init( MOT_STALLN_PIN_GPIO, &GPIO_InitStructure );
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
////=============== MOT_RESET ============================
RCC_AHB1PeriphClockCmd(MOT_RESET_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_RESET_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( MOT_RESET_PIN_GPIO, &GPIO_InitStructure );
////=============== MOT_SLEEP ============================
RCC_AHB1PeriphClockCmd(MOT_SLEEP_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_SLEEP_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( MOT_SLEEP_PIN_GPIO, &GPIO_InitStructure );
////#define MOT_STEP_TIM  	        TIM12
////=============== MOT_STEP ============================
RCC_AHB1PeriphClockCmd(MOT_STEP_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_STEP_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( MOT_STEP_PIN_GPIO, &GPIO_InitStructure );
GPIO_PinAFConfig(MOT_STEP_PIN_GPIO, MOT_STEP_PIN_NPIN, GPIO_AF_TIM1);
////===================================================================

////=============== MOT_DIR ============================
RCC_AHB1PeriphClockCmd(MOT_DIR_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_DIR_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( MOT_DIR_PIN_GPIO, &GPIO_InitStructure );
////GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

////=============== MOT_SPI_SCS ============================
RCC_AHB1PeriphClockCmd(MOT_SPI_SCS_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MOT_SPI_SCS_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( MOT_SPI_SCS_PIN_GPIO, &GPIO_InitStructure );
////============== CAN1_INH ============================
RCC_AHB1PeriphClockCmd(CAN1_INH_PIN_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = CAN1_INH_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init( CAN1_INH_PIN_GPIO, &GPIO_InitStructure );
GPIO_ResetBits(CAN1_INH_PIN_GPIO, CAN1_INH_PIN);

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

////==================================================

volatile uint32_t num_step=0;

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

void stop_mot_step_tim(void)
{
TIM_Cmd(MOT_STEP_TIM, DISABLE);
}
void ena_mot(uint8_t ena_dis)
{
uint16_t tmp;
 
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
volatile uint32_t gsr;
////=======================================================
void MOT_STEP_TIM_IRQHandler(void)
{ 
if(num_step)
  {
  num_step--;  
  if(num_step==0)
    {
    stop_mot_step_tim(); 
    ena_mot(0) ;
    }
  }
////TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC2);
TIM_ClearITPendingBit(MOT_STEP_TIM, TIM_IT_CC1);
}
////===============================================
uint8_t get_conc0(void)
{
return GPIO_ReadInputDataBit(CONC0_PIN_GPIO, CONC0_PIN);
}
uint8_t get_conc1(void)
{
return GPIO_ReadInputDataBit(CONC1_PIN_GPIO, CONC1_PIN);
}
////=============================================
void hw_board_init(void)
{
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
init_gpio();
UART_DBG_Init(); 

mot_step_tim_init();
mot_spi_init();
////init_enc_tim();
////CAN_Config();

}
////============================================
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

G_CTRL_REG.DTIME 	= 0x03;
G_CTRL_REG.ISGAIN 	= 0x03;
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

}
////========================================================  
void set_mot_rej(uint8_t rej)
{
uint16_t tmp;
CTRL_Register_t *t_ctrl_reg=(CTRL_Register_t*)&tmp;
tmp=mot_spi_rd(ADDR_MOT_CTRL);
t_ctrl_reg->MODE=rej;
mot_spi_wr(ADDR_MOT_CTRL,tmp);
}
////============================================
extern uint8_t can1_send(uint16_t id,uint8_t data_len,uint8_t *data);
extern uint8_t  CAN_TxRdy;              /* CAN HW ready to transmit message */
extern uint8_t  CAN_RxRdy;              /* CAN HW received a message        */
////extern CanRxMsg RxMessage;
#if 0
set_dir_mot(uint8_t idat)
void set_mot_dir(uint8_t dir)
{
  
}


void set_mot_step(uint8_t step)
{
  
}
#endif
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
///=========================================================
void CAN1_Init (void)
{
uint32_t id;
 uint32_t mask;
CAN_Config();

mask= ID_MASK << 21; ///5+16

#if STEP_X
  id=ID_X_CMD<<21; ///5+16

#elif STEP_Y
  id=ID_Y_CMD<<21; ///5+16
#elif STEP_Z
  id=ID_Z_CMD<<21; ///5+16
#else 
  #error "\n\r=== STEP_... nodefined ==="; 
#endif

CAN_FilterConfig(0,id,mask);	
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

extern can_msg_t CAN_RxMsg;
////xQueueHandle queu_can_resv;
xQueueHandle queu_to_send;

void can_rsv_task( void *pvParameters )
{
///uint8_t ii=0; 
////go_cmd_t *p_can_cmd=  (go_cmd_t *)CAN_RxMsg.data;

printk("\n\r can_rsv_task"); 
////queu_can_resv=xQueueCreate(CAN_MAX_LEN_QUEU,sizeof(can_msg_t));
 
for(;;)
  {
  if( CAN_RxRdy)
    {
    CAN_RxRdy=0;
    switch(CAN_RxMsg.data[0]) {
      case GO_CMD:
        {
        go_cmd_t *p_can_cmd=  (go_cmd_t *)CAN_RxMsg.data;
         printk("Go [dir=%x:per=%d:steps=%d] ",p_can_cmd->dirs,p_can_cmd->step_per,p_can_cmd->steps);
        }
        break;
      case GET_STAT_CMD:
        {
        put_can_cmd_stat(cur_stat,cur_coord);
 
   ////     put_stat_cmd_t *p_stat_cmd=  (go_cmd_t *)CAN_RxMsg.data;
 
  ////      printk("Go [dir=%x:per=%d:steps=%d] ",p_can_cmd->dirs,p_can_cmd->step_per,p_can_cmd->steps);
        }
        break;
        
    default:
      break;
    }
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

////========================================================  
void tst1_task( void *pvParameters )
{
////uint8_t btst=0; 
uint8_t ii=0; 
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
send_msg.id=ID_X_CMD; 
#endif
///============================================

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
}
////=======================================================
	
