#ifndef __HDLC_H_
#define __HDLC_H_ 

#include <my_types.h>
////#include <rtos.h>
#include <stdint.h>

//=====================

#ifndef TRUE 
#define	TRUE 0x1
#endif
#ifndef FALSE
#define	FALSE 0
#endif

#ifndef NULL
#define NULL 0                   
#endif
//=====================


///========================================
#define PPP_FRAME	0x7E
#define PPP_ESCAPE	0x7D
#define PPP_ESCAPE_BIT	0x20
///========== put to goat_cpu ====================

#define CMD_PUT_DAT  			0x3	
#define CMD_REQ_DAT  			0x4	
#define CMD_PUT_REQ_DAT  	        0x5	
#define CMD_PUT_CMD  			0x6	


///========== get from dev ====================
///#define CMD_GET_DAT  			0x84	
#define CMD_ACK  					0x85
#define CMD_REZ  					0x86
///===================================
#define SEND_DAT			(0x1<<0)
#define SEND_ACK			(0x1<<1)
#define SEND_REQ_DAT		(0x1<<2)
#define SEND_REQ			(0x1<<3)
#define SEND_REZ			(0x1<<4)


#define HDLC1_MAX_FRAME_DATA	128  ///128     ///256  ////1024	//	8192				/// 0x2000 Макс. длина I-поля кадра
///#define HDLC1_MASK_FRAME_DATA	HDLC1_MAX_FRAME_DATA-1	/// 0x1fff
////#define HDLC1_MAX_FRAME_LEN	HDLC1_MAX_FRAME_DATA         ////   (HDLC1_MAX_FRAME_DATA+2)// Макс. длина кадра (C+I+FCS)

///========================================
#define TIMEOUT_ACK	100
#define TIMEOUT_SEND	10
#define TIMEOUT_RSV	500
///========================================

///==================================
typedef struct hdlc_stat_s_
{
uint16_t	frame_in_pos  ;				// Позиция для записи следующего принятого байта
uint8_t 	*in_buf;				// Буфер принимаемого в данный момент кадра
////uint8_t 	*obr_buff;				//
///uint16_t len_obr_dat;
uint8_t  in_esc_byte;				// Флаг принятия ESC-байта 
uint8_t 	*snd_buff;				// 
uint16_t	snd_buff_len;

////uint16_t	frame_out_len;
////uint16_t	offs_snd_buf;

///QueueHandle_t ev_rsv_ack;
////QueueHandle_t ev_rsv_dat;
////QueueHandle_t ev_rsv_frame;
////QueueHandle_t _ev_snd_frame;

u8_fn_pu8_u16 fn_send_frame;

/////int_fn_u8_pvoid fn_set_rec_dat;
////u16_fn_u8_u16_pu8 fn_get_req_dat;

///extern u16 hdlc1_get_req_dat(u8 num_req,u8 *buf);

////int bytes_sent;
////	int bytes_received;
///	int bytes_over_received;
///	int	frames_sent;
/////	int	frames_received;
}hdlc_stat_t;
///================================
extern uint8_t checkfcs16(uint8_t *cp, uint16_t len );
extern void addfcs16( uint8_t *cp, uint16_t len );

extern void hdlc_init(hdlc_stat_t *p_hdlc);
										
extern int hdlc_on_bytein(hdlc_stat_t *p_hdlc, uint8_t in_bt );
extern uint8_t hdlc_send_dat(hdlc_stat_t *p_hdlc, uint8_t icmd, uint8_t *idat, uint16_t len);
extern void obr_hdlc_cmd(hdlc_stat_t *p_hdlc);
extern void hdlc_obr_frame(void *pdata);
extern int hdlc_send_to(hdlc_stat_t *p_hdlc,uint8_t type_send,uint8_t type_dat,uint16_t rez);

///extern void hdlc_snd_task(void *pdata);

#endif ////__HDLC_H_
