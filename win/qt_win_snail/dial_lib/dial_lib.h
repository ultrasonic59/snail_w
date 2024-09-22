#ifndef _DIAL_LIB_H_
#define _DIAL_LIB_H_

#include <QtWidgets/QtWidgets>
#include "PlotProperties.h"

#include "ui_dial_lib.h"
 #include "dev_interf.h"
#include "can_message.h"
#include "lib_paint_scene.h"
#include "snail_types.h"

namespace Ui {
    class Dial_lib;
}


class DialLib : public QDialog
{
Q_OBJECT

protected:
	Ui::Dial_lib ui;

public:
	DialLib(QWidget *parent= 0, PlotProperties* Plot_Prop = 0);
	virtual ~DialLib();
	QWidget* pParent;
	PlotProperties* pPlot_Prop;
	en_rej cur_rej;
	en_item_tipe cur_item;
signals:
///	void req_wr_dbg(int num,dbg_dat_req_t*);
///	void req_rd_dbg(int num,dbg_dat_req_t*);
	void SignalTest();
///	void req_send_can_dbg(can_message_t*);

private slots:
	void  on_butt_select();
	void  on_butt_place();
	void indexChanged(int index);
///	void  slot_send_can_msg();

///	void  slot_butt_rd();
///	void  slot_butt_wr();
///	void  req_dbg_data_rdy(dbg_dat_req_t*);
///	void  req_xil_data_rdy(xil_dat_req_t*);
///	void  req_str_rdy(char*);
	void  SlotTest();
public slots:
    void clear_textEdit();

private: 
///	en_rej cur_rej;
	void  show_rej();

///	dbg_dat_req_t  dbg_dat_req;
///	dbg_dat_req_t  dbg_dat;
///	xil_dat_req_t  xil_dat_req;
///	xil_dat_req_t  xil_dat;
///	can_message_t can_data;
private:
	LibPaintScene* scene;
	QTimer* timer;
	void resizeEvent(QResizeEvent* event);
private slots:
	void slotTimer();


};

#endif // DIAL_ED_PAR_H
