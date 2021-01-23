#include "snail_spd_brd.h"

static void DBG_RCC_Configuration(void)
{
/* Enable BT GPIO clocks */
RCC_AHB1PeriphClockCmd(UART_DBG_TX_GPIO_CLK, ENABLE);
RCC_AHB1PeriphClockCmd(UART_DBG_RX_GPIO_CLK, ENABLE);
UART_DBG_CLK_INIT(UART_DBG_CLK, ENABLE);
}


static void DBG_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    /* Configure BT Rx/tx PIN */
    GPIO_InitStructure.GPIO_Pin = UART_DBG_TX_PIN;
    GPIO_Init(UART_DBG_TX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = UART_DBG_RX_PIN;
    GPIO_Init(UART_DBG_RX_GPIO_PORT, &GPIO_InitStructure);

    /* Connect alternate function */
    GPIO_PinAFConfig(UART_DBG_TX_GPIO_PORT, UART_DBG_TX_SOURCE, UART_DBG_TX_AF);
    GPIO_PinAFConfig(UART_DBG_RX_GPIO_PORT, UART_DBG_RX_SOURCE, UART_DBG_RX_AF);
}
///==========================
int get_byte_dbg(void) 
{
while (!(UART_DBG->SR & USART_SR_RXNE));
return (UART_DBG->DR);
}
int rdy_rx_dbg(void) 
{
if((UART_DBG->SR & USART_SR_RXNE))
  return 1;
else
  return 0;
}
///======================================
int send_char_dbg(int c) 
{ 
while (!(UART_DBG->SR & 0x0080));
UART_DBG->DR = (c & 0x1FF);
return (c);
}

///===========================================
void uart_dbg_init(void)
{
int i;
USART_InitTypeDef USART_InitStructure;
DBG_RCC_Configuration();
DBG_GPIO_Configuration();
  USART_DeInit(UART_DBG);
  USART_InitStructure.USART_BaudRate = DEF_DBG_BR;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
////  USART_InitStructure.USART_StopBits = USART_StopBits_2 ;
  USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(UART_DBG, &USART_InitStructure);
  
  USART_Cmd(UART_DBG, ENABLE);

for (i = 0; i < 0x1000; i++)
  {
  __NOP();   //avoid unwanted output
  }
UART_DBG->CR1 = 0x202C;

UART_DBG->SR = 0;
////init_irq_bt();
}

///================================================
