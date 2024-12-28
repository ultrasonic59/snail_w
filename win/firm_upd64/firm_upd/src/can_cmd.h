#ifndef __CAN_CMD_H_
#define __CAN_CMD_H_

#define MAX_CAN_NUM_BYTES  8
#define OFFS_CAN_CMD       0
#define OFFS_CAN_NUM_BYTES 1
#define OFFS_CAN_DATA      2
#define OFFS_CAN_ADDR      1
///===== common cmd =============

#define RD_EEPROM_REQ         0x8
#define RD_EEPROM_ANS         0x9
#define WR_EEPROM_REQ         0xA
#define WR_EEPROM_ANS         0xB
#define RD_FLASH_REQ          0xC
#define RD_FLASH_ANS          0xD

///===== booter cmd =============
#define CHECK_ERASE_SECTORS   0xF3
#define SET_ADDR_PRG          0xF4
#define GO_TO_BOOTER          0xF5
#define GO_TO_APP             0xF6
#define ERASE_SECTORS         0xF7
#define ERASE_OK              0xF8
#define PRG_DAT               0xF9
#define PRG_DAT_OK            0xFA
#define GET_BOOT_STAT         0xFB
#define PUT_BOOT_STAT         0xFC

#define BOOTER_STATE_IDLE     0xF0
#define BOOTER_STATE_ERASE    0xF1
#define BOOTER_STATE_PROG     0xF2
#define BOOTER_STATE_MASK     0xF0
////#define BOOTER_NO_BOOT        0xF3

#define AXIS_X           (0x1<<0)
#define AXIS_Y           (0x1<<1)
#define AXIS_Z           (0x1<<2)

#define ID_BRD_X (AXIS_X<<5)
#define ID_BRD_Y (AXIS_Y<<5)
#define ID_BRD_Z (AXIS_Z<<5)

typedef struct  put_boot_stat_cmd_s_{
  quint8  cmd;                         /// 
  quint8  axis;                        /// X,Y , Z 
  quint8  state;                     /// 
}put_boot_stat_cmd_t;

typedef struct can_cmd_s{
quint32 id;
quint8 num_bytes;
quint8 data[MAX_CAN_NUM_BYTES];
}can_cmd_t;

#define EEPROM_MAX_NUM_DATES 2
typedef struct rd_eeprom_req_s{
quint8 num_dates;
quint8 addr;
}rd_eeprom_req_t;

typedef struct rd_eeprom_ans_s{
quint8 num_dates;
quint8 addr;
quint16 data[EEPROM_MAX_NUM_DATES ];
}rd_eeprom_ans_t;

typedef struct wr_eeprom_req_s{
quint8 num_dates;
quint8 addr;
quint16 data[EEPROM_MAX_NUM_DATES ];
}wr_eeprom_req_t;
typedef struct wr_eeprom_ans_s{
quint8 num_dates;
quint8 addr;
}wr_eeprom_ans_t;

#endif