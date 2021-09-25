#include "mainwindow.h"
#include <QMediaService>

MainWindow::MainWindow(QWidget *parent) : 
		QMainWindow(parent),
		ui(),
		camera(nullptr)
{
	ui.setupUi(this);

	QByteArray cameraDevice;


	foreach(const QByteArray &deviceName, QCamera::availableDevices())
	{
        QString description = camera->deviceDescription(deviceName);

		if(cameraDevice.isEmpty() && !deviceName.isEmpty())
			cameraDevice = deviceName;
	}

	setCamera(cameraDevice);
}

MainWindow::~MainWindow()
{
    delete camera;
}



void MainWindow::setCamera(const QByteArray &cameraDevice)
{
    delete camera;

    if (cameraDevice.isEmpty())
        camera = new QCamera;
    else
        camera = new QCamera(cameraDevice);

    camera->setViewfinder(ui.viewfinder);

    camera->start();
}
