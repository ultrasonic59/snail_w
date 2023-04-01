#ifndef __FIRM_UPD_H__
#define __FIRM_UPD_H__

#include <QMainWindow>
////#include "ui_firm_upd.h"

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
public:
////	QString CurrDirectory;
	QFile *curFile;		// 
////	COMPortProperites COMpr;
protected:
////	COMPort com_port;
////    QSerialPort* port;
	qint8 CurAxis;
///	CprogHex prog_hex;
///	QString COM_port_name;
   bool messageFinished;
   QString message;
private:
   QThread *m_pThread;
   CprogHex *m_pProg_hex;

public:
	Cfirm_upd(QWidget *parent = 0);
	virtual ~Cfirm_upd();

public slots:
    void refresh_used_ports();
    void connection();
	void on_file_path();
	void progr_flash();
	void set_pb_val(quint32 val);
public slots:
 ////   void openFileDialog();
 ////   void program();
    void serialDataReceived();
    void serialError();
    void serialReady();

signals:
    void hardwareResponseFinished();

};
///===========================================
#endif /// __FIRM_UPD_H__
