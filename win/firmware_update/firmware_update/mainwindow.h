#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QCamera>
#include <QCameraImageCapture>
#include <QFile>
#include "COMPort.h"
#include "QFileDialogCust.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

protected:
	Ui::MainWindow ui;
///	QString CurrDirectory;
	QString UploadFilePath;
	QString DeviceWriteDir;


///    QCamera *camera;

////	void setCamera(const QByteArray &cameraDevice);
public:
	QString CurrDirectory;
	QFile in_out_file;		// 
	COMPortProperites COMpr;
protected:
	COMPort com_port;
///	QString COM_port_name;

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

public slots:
    void refresh_used_ports();
    void connection();
	void on_file_path();



};

#endif // MAINWINDOW_H
