#ifndef __HID_CMD_H__
#define __HID_CMD_H__

#define CMD_SET_LED  0x1
#define CMD_GET_LED  0x2

#define MAX_DAT_CNT 6

typedef struct hid_cmd_s_
{
	quint8 cmd;
	quint8 num_bytes;
	quint8 dat[MAX_DAT_CNT];
}hid_cmd_t;

#endif