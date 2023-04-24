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

	ui->comboBox_axis->addItems(axis_str);
   curFile = new QFile();
///===================================================
   m_pThread = new QThread(this);
   m_pProg_hex = new CprogHex;
   m_pProg_hex->moveToThread(m_pThread);
   connect(m_pThread, SIGNAL(finished()), m_pProg_hex, SLOT(deleteLater()));
   m_pThread->start();
///============================================
	refresh_used_ports();
	ui->comboBox_ports->setCurrentText(_COM_port_name);

    ui->progressBar->hide();

	connect(ui->pushButton_refresh, SIGNAL(clicked()), this, SLOT(refresh_used_ports()));
	connect(ui->pushButton_Conn, SIGNAL(clicked()), this, SLOT(connection()));
    connect(ui->pushButt_file, SIGNAL(clicked()), this, SLOT(on_file_path()));
    connect(ui->pushButton_prog, SIGNAL(clicked()), this, SLOT(progr_flash()));
	connect(ui->pushButt_debug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));

	connect(&dial_dbg, SIGNAL(req_rd_eeprom(dat_req_t*)), this, SLOT(slot_rd_eeprom_dat(dat_req_t*)));
	connect(&dial_dbg, SIGNAL(req_wr_eeprom(dat_req_t*)), this, SLOT(slot_wr_eeprom_dat(dat_req_t*)));
	connect(&dial_dbg, SIGNAL(req_rd_flash(dat_req_t*)), this, SLOT(slot_rd_flash_dat(dat_req_t*)));


////	connect(&prog_hex, SIGNAL(sig_set_pb_val(quint32)), this, SLOT(set_pb_val(quint32)));
	connect(m_pProg_hex, SIGNAL(sig_set_pb_val(quint32)), this, SLOT(set_pb_val(quint32)));

 ////  QObject::connect(port, SIGNAL(readyRead()), this, SLOT(serialDataReceived()));
 ////  QObject::connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serialError()));
   QObject::connect(this, SIGNAL(hardwareResponseFinished()), this, SLOT(serialReady()));

///	connect(prog_hex, SIGNAL(sig_set_pb_val(quint32 val)), this, SLOT(set_pb_val(quint32 val)));
///=====================================================
   if(m_pProg_hex->isConnected())
		ui->pushButton_Conn->setText(tr("Disconnect"));
	else
		ui->pushButton_Conn->setText(tr("Connect"));
///====================================================

}

Cfirm_upd::~Cfirm_upd()
{
if(m_pProg_hex->isConnected())
	m_pProg_hex->SetConnected(false);
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
if(m_pProg_hex->isConnected())
	{
	m_pProg_hex->SetConnected(false);
	ui->statusBar->showMessage("No connected to dev");
	}
else
	{
	ui->statusBar->showMessage("Connecting to dev");
	_COM_port_name=ui->comboBox_ports->currentText();
	m_pProg_hex->COM_port_name = _COM_port_name;		// 
	m_pProg_hex->set_can_id(ui->comboBox_axis->currentText() );
	saveSettings();
	m_pProg_hex->connectToDev();
	quint8 cur_dev_state=0;
	cur_dev_state=m_pProg_hex->get_curr_state();
	if(cur_dev_state&BOOTER_STATE_MASK!=BOOTER_STATE_MASK)
		{
		ui->statusBar->showMessage("Set boot mode");
		m_pProg_hex->SetBootMode();
		}

	}

if(m_pProg_hex->isConnected())
	{
	ui->ind_conn->setStyleSheet("background-color: rgb(0, 128, 0); color: rgb(0, 128, 0)");
	ui->statusBar->showMessage("Connected to dev");
	ui->pushButton_Conn->setText(tr("Disconnect"));
	}
else
	{
	ui->statusBar->showMessage("No connected to dev");
	ui->pushButton_Conn->setText(tr("Connect"));
	ui->ind_conn->setStyleSheet("color: rgb(0, 128, 0)");
	}

 
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
void  Cfirm_upd::on_butt_debug()
{
	dial_dbg.show();
}
void Cfirm_upd::slot_rd_eeprom_dat(dat_req_t* odat)
{
if(!m_pProg_hex->isConnected())
	return;
///odat->data[0]=0x4567;
m_pProg_hex->rd_eeprom(odat);
dial_dbg.req_data_rdy(odat);	
return;
}
void Cfirm_upd::slot_wr_eeprom_dat(dat_req_t* idat)
{
if(!m_pProg_hex->isConnected())
	return;
m_pProg_hex->wr_eeprom(idat);
}
void Cfirm_upd::slot_rd_flash_dat(dat_req_t* odat)
{
////	if(!device_CMD.IsAttached())
		return;
}
