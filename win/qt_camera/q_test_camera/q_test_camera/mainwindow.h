#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QCamera>
#include <QCameraImageCapture>


class MainWindow : public QMainWindow
{
	Q_OBJECT

protected:
	Ui::MainWindow ui;


    QCamera *camera;

	void setCamera(const QByteArray &cameraDevice);


public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();




};

#endif // MAINWINDOW_H
