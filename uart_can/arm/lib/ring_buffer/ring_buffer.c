#include <stdlib.h>
#include <string.h>

#include "ring_buffer.h"

extern void *pvPortMalloc( size_t xWantedSize );

uint8_t*  ringbuffer_init(ringbuffer_t *rbuffer,int size)
{
rbuffer->buffer=(uint8_t*)pvPortMalloc(size); 
if(rbuffer->buffer!=0)
  {
  memset(rbuffer->buffer, 0, size);
  rbuffer->put_index = 0;
  rbuffer->get_index = 0;
  rbuffer->size = size;
////  rbuffer->cnt = 0;
  }
return rbuffer->buffer;
}
void  ringbuffer_clr(ringbuffer_t *rbuffer)
{
  memset(rbuffer->buffer, 0, rbuffer->size);
  rbuffer->put_index = 0;
  rbuffer->get_index = 0;
///  rbuffer->cnt = 0;
}

///inline 
int ringbuffer_putc(ringbuffer_t* rbuffer,char ch)
{
rbuffer->buffer[rbuffer->put_index] = ch;
rbuffer->put_index++;
if(rbuffer->put_index>=rbuffer->size)
  rbuffer->put_index=0;
///rbuffer->cnt++;
return 0;///rbuffer->cnt;
}
////inline 
int ringbuffer_getc(ringbuffer_t *rbuffer ,uint8_t *o_ch)
{
uint8_t ch;
uint16_t cnt=1;
if (rbuffer->get_index == rbuffer->put_index)
  return -1;

   ch = rbuffer->buffer[rbuffer->get_index];
    *o_ch=ch;
    rbuffer->get_index++;
    if(rbuffer->get_index>=rbuffer->size)
        rbuffer->get_index=0;
    if (rbuffer->get_index == rbuffer->put_index)
      cnt=0;
    else
      cnt=1;
return cnt;
}
inline 
uint16_t get_ringbuffer_cnt(ringbuffer_t *ring_buffer)
{
uint32_t head_to_end = ring_buffer->size - ring_buffer->get_index;
return (uint16_t)((head_to_end + ring_buffer->put_index) % ring_buffer->size);
}


