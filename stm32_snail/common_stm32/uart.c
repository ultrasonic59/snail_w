#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "board.h"
#include "hdlc.h"

#define MAX_TRIG   14000
#define MIN_TRIG   200
#define MAX_ENC_COORD   ((1<<14)-1)

extern uint16_t curr_enc;  ///
extern int32_t enc_obor;
extern uint16_t enc_offs;  ///when coord =0;

static encoder_data_t resiv_Enc={0};

void change_coord(void){
uint16_t t_enc;
static uint16_t prev_enc=0;
memcpy(&resiv_Enc,g_hdlc.in_buff,sizeof(encoder_data_t));
t_enc=resiv_Enc.Coord;
curr_enc= MAX_ENC_COORD -t_enc;
 if(prev_enc!=curr_enc){
    if((prev_enc>MAX_TRIG)&&(curr_enc<MIN_TRIG))
      enc_obor++;
    else if((prev_enc<MIN_TRIG)&&(curr_enc>MAX_TRIG))
       enc_obor--;
    prev_enc=curr_enc ;
curr_coord= (enc_obor<<14) + curr_enc- enc_offs;

 ///   t_encoder_data.coord=curr_enc-enc_offs;
///    t_encoder_data.val= enc_obor;
  }
}

void UART_ENC_IRQHandler(void)
{
uint8_t ch;
uint32_t tmp_sr;

tmp_sr=UART_ENC->SR;
////put_tst1(1);
if((tmp_sr&USART_FLAG_RXNE) != 0)
  {
  UART_ENC->SR &= ~USART_FLAG_RXNE;              ///  USART_ClearITPendingBit(UART_BT, USART_IT_RXNE);
  ch = (u8)(UART_ENC->DR & 0x0FF);

  if (hdlc_on_bytein(ch) > 0)
    {
      ;
  }
  }
else if((tmp_sr&USART_FLAG_ORE) != 0)
  {
  ch = (u8)(UART_ENC->DR & 0x0FF);
  USART_ClearITPendingBit(UART_ENC, USART_FLAG_ORE);
  }

}

void init_irq_enc(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_InitStructure.NVIC_IRQChannel = UART_ENC_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = APP_NVIC_LOW_IRQ_PRIORITY;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;////7;	//1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}
///===========================================
////=============================================
void UART_ENC_Init(void)
{
////GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
UART_ENC_CLK_INIT(UART_ENC_CLK, ENABLE);
USART_DeInit(UART_ENC);
USART_InitStructure.USART_BaudRate = ENC_BR;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(UART_ENC, &USART_InitStructure);
UART_ENC->CR1 |= USART_CR1_RXNEIE;
USART_Cmd(UART_ENC, ENABLE);
init_irq_enc();

}
int send_char_enc(int c)
{
while (!(UART_ENC->SR & 0x0080));
UART_ENC->DR = (c & 0x1FF);
return (c);
}

uint8_t uart_send_buff(uint8_t *buff, uint16_t len)
{
 uint16_t ii;
 for(ii=0;ii<len;ii++){
     send_char_enc(buff[ii]);
}
 return len;
}
