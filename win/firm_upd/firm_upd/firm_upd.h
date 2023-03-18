#ifndef __FIRM_UPD_H__
#define __FIRM_UPD_H__

#include <QMainWindow>
#include "ui_firm_upd.h"

#include <QFile>
#include "COMPort.h"
#include "ProgHex.h"
////#include "QFileDialogCust.h"

#define AxisX  0
#define AxisY  1
#define AxisZ  2

class Cfirm_upd : public QMainWindow
{
	Q_OBJECT

protected:
	Ui::firm_upd ui;
	QString CurFilePath;
////	QString DeviceWriteDir;
    void saveSettings();
    void loadSettings();
public:
////	QString CurrDirectory;
	QFile curFile;		// 
	COMPortProperites COMpr;
protected:
	COMPort com_port;
	qint8 CurAxis;
	CProgHex prog_hex;
///	QString COM_port_name;

public:
	Cfirm_upd(QWidget *parent = 0);
	virtual ~Cfirm_upd();

public slots:
    void refresh_used_ports();
    void connection();
	void on_file_path();
	void progr_flash();

};
///===========================================
#endif /// __FIRM_UPD_H__
