#ifndef __BT_CMD_H_
#define __BT_CMD_H_ 
///========================================
#include <stdint.h>
#define BT_CMD_PUT						0x3		/// 
#define BT_CMD_REQ						0x4		/// 

#define NUM_SET_CNGEN			0x1d		/// 
#define NUM_SET_CNUS			0x1e		/// 


#define BT_CMD_MIN_NUM			        0x2c	
#define GET_COORD				0x2c		
#define CLR_COORD				0x2d		

/*
#define BT_GET_OSC0				0x2c		

#define BT_PUT_PAR				0x32	
#define BT_GET_ALL_PAR				0x33	
#define BT_GET_ALL_PAR1			        0x34	
#define BT_GET_NUM_PARAMS			0x35	
#define BT_GET_NEXT_PARAM_NAME			0x36	
#define BT_SET_PARAM_NAME			0x37	
#define BT_SET_CURR_PAR_NUM			0x38	
*/
#define BT_CMD_MAX_NUM			        0x38	


#if 0
extern uint16_t bt_set_rec_param(void);
extern uint16_t bt_set_param_name(void);
extern uint16_t bt_get_all_par(void);
extern uint16_t bt_get_all_par1(void);
extern uint16_t bt_get_num_params(void);
extern uint16_t bt_get_next_param_name(void);
extern uint16_t bt_set_curr_par_num(void);
#endif

#endif///__BT_CMD_H_
