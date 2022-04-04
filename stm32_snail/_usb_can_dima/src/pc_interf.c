#include <stdint.h>

///=================================================
uint16_t pc_get_req_dat(uint8_t num_req,uint16_t offs,uint8_t *buf)
{
uint16_t rez=0;
return rez;
}

int pc_set_rec_dat(uint8_t cmd,void *in_buf)
{
int rez=0;
#if 0
uint16_t n_bytes;
u16 num_bytes;
u8 *bbuf=(u8*)in_buf;
//// ====================================
////printk("\n\r pc_set_rec_dat[%x]",cmd);
///=================================
////return 0;
switch(cmd)
	{
	case NUM_SET_CNGEN:		/// 
////		curr_par_trk.dop_par.curr_gen = *((u8*)(in_buf)+2);
		break;	
	case NUM_SET_CNUS:			/// 
		curr_par_trk.dop_par.curr_us = *((u8*)(in_buf)+2);
		break;	
 	}
#endif        
return rez;
}
