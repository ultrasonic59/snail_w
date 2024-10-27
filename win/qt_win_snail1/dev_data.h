#ifndef _DEV_DATA_H_
#define _DEV_DATA_H_

#include <QTimer>
#include <QObject>
#include <QVector>

#include "dev_interf.h"
#include "hybriddata.h"
#include "RingBuffer.h"
#include "ScaningData.h"
#include "Params.h"
#include "qwin_otter_conf.h"

////#include "FrameShiftArray.h"
////#include "result_data.h"
#define MAX_EL_COUNT 100000

#ifndef MAX_FRAME_LEN
#define MAX_FRAME_LEN			60000
#endif

#define MAX_COORD_MM            5000     // 5m
#define DELT_ALPHA              6     // 6 gr
#define NUM_TIC_OB              (360/DELT_ALPHA)
#define NUM_MM_OB                5   ///5mm/ob

#define MAX_COORD_TIC           (MAX_COORD_MM*NUM_TIC_OB/NUM_MM_OB)       
#define MAX_POS					MAX_COORD_TIC

////#define INIT_BUFF_SIZE 1536     ////1024
////#define DELTA_BUFF_SIZE 64

#define NUM_SLOY	3

#define DEF_FLG			(0x1<<0)
#define VN_DEF_FLG		(0x1<<1)
#define NAR_DEF_FLG		(0x1<<2)
#define PO_DEF_FLG		(0x1<<3)
#define PR_DEF_FLG	    (0x1<<4)
#define RL_DEF_FLG		(0x1<<5)
#define NO_AK_FLG		(0x1<<6)
#define ERR_FLG			(0x1<<7)

#define ANY_DEF_FLG		(VN_DEF_FLG|NAR_DEF_FLG|PR_DEF_FLG|PO_DEF_FLG|RL_DEF_FLG)

struct one_def_dat_t
{
quint8 chan;
quint8 type_def;   ///vn,nar,rassl
quint16 coord_x;
quint16 coord_y;
float db_val;
};

struct one_chan_dat_t
{
bool filled;
rez_amp_us_t amp_us;
////amp_strob_struct_t strb_dat[NUM_REZ_STRBS];
};

struct def_t
{
bool filled;
quint8 flgs[NUM_SLOY];
float db_val[NUM_SLOY];
};
struct xy_coord_t
{
quint16 xx;
quint16 yy;
};

struct chan_dat_t
{
one_chan_dat_t ch_dat[NUM_CHANS];
};

class c_data_array
{
public:
	c_data_array(par_session_t *curr_par_session);
	~c_data_array();
public:
	quint32 get_last_coord()
		{
		return last_coord;
		}
	void set_last_coord(quint32 coord)
		{
		last_coord=coord;
	///	if(last_coord>_max_coord)
	///		_max_coord=last_coord;
		}
	void clr_coord(void)
		{
		last_coord=0;
	///	_max_coord=0;
		}
	par_session_t *p_curr_par_session;
	quint32 get_beg_coord();
	void set_beg_coord(quint32 coord);
	one_chan_dat_t get_chan_data(quint8 num_ch,quint32 pos);
	chan_dat_t get_data(quint32 pos);
////	quint32 min_offs_coord;
////	quint32 max_offs_coord;

	quint16 getSize();
	void _SetSize(quint16 size);
	bool put_chan_data(quint8 num_ch,qint32 pos,one_chan_dat_t tdat, qint32 curr_cord);
	bool put_data(qint32 pos,chan_dat_t tdat);
////	bool check_defect();
	defect_count_t defects;
	void add_def_cnt(def_t def_flg);

	void reset_all_dat();
	def_t get_deftype(quint32 pos);
	def_t get_def_coord(quint32 pos,quint16 offs_y=0,quint8 on_view_chans=0xff);
	def_t get_def_coord_xy(quint16 pos_x,quint16 pos_y=0,quint8 on_view_chans=0xff);
	xy_coord_t get_xy_coord(quint16 pos);
	void set_ena_put_dat(bool on_off);

protected:
////	chan_dat_t *chan_dat;
	quint32 last_coord;
///	quint32 _max_coord;
	quint32 beg_coord;
	void clear_one_dat(quint32 pos);
	void add_dat(quint8 num_ch,quint32 pos,one_chan_dat_t tdat);
	def_t add_def(def_t old_rez,def_t new_rez);
	def_t get_def_chan(quint32 pos,quint8 chan);
	def_t get_pr_def(quint32 pos,quint8 num_chan);
	def_t get_po_def(quint32 pos,quint8 num_chan);
	def_t get_rl_def(quint32 pos,quint8 num_chan);

	QVector<chan_dat_t> chan_data;
////	quint32 _curr_len_data;
	quint32 curr_size;
	bool ena_put_dat;
};

class c_dev_data : public QObject
{

Q_OBJECT
public:
	c_dev_data();
	~c_dev_data();
///protected:
///	par_session_t *p_curr_par_session;
public:
	par_session_t curr_par_session;
	quint32 max_offs_coord;

public:
	osc_struct_t osc_data;
	cScaningData scaning_data;
	c_data_array data_array;
	amp_stat_buff_t buff_struct;
	void SetInitialProbeOffsets();
	void SetDefaultSessionPar();
	void SetDefChanalsRej();
	void ReApplyChanalsRej();
	void CalcMaxProbeOffs();
	quint8 GetOnChans();
	quint16 GetOffsChan(quint8 ch);

	////quint8 get_num_chan_strb(quint8 view_ch, quint8 &num_strb,quint8 &type_chan);

public:
	quint16 calc_endr(quint16 beg_r, quint8 step);

};

#endif ///_DEV_DATA_H_