#ifndef _CAN_MESSAGE_H_
#define _CAN_MESSAGE_H_

#define MAX_CAN_DADA_LEN 8

typedef struct can_message_s
{
  struct {
    quint8 dlc:4;
    quint8 RTR:1;
    quint8 IDE:1;
  };
  quint32 id;
  quint8 data[MAX_CAN_DADA_LEN];
} can_message_t;

#endif ///_CAN_MESSAGE_H_
