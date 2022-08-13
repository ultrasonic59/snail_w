#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "my_grbl.h"
#include "can.h"
#include "can_cmds.h"
#include "printk.h"
////=======================================
extern xQueueHandle queu_to_send;

int put_can_cmd_reset_all(void)
{
  return 0;
}

void _mc_reset(void)
{
put_can_cmd_reset_all();  
report_init_message();
}
#if 0
  unsigned int   id;                 // 29 bit identifier
  unsigned char  data[CAN_MAX_NUM_BYTES];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
#endif
int put_can_cmd_go(uint8_t dirs,uint16_t per
                   ,uint32_t step_x
                   ,uint32_t step_y
                   ,uint32_t step_z)
{
///uint8_t btst=0;  
can_msg_t  send_msg;
go_cmd_t t_go_cmd;
t_go_cmd.cmd=GO_CMD ;
t_go_cmd.dirs=dirs;
t_go_cmd.step_per=per;
send_msg.len=CAN_MAX_NUM_BYTES;
send_msg.format=STANDARD_FORMAT;
send_msg.type=DATA_FRAME;
if(step_x)
  {
   t_go_cmd.steps=step_x;
   memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
   send_msg.id=ID_X_CMD; 
   xQueueSend(queu_to_send,&send_msg,CAN_TIMEOUT_SEND);
  }
if(step_y)
  {
   t_go_cmd.steps=step_y;
   memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
   send_msg.id=ID_Y_CMD; 
   xQueueSend(queu_to_send,&send_msg,CAN_TIMEOUT_SEND);
  }
if(step_z)
  {
   t_go_cmd.steps=step_z;
   memcpy(send_msg.data,&t_go_cmd,sizeof(go_cmd_t));
   send_msg.id=ID_Z_CMD; 
   xQueueSend(queu_to_send,&send_msg,CAN_TIMEOUT_SEND);
  }

////send_msg.data[1]=btst;    
////xQueueSend(queu_to_send,&send_msg,CAN_TIMEOUT_SEND);

///go_cmd_t   go_cmd;
#if 0        
        printk("\n\r tst_cnt[%d][%02x][%d][%d][%d]", per, dirs
            , step_x
            , step_y
            , step_z
        );
#endif

  return 0;
}
