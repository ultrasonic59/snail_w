////  #include "stm32f2xx.h"
 //// #include "stm32f2xx_conf.h"

#include <hdlc.h>
////#include <rtos.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "printk.h"

hdlc_stat_t g_hdlc;

///==============================
void hdlc_init(hdlc_stat_t *p_hdlc)
{
p_hdlc->frame_in_pos  =0;	
p_hdlc->in_esc_byte		=0;	
p_hdlc->snd_buff_len= 0;
p_hdlc->in_buff = (uint8_t*)malloc( HDLC1_MAX_FRAME_DATA );
if( p_hdlc->in_buff == NULL ) 
	printk("hdlc_frames_init(): NO MEM\n");
p_hdlc->snd_buff	= (uint8_t*)malloc(HDLC1_MAX_FRAME_DATA);
if(p_hdlc->snd_buff == NULL )
	printk("hdlc1_init(): NO MEM FOR SND_BUF\n");
p_hdlc->obr_buff	= (uint8_t*)malloc(HDLC1_MAX_FRAME_DATA);
if( p_hdlc->obr_buff == NULL )
	printk("hdlc1_init(): NO MEM FOR OBR_TMPBUF\n");
p_hdlc->fn_send_frame=uart_send_buff;
}
uint8_t hdlc_send_frame(uint8_t *data, uint8_t len)
{
////frame_t fr;
uint16_t len_o=0;
uint16_t ii;
uint8_t bt;
///uint8_t rez=TRUE;
uint8_t *tbuff= (uint8_t*) malloc(len+8);
///================================
memcpy(tbuff, data, len );
///p_hdlc->frame_out_len=len ;
addfcs16(tbuff,len);             // Добавить циклический код
///p_hdlc->frame_out_len += 2;
g_hdlc.snd_buff[len_o]= PPP_FRAME;
////p_hdlc->fn_send_byte(PPP_FRAME);
len_o++;
for(ii=0;ii<len+2;ii++)
    {
    bt = tbuff[ii];
    if( bt == PPP_FRAME || bt == PPP_ESCAPE )           // Замена "FLAG" или "ESC" на ESC-последовательность
        {
        g_hdlc.snd_buff[len_o]= PPP_ESCAPE;
        len_o++;
        g_hdlc.snd_buff[len_o]= bt ^ PPP_ESCAPE_BIT;
        len_o++;
        }
    else
        {
        g_hdlc.snd_buff[len_o]= bt;
        len_o++;
        }
      }
g_hdlc.snd_buff[len_o]= PPP_FRAME;

len_o++;
g_hdlc.snd_buff_len=len_o;
g_hdlc.fn_send_frame(g_hdlc.snd_buff,len_o);
free(tbuff );
return len_o;
}
int hdlc_on_bytein( uint8_t in_bt )
{
///p_hdlc->bytes_received++;
/// set_tst3(1);
////        printk("[%x]",in_bt);
///uint8_t ii;
if( in_bt == PPP_FRAME )                        // Пришел флаг
    {
    if(g_hdlc.frame_in_pos > 2 )               // Если между двумя флагами были данные:
        {
///        memcpy(g_hdlc.obr_buff,g_hdlc.in_buff,g_hdlc.frame_in_pos);
        memcpy(&resiv_enc,g_hdlc.in_buff,sizeof(send_data_t));
  
        g_hdlc.len_obr_dat=g_hdlc.frame_in_pos;
        g_hdlc.frame_in_pos = 0;
        g_hdlc.in_esc_byte  = 0;
        return 1;
        }
    }
else
    {
    if(g_hdlc.frame_in_pos >= HDLC1_MAX_FRAME_DATA )
        {
////        hdlc1_error_frame_len(p_hdlc);
        printk("\n hdlc1_error_frame_len");
        g_hdlc.frame_in_pos=0; ///
        return -1;
        }
    if(g_hdlc.in_esc_byte )                                // Второй байт ESC-последовательности
        {
        g_hdlc.in_buff[g_hdlc.frame_in_pos++] = in_bt ^ PPP_ESCAPE_BIT;
        g_hdlc.in_esc_byte = 0;
        }
    else
        {
        if( in_bt == PPP_ESCAPE)                        // Первый байт ESC-последовательности
            {
            g_hdlc.in_esc_byte = TRUE;
            }
        else                                // Обычный байт данных
            {
             g_hdlc.in_buff[g_hdlc.frame_in_pos] = in_bt; // Запись пришедшего байта в буфер
////            printk("[%x:%x:%x]", g_hdlc.in_buff[g_hdlc.frame_in_pos],in_bt,g_hdlc.frame_in_pos);
            g_hdlc.frame_in_pos++;
            }
        }
    return 0;
    }
return 0;
}
///==============================
