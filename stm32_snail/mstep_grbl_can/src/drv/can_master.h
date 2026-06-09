#ifndef CAN_MASTER_H
#define CAN_MASTER_H

#include <stdint.h>
#include "can.h"

#define CAN_MAX_LEN_QUEU        8
#define CAN_SEND_STACK_SIZE     512
#define CAN_TASK_STACK_SIZE     512
#define CAN_SEND_TASK_PRIORITY  5
#define CAN_TASK_PRIORITY       5
#define CAN_POLL_TASK_PRIORITY  4

#define CAN_POLL_STACK_SIZE     256

int can_master_tx(uint32_t id, const uint8_t *data, uint8_t len);
void can_threads_start(void);
void st_can_master_service_rx(void);

#endif
