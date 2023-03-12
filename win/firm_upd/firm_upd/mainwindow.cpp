#include "mainwindow.h"
#include <QMediaService>
#include <QtSerialPort/QSerialPortInfo>
#include "dialog_write_file.h"

MainWindow::MainWindow(QWidget *parent) : 
		QMainWindow(parent),
		COMpr(),
		ui(),com_port(this, &COMpr)		
{
	ui.setupUi(this);
#if 0
	QByteArray cameraDevice;


	foreach(const QByteArray &deviceName, QCamera::availableDevices())
	{
        QString description = camera->deviceDescription(deviceName);

		if(cameraDevice.isEmpty() && !deviceName.isEmpty())
			cameraDevice = deviceName;
	}

	setCamera(cameraDevice);
#endif
	connect(ui.pushButton_refresh, SIGNAL(clicked()), this, SLOT(refresh_used_ports()));
	connect(ui.pushButton_Conn, SIGNAL(clicked()), this, SLOT(connection()));
    connect(ui.pushButt_file, SIGNAL(clicked()), this, SLOT(on_file_path()));

}

MainWindow::~MainWindow()
{
 ///   delete camera;
}



void MainWindow::refresh_used_ports()
{
	ui.comboBox_ports->clear();
#if 1
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		if(info.description() != "")
		{
			ui.comboBox_ports->addItem(info.portName());
////			if(device_CMD.COM_port_name == info.portName())
////				ui.comboBox_ports->setCurrentIndex( ui.comboBox_ports->count() - 1 );		// переключаем на выбранный порт
		}
	}

////	ui.pushButton_start_stop->setEnabled(ui.comboBox_ports->count() > 0);
#endif
}
void MainWindow::connection()
{
	if(com_port.IsConnected())
		{
		ui.pushButton_Conn->setText(tr("Connect"));
		com_port.SetConnected(false);
		}
	else
		{
		com_port.setPortName(ui.comboBox_ports->currentText());
		///device_CMD.COM_port_name = ui.comboBox_ports->currentText();
		////device_CMD.SetupDevice();
		ui.pushButton_Conn->setText(tr("Disconnect"));
		com_port.SetConnected(true);

		}
#if 0
	if(device_CMD.IsAttached())
	{
		SetActionsState(false);
		ui.pushButton_start_stop->setText(tr("\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214"));
		device_CMD.StopDevice();

		SetConnectStatus();

		dial_load_status.hide();
		dial_process_status.hide();

		SetConnectionChange(true);
	}
	else
	{
		SetConnectionChange(false);
		device_CMD.COM_port_name = ui.comboBox_ports->currentText();
		device_CMD.SetupDevice();
		ui.pushButton_start_stop->setText(tr("\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214"));
	}
#endif
}
void MainWindow::on_file_path()
{

	Dialog_write_file dial_write(this, UploadFilePath, DeviceWriteDir);
	dial_write.show();
	if(dial_write.exec() != QDialog::Accepted)
		return;
	dial_write.GetFilePathAndWrDir(&UploadFilePath, &DeviceWriteDir);

////QString str1 = QFileDialog::getOpenFileName(0, "Open", "", "*.hex *.bin");
///    QString str = QFileDialog::getExistingDirectory(0, "Выбор папки", "D:\\_Qt", QFileDialog::ShowDirsOnly
 ///                                                   | QFileDialog::DontResolveSymlinks);

////	QFileDialogCust dial_file_sel;
#if 0
	QFileDialog dial_file_sel(this);

	dial_file_sel.exec();

	dial_file_sel.setFileMode(QFileDialog::ExistingFile);


	QDir old_dir(ui.lineEdit_file_path->text().section('/',0, -2));
	if(old_dir.exists())
		dial_file_sel.setDirectory(old_dir.path());
	else
		dial_file_sel.setDirectory(QCoreApplication::applicationDirPath());


	dial_file_sel.setOption(QFileDialog::DontUseNativeDialog, true);
	dial_file_sel.setNameFilter("*.*");

	dial_file_sel.setWindowTitle(tr(" xaxa \320\227\320\260\320\277\320\270\321\201\321\213\320\262\320\260\320\265\320\274\321\213\320\271 \321\204\320\260\320\271\320\273"));


	dial_file_sel.show();
	if(dial_file_sel.exec())
	{
		QStringList temp = dial_file_sel.selectedFiles();
		ui.lineEdit_file_path->setText(temp[0]);
	}
#endif
}
