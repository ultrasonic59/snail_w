#ifndef __FIRM_UPD_H__
#define __FIRM_UPD_H__

#include <QMainWindow>
#include "dial_debug.h"

#include <QFile>
///#include <QtSerialPort/QSerialPort>
///#include <QtSerialPort/QSerialPortInfo>

////#include <QSerialPort>
////#include <QSerialPortInfo>
#include <QFileDialog>
#include <QtCore>
#include <QFile>

#include <QThread>

#include "progHex.h"
////#include "QFileDialogCust.h"

#define AxisX  0
#define AxisY  1
#define AxisZ  2

namespace Ui {
class firm_upd;
}

class Cfirm_upd : public QMainWindow
{
	Q_OBJECT

protected:
	Ui::firm_upd *ui;
	QString CurFilePath;
	QString _COM_port_name;
    void saveSettings();
    void loadSettings();
	bool connected;
public:
	bool data_ok;
	can_cmd_t  odat;
	quint8 curr_dev_state;
	qint32 cur_pb_val;
	quint8 answ;
	bool is_connected();
	void set_connected(bool con);
////	QString CurrDirectory;
	QFile *curFile;		// 
////	COMPortProperites COMpr;
protected:
	bool get_curr_state();
////	quint8 curr_dev_state;
////	COMPort com_port;
////    QSerialPort* port;
	qint8 CurAxis;
///	CprogHex prog_hex;
///	QString COM_port_name;
   bool messageFinished;
   QString message;
   DialDebug dial_dbg;

private:
   QThread *m_pThread;
   CprogHex *m_pProgHex;
   void show_connect(bool conn);

public:
	Cfirm_upd(QWidget *parent = 0);
	virtual ~Cfirm_upd();

public slots:
    void refresh_used_ports();
    void connection();
	void on_file_path();
	void progr_flash();
	void set_pb_val(quint32 val);
	void setBootMode();
	void ver_flash();
	void init_prg();

signals:
    void hardwareResponseFinished();
	void s_connect(bool);
	void s_set_com_name(QString);
	void s_set_can_id(QString);
	void s_SetBootMode();
	void s_progr(QFile*);
	void s_init(QFile*);

	void s_req_curr_state();
	void s_rd_eeprom(dat_req_t*);
	void s_wr_eeprom(dat_req_t*);
	void s_rd_flash(dat_req_t*);
	void s_verif(QFile*);

private slots:
	void on_butt_debug();
	void slot_rd_eeprom_dat(dat_req_t* odat);
	void slot_wr_eeprom_dat(dat_req_t* idat);
	void slot_rd_flash_dat(dat_req_t* odat);

};
///===========================================
#endif /// __FIRM_UPD_H__
