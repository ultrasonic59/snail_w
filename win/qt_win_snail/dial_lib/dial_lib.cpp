#include "dial_lib.h"

DialLib::DialLib(QWidget *parent, PlotProperties* Plot_Prop):
    QDialog(parent, Qt::Window),pParent(parent),pPlot_Prop(Plot_Prop)
   , ui()
{
	ui.setupUi(this);
    scene = new LibPaintScene(this,pPlot_Prop);       // 
    ui.graphicsView->setScene(scene);  // 

    timer = new QTimer();       // 
    connect(timer, &QTimer::timeout, this, &DialLib::slotTimer);
    timer->start(100);          // 

///	ui.comboBox_rej->addItem("HID",HID_REJ);
//// 	ui.comboBox_rej->addItem("CAN",CAN_REJ);
////	ui.comboBox_rej->addItem("LIN",LIN_REJ);
 ///   connect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
 ///   connect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));

	////connect(ui.pushButton_test, SIGNAL(clicked()), this, SLOT(SlotTest()));
  ///  connect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));
  
  ///  connect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
}

DialLib::~DialLib()
{
  ////  disconnect(this, SIGNAL(req_rd_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_rd_dbg(int, dbg_dat_req_t*)));
 ////   disconnect(this, SIGNAL(req_wr_dbg(int, dbg_dat_req_t*)), pParent, SLOT(slot_wr_dbg(int, dbg_dat_req_t*)));
 ///   disconnect(this, SIGNAL(req_send_can_dbg(can_message_t*)), pParent, SLOT(slot_send_can_dbg(can_message_t*)));
 ///   disconnect(ui.pushButton_send_can, SIGNAL(clicked()), this, SLOT(slot_send_can_msg()));

}

void  DialLib::slot_butt_rd()
{
	dbg_dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
	dbg_dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);
	int num_rej=ui.comboBox_rej->currentIndex();
	emit req_rd_dbg(num_rej,&dbg_dat_req);
}
void  DialLib::slot_butt_wr()
{
    dbg_dat_req.addr=ui.lineEdit_addr->text().toInt(0,16);
    dbg_dat_req.nbytes=1;
    dbg_dat_req.data[0]=ui.lineEdit_wr_dat->text().toInt(0,16);
	if(ui.comboBox_rej->currentIndex()==CAN_REJ)
      dbg_dat_req.nbytes=ui.lineEdit_count->text().toInt(0,16);

	int num_rej=ui.comboBox_rej->currentIndex();
	emit req_wr_dbg(num_rej,&dbg_dat_req);
}
void  DialLib::slot_send_can_msg()
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

void  DialLib::req_dbg_data_rdy(dbg_dat_req_t* p_dbg_dat)
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
void  DialLib::req_xil_data_rdy(xil_dat_req_t* p_xil_dat)
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

void  DialLib::req_str_rdy(char* istr)
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

void DialLib::clear_textEdit()
{
  ////  ui.textEdit_rd_dat->clear();
}
void DialLib::SlotTest()
{
 emit SignalTest();
}
///============================================
///===========================================
void DialLib::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0, 0, ui.graphicsView->width() - 20, ui.graphicsView->height() - 20);
}

void DialLib::resizeEvent(QResizeEvent* event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}
