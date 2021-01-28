#include <stdint.h>
#include <string.h>

#include "_hdlc.h"
#include "board.h"
#include "bt_cmd.h"
#include "printk.h"

///=================================================
int pc_set_rec_dat(uint8_t cmd,void *in_buf)
{
///uint16_t n_bytes;
///uint16_t num_bytes;
////uint8_t *bbuf=(u8*)in_buf;
int rez=0;
//// ====================================
/// _printk("\n\r pc_set_rec_dat[%x]",cmd);
///=================================
////return 0;
switch(cmd)
	{
	case NUM_SET_CNGEN:		/// 
////		curr_par_trk.dop_par.curr_gen = *((u8*)(in_buf)+2);
		break;	
	case NUM_SET_CNUS:			/// 
////		curr_par_trk.dop_par.curr_us = *((u8*)(in_buf)+2);
		break;	
 	}
return rez;
}
///=====================================================
uint16_t	pc_get_req_dat(u8 num_req,u16 offs,u8 *buf)
{
uint16_t rez=0;
#if 0
//// ====================================
if((num_req!= 0x2c)&&(num_req!= 0x2d)&&(num_req!= 0x2e))
{
  _printk("\n\r pc_get_req_dat[%x]",num_req);
}
///=================================
#endif
/////_printk("<");
#if 1
switch(num_req)
	{
	case GET_COORD:
                memcpy(buf,(const void*)&cur_dp_dat,sizeof(dp_dat_t));
		rez=sizeof(dp_dat_t);
		break;
	case CLR_COORD:
                memset(&cur_dp_dat,0,sizeof(dp_dat_t));
                clr_all_dp();
		rez=1;
		break;
	default:
          printk("z[%x]!",num_req);
          rez=0;
          break;
                
	}
#endif
return rez;
}
