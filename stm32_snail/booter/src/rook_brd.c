///#include "stm32f2xx_gpio.h"
#ifdef EMW3165
#include "stm32f4xx_gpio.h"
#else
#include "stm32f2xx_gpio.h"
#endif

#include "rook_v3_brd.h"
#include "drv_spi.h"
#include "rook_sd.h"
///============================================
///==========================
#if 1
void UART_DBG_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
////NVIC_InitTypeDef NVIC_InitStructure;
////  DMA_InitTypeDef  DMA_InitStructure;
GPIO_CLK_INIT(UART_DBG_RX_GPIO_CLK, ENABLE);
GPIO_CLK_INIT(UART_DBG_TX_GPIO_CLK, ENABLE);
UART_DBG_CLK_INIT(UART_DBG_CLK, ENABLE);
////RCC_AHB1PeriphClockCmd(DMA_CLK_INIT,ENABLE);
 /// NVIC_InitStructure.NVIC_IRQChannel                   = UART_DBG_IRQn;
 /// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;////(uint8_t) 0x6;
 /// NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;///0x7;
 /// NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
///  NVIC_Init( &NVIC_InitStructure );
  
  /* Configure USART pin*/
  GPIO_PinAFConfig(UART_DBG_TX_GPIO_PORT, UART_DBG_TX_SOURCE, UART_DBG_TX_AF);
  GPIO_PinAFConfig(UART_DBG_RX_GPIO_PORT, UART_DBG_RX_SOURCE, UART_DBG_RX_AF);
  
  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  
  GPIO_InitStructure.GPIO_Pin = UART_DBG_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(UART_DBG_TX_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = UART_DBG_RX_PIN;
  GPIO_Init(UART_DBG_RX_GPIO_PORT, &GPIO_InitStructure);
  
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
#endif
///==================================

uint16_t spi_SendWord(uint16_t i_data)
{
SPI1_SD_GPIO->BSRRH= SPI1_SD_PIN;		 ///sd=0
  /*!< Loop while DR register in not emplty */
while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
SPI1_NSS_GPIO->BSRRH= SPI1_NSS_PIN;
SPI_I2S_SendData(SPI1, i_data);
while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
SPI1_NSS_GPIO->BSRRL= SPI1_NSS_PIN;
return SPI_I2S_ReceiveData(SPI1);
}

void spi_set_addr(uint16_t i_addr)
{
hw_spi1_set_data_size(SPI_DataSize_16b);
SPI1_A_D_GPIO->BSRRL= SPI1_A_D_PIN;		///a_d =1
SPI1_R_W_GPIO->BSRRH= SPI1_R_W_PIN;		 ///r_w=0
spi_SendWord(i_addr);
}
///==================================
uint16_t spi_get_addr(void)
{
uint16_t  tmp;
hw_spi1_set_data_size(SPI_DataSize_16b);
SPI1_A_D_GPIO->BSRRL= SPI1_A_D_PIN;		///a_d =1
SPI1_R_W_GPIO->BSRRL= SPI1_R_W_PIN;		 ///r_w=1
tmp=spi_SendWord(0);
return tmp;
}
///==================================
void spi_set_dat(uint16_t i_dat)
{
hw_spi1_set_data_size(SPI_DataSize_16b);
SPI1_A_D_GPIO->BSRRH= SPI1_A_D_PIN;		///a_d =0
SPI1_R_W_GPIO->BSRRH= SPI1_R_W_PIN;		 ///r_w=0
spi_SendWord(i_dat);
}
///==================================
uint16_t spi_get_dat(void)
{
uint16_t  tmp;
hw_spi1_set_data_size(SPI_DataSize_16b);
SPI1_A_D_GPIO->BSRRH= SPI1_A_D_PIN;		///a_d =0
SPI1_R_W_GPIO->BSRRL= SPI1_R_W_PIN;		 ///r_w=1
tmp=spi_SendWord(0);
return tmp;
}

u16 rd_dat_addr(u16 addr)
{
u16 rez;
spi_set_addr(addr);
rez= spi_get_dat();
return rez;
}
void wr_dat_addr(u16 addr,u16 dat)
{
spi_set_addr(addr);
spi_set_dat(dat);
}
///====================================
///==================================
void on_pow_bt(u8 on_off)
{
if(on_off&0x1)
	wr_dat_addr(ADDR_UPR_BT,0x03);
else
	wr_dat_addr(ADDR_UPR_BT,0x2);
}

///=============================
int sendchar1 (int c) 
{ 
	while (!(USART1->SR & 0x0080));
	USART1->DR = (c & 0x1FF);
	return (c);
}

void _putk(char ch)
{
//sendchar_hdlc(ch);
sendchar1(ch);
}
void gpio_init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
///====== done fpga =====================
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = FPGA_DONE_PIN;
GPIO_Init(FPGA_DONE_GPIO, &GPIO_InitStructure);
GPIO_SetBits(FPGA_DONE_GPIO, FPGA_DONE_PIN);

/*

///====== programm_b fpga =====================
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = FPGA_PRG_PIN;
GPIO_Init(FPGA_PRG_GPIO, &GPIO_InitStructure);
GPIO_SetBits(FPGA_PRG_GPIO, FPGA_PRG_PIN);
///====== init_b fpga =====================
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = FPGA_INIT_PIN;
GPIO_Init(FPGA_INIT_GPIO, &GPIO_InitStructure);
GPIO_SetBits(FPGA_INIT_GPIO, FPGA_INIT_PIN);
///====== suspend fpga =====================
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = FPGA_SUSP_PIN;
GPIO_Init(FPGA_SUSP_GPIO, &GPIO_InitStructure);
GPIO_SetBits(FPGA_SUSP_GPIO, FPGA_SUSP_PIN);
*/
///init_fpga();

}
///
#define DISABLE_INTERRUPTS() do { __asm("CPSID i"); } while (0)

///====================================
void hw_board_init(void)
{
DISABLE_INTERRUPTS();
UART_DBG_Init(); 
////UART_BT_Init(); 
hw_spi1_init();
gpio_init();
////on_pow_bt(1);	
on_pow_sd(0);
}



