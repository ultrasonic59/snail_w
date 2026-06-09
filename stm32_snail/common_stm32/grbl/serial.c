/*
  serial.c - Low level functions for sending and recieving bytes via the serial port
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

#ifdef USEUSB
#include "FreeRTOS.h"
#include "task.h"
#endif

#define RX_RING_BUFFER (RX_BUFFER_SIZE+1)
#define TX_RING_BUFFER (TX_BUFFER_SIZE+1)

uint8_t serial_rx_buffer[RX_RING_BUFFER];
volatile uint8_t serial_rx_buffer_head = 0;
volatile uint8_t serial_rx_buffer_tail = 0;

uint8_t serial_tx_buffer[TX_RING_BUFFER];
uint8_t serial_tx_buffer_head = 0;
volatile uint8_t serial_tx_buffer_tail = 0;


// Returns the number of bytes available in the RX serial buffer.
uint8_t serial_get_rx_buffer_available()
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(RX_BUFFER_SIZE - (serial_rx_buffer_head-rtail)); }
  return((rtail-serial_rx_buffer_head-1));
}


// Returns the number of bytes used in the RX serial buffer.
// NOTE: Deprecated. Not used unless classic status reports are enabled in config.h.
uint8_t serial_get_rx_buffer_count()
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(serial_rx_buffer_head-rtail); }
  return (RX_BUFFER_SIZE - (rtail-serial_rx_buffer_head));
}


// Returns the number of bytes used in the TX serial buffer.
// NOTE: Not used except for debugging and ensuring no TX bottlenecks.
uint8_t serial_get_tx_buffer_count()
{
  uint8_t ttail = serial_tx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_tx_buffer_head >= ttail) { return(serial_tx_buffer_head-ttail); }
  return (TX_RING_BUFFER - (ttail-serial_tx_buffer_head));
}


void serial_init()
{

}


// Writes one byte to the TX serial buffer. Called by main program.
void serial_write(uint8_t data) {
#ifdef USEUSB
  uint8_t next_head = serial_tx_buffer_head + 1;
  uint32_t wait = 0;

  while (next_head == serial_tx_buffer_tail) {
    if (sys_rt_exec_state & EXEC_RESET) {
      return;
    }
    taskYIELD();
    if (++wait > 8000U) {
      return;
    }
  }
  serial_tx_buffer[serial_tx_buffer_head] = data;
  serial_tx_buffer_head = next_head;
#else
  (void)data;
#endif
}

int serial_read_tx(void)
{
  uint8_t tail = serial_tx_buffer_tail;

  if (serial_tx_buffer_head == tail) {
    return -1;
  }
  uint8_t data = serial_tx_buffer[tail];
  tail++;
  serial_tx_buffer_tail = tail;
  return data;
}

void serial_tx_unget(void)
{
  if (serial_tx_buffer_tail != serial_tx_buffer_head) {
    serial_tx_buffer_tail--;
  }
}


void serial_rx_push(uint8_t data)
{
  uint8_t next_head = serial_rx_buffer_head + 1;

  if (next_head != serial_rx_buffer_tail) {
    serial_rx_buffer[serial_rx_buffer_head] = data;
    serial_rx_buffer_head = next_head;
  }
}


// Fetches the first byte in the serial read buffer. Called by main program.
uint8_t serial_read()
{
  uint8_t tail = serial_rx_buffer_tail;

  if (serial_rx_buffer_head == tail) {
    return SERIAL_NO_DATA;
  }
  {
    uint8_t data = serial_rx_buffer[tail];

    tail++;
    serial_rx_buffer_tail = tail;
    return data;
  }
}


void serial_reset_read_buffer()
{
  serial_rx_buffer_tail = serial_rx_buffer_head;
}
