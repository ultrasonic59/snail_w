#include <stdio.h>
#include <string.h>

#include "board.h"
#include "serial.h"
#include "my_misc.h"

uint8_t UserTxBuffer[64];

uint8_t uart_read_blocking(void) {
int cnt;
///int32_t ret;
uint8_t ch;
do {
    cnt= ringbuffer_getc(&uart_rx_buffer ,&ch); 
  } while(cnt < 0);
return ch;
}

uint32_t get_nibbles(int nibbles) {
int i;
uint32_t id;
char c;

id = 0;
for (i = 0; i < nibbles; i++) {
  c = uart_read_blocking();
  id <<= 4;
  id |= nibble2bin(c);
  }
return id;
}

int slcan_command(void) {
uint8_t num_bytes=0;  
///uint8_t sw_flow = _TRUE;
uint8_t ext, rtr;
uint8_t i, dlc, data[MAX_CAN_LEN];
uint32_t id;
int32_t ret ;
char ch;
uint8_t send_can;

id = 0;
dlc = 0;
ext = _TRUE;
send_can = _TRUE;
rtr = _FALSE;
ch = uart_read_blocking();
switch (ch) {
  case 'T':
    id = get_nibbles(8);
    dlc = get_nibbles(1);
    break;
  case 't':
    ext = _FALSE;
    id = get_nibbles(3);
    dlc = get_nibbles(1);
    break;
  case 'R':
    rtr = _TRUE;
    ext = _TRUE;
    id = get_nibbles(8);
    dlc = get_nibbles(1);
    break;
  case 'r':
    rtr = _TRUE;
    ext = _FALSE;
    id = get_nibbles(3);
    dlc = get_nibbles(1);
    break;
  case 'S':
    ch = get_nibbles(1);
   cur_can_br=ch;
 ////   can_speed(ch);
    num_bytes = sprintf((char*)UserTxBuffer,"\r");
   send_can = _FALSE;
    break;
  case 'v':
    send_can = _FALSE;
    num_bytes = sprintf((char*)UserTxBuffer,"vSTM32\r");
    break;
  case 'V':
    send_can = _FALSE;
    num_bytes = sprintf((char*)UserTxBuffer,"V0102\r");
   break;
  case 'C':    ////  close
    send_can = _FALSE;
    break;
  case 'O':     ////open
   init_can();
    send_can = _FALSE;
    num_bytes = sprintf((char*)UserTxBuffer,"\r");
   break;
default:
    send_can = _FALSE;
    num_bytes = sprintf((char*)UserTxBuffer,"%c\r",ch);
   break;
    }
  if(dlc > MAX_CAN_LEN) {
  /* consume chars until eol reached */
    do {
        ret = uart_read_blocking();
      } while (ret != '\r');
    return -1;
    }
  for (i = 0; i < dlc; i++) {
      data[i] = (uint8_t) get_nibbles(2);
      }

	/* consume chars until eol reached */
   do {
    ret = uart_read_blocking();
  } while (ret != '\r');
////================================================
  if (send_can) {
    ret = can_transmit( id, ext, rtr, dlc, data);
    on_led();
  }
if(num_bytes)
  {
   write_my_uart((char*)UserTxBuffer,num_bytes); 
  }
return 0;
}
void slc_task( void *pvParameters )
{
uint32_t rd_cnt;
q_uart_rd  = xQueueCreate(1,sizeof(uint32_t));
for( ;; )
  {
  xQueueReceive(q_uart_rd,&rd_cnt,portMAX_DELAY);
  slcan_command();
  }
  
}

