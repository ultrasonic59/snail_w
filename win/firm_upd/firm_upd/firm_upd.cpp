#include "firm_upd.h"
#include <QSettings>
#include <QtSerialPort/QSerialPortInfo>
////#include "dialog_write_file.h"
#include "QFileDialog.h"
////   QStringList fonts = { "Arial", "Helvetica", "Times" };

///==========================================================
void Cfirm_upd::saveSettings()
{
	QSettings settings( QCoreApplication::applicationDirPath()+"//firm_upd.ini",
					   QSettings::IniFormat);
	settings.setValue("COM_port_name", com_port.COMstate.PortName);

	settings.setValue("CurFilePath", CurFilePath);
	settings.setValue("CurAxis", CurAxis);
	
////	settings.setValue("DeviceReadFile", DeviceReadFile);
////	settings.setValue("DeviceWriteDir", DeviceWriteDir);
}

void Cfirm_upd::loadSettings()
{
	QSettings settings( QCoreApplication::applicationDirPath()+"//firm_upd.ini",
					   QSettings::IniFormat);
	com_port.COMstate.PortName = settings.value("COM_port_name", "COM8").toString();		// 

	CurFilePath = settings.value("CurFilePath", QCoreApplication::applicationDirPath() ).toString();
	CurAxis = settings.value("CurAxis", AxisX).toInt();
}

///==========================================================
Cfirm_upd::Cfirm_upd(QWidget *parent) : 
		QMainWindow(parent),
		COMpr(),
		CurAxis(AxisX),
		ui(),com_port(this, &COMpr)		
{
	ui.setupUi(this);
	loadSettings();
	ui.lineEdit_file_path->setText(CurFilePath);
////       QStringList _axis = { "Arial", "Helvetica", "Times" };
   QStringList axis_str;
     axis_str << "AxisX"
           << "AxisY"
           << "AxisZ" ;

	ui.comboBox_axis->insertItems( 3, axis_str);

ui.progressBar->hide();

	connect(ui.pushButton_refresh, SIGNAL(clicked()), this, SLOT(refresh_used_ports()));
	connect(ui.pushButton_Conn, SIGNAL(clicked()), this, SLOT(connection()));
    connect(ui.pushButt_file, SIGNAL(clicked()), this, SLOT(on_file_path()));
    connect(ui.pushButton_prog, SIGNAL(clicked()), this, SLOT(progr_flash()));

}

Cfirm_upd::~Cfirm_upd()
{
	saveSettings();
}



void Cfirm_upd::refresh_used_ports()
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
void Cfirm_upd::connection()
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
void Cfirm_upd::on_file_path()
{
QFileDialog dial_file_sel(this);

dial_file_sel.setFileMode(QFileDialog::ExistingFile);

QDir old_dir(ui.lineEdit_file_path->text().section('/',0, -2));
if(old_dir.exists())
	dial_file_sel.setDirectory(old_dir.path());
else
	dial_file_sel.setDirectory(QCoreApplication::applicationDirPath());

dial_file_sel.setOption(QFileDialog::DontUseNativeDialog, true);
dial_file_sel.setNameFilter("*.hex");

dial_file_sel.setWindowTitle(tr(" Open Prog File"));
if(dial_file_sel.exec())
   {
	QStringList temp = dial_file_sel.selectedFiles();
    CurFilePath=temp[0];
    ui.lineEdit_file_path->setText(CurFilePath);
    saveSettings();
    }
}
///=========================================================================
void Cfirm_upd::progr_flash()
{
ui.progressBar->show();

}
///=========================================================================
