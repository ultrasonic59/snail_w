/*
 * tvd_dev.c
 *
 *  Created on: 2018Äê12ÔÂ1ÈÕ
 *      Author: VeiLiang
 */
 
#include <stdio.h>
#include "irq_misc.h"
#include "tvd.h"
#include "io.h"
extern void tvd_irq_enable(unsigned int id,tvd_irq_t irq);

static int tvd_id = 0;
unsigned char tvd_y_buf[DEF_TWD_W*DEF_TWD_H]; 
unsigned char tvd_c_buf[DEF_TWD_W*DEF_TWD_H];

unsigned char tvd_y_buf_disp[DEF_TWD_W*DEF_TWD_H];
unsigned char tvd_c_buf_disp[DEF_TWD_W*DEF_TWD_H];
////extern void RefleshLcdWithTVD(unsigned char *ydat,unsigned char * cbcr,int w,int h);
int tcountt = 0;

////void tvd_irq_handle(int arg)
void tvd_irq_handle(void)
{
printf("tvd irq\n");

//	TVD_Printf("%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n",
//			tvd_y_buf[0],tvd_y_buf[1],tvd_y_buf[2],tvd_y_buf[3],
//			tvd_y_buf[4],tvd_y_buf[5],tvd_y_buf[6],tvd_y_buf[7]);
//	TVD_Printf("%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n",
//				tvd_y_buf[1000],tvd_y_buf[1001],tvd_y_buf[1002],tvd_y_buf[1003],
//				tvd_y_buf[1004],tvd_y_buf[1005],tvd_y_buf[1006],tvd_y_buf[1007]);
	//tcountt ++;
////????	
#if 1	
////	memcpy(tvd_y_buf_disp,tvd_y_buf,DEF_TWD_W*DEF_TWD_H);
/////	memcpy(tvd_c_buf_disp,tvd_c_buf,DEF_TWD_W*DEF_TWD_H);
	tvd_irq_status_clear(tvd_id,TVD_FRAME_DONE);
////	f1c100s_intc_clear_pend();
#endif
	// dma_cache_sync(tvd_y_buf,720*576,3);
	// dma_cache_sync(tvd_c_buf,720*576,3);
/////	RefleshLcdWithTVD(tvd_y_buf_disp,tvd_c_buf_disp,DEF_TWD_W,DEF_TWD_H);
}


void _tv_in_decode_init(int id)
{
////	int		   	retval  = 0;
	tvd_id = id;
	/////retval = request_irq(IRQ_TVD, tvd_irq_handle,0);//first requet irq
  f1c100s_intc_set_isr(IRQ_TVD, tvd_irq_handle);
  f1c100s_intc_enable_irq(IRQ_TVD);
	
	printf("request_irq \n");

	tvd_bsp_init(0);//bsp init like open clk ,reset ...
	TVD_Printf("tvd_bsp_init \n");
	tvd_config(TVD_SOURCE_CVBS,TVD_SOURCE_PAL,TVD_PL_YUV420);
	TVD_Printf("tvd_config \n");

	tvd_set_fmt(id,TVD_PL_YUV420);
	TVD_Printf("tvd_set_fmt \n");
	tvd_set_addr_y(id,tvd_y_buf);
	tvd_set_addr_c(id,tvd_c_buf);
	tvd_set_blue_flag(0);
	//Enable irq
	tvd_irq_status_clear(id,TVD_FRAME_DONE);
	TVD_Printf("tvd_irq_status_clear \n");

	tvd_irq_enable(id,TVD_FRAME_DONE);
	TVD_Printf("tvd_irq_enable \n");
	
	tvd_capture_on(id);
	TVD_Printf("tvd_capture_on \n");



}

