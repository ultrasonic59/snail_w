#ifndef _CSV_DLG_H___
#define _CSV_DLG_H___

#include <QtWidgets/QtWidgets>
#include <QObject>
#include <QFile>
#include <QList>

#include "ui_csv_dlg.h"

#define CSV_NUM_COL 7

namespace Ui {
    class csv_dlg;
}

class csv_dlg : public QDialog
{
	Q_OBJECT

protected:
	Ui::csv_dlg ui;

public:
	csv_dlg(QWidget* parent = 0);
	virtual ~csv_dlg();
	QWidget* pParent;
/*
signals:
	void req_wr_dbg(int num, dbg_dat_req_t*);
	void req_rd_dbg(int num, dbg_dat_req_t*);
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
	*/
private:
	QStandardItemModel* csvModel;

private slots:
	void SlotOpenFile();

};

#endif ///_CSV_DLG_H__