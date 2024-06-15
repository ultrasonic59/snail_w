/*
 * usb_hid_thr.h
 *
 *  Created on: May 9, 2024
 *      Author: vovag
 */

#ifndef _USB_HID_THR_H_
#define _USB_HID_THR_H_

#include "FreeRTOS.h"
#include "queue.h"

#define CMD_SET_LED  0x1
#define CMD_GET_LED  0x2

#define MAX_DAT_CNT 6

typedef struct hid_cmd_s_
{
uint8_t cmd;
uint8_t num_bytes;
uint8_t dat[MAX_DAT_CNT];
}hid_cmd_t;

extern xQueueHandle ev_rsv_hid;

extern void usb_hid_thr(void* pp);


#endif /* _USB_HID_THR_H_ */
