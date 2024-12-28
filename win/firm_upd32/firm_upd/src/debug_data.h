#ifndef __DEBUG_DATA_H__
#define __DEBUG_DATA_H__
#define MAX_ALT_DATA_LEN 4

struct dat_req_t
{
	quint32 addr;
	quint16 nbytes;
	quint16 data[MAX_ALT_DATA_LEN];
};

#endif