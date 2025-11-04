#include "dial_debug.h"
#include "cmd_sender.h"

DialDebug::DialDebug(QWidget *parent):
    QDialog(parent, Qt::Window),pParent(parent)
   , ui()
{
	ui.setupUi(this);
	ui.comboBox_rej->addItem("HID",HID_REJ);
 	ui.comboBox_rej->addItem("CAN",CAN_REJ);
	ui.comboBox_rej->addItem("SPI_MOT",SPI_REJ);
    ui.comboBox_rej->addItem("EEPROM", EEPROM_REJ);

    ui.comboBox_axis->addItem("X", AXI_X);
    ui.comboBox_axis->addItem("Y", AXI_Y);
    ui.comboBox_axis->addItem("Z", AXI_Z);
    ui.comboBox_axis->addItem("DOZA", AXI_DOZA);

    connect(this, SIGNAL(req_rd_dbg(int,int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int,int, dbg_dat_req_t*)));
    connect(this, SIGNAL(req_wr_dbg(int,int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int,int, dbg_dat_req_t*)));

	connect(ui.pushButton_test, SIGNAL(clicked()), this, SLOT(SlotTest()));
    connect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));

 ////  connect(parent, SIGNAL(put_str_dial(char*)), this, SLOT(req_str_rdy(char*)));
  connect(pParent, SIGNAL(put_msg_dial(can_message_t)), this, SLOT(req_msg_rdy(can_message_t)));

    connect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
}

DialDebug::~DialDebug()
{
    disconnect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));
    disconnect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
  ///  disconnect(pParent, SIGNAL(put_str_dial(char*)), this, SLOT(req_str_rdy(char*)));
    disconnect(pParent, SIGNAL(put_msg_dial(can_message_t)), this, SLOT(req_msg_rdy(can_message_t)));

    disconnect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));

}

void  DialDebug::slot_butt_rd()
{
	dbg_dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
	dbg_dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);
	int num_rej=ui.comboBox_rej->currentIndex();
    int num_axi = ui.comboBox_axis->currentIndex();

	emit req_rd_dbg(num_axi,num_rej,&dbg_dat_req);
}
void  DialDebug::slot_butt_wr()
{
    dbg_dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
    dbg_dat_req.nbytes=1;
    dbg_dat_req.data[0]=ui.lineEdit_wr_dat->text().toInt(0,16);
	if(ui.comboBox_rej->currentIndex()==CAN_REJ)
      dbg_dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);
    else if (ui.comboBox_rej->currentIndex() == SPI_REJ)
        dbg_dat_req.nbytes = ui.lineEdit_count->text().toInt(0, 16)*2;
	int num_rej=ui.comboBox_rej->currentIndex();
    int num_axi = ui.comboBox_axis->currentIndex();
    emit req_wr_dbg(num_axi, num_rej,&dbg_dat_req);
}
void  DialDebug::slot_send_can_msg()
{
    can_data.id= ui.lineEdit_ID->text().toInt(0, 16);
    can_data.dlc= ui.lineEdit_DLC->text().toInt(0, 16);
    can_data.IDE = 0;
    can_data.RTR = 0;
    can_data.data[0]= ui.lineEdit_dat0->text().toInt(0, 16);
    can_data.data[1] = ui.lineEdit_dat1->text().toInt(0, 16);
    can_data.data[2] = ui.lineEdit_dat2->text().toInt(0, 16);
    can_data.data[3] = ui.lineEdit_dat3->text().toInt(0, 16);
    can_data.data[4] = ui.lineEdit_dat4->text().toInt(0, 16);
    can_data.data[5] = ui.lineEdit_dat5->text().toInt(0, 16);
    can_data.data[6] = ui.lineEdit_dat6->text().toInt(0, 16);
    can_data.data[7] = ui.lineEdit_dat7->text().toInt(0, 16);
    emit req_send_can_dbg( &can_data);

}

void  DialDebug::req_dbg_data_rdy(dbg_dat_req_t* p_dbg_dat)
{
#if 1
    QString tstr;
    int ii;
    if(p_dbg_dat->nbytes==0)
        p_dbg_dat->nbytes=1;
    else if(p_dbg_dat->nbytes>MAX_DBG_DATA_LEN)
        p_dbg_dat->nbytes=MAX_DBG_DATA_LEN;
    for(ii=0;ii<p_dbg_dat->nbytes;ii++)
    {
        tstr.asprintf("\nAddr=%x->%x",p_dbg_dat->addr+ii,p_dbg_dat->data[ii]);
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
#if 1
 QString tstr(istr);
 ////tstr.sprintf("\n%s",istr);
 ui.textEdit_rd_dat->append(tstr);
 QTextCursor c = ui.textEdit_rd_dat->textCursor();
 c.movePosition(QTextCursor::End);
 ui.textEdit_rd_dat->setTextCursor(c);
#endif
}
void  DialDebug::req_msg_rdy(can_message_t istr)
{
    //// QString tstr;
    can_message_t t_can_message = istr;
    put_ack_t* p_put_ack = (put_ack_t*)t_can_message.data;
    if (p_put_ack->cmd == PUT_ACK) {
        QString tstr = QString("ack[axis:%1 cmd:%2]").arg(QString::number(p_put_ack->ack.axis)).arg(QString::number(p_put_ack->ack.ack_cmd, 16));
        ui.textEdit_rd_dat->append(tstr);

    }
    else {
        spi_mot_cmd_t* spi_mot_cmd = (spi_mot_cmd_t*)t_can_message.data;

        quint32 tmp;
        if (spi_mot_cmd->len_dat > 1)
            tmp = spi_mot_cmd->w_val;
        else
            tmp = spi_mot_cmd->b_val;
        QString tstr = QString("Addr=%1 :%2").arg(QString::number(spi_mot_cmd->addr, 16)).arg(QString::number(tmp, 16));

        ui.textEdit_rd_dat->append(tstr);
    }
#if 0
    QString tstr(istr);
    ////tstr.sprintf("\n%s",istr);
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

