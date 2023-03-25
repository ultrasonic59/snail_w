#ifndef __CAN_CMD_H_
#define __CAN_CMD_H_
#define MAX_CAN_NUM_BYTES 8

typedef struct can_cmd_s{
quint8 num_bytes;
quint8 data[MAX_CAN_NUM_BYTES];
}can_cmd_t;

#endif