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
#ifdef WIN32
#include <stdio.h>
#include <process.h> 
#include <conio.h>
CRITICAL_SECTION CriticalSection;

/////#define LOCAL_ECHO

HANDLE hSerial = INVALID_HANDLE_VALUE;
void RecvthreadFunction( void *);
void SendthreadFunction( void *);

#endif

#define RX_RING_BUFFER (RX_BUFFER_SIZE+1)
#define TX_RING_BUFFER (TX_BUFFER_SIZE+1)

uint8_t serial_rx_buffer[RX_RING_BUFFER];
uint8_t serial_rx_buffer_head = 0;
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
#ifdef WIN32
  InitializeCriticalSectionAndSpinCount(&CriticalSection,0x00000400);
#endif
}
#ifdef WIN32
#define MAX_DEVPATH_LENGTH 1024
void winserial_init(char *pPort)
{
    DCB dcb;
    BOOL fSuccess;
    TCHAR devicePath[MAX_DEVPATH_LENGTH];
    COMMTIMEOUTS commTimeout;

    if (pPort != NULL)
    {
        mbstowcs_s(NULL, devicePath, MAX_DEVPATH_LENGTH, pPort, strlen(pPort));
        hSerial = CreateFile(devicePath, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                    OPEN_EXISTING, 0, NULL);
    }
    if (hSerial != INVALID_HANDLE_VALUE)
    {
        //  Initialize the DCB structure.
        SecureZeroMemory(&dcb, sizeof(DCB));
        dcb.DCBlength = sizeof(DCB);
        fSuccess = GetCommState(hSerial, &dcb);
        if (!fSuccess) 
        {
            CloseHandle(hSerial);
            hSerial = INVALID_HANDLE_VALUE;
            return;
        }

        GetCommState(hSerial, &dcb);
        dcb.BaudRate = CBR_115200;     //  baud rate
        dcb.ByteSize = 8;             //  data size, xmit and rcv
        dcb.Parity   = NOPARITY;      //  parity bit
        dcb.StopBits = ONESTOPBIT;    //  stop bit
        dcb.fBinary = TRUE;
        dcb.fParity = TRUE;

        fSuccess = SetCommState(hSerial, &dcb);
        if (!fSuccess) 
        {
            CloseHandle(hSerial);
            hSerial = INVALID_HANDLE_VALUE;
            return;
        }

        GetCommTimeouts(hSerial, &commTimeout);
        commTimeout.ReadIntervalTimeout     = 1;
        commTimeout.ReadTotalTimeoutConstant     = 1;
        commTimeout.ReadTotalTimeoutMultiplier     = 1;
        commTimeout.WriteTotalTimeoutConstant     = 1;
        commTimeout.WriteTotalTimeoutMultiplier = 1;
        SetCommTimeouts(hSerial, &commTimeout);
    }
    _beginthread( RecvthreadFunction, 0, NULL );
    _beginthread( SendthreadFunction, 0, NULL );
}
#endif


// Writes one byte to the TX serial buffer. Called by main program.
void serial_write(uint8_t data) {
  // Calculate next head
  uint8_t next_head = serial_tx_buffer_head + 1;
   if (next_head == TX_RING_BUFFER) { next_head = 0; }

  // Wait until there is space in the buffer
  while (next_head == serial_tx_buffer_tail) {
    // TODO: Restructure st_prep_buffer() calls to be executed here during a long print.
    if (sys_rt_exec_state & EXEC_RESET) { return; } // Only check for abort to avoid an endless loop.
#ifdef WIN32
     Sleep(1);
#endif
  }

  // Store data and advance head
  serial_tx_buffer[serial_tx_buffer_head] = data;

  serial_tx_buffer_head = next_head;


}

#ifdef WIN32
void SendthreadFunction( void *pVoid)
{
    unsigned char szBuf[RX_RING_BUFFER + 1];

	DWORD dwBytesWritten;
	uint8_t nNextTai;
    for (;;)
    {
		while (serial_tx_buffer_head == serial_tx_buffer_tail)
			Sleep(1);
	    uint16_t USB_Tx_length;

        if (serial_tx_buffer_head > serial_tx_buffer_tail)
		    USB_Tx_length = serial_tx_buffer_head - serial_tx_buffer_tail;
        else
        {
		    USB_Tx_length = RX_RING_BUFFER - serial_tx_buffer_tail;
            if (USB_Tx_length == 0)
            {
                USB_Tx_length = serial_tx_buffer_head;
            }
        }
		nNextTai = serial_tx_buffer_tail;

        if (USB_Tx_length != 0)
        {
			if (hSerial != INVALID_HANDLE_VALUE)
			{
				WriteFile(hSerial, serial_tx_buffer + serial_tx_buffer_tail, USB_Tx_length, &dwBytesWritten, NULL);
				nNextTai += (uint8_t)dwBytesWritten;
#ifdef LOCAL_ECHO
				memcpy(szBuf, &serial_tx_buffer[serial_tx_buffer_tail], dwBytesWritten);
				szBuf[dwBytesWritten] = 0;
				printf(szBuf);
#endif
			}
			else
			{
			//	fwrite(szBuf, 1, USB_Tx_length, stdout);
				memcpy(szBuf, &serial_tx_buffer[serial_tx_buffer_tail], USB_Tx_length);
				szBuf[USB_Tx_length] = 0;
				printf(szBuf);
				nNextTai += USB_Tx_length;
			}
			if (nNextTai == RX_RING_BUFFER)
				nNextTai = 0;

			serial_tx_buffer_tail = nNextTai;
		}
	}
}
#endif

// Fetches the first byte in the serial read buffer. Called by main program.
uint8_t serial_read()
{
  uint8_t tail = serial_rx_buffer_tail; // Temporary serial_rx_buffer_tail (to optimize for volatile)
  if (serial_rx_buffer_head == tail) {
    return SERIAL_NO_DATA;
  } else {
    uint8_t data = serial_rx_buffer[tail];

    tail++;
    if (tail == RX_RING_BUFFER) { tail = 0; }
    serial_rx_buffer_tail = tail;

    return data;
  }
}

#ifdef WIN32
//#define WINLOG
void RecvthreadFunction(void *pVoid )
{
    DWORD  dwBytesRead;
    uint8_t data;
    uint8_t next_head;
    for (;;)
    {
        if (hSerial != INVALID_HANDLE_VALUE)
        {
            if (ReadFile(hSerial, &data, 1, &dwBytesRead, NULL) && dwBytesRead == 1)
            {
            }
            else
            {
#ifdef WIN32
								Sleep(1);
#endif

                data = 0;
            }
        }
        else
        {
            while (_kbhit() == 0)
                ;
            data = _getch();
        }
         if (data == 0)
             continue;
#endif
  // Pick off realtime command characters directly from the serial stream. These characters are
  // not passed into the main buffer, but these set system state flag bits for realtime execution.
  switch (data) {
    case CMD_RESET:         mc_reset(); break; // Call motion control reset routine.
    case CMD_STATUS_REPORT: system_set_exec_state_flag(EXEC_STATUS_REPORT); break; // Set as true
    case CMD_CYCLE_START:   system_set_exec_state_flag(EXEC_CYCLE_START); break; // Set as true
    case CMD_FEED_HOLD:     system_set_exec_state_flag(EXEC_FEED_HOLD); break; // Set as true
    default :
      if (data > 0x7F) { // Real-time control characters are extended ACSII only.
        switch(data) {
          case CMD_SAFETY_DOOR:   system_set_exec_state_flag(EXEC_SAFETY_DOOR); break; // Set as true
          case CMD_JOG_CANCEL:   
            if (sys.state & STATE_JOG) { // Block all other states from invoking motion cancel.
              system_set_exec_state_flag(EXEC_MOTION_CANCEL); 
            }
            break; 
          #ifdef DEBUG
            case CMD_DEBUG_REPORT: {uint8_t sreg = SREG; cli(); bit_true(sys_rt_exec_debug,EXEC_DEBUG_REPORT); SREG = sreg;} break;
          #endif
          case CMD_FEED_OVR_RESET: system_set_exec_motion_override_flag(EXEC_FEED_OVR_RESET); break;
          case CMD_FEED_OVR_COARSE_PLUS: system_set_exec_motion_override_flag(EXEC_FEED_OVR_COARSE_PLUS); break;
          case CMD_FEED_OVR_COARSE_MINUS: system_set_exec_motion_override_flag(EXEC_FEED_OVR_COARSE_MINUS); break;
          case CMD_FEED_OVR_FINE_PLUS: system_set_exec_motion_override_flag(EXEC_FEED_OVR_FINE_PLUS); break;
          case CMD_FEED_OVR_FINE_MINUS: system_set_exec_motion_override_flag(EXEC_FEED_OVR_FINE_MINUS); break;
          case CMD_RAPID_OVR_RESET: system_set_exec_motion_override_flag(EXEC_RAPID_OVR_RESET); break;
          case CMD_RAPID_OVR_MEDIUM: system_set_exec_motion_override_flag(EXEC_RAPID_OVR_MEDIUM); break;
          case CMD_RAPID_OVR_LOW: system_set_exec_motion_override_flag(EXEC_RAPID_OVR_LOW); break;
          case CMD_SPINDLE_OVR_RESET: system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_RESET); break;
          case CMD_SPINDLE_OVR_COARSE_PLUS: system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_COARSE_PLUS); break;
          case CMD_SPINDLE_OVR_COARSE_MINUS: system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_COARSE_MINUS); break;
          case CMD_SPINDLE_OVR_FINE_PLUS: system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_FINE_PLUS); break;
          case CMD_SPINDLE_OVR_FINE_MINUS: system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_FINE_MINUS); break;
          case CMD_SPINDLE_OVR_STOP: system_set_exec_accessory_override_flag(EXEC_SPINDLE_OVR_STOP); break;
          case CMD_COOLANT_FLOOD_OVR_TOGGLE: system_set_exec_accessory_override_flag(EXEC_COOLANT_FLOOD_OVR_TOGGLE); break;
          #ifdef ENABLE_M7
            case CMD_COOLANT_MIST_OVR_TOGGLE: system_set_exec_accessory_override_flag(EXEC_COOLANT_MIST_OVR_TOGGLE); break;
          #endif
        }
        // Throw away any unfound extended-ASCII character by not passing it to the serial buffer.
      } else { // Write character to buffer
        next_head = serial_rx_buffer_head + 1;
        if (next_head == RX_RING_BUFFER) { next_head = 0; }

        // Write data to buffer unless it is full.
        if (next_head != serial_rx_buffer_tail) {
          serial_rx_buffer[serial_rx_buffer_head] = data;
          serial_rx_buffer_head = next_head;
        }
      }
  }
#ifdef WIN32
    }
#endif
}

void serial_reset_read_buffer()
{
  serial_rx_buffer_tail = serial_rx_buffer_head;
}
