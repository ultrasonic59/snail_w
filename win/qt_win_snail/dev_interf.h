#ifndef _DEV_INTERF_H_
#define _DEV_INTERF_H_
 ///#include "params.h"
///#include "cmd_flags.h"
///#include "contr_par.h"

///=====================================================
#define MAX_XIL_DATA_LEN		4
#define MAX_DBG_DATA_LEN		2
////#define	LEN_OSC					256
////#define NUM_PORTS_CON  			2

#define MAX_AMPL_BUFF_LEN		32  ////16

#define BASE_REPOST_SIZE            3
#define TIME_UNIT		0.025f
///=================================================
struct xil_dat_req_t
{
	quint16 addr;
	quint16 nbytes;
	quint16 data[MAX_XIL_DATA_LEN];
};
struct dbg_dat_req_t
{
	quint32 addr;
	quint32 nbytes;
	quint32 data[MAX_DBG_DATA_LEN];
};


struct cpu_dat_req_t
{
	quint32 addr;
	quint32 nbytes;
	quint32 *data;///[MAX_SPI_ADC_LEN];
};


///#pragma pack (push, 1)
#pragma pack (push, 1)
struct amp_strob_struct_t
{
	quint16 time;
	quint8 ampl;
};
#pragma pack (pop)


#endif