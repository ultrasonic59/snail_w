#ifndef __CAN_CMDS_H_
#define __CAN_CMDS_H_
///=========================================================
#define CAN_MAX_LEN_QUEU 16
#define ID_MASK         (0x7e0)

#define ID_X_CMD         (0x1<<5)
#define ID_Y_CMD         (0x1<<6)
#define ID_Z_CMD         (0x1<<7)

#define ID_MASTER_CMD    (0x1<<9)

#define DIR_X           (0x1<<0)
#define DIR_Y           (0x1<<1)
#define DIR_Z           (0x1<<2)

#define READY_X           (0x1<<0)
#define READY_Y           (0x1<<1)
#define READY_Z           (0x1<<2)

#define AXIS_X           (0x1<<0)
#define AXIS_Y           (0x1<<1)
#define AXIS_Z           (0x1<<2)

#define GO_CMD                0x1
#define GET_STAT_CMD          0x2
#define PUT_STAT_CMD          0x3
#define PUT_ACK               0x4
#define PRG_PARAM             0x5

#define STATE_IDLE           0
#define STATE_READY          1
#define STATE_MOVE           2
#define STATE_ERROR          3

#define LEN_ACK_QU      8

#define CAN_REQ_STAT_NUM_BYTES 1

typedef struct  go_cmd_s_{
  uint8_t  cmd;                       /// 
  uint8_t  dirs;                     /// Dirs X,Y,Z ....
  uint16_t  step_per;                 /// period step
  uint32_t  steps;                 /// steps X,Y , Z 
}go_cmd_t;

typedef struct  put_stat_cmd_s_{
  uint8_t  cmd;                         /// 
  uint8_t  axis;                        /// X,Y , Z 
  uint8_t  state;                     /// ready,move,error
  uint8_t  rsv;
  uint32_t  coord;                      /// 
}put_stat_cmd_t;

typedef struct  ack_s_{
  uint8_t  ack_cmd;                         /// 
  uint8_t  axis;                        /// X,Y , Z 
}ack_t;

typedef struct  put_ack_s_{
  uint8_t  cmd;                         /// 
  ack_t   ack;                         /// 
}put_ack_t;

typedef struct  prg_param_cmd_s_{
  uint8_t   cmd;                         /// 
  uint16_t  num_par;                        /// 
  uint8_t   len_par;                     ///bytes 
  uint32_t  par_val;                      /// 
}prg_param_cmd_t;

///=========================================================
extern void mc_reset(void);
extern int put_can_cmd_go(uint8_t dirs,uint16_t per
                   ,uint32_t step_x
                   ,uint32_t step_y
                   ,uint32_t step_z);

extern int put_can_cmd_stat(uint8_t state
                   ,uint32_t coord);
extern int put_can_ack(uint8_t cmd );

#endif  //// __CAN_CMDS_H_
