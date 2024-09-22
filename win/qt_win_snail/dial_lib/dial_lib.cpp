#include "dial_lib.h"

DialLib::DialLib(QWidget *parent, PlotProperties* Plot_Prop):
    QDialog(parent, Qt::Window),pParent(parent),pPlot_Prop(Plot_Prop)
   , ui(), cur_rej(REJ_SELECT), cur_item(RECT_TYPE)
{
	ui.setupUi(this);
    scene = new LibPaintScene(this,pPlot_Prop,&cur_item, &cur_rej);       // 
    ui.graphicsView->setScene(scene);  // 

    timer = new QTimer();       // 
    connect(timer, &QTimer::timeout, this, &DialLib::slotTimer);
    timer->start(100);          // 

    ui.comboBox_item->addItem("Rect", RECT_TYPE);
	ui.comboBox_item->addItem("FRect", FRECT_TYPE);
	ui.comboBox_item->addItem("VLine", VLINE_TYPE);
    ui.comboBox_item->addItem("HLine", HLINE_TYPE);
    ui.comboBox_item->addItem("Circle", CIRCLE_TYPE);

    connect(ui.butt_select, SIGNAL(clicked()), this, SLOT(on_butt_select()));
    connect(ui.butt_place, SIGNAL(clicked()), this, SLOT(on_butt_place()));
    connect(ui.comboBox_item, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));

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
///connect(ui.butt_select, SIGNAL(clicked()), this, SLOT(on_butt_select()));
////connect(ui.butt_place, SIGNAL(clicked()), this, SLOT(on_butt_place()));
void  DialLib::show_rej()
{
    if (cur_rej == REJ_SELECT)
    {
        ui.butt_select->setStyleSheet("background-color: green;");
        ui.butt_place->setStyleSheet(" ");
}
    else if (cur_rej == REJ_PLACE)
    {
        ui.butt_select->setStyleSheet("");
        ui.butt_place->setStyleSheet("background-color: green; ");
    }

}
void  DialLib::on_butt_select()
{
    cur_rej = REJ_SELECT;
    show_rej();
}

void  DialLib::on_butt_place()
{
    cur_rej = REJ_PLACE;
    show_rej();
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
     timer->stop();
 ///   scene->setSceneRect(0, 0, ui.graphicsView->width() - 20, ui.graphicsView->height() - 20);
}

void DialLib::resizeEvent(QResizeEvent* event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}
void DialLib::indexChanged(int index)
{
 cur_item = (en_item_tipe)ui.comboBox_item->currentIndex();

    // Do something here on ComboBox index change
}