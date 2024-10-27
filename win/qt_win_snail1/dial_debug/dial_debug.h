#ifndef _DIAL_DEBUG_H_
#define _DIAL_DEBUG_H_

#include <QtWidgets/QtWidgets>

#include "ui_dial_debug.h"
 #include "dev_interf.h"
#include "can_message.h"

namespace Ui {
    class Dial_debug;
}

#define HID_REJ		0
#define CAN_REJ	    1
///#define LIN_REJ		2

class DialDebug : public QDialog
{
Q_OBJECT

protected:
	Ui::Dial_debug ui;

public:
	DialDebug(QWidget *parent= 0);
	virtual ~DialDebug();
	QWidget* pParent;
signals:
	void req_wr_dbg(int num,dbg_dat_req_t*);
	void req_rd_dbg(int num,dbg_dat_req_t*);
	void SignalTest();
	void req_send_can_dbg(can_message_t*);

private slots:
	void  slot_send_can_msg();

	void  slot_butt_rd();
	void  slot_butt_wr();
	void  req_dbg_data_rdy(dbg_dat_req_t*);
	void  req_xil_data_rdy(xil_dat_req_t*);
	void  req_str_rdy(char*);
	void  SlotTest();
public slots:
    void clear_textEdit();

private: 
	dbg_dat_req_t  dbg_dat_req;
	dbg_dat_req_t  dbg_dat;
	xil_dat_req_t  xil_dat_req;
	xil_dat_req_t  xil_dat;
	can_message_t can_data;
};

#endif // DIAL_ED_PAR_H
