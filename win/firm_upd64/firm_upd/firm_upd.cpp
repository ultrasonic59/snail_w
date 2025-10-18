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
		QMainWindow(parent), connected(false),
	    answ(0), data_ok(false),
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
   m_pProgHex = new CprogHex(&data_ok, &odat, &curr_dev_state,&cur_pb_val);
   m_pProgHex->moveToThread(m_pThread);
   connect(m_pThread, SIGNAL(finished()), m_pProgHex, SLOT(deleteLater()));
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
	connect(ui->butt_set_boot, SIGNAL(clicked()), this, SLOT(setBootMode()));
	connect(ui->pushButton_ver, SIGNAL(clicked()), this, SLOT(ver_flash()));

	connect(&dial_dbg, SIGNAL(req_rd_eeprom(dat_req_t*)), this, SLOT(slot_rd_eeprom_dat(dat_req_t*)));
	connect(&dial_dbg, SIGNAL(req_wr_eeprom(dat_req_t*)), this, SLOT(slot_wr_eeprom_dat(dat_req_t*)));
	connect(&dial_dbg, SIGNAL(req_rd_flash(dat_req_t*)), this, SLOT(slot_rd_flash_dat(dat_req_t*)));

	connect(ui->pushButton_tst, SIGNAL(clicked()), m_pProgHex, SLOT(sl_progr_eeprom()));


////	connect(&prog_hex, SIGNAL(sig_set_pb_val(quint32)), this, SLOT(set_pb_val(quint32)));
///	connect(m_pProgHex, SIGNAL(sig_set_pb_val(quint32)), this, SLOT(set_pb_val(quint32)));

 ////  QObject::connect(port, SIGNAL(readyRead()), this, SLOT(serialDataReceived()));
 ////  QObject::connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serialError()));
 ////  QObject::connect(this, SIGNAL(hardwareResponseFinished()), this, SLOT(serialReady()));

///	connect(prog_hex, SIGNAL(sig_set_pb_val(quint32 val)), this, SLOT(set_pb_val(quint32 val)));
///=====================================================
	connect(this, SIGNAL(s_connect(bool)), m_pProgHex, SLOT(sl_connect(bool)));
	connect(this, SIGNAL(s_set_com_name(QString)), m_pProgHex, SLOT(sl_set_com_name(QString)));
	connect(this, SIGNAL(s_set_can_id(QString)), m_pProgHex, SLOT(sl_set_can_id(QString)));
	connect(this, SIGNAL(s_SetBootMode()), m_pProgHex, SLOT(sl_SetBootMode()));
	connect(this, SIGNAL(s_progr(QFile*)), m_pProgHex, SLOT(sl_progr(QFile*)));
	connect(this, SIGNAL(s_req_curr_state()), m_pProgHex, SLOT(sl_req_curr_state()));
	connect(this, SIGNAL(s_rd_eeprom(dat_req_t*)), m_pProgHex, SLOT(sl_rd_eeprom(dat_req_t*)));
	connect(this, SIGNAL(s_wr_eeprom(dat_req_t*)), m_pProgHex, SLOT(sl_wr_eeprom(dat_req_t*)));
	connect(this, SIGNAL(s_rd_flash(dat_req_t*)), m_pProgHex, SLOT(sl_rd_flash(dat_req_t*)));
	connect(this, SIGNAL(s_verif(QFile*)), m_pProgHex, SLOT(sl_verif(QFile*)));

////	connect(m_pProgHex, SIGNAL(s_set_curr_state(quint8)), this, SLOT(sl_set_curr_state(quint8)));

/* 
   if(m_pProg_hex->isConnected())
		ui->pushButton_Conn->setText(tr("Disconnect"));
	else
		ui->pushButton_Conn->setText(tr("Connect"));
		*/
///====================================================

}

Cfirm_upd::~Cfirm_upd()
{
///if(m_pProg_hex->isConnected())
////	m_pProg_hex->SetConnected(false);
	m_pThread->quit();
	m_pThread->wait(200);

saveSettings();
}

bool Cfirm_upd::is_connected()
{
return connected;
}

void Cfirm_upd::set_connected(bool conn) {
	connected = conn;
}
/*
void Cfirm_upd::sl_set_curr_state(quint8 new_state) {
	state_ok = true;
	curr_dev_state = new_state;
}
*/

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
void Cfirm_upd::show_connect(bool conn)
{
if(conn)
	{
////	ui->pushButton_Conn->setStyleSheet("background-color: rgb(0, 128, 0); color: rgb(0, 128, 0)");
	ui->pushButton_Conn->setStyleSheet("background-color: rgb(0, 128, 0)");
	ui->statusBar->showMessage("Connected to dev");
	ui->pushButton_Conn->setText(tr("Disconnect"));
	}
else
	{
	ui->statusBar->showMessage("No connected to dev");
	ui->pushButton_Conn->setText(tr("Connect"));
	ui->pushButton_Conn->setStyleSheet("");
	}
}
#if 0
void Cfirm_upd::connection()
{
if(is_connected())
	{
	emit s_connect(false);
	set_connected(false);
///	m_pProg_hex->SetConnected(false);
	show_connect(false);

	ui->statusBar->showMessage("No connected to dev");
	}
else
	{
	ui->statusBar->showMessage("Connecting to dev");
	_COM_port_name=ui->comboBox_ports->currentText();
	emit s_set_com_name(_COM_port_name);
	///m_pProg_hex->COM_port_name = _COM_port_name;		// 
///	m_pProg_hex->set_can_id(ui->comboBox_axis->currentText() );
	emit s_set_can_id(ui->comboBox_axis->currentText());

	saveSettings();
///	m_pProg_hex->connectToDev();
	emit s_connect(true);

///	quint8 t_dev_state=0;
 ///   t_dev_state= get_curr_state();
	if (get_curr_state()) {

		if ((curr_dev_state & BOOTER_STATE_MASK) != BOOTER_STATE_MASK)
	     {
			ui->statusBar->showMessage("Set boot mode");
			emit s_SetBootMode();
			if (get_curr_state()) {
				if ((curr_dev_state & BOOTER_STATE_MASK) != BOOTER_STATE_MASK)
				    {
					ui->statusBar->showMessage("Error mode");
					show_connect(false);
				    }
				else
				   {
					ui->statusBar->showMessage("Connected");
					show_connect(true);
				   }
			}
			else
			{
				ui->statusBar->showMessage("Error rd mode2");
				show_connect(false);

			}
		 }
		else
		   {
			ui->statusBar->showMessage("Connected");
			set_connected(true);
			show_connect(true);
		   }
	}
	else {
		ui->statusBar->showMessage("Error rd mode");
		set_connected(false);
		show_connect(false);
	   }
}
}
#endif
void Cfirm_upd::setBootMode()
{
ui->statusBar->showMessage("Set boot mode");
emit s_SetBootMode();
QThread::msleep(100);
if (get_curr_state()) {
	if ((curr_dev_state & BOOTER_STATE_MASK) != BOOTER_STATE_MASK)
	{
		ui->label_rej->setText(tr("No Boot"));
	}
	else
	{
		ui->label_rej->setText(tr("Boot"));
	}
}
else
  ui->label_rej->setText(tr("--------"));
}

void Cfirm_upd::connection()
{
	if (is_connected())
	{
		emit s_connect(false);
		set_connected(false);
///		show_connect(false);
	     ui->statusBar->showMessage("No connected to dev");
	}
	else
	{
		ui->statusBar->showMessage("Connecting to dev");
		_COM_port_name = ui->comboBox_ports->currentText();
		emit s_set_com_name(_COM_port_name);
		emit s_set_can_id(ui->comboBox_axis->currentText());
		saveSettings();
		emit s_connect(true);
		if (get_curr_state()) {
			ui->statusBar->showMessage("Connected");
			set_connected(true);
			if ((curr_dev_state & BOOTER_STATE_MASK) != BOOTER_STATE_MASK)
			{
				ui->label_rej->setText(tr("No Boot"));
			}
			else
			{
				ui->label_rej->setText(tr("Boot"));
			}
		}
		else
		{
			set_connected(false);
			ui->label_rej->setText(tr("--------"));

		}

	}
	show_connect(is_connected());
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

#define NUM_WAIT 5
bool Cfirm_upd::get_curr_state()
{
///answ = 0;
data_ok = false;
emit s_req_curr_state();
for (int ii = 0; ii < NUM_WAIT; ii++) {
if (data_ok)
	{
	return true;
	}
QThread::msleep(100);
}
return false;
}
void Cfirm_upd::progr_flash()
{
quint64 file_size;
qint32 prev_pb_val = -1;
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
////m_pProg_hex->progr(curFile);
data_ok = false;
emit s_progr(curFile);
while (!data_ok)
{
	if (prev_pb_val != cur_pb_val)
	{
		prev_pb_val = cur_pb_val;
		set_pb_val(cur_pb_val);
   }
}

curFile->close();

QApplication::restoreOverrideCursor();
ui->progressBar->hide();
if(curr_dev_state== BOOTER_STATE_OK)
    ui->statusBar->showMessage("Prog OK");
else
   ui->statusBar->showMessage("Prog Error");
}
void Cfirm_upd::ver_flash()
{
	quint64 file_size;
	qint32 prev_pb_val = -1;
	////ui->progressBar->show();
	curFile->setFileName(CurFilePath);
	if (!curFile->open(QFile::ReadOnly))
	{
		ui->statusBar->showMessage("Aborted: unable to open file for reading.");
		return;
	}
	ui->statusBar->showMessage("Verifing... ");
	QApplication::setOverrideCursor(Qt::WaitCursor);
	file_size = curFile->size();
	ui->progressBar->setMinimum(0);
	ui->progressBar->setMaximum(file_size);
	ui->progressBar->show();
	data_ok = false;
	emit s_verif(curFile);
	while (!data_ok)
	{
		if (prev_pb_val != cur_pb_val)
		{
			prev_pb_val = cur_pb_val;
			set_pb_val(cur_pb_val);
		}
	}

	curFile->close();

	QApplication::restoreOverrideCursor();
	ui->progressBar->hide();
	if (curr_dev_state == BOOTER_STATE_OK)
		ui->statusBar->showMessage("Prog OK");
	else
		ui->statusBar->showMessage("Prog Error");
}

///=========================================================================
void  Cfirm_upd::on_butt_debug()
{
	dial_dbg.show();
}
void Cfirm_upd::slot_rd_eeprom_dat(dat_req_t* odat)
{
if(!is_connected())
	return;
///odat->data[0]=0x4567;
#if 0
int nValue = 125;
QString t_str = QString::number(nValue, 16);
///	qDebug() << "data" ;
qDebug() << "Error crc " << t_str;
#endif
emit s_rd_eeprom(odat);
dial_dbg.req_data_rdy(odat);	
return;
}
void Cfirm_upd::slot_wr_eeprom_dat(dat_req_t* idat)
{
if(!is_connected())
	return;
emit s_wr_eeprom(idat);
}
void Cfirm_upd::slot_rd_flash_dat(dat_req_t* odat)
{
if(!is_connected())
	return;
emit s_rd_flash(odat);
dial_dbg.req_data_rdy(odat);
		return;
}
