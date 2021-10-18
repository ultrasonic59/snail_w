#ifndef _DRV_BT_H_
#define _DRV_BT_H_
/// #include <rtdevice.h>

#define MAX_LEN_STR_BT 	        32
#define TIME_WAIT_BT	        1000
#define BT_CMD_DELAY	        1000

#if 0
#ifndef RT_DEVICE_CTRL_GET_RE
#define RT_DEVICE_CTRL_GET_RE						0x13
#endif
#define RT_DEVICE_CTRL_CONFIG           0x03    /* configure device */

#define RT_DEVICE_GET_LEN						0x14
#endif

#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_14400			14400// 1 14400 bps
#define BAUD_RATE_19200	                19200
#define BAUD_RATE_28800	                28800
#define BAUD_RATE_38400	                38400
#define BAUD_RATE_56000	                56000
#define BAUD_RATE_57600	                57600
#define BAUD_RATE_115200	        115200
#define BAUD_RATE_128000 	        128000
#define BAUD_RATE_256000	        256000

#define  DEF_BT_BR BAUD_RATE_115200	///BT_DIV_BR_57600 ///BT_DIV_BR_115200	///

#define MAX_LEN_BT_BUFF	2048
#define BT_TIME_PAUSE   5

extern void on_pow_bt(unsigned char on_off);
extern void reset_bt(void);
extern void init_bt(void);

////extern  rt_device_t uart4_id;

#define bt_id uart4_id

typedef struct bt_head_s
{
uint8_t cmd;
uint8_t rsv;
uint16_t size;	
}bt_head_t;


#endif

