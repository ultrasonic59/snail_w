#include "dial_debug.h"

DialDebug::DialDebug(QWidget *parent):
    QDialog(parent, Qt::Window),
    ui()

{
	ui.setupUi(this);
	ui.comboBox_rej->addItem("EEPROM",EEPROM_REJ);
	ui.comboBox_rej->addItem("FLASH",FLASH_REJ);
	ui.buttonBox->hide();


}

void DialDebug::closeEvent( QCloseEvent * event )
{
QDialog::closeEvent(event);
}

DialDebug::~DialDebug()
{
}

void DialDebug::setMinMaxValues(QString &text)
{
	ui.label_min_max_values->setText(text);
}

void  DialDebug::on_butt_rd(void)
{
dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);
if(ui.comboBox_rej->currentIndex()==EEPROM_REJ)
	emit req_rd_eeprom(&dat_req);
else if(ui.comboBox_rej->currentIndex()==FLASH_REJ)
	emit req_rd_flash(&dat_req);
}
void  DialDebug::on_butt_wr(void)
{
dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
dat_req.nbytes=1;
dat_req.data[0]=ui.lineEdit_wr_dat->text().toInt(0,16);
if(ui.comboBox_rej->currentIndex()==EEPROM_REJ)
	emit req_wr_eeprom(&dat_req);
///qDebug()<<"on_butt_wr";
}
void  DialDebug::req_data_rdy(dat_req_t* p_alt_dat)
{
QString tstr;
int ii;
if(p_alt_dat->nbytes==0)
p_alt_dat->nbytes=1;
else if(p_alt_dat->nbytes>MAX_ALT_DATA_LEN)
	p_alt_dat->nbytes=MAX_ALT_DATA_LEN;
for(ii=0;ii<p_alt_dat->nbytes;ii++)
{
tstr.sprintf("\naddr=%x->%x",p_alt_dat->addr+ii,p_alt_dat->data[ii]);
//ui.textEdit_rd_dat->textCursor().insertText(tstr);

ui.textEdit_rd_dat->append(tstr);


QTextCursor c = ui.textEdit_rd_dat->textCursor();
c.movePosition(QTextCursor::End);
ui.textEdit_rd_dat->setTextCursor(c);
}

}

void DialDebug::clear_textEdit()
{
	ui.textEdit_rd_dat->clear();
}

