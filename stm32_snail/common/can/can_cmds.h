#ifndef __CAN_CMDS_H_
#define __CAN_CMDS_H_
///=========================================================
#define CAN_MAX_LEN_QUEU 16

#define ID_X_CMD         (0x1<<5)
#define ID_Y_CMD         (0x1<<6)
#define ID_Z_CMD         (0x1<<7)

#define DIR_X           (0x1<<0)
#define DIR_Y           (0x1<<1)
#define DIR_Z           (0x1<<2)

#define GO_CMD                0x1
#define GET_STAT_CMD          0x2

typedef struct  go_cmd_s_{
  uint8_t  cmd;                       /// 
  uint8_t  dirs;                     /// Dirs X,Y,Z ....
  uint16_t  step_per;                 /// period step
  uint32_t  steps;                 /// steps X,Y , Z 
}go_cmd_t;
#if 0
typedef struct  can_msg_s_{
  uint32_t  id;                       /// 
  uint8_t  type;                     /// 
  uint8_t  data[CAN_MAX_NUM_BYTES];                 ///
 }can_msg_t;
#endif
///=========================================================
extern void mc_reset(void);
extern int put_can_cmd_go(uint8_t dirs,uint16_t per
                   ,uint32_t step_x
                   ,uint32_t step_y
                   ,uint32_t step_z);

#endif  //// __CAN_CMDS_H_
