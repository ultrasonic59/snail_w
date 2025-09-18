////  #include "stm32f2xx.h"
 //// #include "stm32f2xx_conf.h"

#include <hdlc.h>
////#include <rtos.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
///#include <contr_akela_brd.h>

///==============================
void hdlc_error( char const *err )
{
////puts(err);
}
///==============================
void hdlc_init(hdlc_stat_t *p_hdlc)
{
p_hdlc->frame_in_pos  =0;	
p_hdlc->in_esc_byte		=0;	
///p_hdlc->frame_out_len	= 0;
p_hdlc->snd_buff_len= 0;
////p_hdlc->snd_buff1_len= 0;
///p_hdlc->snd_buff2_len= 0;
p_hdlc->in_buf = (uint8_t*)malloc( HDLC1_MAX_FRAME_DATA );
if( p_hdlc->in_buf == NULL ) 
	hdlc_error("hdlc_frames_init(): NO MEM\n");

p_hdlc->snd_buff	= (uint8_t*)malloc(HDLC1_MAX_FRAME_DATA);
if(p_hdlc->snd_buff == NULL )
	hdlc_error("hdlc1_init(): NO MEM FOR SND_BUF\n");
///p_hdlc->obr_buff	= (uint8_t*)malloc(HDLC1_MAX_FRAME_DATA);
////if( p_hdlc->obr_buff == NULL )
/////	hdlc_error("hdlc1_init(): NO MEM FOR OBR_TMPBUF\n");
#if 0	
p_hdlc->t_snd_buff1 = (uint8_t*)pvPortMalloc(HDLC1_MAX_FRAME_LEN);
if(p_hdlc->t_snd_buff1 == NULL)
	{
	hdlc1_error("hdlc1_init(): NO MEM FOR hdlc1_tbuff_send\n");
	return ;	
	}
memset(p_hdlc->t_snd_buff1,0,HDLC1_MAX_FRAME_LEN);	
#endif
#if 0
p_hdlc->t_snd_buff2 = (uint8_t NULL)
	{
	hdlc1_error("hdlc1_init(): NO MEM FOR hdlc1_tbuff_send\n");
	return ;	
	}
#endif

}
#if 0
///========================================================
uint8_t hdlc_send_iframe(hdlc_stat_t *p_hdlc,/*uint8_t *data, */int len)
{
////frame_t fr;
uint16_t len_o=0;
uint16_t ii;
uint8_t bt;
uint8_t rez=TRUE;
uint8_t *tbuf= (uint8_t*) malloc(len*4);
///================================
////memcpy(p_hdlc->snd_buff, data, len );
///p_hdlc->frame_out_len=len ;
addfcs16(p_hdlc->snd_buff,len);				// Добавить циклический код
///p_hdlc->frame_out_len += 2;

////p_hdlc->fn_send_byte(PPP_FRAME);
tbuf[len_o]= PPP_FRAME;
len_o++;
for(ii=0;ii<p_hdlc->frame_out_len;ii++)
	{
	bt = p_hdlc->snd_buff[ii];
	if( bt == PPP_FRAME || bt == PPP_ESCAPE )			// Замена "FLAG" или "ESC" на ESC-последовательность
		{
		///p_hdlc->fn_send_byte(PPP_ESCAPE);
                tbuf[len_o]= PPP_ESCAPE;
		len_o++;
		////p_hdlc->fn_send_byte((bt ^ PPP_ESCAPE_BIT));
                tbuf[len_o]= bt ^ PPP_ESCAPE_BIT;
		len_o++;
		}
	else
		{
		////p_hdlc->fn_send_byte(bt);
                tbuf[len_o]= bt;
		len_o++;
		}
		}
////p_hdlc->fn_send_byte(PPP_FRAME);
tbuf[len_o]= PPP_FRAME;

len_o++;
///put_tst1(0);

////rez = hdlc1_send_frame(send_byte_ua0,&snd_fr);
p_hdlc->fn_send_frame(tbuf,len_o);
free(tbuf );
return rez;
}

///==============================
int hdlc_parse_framein(hdlc_stat_t *p_hdlc)
{
int rez =0;
uint8_t btmp;
uint32_t wtmp=0;
///uint16_t h_rez;
uint8_t *in_buf=p_hdlc->obr_buff;
////uint16_t len=p_hdlc->len_obr_dat;
p_hdlc->frames_received++;
#if 1
switch(*in_buf)
	{
	case CMD_ACK:
		btmp = *(in_buf+1);
		xQueueSend(p_hdlc->ev_rsv_ack,&btmp,TIMEOUT_SEND);
///		rt_mq_send(p_hdlc->ev_rsv_ack,&btmp,sizeof(uint8_t));

		break;	
	case CMD_PUT_DAT:
		btmp = *(in_buf+1);
		p_hdlc->fn_set_rec_dat(btmp,(void *)((uint32_t)in_buf+2));
	///	xQueueSend(ev_rsv_dat,&btmp,TIMEOUT_SEND);
		wtmp=SEND_ACK;
		wtmp |= (btmp<<8);
///		xQueueSend(p_hdlc->ev_snd_frame,&wtmp,TIMEOUT_SEND);
	///	rt_mq_send(p_hdlc->ev_snd_frame,&wtmp,sizeof(uint32_t));
		hdlc_send_to(p_hdlc,wtmp&0xff,wtmp>>8,wtmp>>16);
		break;
#if 0
	case CMD_PUT_CMD:
		btmp = *(in_buf+1);
		h_rez=p_hdlc->fn_set_rec_dat(btmp,(void *)((uint32_t)in_buf+2));
	///	xQueueSend(ev_rsv_dat,&btmp,TIMEOUT_SEND);
		wtmp=SEND_REZ;
		wtmp |= (btmp<<8);
		wtmp |= (h_rez<<16);
 		xQueueSend(p_hdlc->ev_snd_frame,&wtmp,TIMEOUT_SEND);
		break;
#endif
	case CMD_PUT_REQ_DAT:
		btmp = *(in_buf+1);
		p_hdlc->fn_set_rec_dat(btmp,(void *)((uint32_t)in_buf+2));
        xQueueSend(p_hdlc->ev_rsv_dat,&btmp,TIMEOUT_SEND);
             ///  rt_mq_send(p_hdlc->ev_rsv_dat,&btmp,sizeof(uint8_t));

///		htmp=SEND_ACK;
///		htmp |= (btmp<<8);
///		xQueueSend(ev_snd_frame,&htmp,TIMEOUT_SEND);
		break;
	case CMD_REQ_DAT:
		btmp = *(in_buf+1);
		p_hdlc->offs_snd_buf = *(in_buf+2);
		p_hdlc->offs_snd_buf |= (*(in_buf+3))<<8;
		wtmp = SEND_REQ_DAT;
		wtmp |= (btmp<<8);
///		set_req_rez((req_rez_t *)((uint32_t)in_buf+1) );
///		xQueueSend(p_hdlc->ev_snd_frame,&wtmp,TIMEOUT_SEND);
///		rt_mq_send(p_hdlc->ev_snd_frame,&wtmp,sizeof(uint32_t));
        hdlc_send_to(p_hdlc,wtmp&0xff,wtmp>>8,wtmp>>16);

		rez =0;
////		printk("r");
		break;
	}
#endif
return rez;
}
///==================================
int hdlc_check_framein(hdlc_stat_t *p_hdlc)
{
int res = 1;
if(p_hdlc->len_obr_dat < 3 )
	{
////	p_hdlc->err_len++;
	res = -1;
	}
else if( !checkfcs16(p_hdlc->obr_buff, p_hdlc->len_obr_dat - 2 ) )
	{
////	p_hdlc->err_fcs++;
	res = -2;
	}
return res;
}
///=====================================
int	hdlc_send_ack_to(hdlc_stat_t *p_hdlc,uint8_t ipar)
{
int num_send=0;
uint8_t *p_tmp	 =p_hdlc->snd_buff;
*p_tmp++  = CMD_ACK;
num_send++;
*p_tmp++  = ipar;
num_send++;
return hdlc_send_iframe(p_hdlc,/*p_hdlc->snd_buff,*/ num_send);
////return 0;
}
int	hdlc_send_rez_to(hdlc_stat_t *p_hdlc,uint8_t ipar,uint16_t rez)
{
int num_send=0;
uint8_t *p_tmp	 =p_hdlc->snd_buff;
*p_tmp++  = CMD_REZ;
num_send++;
*p_tmp++  = ipar;
num_send++;
*p_tmp++  = rez&0xff;
num_send++;
*p_tmp++  = (rez>>8)&0xff;
num_send++;
return hdlc_send_iframe(p_hdlc,/*p_hdlc->snd_buff, */num_send);
////return 0;
}

///====== from uart isr ============================
int hdlc_on_bytein(hdlc_stat_t *p_hdlc, uint8_t in_bt )
{
p_hdlc->bytes_received++;
 set_tst3(1);

if( in_bt == PPP_FRAME )						// Пришел флаг
	{
	if(p_hdlc->frame_in_pos > 2 )				// Если между двумя флагами были данные:
		{
		memcpy(p_hdlc->obr_buff,p_hdlc->in_buf,p_hdlc->frame_in_pos);
		p_hdlc->len_obr_dat=p_hdlc->frame_in_pos;
		p_hdlc->frame_in_pos = 0;			
		p_hdlc->in_esc_byte	 = 0;
		return 1;
		}
	}
else
	{
	if(p_hdlc->frame_in_pos >= HDLC1_MAX_FRAME_DATA )
		{
////		hdlc1_error_frame_len(p_hdlc);
		printf("\n hdlc1_error_frame_len");
		p_hdlc->frame_in_pos=0; ///
		return -1;
		}
	if(p_hdlc->in_esc_byte )								// Второй байт ESC-последовательности
		{
		p_hdlc->in_buf[p_hdlc->frame_in_pos++] = in_bt ^ PPP_ESCAPE_BIT;
		p_hdlc->in_esc_byte = 0;
		}
	else
		{
		if( in_bt == PPP_ESCAPE)						// Первый байт ESC-последовательности
			{
			p_hdlc->in_esc_byte = TRUE;
			}
		else								// Обычный байт данных
			{
			p_hdlc->in_buf[p_hdlc->frame_in_pos++] = in_bt;	// Запись пришедшего байта в буфер
			}
		}
	return 0;	
	}
return 0;	
}
///==============================
////extern uint16_t pppfcs16(uint16_t fcs, unsigned char *cp, int len);
///====================================
void obr_hdlc_cmd(hdlc_stat_t *p_hdlc)
{

int res;
uint8_t ii;
set_tst1(0);
if((res= hdlc_check_framein(p_hdlc))>0 )	// Проверить правильность входящего кадра
	{
///==================================
	hdlc_parse_framein(p_hdlc);
	}
else
	{
	printf("\n\r error framein[%d][%02x]",res,p_hdlc->len_obr_dat);
	if(res==-2)
		{
        printf("\n\r[%02x]:",p_hdlc->len_obr_dat);
	for(ii=0;ii<p_hdlc->len_obr_dat;ii++)
		{
		printf("%02x ",p_hdlc->obr_buff[ii]);
		}
///	printf("%x\r\n ", 0xffff ^ pppfcs16( 0xffff, p_hdlc->obr_buff, p_hdlc->len_obr_dat-2));	// dbg!
	}
	;
	}
}

///====================================
void hdlc_obr_frame(void *pdata)
{
hdlc_stat_t *p_hdlc=(hdlc_stat_t *)pdata;
uint8_t res_byte;
printf("\n\r= hdlc1_obr_frame=  \n\r");
for(;;)
    {
    xQueueReceive(p_hdlc->ev_rsv_frame,&res_byte,portMAX_DELAY);
    obr_hdlc_cmd(p_hdlc);
    }

#if 0
for(;;)
	{
///  if (rt_mq_recv(p_hdlc->ev_rsv_frame, &res_byte, sizeof(uint8_t), RT_WAITING_FOREVER) == RT_EOK)
        if (rt_mq_recv(p_hdlc->ev_rsv_frame, &res_byte, sizeof(uint8_t), 1000) == RT_EOK)
   ///     if (rt_mq_recv(p_hdlc->ev_rsv_frame, &res_byte, sizeof(uint8_t), RT_WAITING_NO) == RT_EOK)
	     obr_hdlc_cmd(p_hdlc);
        else {
///            ;
          rt_thread_mdelay(1);
        }
	}
#endif
}

int	hdlc_send_to(hdlc_stat_t *p_hdlc,uint8_t type_send,uint8_t type_dat,uint16_t rez)
{
int res=0;
uint16_t len_dat;
int num_send=0;
uint8_t *p_tmp1;
uint8_t *p_tmp	 = p_hdlc->snd_buff;
if(type_send == SEND_REZ)
	{
	res=hdlc_send_rez_to(p_hdlc,type_dat,rez);
	}
else if(type_send == SEND_ACK)
	{
	res=hdlc_send_ack_to(p_hdlc,type_dat);
	}
else if(type_send == SEND_REQ_DAT)
	{
	*p_tmp++  = CMD_PUT_REQ_DAT;
	num_send++;
	*p_tmp++  = type_dat;
	num_send++;
	p_tmp1 = p_tmp+2;  
	len_dat = p_hdlc->fn_get_req_dat(type_dat,p_hdlc->offs_snd_buf, p_tmp1);
	*p_tmp++  = len_dat&0xff;
	num_send++;
	*p_tmp++  = (len_dat>>8)&0xff;
	num_send++;
	if(len_dat > HDLC1_MAX_FRAME_DATA)
		len_dat = HDLC1_MAX_FRAME_DATA;
	num_send += len_dat;
	res=hdlc_send_iframe(p_hdlc,/*p_hdlc->snd_buff, */num_send);
	}
else if(type_send == SEND_DAT)
	{
	num_send = p_hdlc->snd_buff_len;
	memcpy(p_tmp,p_hdlc->snd_buff,num_send);
	res=hdlc_send_iframe(p_hdlc,/*p_hdlc->snd_buff,*/ num_send);
	}
else if(type_send == SEND_REQ)
	{
	num_send = p_hdlc->snd_buff_len;
	memcpy(p_tmp,p_hdlc->snd_buff,num_send);
	res=hdlc_send_iframe(p_hdlc,/*p_hdlc->snd_buff,*/ num_send);
	}
return res;
}

void _hdlc_snd_task(void *pdata)
{
////t_frametx frame_tx;
uint32_t type_send;
hdlc_stat_t *p_hdlc=(hdlc_stat_t *)pdata;
///==================================
fprintf(stderr,"\n\r hdlc1_snd_task");
///==================================
for(;;)
  {
  if(xQueueReceive(p_hdlc->_ev_snd_frame,&type_send,portMAX_DELAY))
    hdlc_send_to(p_hdlc,type_send&0xff,type_send>>8,type_send>>16);
  }

///==================================
#if 0
for(;;)
  {
////  if(xQueueReceive(p_hdlc->ev_snd_frame,&type_send,portMAX_DELAY))
 ///   if (rt_mq_recv(p_hdlc->ev_rsv_frame, &res_byte, sizeof(uint8_t), RT_WAITING_FOREVER) == RT_EOK)
  ////      if (rt_mq_recv(p_hdlc->ev_snd_frame, &type_send, sizeof(uint32_t), RT_WAITING_FOREVER) == RT_EOK)
       if (rt_mq_recv(p_hdlc->ev_snd_frame, &type_send, sizeof(uint32_t), 1000) == RT_EOK)

   //// if (rt_mq_recv(p_hdlc->ev_snd_frame, &type_send, sizeof(uint32_t), RT_WAITING_NO) == RT_EOK)
           hdlc_send_to(p_hdlc,type_send&0xff,type_send>>8,type_send>>16);
    else {
        rt_thread_mdelay(10);
    }
  }
#endif
}
///====================================
#endif

