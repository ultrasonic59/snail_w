#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include "board.h"

#include "serial.h"
#include "ring_buffer.h"

ringbuffer_t uart_rx_buffer;
ringbuffer_t uart_tx_buffer;
xQueueHandle q_uart_rd = 0;

////======================================
#if 0   
void ring_init(ring_t *ring, uint8_t * buf, ring_size_t size) {
ring->data = buf;
ring->size = size;
ring->begin = 0;
ring->end = 0;
}
#endif
#if 0
int32_t _ring_write_ch(ring_t *ring, uint8_t ch) {
if (((ring->end + 1) % ring->size) != ring->begin) {
  ring->data[ring->end++] = ch;
  ring->end %= ring->size;
  return (uint32_t) ch;
  }
return -1;
}
int32_t ring_write(ring_t *ring, uint8_t * data, ring_size_t size) {
int32_t i;
///=============================
taskENTER_CRITICAL();
for (i = 0; i < size; i++) {
	if (ring_write_ch(ring, data[i]) < 0)
		return -i;
  }
taskEXIT_CRITICAL();
///============================
return i;
}
#endif
int32_t ring_write(ringbuffer_t *ring, uint8_t * data, uint32_t size) {
int32_t i;
///=============================
////taskENTER_CRITICAL();
for (i = 0; i < size; i++) {
  ringbuffer_putc(ring, data[i]);
////    if (ringbuffer_putc(ring, data[i]) < 0)
////      return -i;
  }
////taskEXIT_CRITICAL();
///============================
return 0;
}

#if 0
int32_t ring_read_ch(ring_t *ring, uint8_t * ch) {
	int32_t ret = -1;

	if (ring->begin != ring->end) {
		ret = ring->data[ring->begin++];
		ring->begin %= ring->size;
		if (ch)
			*ch = ret;
	}
	return ret;
}

int32_t ring_bytes_free(const ring_t *rb)
{
    if (rb->end >= rb->begin)
        return BUFFER_SIZE - (rb->end - rb->begin);
    else
        return rb->begin - rb->end - 1;
}

ring_t output_ring;
ring_t input_ring;
uint8_t output_ring_buffer[BUFFER_SIZE];
uint8_t input_ring_buffer[BUFFER_SIZE];
#endif

/*-----------------------------------------------------------*/
void init_serial(void)
{
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
/* Enable USART2 clock */
RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );	
USART_InitStructure.USART_BaudRate = MY_USART_SPEED;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No ;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		
USART_Init( MY_UART, &USART_InitStructure );
		
USART_ITConfig( MY_UART, USART_IT_RXNE, ENABLE );

NVIC_InitStructure.NVIC_IRQChannel = MY_UART_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_KERNEL_INTERRUPT_PRIORITY;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init( &NVIC_InitStructure );
		
USART_Cmd( MY_UART, ENABLE );		
}
#if 0
void dma_read()
{
	/* Reset DMA channel*/
	dma_channel_reset(DMA1, DMA_CHANNEL6);

	dma_set_peripheral_address(DMA1, DMA_CHANNEL6, (uint32_t)&USART2_DR);
	dma_set_memory_address(DMA1, DMA_CHANNEL6, (uint32_t)dma_rx_buf);
	dma_set_number_of_data(DMA1, DMA_CHANNEL6, sizeof(dma_rx_buf));
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL6);
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL6);
	dma_enable_circular_mode(DMA1, DMA_CHANNEL6);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL6, DMA_CCR_PSIZE_8BIT);
	dma_set_memory_size(DMA1, DMA_CHANNEL6, DMA_CCR_MSIZE_8BIT);
	dma_set_priority(DMA1, DMA_CHANNEL6, DMA_CCR_PL_HIGH);

	//dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL6);

	dma_enable_channel(DMA1, DMA_CHANNEL6);

    usart_enable_rx_dma(USART2);
}
#endif
#if 0
void init_dma_uart_read(void)
{
DMA_InitTypeDef dma; 

DMA_StructInit(&dma);

dma.DMA_PeripheralBaseAddr = (uint32_t)&MY_UART ->DR ;
dma.DMA_MemoryBaseAddr = (uint32_t)&dma_rx_buf[0];
dma.DMA_DIR = DMA_DIR_PeripheralSRC;
dma.DMA_BufferSize = sizeof(dma_rx_buf);
dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
DMA_Init(DMA1_Channel6, &dma);

}
#endif
void usart_setup(void) {
if(ringbuffer_init(&uart_rx_buffer,RB_SIZE)==0)
  {
    for(;;)
    {
      ;
    }
  }
if(ringbuffer_init(&uart_tx_buffer,RB_SIZE)==0)
    {
    for(;;)
    {
      ;
    }
    }
init_serial();
////init_dma_uart_read();
}
int sendchar_my_uart (int c) 
{ 
while (!(MY_UART->SR & 0x0080));
MY_UART->DR = (c & 0x1FF);
return (c);
}

////===========================================
void MY_UART_IRQHandler(void)
{
uint8_t ch;
static uint32_t cnt_rd=0;  
uint32_t t_cnt_rd=0;  
int cnt=0;  

signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
////volatile int32_t data;
volatile uint32_t tsr;
tsr = MY_UART->SR;
if (((tsr & USART_SR_TXE) != 0)) {
  cnt= ringbuffer_getc(&uart_tx_buffer ,&ch); 
   if(cnt>=0)
      {
      MY_UART->DR=ch;
      if(cnt==0)
        MY_UART->CR1 &= ~USART_CR1_TXEIE;
      }
     else
        MY_UART->CR1 &= ~USART_CR1_TXEIE;
     MY_UART->SR &= ~USART_SR_TXE;	          // clear interrupt
   }
if (tsr & USART_FLAG_RXNE) 
    {                  // 
     ch = (uint8_t)(MY_UART->DR & 0x0FF);
     ringbuffer_putc(&uart_rx_buffer, ch); 
     MY_UART->SR &= ~USART_FLAG_RXNE;	          // clear interrupt
     if(ch=='\r')
        {
        t_cnt_rd=cnt_rd; 
        xQueueSendFromISR(q_uart_rd, &t_cnt_rd, &xHigherPriorityTaskWoken);
        cnt_rd=0;
        }
     else
        {
        cnt_rd++;
        }
     
    }

}


///===========================================
int write_my_uart( char *ptr, int len) {
int ret;
ret = ring_write(&uart_tx_buffer, (uint8_t *) ptr, len);
  if (ret < 0)
    ret = -ret;
 MY_UART->CR1 |= USART_CR1_TXEIE;	          // 
return ret;
}

	
