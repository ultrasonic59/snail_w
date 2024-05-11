#include "dial_debug.h"

DialDebug::DialDebug(QWidget *parent):
    QDialog(parent, Qt::Window),pParent(parent)
   , ui()
{
	ui.setupUi(this);
	ui.comboBox_rej->addItem("HID",HID_REJ);
 	ui.comboBox_rej->addItem("CAN",CAN_REJ);
////	ui.comboBox_rej->addItem("LIN",LIN_REJ);
    connect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
    connect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));

	connect(ui.pushButton_test, SIGNAL(clicked()), this, SLOT(SlotTest()));

///	ui.buttonBox->hide();
}

DialDebug::~DialDebug()
{
    disconnect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));

}

void  DialDebug::slot_butt_rd()
{
	dbg_dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
	dbg_dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);
	int num_rej=ui.comboBox_rej->currentIndex();
	emit req_rd_dbg(num_rej,&dbg_dat_req);
}
void  DialDebug::slot_butt_wr()
{
    dbg_dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
    dbg_dat_req.nbytes=1;
    dbg_dat_req.data[0]=ui.lineEdit_wr_dat->text().toInt(0,16);
	if(ui.comboBox_rej->currentIndex()==CAN_REJ)
      dbg_dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);

	int num_rej=ui.comboBox_rej->currentIndex();
	emit req_wr_dbg(num_rej,&dbg_dat_req);
}

void  DialDebug::req_dbg_data_rdy(dbg_dat_req_t* p_dbg_dat)
{
#if 0
    QString tstr;
    int ii;
    if(p_dbg_dat->nbytes==0)
        p_dbg_dat->nbytes=1;
    else if(p_dbg_dat->nbytes>MAX_DBG_DATA_LEN)
        p_dbg_dat->nbytes=MAX_DBG_DATA_LEN;
    for(ii=0;ii<p_dbg_dat->nbytes;ii++)
    {
        tstr.sprintf("\nAddr=%x->%x",p_dbg_dat->addr+ii,p_dbg_dat->data[ii]);
        ui.textEdit_rd_dat->append(tstr);
    }
    QTextCursor c = ui.textEdit_rd_dat->textCursor();
    c.movePosition(QTextCursor::End);
    ui.textEdit_rd_dat->setTextCursor(c);
#endif
}
void  DialDebug::req_xil_data_rdy(xil_dat_req_t* p_xil_dat)
{
#if 0
    QString tstr;
    int ii;
    if(p_xil_dat->nbytes==0)
        p_xil_dat->nbytes=1;
    else if(p_xil_dat->nbytes>MAX_XIL_DATA_LEN)
        p_xil_dat->nbytes=MAX_XIL_DATA_LEN;
    for(ii=0;ii<p_xil_dat->nbytes;ii++)
    {
        tstr.sprintf("\nAddr=%x->%x",p_xil_dat->addr+ii,p_xil_dat->data[ii]);
        ui.textEdit_rd_dat->append(tstr);
    }
    QTextCursor c = ui.textEdit_rd_dat->textCursor();
    c.movePosition(QTextCursor::End);
    ui.textEdit_rd_dat->setTextCursor(c);
#endif
}

void  DialDebug::req_str_rdy(char* istr)
{
#if 0
 QString tstr;
 tstr.sprintf("\n%s",istr);
 ui.textEdit_rd_dat->append(tstr);
 QTextCursor c = ui.textEdit_rd_dat->textCursor();
 c.movePosition(QTextCursor::End);
 ui.textEdit_rd_dat->setTextCursor(c);
#endif
}

void DialDebug::clear_textEdit()
{
    ui.textEdit_rd_dat->clear();
}
void DialDebug::SlotTest()
{
 emit SignalTest();
}

