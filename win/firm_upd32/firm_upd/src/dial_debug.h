#ifndef _DIAL_DEBUG_H_
#define _DIAL_DEBUG_H_

#include <QCloseEvent>
#include <QDialog>
//#include <QtWidgets/QtWidgets>

#include "ui_dial_debug.h"
#include "debug_data.h"

namespace Ui {
    class Dial_debug;
}

#define EEPROM_REJ		0
#define FLASH_REJ		1

class DialDebug : public QDialog
{
Q_OBJECT

protected:
	Ui::Dial_debug ui;
	virtual void closeEvent( QCloseEvent * event );

public:

	DialDebug(QWidget *parent= 0);
	virtual ~DialDebug();
	void req_data_rdy(dat_req_t*);
	void setMinMaxValues(QString &text);
signals:
	void req_rd_eeprom(dat_req_t*);
	void req_wr_eeprom(dat_req_t*);
	void req_rd_flash(dat_req_t*);

private slots:
	void  on_butt_rd();
	void  on_butt_wr();
public slots:
	void clear_textEdit();
private: 
	dat_req_t  dat_req;
	dat_req_t  dat;
};

#endif // DIAL_ED_PAR_H
