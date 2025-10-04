

#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "board.h"
#include "hdlc.h"

encoder_data_t resiv_enc={0};

void UART_ENC_IRQHandler(void)
{
///int cnt;  
uint8_t ch;
uint32_t tmp_sr;
////signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
////signed portBASE_TYPE xTaskWoken= pdFALSE;

tmp_sr=UART_ENC->SR;  
////put_tst1(1);  
if((tmp_sr&USART_FLAG_RXNE) != 0)
////if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
  UART_ENC->SR &= ~USART_FLAG_RXNE;              ///  USART_ClearITPendingBit(UART_BT, USART_IT_RXNE);
  ch = (u8)(UART_ENC->DR & 0x0FF);
  
  if (hdlc_on_bytein(ch) > 0)
    {
 ///    memcpy(&resiv_enc,g_hdlc.obr_buff,sizeof(send_data_t));

      ;
   //// xQueueSendFromISR(g_hdlc_bt.ev_rsv_frame, &ch, &xHigherPriorityTaskWoken);
  }
  }
else if((tmp_sr&USART_FLAG_ORE) != 0)
////if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
////  put_tst3(1);  
  ch = (u8)(UART_ENC->DR & 0x0FF);
///  ringbuffer_putc(&rx_bt_buffer, ch); 
////  rt_hw_serial_isr(&serial4);
  /* clear interrupt */
  USART_ClearITPendingBit(UART_ENC, USART_FLAG_ORE);
  }

}

void init_irq_enc(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_InitStructure.NVIC_IRQChannel = UART_ENC_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_KERNEL_INTERRUPT_PRIORITY;///0x6;
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


