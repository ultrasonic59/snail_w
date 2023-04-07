#include "firm_upd.h"
#include <QSettings>
#include "ui_firm_upd.h"

#include <QtSerialPort/QSerialPortInfo>

////#include "dialog_write_file.h"
////#include "QFileDialog.h"
////   QStringList fonts = { "Arial", "Helvetica", "Times" };
QByteArray lastLine;

///==========================================================
void Cfirm_upd::saveSettings()
{
	QSettings settings( QCoreApplication::applicationDirPath()+"//firm_upd.ini",
					   QSettings::IniFormat);
	settings.setValue("COM_port_name", _COM_port_name);

	settings.setValue("CurFilePath", CurFilePath);
	settings.setValue("CurAxis", CurAxis);
	
}

void Cfirm_upd::loadSettings()
{
	QSettings settings( QCoreApplication::applicationDirPath()+"//firm_upd.ini",
					   QSettings::IniFormat);
	_COM_port_name = settings.value("COM_port_name", "COM8").toString();		// 

	CurFilePath = settings.value("CurFilePath", QCoreApplication::applicationDirPath() ).toString();
	CurAxis = settings.value("CurAxis", AxisX).toInt();
}

///==========================================================
Cfirm_upd::Cfirm_upd(QWidget *parent) : 
		QMainWindow(parent),
////		COMpr(),
		CurAxis(AxisX), 
		ui(new Ui::firm_upd)
{
	ui->setupUi(this);
	loadSettings();
	ui->lineEdit_file_path->setText(CurFilePath);
////       QStringList _axis = { "Arial", "Helvetica", "Times" };
   QStringList axis_str;
     axis_str << "AxisX"
           << "AxisY"
           << "AxisZ" ;
////   port = new QSerialPort();
   curFile = new QFile();
///===================================================
   m_pThread = new QThread(this);
   m_pProg_hex = new CprogHex;
   m_pProg_hex->moveToThread(m_pThread);
   connect(m_pThread, SIGNAL(finished()), m_pProg_hex, SLOT(deleteLater()));
   m_pThread->start();
///============================================
	refresh_used_ports();
///============================================
////	ui.comboBox_axis->insertItems( 3, axis_str);

    ui->progressBar->hide();

	connect(ui->pushButton_refresh, SIGNAL(clicked()), this, SLOT(refresh_used_ports()));
	connect(ui->pushButton_Conn, SIGNAL(clicked()), this, SLOT(connection()));
    connect(ui->pushButt_file, SIGNAL(clicked()), this, SLOT(on_file_path()));
    connect(ui->pushButton_prog, SIGNAL(clicked()), this, SLOT(progr_flash()));

////	connect(&prog_hex, SIGNAL(sig_set_pb_val(quint32)), this, SLOT(set_pb_val(quint32)));
	connect(m_pProg_hex, SIGNAL(sig_set_pb_val(quint32)), this, SLOT(set_pb_val(quint32)));

 ////  QObject::connect(port, SIGNAL(readyRead()), this, SLOT(serialDataReceived()));
 ////  QObject::connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serialError()));
   QObject::connect(this, SIGNAL(hardwareResponseFinished()), this, SLOT(serialReady()));

///	connect(prog_hex, SIGNAL(sig_set_pb_val(quint32 val)), this, SLOT(set_pb_val(quint32 val)));

}

Cfirm_upd::~Cfirm_upd()
{
	saveSettings();
}



void Cfirm_upd::refresh_used_ports()
{
	ui->comboBox_ports->clear();
#if 1
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		if(info.description() != "")
		{
			ui->comboBox_ports->addItem(info.portName());
////			if(device_CMD.COM_port_name == info.portName())
////				ui.comboBox_ports->setCurrentIndex( ui.comboBox_ports->count() - 1 );		// переключаем на выбранный порт
		}
	}

////	ui.pushButton_start_stop->setEnabled(ui.comboBox_ports->count() > 0);
#endif
}
void Cfirm_upd::connection()
{
#if 0
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
#endif
	_COM_port_name=ui->comboBox_ports->currentText();
	m_pProg_hex->COM_port_name = _COM_port_name;		// 
	saveSettings();


	m_pProg_hex->connectToDev();

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

QDir old_dir(ui->lineEdit_file_path->text().section('/',0, -2));
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
    ui->lineEdit_file_path->setText(CurFilePath);
    saveSettings();
    }
}
///=========================================================================
void Cfirm_upd::set_pb_val(quint32 val)
{
ui->progressBar->setValue(val);
}

void Cfirm_upd::progr_flash()
{
quint64 file_size;
////ui->progressBar->show();
curFile->setFileName(CurFilePath);
if(!curFile->open(QFile::ReadOnly))
    {
    ui->statusBar->showMessage("Aborted: unable to open file for reading.");
    return;
    }
ui->statusBar->showMessage("Programming... ");
QApplication::setOverrideCursor(Qt::WaitCursor);
file_size=curFile->size();
ui->progressBar->setMinimum(0);
ui->progressBar->setMaximum(file_size);
ui->progressBar->show();

////ui->progressBar->setValue(file_size/4);

//// prog_hex.progr(curFile);
m_pProg_hex->progr(curFile);

QApplication::restoreOverrideCursor();

ui->progressBar->hide();
ui->statusBar->showMessage("");

#if 0
QTextStream in(curFile);
QString line = in.readLine();
file_size=curFile->size();
ui->progressBar->setMinimum(0);
ui->progressBar->setMaximum(file_size);
////ui->progressBar->setValue(file_size/4);
ui->progressBar->show();
while(!line.isNull()) {
	if (line.startsWith(":"))
////		processHexLine(line);
		line = in.readLine();
	}
#endif
curFile->close();


}
///=========================================================================
#if 0
void Cfirm_upd::program()
{
#if 1
    curFile->setFileName(ui->lineEdit_file_path->text());

    if(!curFile->exists())
    {
        ui->statusBar->showMessage("Aborted: file does not exist.");
        return;
    }

    if(!curFile->open(QFile::ReadOnly))
    {
        ui->statusBar->showMessage("Aborted: unable to open file for reading.");
        return;
    }

    if(port->isOpen())
    {
        port->close();
    }

    QSerialPortInfo info;
#if 0
    foreach(info, QSerialPortInfo::availablePorts())
    {
        if(info.portName() == ui->portList->currentText())
        {
            qDebug() << "Port selected";
            port->setPort(info);
            break;
        }
    }
#endif
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setStopBits(QSerialPort::OneStop);
    port->setParity(QSerialPort::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if(port->open(QIODevice::ReadWrite))
    {
        qDebug("Port open");
    }

    ui->statusBar->showMessage("Programming... ");

    serialReady();
#endif
}
#endif
void Cfirm_upd::serialDataReceived()
{
#if 0
QString msg = QString(port->readAll());
    message += msg;

    if(msg.contains('>') && !messageFinished)
    {
        messageFinished = true;

        if(message.contains("ERR") || message.contains("WARN"))
        {
            qDebug() << "WARNING: PROGRAMMER THREW ERROR DURING PROGRAMMING.";
            qDebug() << message;

            ui->statusBar->showMessage("WARNING: Programming error detected");

            QObject::disconnect(port, SIGNAL(readyRead()), this, SLOT(serialDataReceived()));

            port->write(QByteArray(1, '\n'));
            QThread::msleep(500);
            port->write(QByteArray(1, '\n'));
            QThread::msleep(500);

            qDebug() << port->readAll();

            QObject::connect(port, SIGNAL(readyRead()), this, SLOT(serialDataReceived()));

            qDebug() << "Writing " << lastLine;

            message = "";
            messageFinished = false;
            port->write(lastLine);
            return;
        }

        ui->statusBar->showMessage("Programming... ");
        qDebug() << message;
        QThread::msleep(200);
        emit hardwareResponseFinished();
    }
#endif
}

void Cfirm_upd::serialError()
{
////    qDebug() << port->errorString();
}

void Cfirm_upd::serialReady()
{
#if 0
    if(!curFile->isOpen())
    {
        ui->statusBar->showMessage("Error: file is closed while trying to program.");
        port->close();
        return;
    }

    messageFinished = false;
    message = "";

    if(!curFile->atEnd())
    {
        //TODO: remove trailing endline char from line
        QByteArray line = curFile->readLine();
        line.truncate(line.length() - 2);
        line.append('\n');
        lastLine = line;
        qDebug() << "Writing " << line;
        port->write(line);
    }
    else
    {
        ui->statusBar->showMessage("Programming complete");
    }
#endif
}