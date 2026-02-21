#include "win_snail.h"
///#include <QCameraInfo>
#include "ViewProperties.h"
#include <QColorDialog>
#include <QtScript/QScriptValue>
#include <QVariant>
#include <QMetaType>

#include "dial_lib.h"
#include "params.h"
#include "svgreader.h"
#include "cust_rect.h"
#include "cust_line.h"
#include "cust_circle.h"
#include "component.h"

QElapsedTimer el_timer;
int	el_time=0;

Q_DECLARE_METATYPE(QList<int>)

win_snail::win_snail(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win_snail())
    , cnf_flags(0)
    , m_can_isConnected(false)
     , on_esc_key(false)
    , data_ready(false)
    , cnt_req(0)
    

  {
    ui->setupUi(this);
    prev_states[XX] = 0xff;
    prev_states[YY] = 0xff;
    prev_states[ZZ] = 0xff;
    init_con_axis();

///====================================
  qRegisterMetaType<cv::Mat>("cv::Mat");
  qRegisterMetaType<mot_cmd_t>("mot_cmd_t");
  qRegisterMetaType<spi_mot_cmd_t>("spi_mot_cmd_t");
  qRegisterMetaType <can_message_t>("can_message_t");

  qRegisterMetaTypeStreamOperators<QList<int> >("QList<int>");
  qRegisterMetaType <doza_cmd_t>("doza_cmd_t");

 
   p_camera = new CameraDevice(this);
   p_CamView = ui->CamWidget;
 ///   connect(pt_camera, SIGNAL(frame_updated(QImage&, QImage::Format)), p_cam_plotter, SLOT(sl_update_image(QImage&, QImage::Format)));
 ///   connect(p_cam_plotter, SIGNAL(s_update_image(QImage&, QImage::Format)), ui->CamWidget, SLOT(update_image(QImage&, QImage::Format)));
 ///==================================================================================  
 /// connect(this, SIGNAL(s_start(int)), p_camera, SLOT(sl_start(int)));
 /// connect(p_camera, SIGNAL(imageReady(const QImage&)), p_CamView, SLOT(update_image(const QImage&)));

 /// connect(p_camera, SIGNAL(imageReady(const QImage&)), p_cam_plotter, SLOT(sl_update_image(QImage&, QImage::Format)));
  
 /// connect(p_cam_plotter, SIGNAL(s_update_image(const QImage&)), p_CamView, SLOT(update_image(const QImage&)));
 ///==================================================================================  

///===================================================
   createMenus();
 ////   createThreads();
    setupActions();
    loadSettings();
    //======================================
    ui->splitter->setSizes(splitter_sizes);
    /// ====================================
 ////   qDebug() << QCameraInfo::availableCameras().count(); 
    int camid = 0; // video device id
 ////   p_CamView = ui->CamWidget;

#if 1
    if (hid_init() == 0) {
        hid_handle = hid_open(DEF_HID_USB_VID, DEF_HID_USB_PID, NULL);
        if (!hid_handle) {
            qDebug() << "unable to open device";
            ///      return 1;
        }
/*
        else
        {
            qDebug() << "hid_blocking0:";

            hid_set_nonblocking(hid_handle, 1);

            qDebug() << "hid_blocking1:";

        }
*/
    }

  
#endif
/*
    int tsize = sizeof(float);
    qDebug() << "float="<< tsize;
    tsize = sizeof(int);
    qDebug() << "int=" << tsize;
    */
    ///=======================================================
connect(ui->Butt_test, SIGNAL(clicked()), this, SLOT(on_butt_test()));
connect(ui->Butt_test1, SIGNAL(clicked()), this, SLOT(on_butt_test1()));
connect(ui->Butt_test2, SIGNAL(clicked()), this, SLOT(on_butt_test2()));
connect(ui->Butt_test3, SIGNAL(clicked()), this, SLOT(on_butt_test3()));

connect(ui->Butt_load, SIGNAL(clicked()), this, SLOT(on_butt_load()));

 connect(ui->buttDebug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));
 connect(ui->buttConHid, SIGNAL(clicked()), this, SLOT(on_butt_con_hid()));
 ///==================CAN =============================================
 connect(ui->buttConCAN, SIGNAL(clicked()), this, SLOT(on_butt_con_can()));

  connect(ui->lightSlider0, SIGNAL(valueChanged(int)), this, SLOT(on_value_led0_changed(int)));
  connect(ui->lightSlider1, SIGNAL(valueChanged(int)), this, SLOT(on_value_led1_changed(int)));
  ///===================================================
  pSenderThread = new QThread(this);
  p_cmd_sender = new CcmdSender(&data_ready, &rsv_msg,  &dev_state);
  p_cmd_sender->moveToThread(pSenderThread);
  connect(pSenderThread, SIGNAL(finished()), p_cmd_sender, SLOT(deleteLater()));
  pSenderThread->start();
 /// connect(this, SIGNAL(s_SendCmd(can_message_t*)), m_cmd_sender, SLOT(SlSendCmd(can_message_t*)));
  connect(p_cmd_sender, SIGNAL(s_rsv_can_dat(can_message_t)), this, SLOT(sl_rsv_can_dat(can_message_t)));

  ///============================================
///=======================================================
 pCamThread= new QThread(this);
 p_cam_plotter=new CamPlotter(&PlotProp,&cnf_flags, &snail_data);
 p_cam_plotter->ConnectToWidget(ui->CamWidget);

#if 0
 ///  connect(pt_camera, SIGNAL(frame_updated(QImage&, QImage::Format)), ui->CamWidget, SLOT(update_image1(QImage&, QImage::Format)), Qt::DirectConnection);
  connect(&pt_camera->m_qvideosurface, SIGNAL(frame_available(QImage, QImage::Format)), ui->CamWidget, SLOT(update_image(QImage, QImage::Format)));

#else
 ///  connect(&pt_camera->m_qvideosurface, SIGNAL(frame_available1(QImage&, QImage::Format)), p_cam_plotter, SLOT(sl_update_image(QImage&, QImage::Format)), Qt::DirectConnection);
 ///  connect(pt_camera, SIGNAL(frame_updated(QImage&, QImage::Format)), p_cam_plotter, SLOT(sl_update_image(QImage&, QImage::Format)), Qt::DirectConnection);
////   connect(p_cam_plotter, SIGNAL(s_update_image(QImage&, QImage::Format)), ui->CamWidget, SLOT(update_image1(QImage&, QImage::Format)), Qt::DirectConnection);
#endif
 ///==================================================================================  
 connect(this, SIGNAL(s_start(int)), p_camera, SLOT(sl_start(int)));
 /// connect(p_camera, SIGNAL(imageReady(const QImage&)), p_CamView, SLOT(update_image(const QImage&)));

 connect(p_camera, SIGNAL(imageReady(const QImage&)), p_cam_plotter, SLOT(sl_update_image(const QImage&)));
 /// 
 connect(p_cam_plotter, SIGNAL(s_update_image(const QImage&)), p_CamView, SLOT(update_image(const QImage&)));
 ///==================================================================================  

   connect(p_CamView, SIGNAL(sSetPoint(QPoint*)), p_cam_plotter, SLOT(slSetPoint(QPoint*)));
   connect(p_CamView, SIGNAL(sMovePoint(QPoint*)), p_cam_plotter, SLOT(slMovePoint(QPoint*)));
   connect(p_CamView, SIGNAL(sClrPoint(QPoint*)), p_cam_plotter, SLOT(slClrPoint(QPoint*)));


 ///  connect(p_CamView, SIGNAL(sel_rect_changet(QRect)), p_cam_plotter, SLOT(sl_set_sel_rect(QRect)), Qt::QueuedConnection);
   connect(p_CamView, SIGNAL(sel_rect_changet(QRect)), p_cam_plotter, SLOT(sl_set_sel_rect(QRect)));
   connect(p_cam_plotter, SIGNAL(s_show_rule_coord(QRect&)), this, SLOT(sl_show_rule_coord(QRect&)));

 connect(pCamThread, SIGNAL(finished()), p_cam_plotter, SLOT(deleteLater()));
 ///connect(ui->buttDebug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));

 connect(ui->pushButtonCross, SIGNAL(clicked()), this, SLOT(on_butt_cross()));
 connect(ui->pushButtonSel, SIGNAL(clicked()), this, SLOT(on_butt_sel()));
 connect(ui->pushButtonRule, SIGNAL(clicked()), this, SLOT(on_butt_rule()));
 connect(ui->pushButtonPnt, SIGNAL(clicked()), this, SLOT(on_butt_pnt()));

 connect(ui->pushButtonGrid, SIGNAL(clicked()), this, SLOT(on_butt_grid()));
 ///==========================================================================
 connect(this, SIGNAL(s_can_connect(bool)), p_cmd_sender, SLOT(sl_connect(bool)));
 connect(p_cmd_sender, SIGNAL(s_connected(bool)), this, SLOT(sl_can_connected(bool)));
 connect(this, SIGNAL(s_set_can_com_name(QString)), p_cmd_sender, SLOT(sl_set_com_name(QString)));
 connect(p_cmd_sender, SIGNAL(s_state_changed(quint8)), this, SLOT(sl_state_changed(quint8)));
 connect(ui->sh_widget, SIGNAL(zoom_chnged(double)), this, SLOT(sl_zoom_changed(double)));


 pCamThread->start();
 ///======================================================
 scene = new PaintScene(this);       // 
 scene->setItemIndexMethod(QGraphicsScene::NoIndex); ///???
 view_sc = ui->sh_widget;
 ui->sh_widget->setScene(scene);  // 
 ui->sh_widget->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
 ui->sh_widget->setDragMode(QGraphicsView::ScrollHandDrag);
 /// GraphicsView->setStyleSheet("background: transparent;border:0px");
 ui->sh_widget->setStyleSheet("background: transparent;border:10px");

 ////ui.graphicsView->setCursor(QCursor());

 scene->setSceneRect(0, 0, 2000, 2000); //
///==================================================
 pMotorThread = new QThread(this);
 p_motor_wrk =new Cmotor_wrk(p_cmd_sender, &dev_state,&data_ready, &mot_param);
 p_motor_wrk->moveToThread(pMotorThread);
 connect(pMotorThread, SIGNAL(finished()), p_motor_wrk, SLOT(deleteLater()));
 pMotorThread->start();

 connect(this, SIGNAL(s_eeprom(int, eeprom_cmd_t)), this, SLOT(sl_eeprom(int, eeprom_cmd_t)));
 connect(this, SIGNAL(s_SendCmd(can_message_t*)), p_cmd_sender, SLOT(SlSendCmd(can_message_t*)));

 connect(this, SIGNAL(s_mot_spi(int,spi_mot_cmd_t)), p_motor_wrk, SLOT(sl_mot_spi(int,spi_mot_cmd_t)));
 connect(this, SIGNAL(s_mot_go(mot_cmd_t)), p_motor_wrk, SLOT(sl_mot_go(mot_cmd_t)));

 connect(this, SIGNAL(s_put_doza(doza_cmd_t)), p_motor_wrk, SLOT(sl_put_doza(doza_cmd_t)));

 connect(ui->butt_go_x, SIGNAL(pressed()), this, SLOT(sl_go()));
 connect(ui->butt_go_y, SIGNAL(pressed()), this, SLOT(sl_go()));
 connect(ui->butt_go_z, SIGNAL(pressed()), this, SLOT(sl_go()));

 connect(ui->butt_XMinus, SIGNAL(pressed()), this, SLOT(sl_motor_go()));
 connect(ui->butt_XPlus, SIGNAL(pressed()), this, SLOT(sl_motor_go()));
 connect(ui->butt_YMinus, SIGNAL(pressed()), this, SLOT(sl_motor_go()));
 connect(ui->butt_YPlus, SIGNAL(pressed()), this, SLOT(sl_motor_go()));
 connect(ui->butt_ZMinus, SIGNAL(pressed()), this, SLOT(sl_motor_go()));
 connect(ui->butt_ZPlus, SIGNAL(pressed()), this, SLOT(sl_motor_go()));

 ///connect(ui->butt_XMinus, SIGNAL(pressed()), this, SLOT(sl_xminus()));
 /// connect(ui->butt_XPlus, SIGNAL(pressed()), this, SLOT(sl_xplus()));
  connect(ui->butt_XMinus, SIGNAL(released()), p_motor_wrk, SLOT(sl_x_rel()));
  connect(ui->butt_XPlus, SIGNAL(released()), p_motor_wrk, SLOT(sl_x_rel()));

///connect(ui->butt_YMinus, SIGNAL(pressed()), this, SLOT(sl_yminus()));
/// connect(ui->butt_YPlus, SIGNAL(pressed()), this, SLOT(sl_yplus()));
 connect(ui->butt_YMinus, SIGNAL(released()), p_motor_wrk, SLOT(sl_y_rel()));
 connect(ui->butt_YPlus, SIGNAL(released()), p_motor_wrk, SLOT(sl_y_rel()));

 connect(ui->butt_YPlus, SIGNAL(released()), p_motor_wrk, SLOT(sl_y_rel()));

 connect(this, SIGNAL(s_key_release(int)), p_motor_wrk, SLOT(sl_axi_rel(int)));

 ///void s_key_release(int axi);


 ///connect(ui->butt_ZMinus, SIGNAL(pressed()), this, SLOT(sl_zminus()));
 ///connect(ui->butt_ZPlus, SIGNAL(pressed()), this, SLOT(sl_zplus()));
 connect(ui->butt_ZMinus, SIGNAL(released()), p_motor_wrk, SLOT(sl_z_rel()));
 connect(ui->butt_ZPlus, SIGNAL(released()), p_motor_wrk, SLOT(sl_z_rel()));

 connect(ui->butt_Doza, SIGNAL(pressed()), this, SLOT(sl_doza()));
 connect(ui->butt_Doza, SIGNAL(released()), p_motor_wrk, SLOT(sl_stop_doza()));

 connect(ui->butt_home, SIGNAL(pressed()), p_motor_wrk, SLOT(sl_go_home()));

  ///======================= upr motor ========================================
 connect(ui->butt_Stop, SIGNAL(clicked()), p_motor_wrk, SLOT(sl_stop_all()));


 connect(ui->butt_clr_x, SIGNAL(pressed()), p_motor_wrk, SLOT(sl_clr_x()));
 connect(ui->butt_clr_y, SIGNAL(pressed()), p_motor_wrk, SLOT(sl_clr_y()));
 connect(ui->butt_clr_z, SIGNAL(pressed()), p_motor_wrk, SLOT(sl_clr_z()));
 ///============ set rej motor ==========================================
 connect(ui->butt_set_x, SIGNAL(pressed()), this, SLOT(sl_set_mot_rej()));
 connect(ui->butt_set_y, SIGNAL(pressed()), this, SLOT(sl_set_mot_rej()));
 connect(ui->butt_set_z, SIGNAL(pressed()), this, SLOT(sl_set_mot_rej()));
 connect(this, SIGNAL(s_set_mot_rej(quint32, quint8, quint8)), p_motor_wrk, SLOT(sl_set_rej(quint32, quint8, quint8)));

 ////connect(ui->butt_go_x, SIGNAL(pressed()), p_motor_wrk, SLOT(cl_go_x()));
 ///connect(ui->butt_go_y, SIGNAL(pressed()), p_motor_wrk, SLOT(cl_go_y()));
 ///connect(ui->butt_go_z, SIGNAL(pressed()), p_motor_wrk, SLOT(cl_go_z()));
/// connect(ui->butt_home, SIGNAL(pressed()), p_motor_wrk, SLOT(cl_go_home()));
 connect(ui->butt_clear, SIGNAL(clicked()), this, SLOT(on_clr()));

 ///connect(scene, &PaintScene::signalPress, this, &DialLib::slShowBeg);
 connect(scene, SIGNAL(s_mouse_pos(QPointF)), this, SLOT(sl_mouse_pos(QPointF)));

 connect(scene, SIGNAL(s_show_json(QByteArray)), this, SLOT(sl_show_json(QByteArray)));
 p_ReqTimer = new QTimer();
 connect(p_ReqTimer, SIGNAL(timeout()), this, SLOT(req_timer_timeout()));
///p_ReqTimer->start(REQ_TIME_DT);
///connect(this, SIGNAL(s_send_msg(can_message_t*)), p_cmd_sender, SLOT(can_send_msg(can_message_t*)));

 }
 void win_snail::show_con_axis(void)
 {
     if (ConAxis.prev_connected_axis[XX] != ConAxis.connected_axis[XX]) {
         ConAxis.prev_connected_axis[XX] = ConAxis.connected_axis[XX];
         if(ConAxis.connected_axis[XX])
            ui->Butt_x_con->setStyleSheet("background-color: green; ");
         else
             ui->Butt_x_con->setStyleSheet("");

     }
     if (ConAxis.prev_connected_axis[YY] != ConAxis.connected_axis[YY]) {
         ConAxis.prev_connected_axis[YY] = ConAxis.connected_axis[YY];
         if (ConAxis.connected_axis[YY])
             ui->Butt_y_con->setStyleSheet("background-color: green; ");
         else
             ui->Butt_y_con->setStyleSheet("");
     }
     if (ConAxis.prev_connected_axis[ZZ] != ConAxis.connected_axis[ZZ]) {
         ConAxis.prev_connected_axis[ZZ] = ConAxis.connected_axis[ZZ];
         if (ConAxis.connected_axis[ZZ])
             ui->Butt_z_con->setStyleSheet("background-color: green; ");
         else
             ui->Butt_z_con->setStyleSheet("");
     }
     if (ConAxis.prev_connected_axis[DZ] != ConAxis.connected_axis[DZ]) {
         ConAxis.prev_connected_axis[DZ] = ConAxis.connected_axis[DZ];
         if (ConAxis.connected_axis[DZ])
             ui->Butt_doza_con->setStyleSheet("background-color: green; ");
         else
             ui->Butt_doza_con->setStyleSheet("");
     }
 }
 void win_snail::check_con_axis(void)
 {
     for (int ii = 0; ii < MAX_NUM_AXIS; ii++) {
         if (ConAxis.cnt_no_conn[ii] < MAX_CNT_CONN) {
             ConAxis.cnt_no_conn[ii]++;
         }
         else {
             ConAxis.connected_axis[ii] = false;
         }
     }
 }
 void win_snail::set_con_axis(quint8 axi)
 {
     if (axi > MAX_NUM_AXIS)
         axi = MAX_NUM_AXIS-1;
     ConAxis.cnt_no_conn[axi] =0;
     ConAxis.connected_axis[axi] = true;
 }
 void win_snail::init_con_axis(void) {
     for (int ii = 0; ii < MAX_NUM_AXIS; ii++) {
         ConAxis.cnt_no_conn[ii] = 0;
         ConAxis.prev_connected_axis[ii] = true;
         ConAxis.connected_axis[ii] = false;
}
}

 void win_snail::req_timer_timeout(void)
 {
     if (!msg_queue.isEmpty()) {
         can_message_t t_can_message;
         t_can_message = msg_queue.dequeue();
         s_SendCmd(&t_can_message);
     }
     else {
         if (cnt_req >= MAX_CNT_REQ)
         {
             cnt_req = 0;
             req_status_axis();
             ///       ConAxis.connected_axis[YY] = true;
             ///       ConAxis.prev_connected_axis[YY] = false;
             ///       set_con_axis(YY);
             check_con_axis();
             show_con_axis();
         }
         else
             cnt_req++;
     }
 }

 void win_snail::req_status_axis(void)
 {
     can_message_t t_can_message;
     t_can_message.id = X_AXIS_CAN_ID| Y_AXIS_CAN_ID|Z_AXIS_CAN_ID | DOZA_CAN_ID;
     t_can_message.dlc = 1;
     t_can_message.IDE = 0;
     t_can_message.RTR = 0;
     t_can_message.data[0] = GET_STAT_CMD;
     emit s_send_msg(&t_can_message);
 }



 void win_snail::sl_mouse_pos(QPointF pnt)
 {
     ui->lab_mouse_x->setText(QString("X=%1").arg(pnt.x()));
     ui->lab_mouse_y->setText(QString("Y=%1").arg(pnt.y()));
 }

win_snail::~win_snail()
{
 saveSettings();
 pSenderThread->quit();
 pSenderThread->wait(200);
 pCamThread->quit();
 pCamThread->wait(200);
 pMotorThread->quit();
 pMotorThread->wait(200);
 delete ui;
}
void win_snail::showConState()
{
///===============x ===========================
 quint8 change_con = prev_states[XX] ^ dev_state.states[XX];
 prev_states[XX] = dev_state.states[XX];
 if (change_con & CONC0_FLG)
    {
     if (dev_state.states[XX] & CONC0_FLG)
        {
         ui->butt_XMinus->setStyleSheet("background-color: red;");
       }
     else
        {
         ui->butt_XMinus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
        }
    }
 if (change_con & CONC1_FLG)
     {
     if (dev_state.states[XX] & CONC1_FLG)
        {
         ui->butt_XPlus->setStyleSheet("background-color: red;");
        }
     else
        {
         ui->butt_XPlus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
        }
     }
 ///================== y =====================================
change_con = prev_states[YY] ^ dev_state.states[YY];
 prev_states[YY] = dev_state.states[YY];
 if (change_con & CONC0_FLG)
    {
     if (dev_state.states[YY] & CONC0_FLG)
         {
         ui->butt_YMinus->setStyleSheet("background-color: red;");
         }
     else
        {
         ui->butt_YMinus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
        }
    }
 if (change_con & CONC1_FLG)
 {
     if (dev_state.states[YY] & CONC1_FLG)
     {
         ui->butt_YPlus->setStyleSheet("background-color: red;");
     }
     else
     {
         ui->butt_YPlus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
     }
 }
 ///================== z =====================================
 change_con = prev_states[ZZ] ^ dev_state.states[ZZ];
 prev_states[ZZ] = dev_state.states[ZZ];
 if (change_con & CONC0_FLG)
 {
     if (dev_state.states[ZZ] & CONC0_FLG)
     {
         ui->butt_ZMinus->setStyleSheet("background-color: red;");
     }
     else
     {
         ui->butt_ZMinus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
     }
 }
 if (change_con & CONC1_FLG)
    {
     if (dev_state.states[ZZ] & CONC1_FLG)
        {
         ui->butt_ZPlus->setStyleSheet("background-color: red;");
        }
     else
        {
         ui->butt_ZPlus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
        }
    }
}

void win_snail::sl_state_changed(quint8 axi)
{
    if (axi == XX) {
        ui->le_x->setText(QString::number(dev_state.coord[XX]));
        ui->lab_enc_coord_x->setText(QString::number(dev_state.Coord_enc[XX]));
        ui->lab_enc_obor_x->setText(QString::number(dev_state.obor_enc[XX]));
    }
    else if (axi == YY) {
        ui->le_y->setText(QString::number(dev_state.coord[YY]));
///        ui->lab_enc_coord_y->setText(QString::number(dev_state.Coord_enc[YY]));
        ui->lab_enc_coord_y->setText(QString::number(dev_state.coord[YY]));
        ui->lab_enc_obor_y->setText(QString::number(dev_state.obor_enc[YY]));

    }
    else if (axi == ZZ) {
        ui->le_z->setText(QString::number(dev_state.coord[ZZ]));
    }
    else if (axi == DZ) {

    }
    if (axi < NUM_AXIS) {
        set_con_axis(axi);
    }
    showConState();
}

void win_snail::timerEvent(QTimerEvent* e)
{
 ////   bool rez;
#if 0
    if (_cap.isOpened())
    {
     ////  _frame = cv::Mat::zeros(640, 480, 3); // fill zeros for debug purpose
        rez = _cap.read(_frame);
         qDebug() << "rez" << rez;
         if (rez == false)
             return;
        ////  _cap >> _frame;
             /// <param name="e"></param>
        _image = Mat2QImage(_frame);
        QPainter painter(&_image);    ////???   _label->setPixmap(QPixmap::fromImage(_image));
        painter.setPen(QPen(Qt::red, 40, Qt::SolidLine));
        painter.setFont(QFont("Arial", 20));
        ////  QRect text_rc = QRect(15, 25, 200,100);
        QRect text_rc = _image.rect();

        painter.drawText(text_rc, Qt::AlignVCenter | Qt::AlignCenter, "TEST");

        painter.end();
        emit updateCamView(_image);
    }
#endif
}

///======================================================================
void win_snail::setupActions()
{
  ////  connect(actionSet_colors, &QAction::triggered, this, SLOT(sl_setDrawProp()));
  connect(actionSet_colors, SIGNAL(triggered()), this, SLOT(sl_setDrawProp()));
  connect(actionSelect, SIGNAL(triggered()), this, SLOT(selectVideoSource()));
  connect(actionFile_Csv, SIGNAL(triggered()), this, SLOT(sl_openCsvFile()));
  connect(actionFile_Tbl, SIGNAL(triggered()), this, SLOT(sl_openTblFile()));

  connect(actionNew_prj, SIGNAL(triggered()), this, SLOT(sl_newPrj()));
  connect(actionNew_file, SIGNAL(triggered()), this, SLOT(sl_newFile()));


/*
    ui->pausevideoAct->setStatusTip(tr("Pause video"));
    connect(ui->pausevideoAct, SIGNAL(triggered(bool)), pt_qvideosource, SLOT(pause()));

    ui->resumevideoAct->setStatusTip(tr("Resume video"));
    connect(ui->resumevideoAct, SIGNAL(triggered(bool)), pt_qvideosource, SLOT(resume()));
    */
}
void win_snail::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
 ///   menu.addAction(ui->resumevideoAct);
 ///   menu.addAction(ui->pausevideoAct);
    menu.exec(event->globalPos());
 ///   menu.addSection
 ///  menu.addSeparator
}
void win_snail::selectVideoSource()
{
 QDialog dialog;
int pS = dialog.font().pointSize();
dialog.resize(40 * pS, 10 * pS);

QVBoxLayout dialogL;

QComboBox devicesCB;
QList<camera_info> devlist=p_camera->enumerator();
    
///QList<QCameraInfo> devlist = QCameraInfo::availableCameras();
#if 1
for (int i = 0; i < devlist.length(); i++)
    devicesCB.addItem(devlist.at(i).deviceName);

QHBoxLayout buttonsL;
QPushButton cancelB(tr("Cancel"));

connect(&cancelB, SIGNAL(clicked()), &dialog, SLOT(reject()));
QPushButton acceptB(tr("Accept"));
connect(&acceptB, SIGNAL(clicked()), &dialog, SLOT(accept()));
buttonsL.addWidget(&cancelB);
buttonsL.addWidget(&acceptB);

dialogL.addWidget(&devicesCB);
dialogL.addLayout(&buttonsL);

dialog.setLayout(&dialogL);
dialog.setLayout(&dialogL);

if (dialog.exec() == QDialog::Accepted) {
  ///  p_camera->start(devicesCB.currentIndex());
 ////   p_camera->m_camera = new cv::VideoCapture(devlist.at(devicesCB.currentIndex()));
    emit s_start(devicesCB.currentIndex());
 ///   delete m_camera;
 ///   m_camera = nullptr;
 ///   m_camera = new QCamera(devlist.at(devicesCB.currentIndex()));
}
#endif
 ///   pt_camera->selectDevice();
 ///   pt_camera->open();
}
void win_snail::sl_setDrawProp()
{
    qDebug() << "sl_setDrawProp";
    ViewProperties* viewProp;
    viewProp = new ViewProperties(this, this, &PlotProp);
    if (viewProp->exec())
    {
        saveSettings();
    }
  delete viewProp;
  ////  viewProp->show();
}

void win_snail::sl_openCsvFile()
{
 qDebug() << "sl_openCsvFile";
 
  csv_dlg CsvDlg(this, &snail_data);

 if (CsvDlg.exec())
 {
     qDebug() << "Ok";
 }
 else
 {
     qDebug() << "cancel";
 }
 ////ViewProperties* viewProp;
 ////viewProp = new ViewProperties(this, this, &PlotProp);
 ////viewProp->show();
}
void win_snail::sl_openTblFile()
{
    qDebug() << "sl_openTblFile";

    tbl_dlg TblDlg(this, &snail_data);

    if (TblDlg.exec())
    {
        qDebug() << "Ok";
    }
    else
    {
        qDebug() << "cancel";
    }
    ////ViewProperties* viewProp;
    ////viewProp = new ViewProperties(this, this, &PlotProp);
    ////viewProp->show();
}

#if 0
static QString getExistingDirectory(QWidget* parent = nullptr,
    const QString& caption = QString(),
    const QString& dir = QString(),
    Options options = ShowDirsOnly);
#endif
#if 0
QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
    tr("Csv Files (*.csv *.pnp)"));
#endif

void win_snail::sl_newPrj()
{
    qDebug() << "sl_newPrj";
    QString path = QFileDialog::getSaveFileName(this, tr("New project"), tr("Project files (*.dprj)")); 
    QFile file(path); /*Создаем экземпляр класса QFile*/
    if (file.open(QIODevice::WriteOnly)) /*Открываем файл в режиме только для записи. В этом с*/
    {
        QByteArray data;
        data = QString("first string").toUtf8();
       ///?? data.append(QString("second string"));
      ///???  data.append(QString("%1").arg(100));
        file.write(data); /*Записываем данные*/
        file.close(); /*Закрываем файл*/
    }
  ///  QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Dir"));

}
void win_snail::sl_newFile()
{
    qDebug() << "sl_newFile";

}

#if 0
void win_snail::createThreads()
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    p_CamView = ui->CamWidget;

    pt_camera = new MyCamera(0,&snail_data);

    connect(pt_camera, SIGNAL(frameUpdated(cv::Mat&, QImage::Format)), ui->CamWidget, SLOT(updateImage(cv::Mat&, QImage::Format)));
  ///   connect(pt_camera, SIGNAL(frameUpdated(cv::Mat&, QImage::Format)), p_CamView, SLOT(updateImage(cv::Mat&, QImage::Format)));
 
/*
    connect(ui->actionRotate, SIGNAL(triggered()), pt_qvideosource, SLOT(nextTransform()));
    connect(ui->actionResolution, SIGNAL(triggered()), pt_qvideosource, SLOT(setViewfinderSettings()));
    */
}
#endif
void win_snail::on_butt_cross()
{
/// qDebug() << "on_butt_cross";
cnf_flags ^= FLG_ON_CRS;
if(cnf_flags& FLG_ON_CRS)
    ui->pushButtonCross->setStyleSheet("background-color: green; ");
else
    ui->pushButtonCross->setStyleSheet("");
}
void win_snail::on_butt_sel()
{
  ///  qDebug() << "on_butt_sel";
    cnf_flags ^= FLG_ON_SEL;
    if (cnf_flags & FLG_ON_SEL)
        ui->pushButtonSel->setStyleSheet("background-color: green; ");
    else
        ui->pushButtonSel->setStyleSheet("");
}
void win_snail::on_butt_rule()
{
 ///   qDebug() << "on_butt_sel";
    cnf_flags ^= FLG_ON_RULE;
    if (cnf_flags & FLG_ON_RULE)
        ui->pushButtonRule->setStyleSheet("background-color: green; ");
    else
        ui->pushButtonRule->setStyleSheet("");
}

void win_snail::on_butt_grid()
{
 ///   qDebug() << "on_butt_sel";
    cnf_flags ^= FLG_ON_GRID;
    if (cnf_flags & FLG_ON_GRID)
        ui->pushButtonGrid->setStyleSheet("background-color: green; ");
    else
        ui->pushButtonGrid->setStyleSheet("");
}
void win_snail::on_butt_pnt()
{
    ///   qDebug() << "on_butt_sel";
    cnf_flags ^= FLG_ON_PNT;
    if (cnf_flags & FLG_ON_PNT)
        ui->pushButtonPnt->setStyleSheet("background-color: green; ");
    else
        ui->pushButtonPnt->setStyleSheet("");
}

///================================
void win_snail::on_butt_debug()
{
    qDebug() << "start debug" ;
    DialDebug Dial_dbg(this);
 ///   DialLib _dial_dbg(this, &PlotProp);
    Dial_dbg.ui.lineEdit_ID->setText(QString::number (params::dbg_last_can_id, 16));
    Dial_dbg.ui.lineEdit_DLC->setText(QString::number(params::dbg_last_can_dlc,16));
    Dial_dbg.ui.lineEdit_dat0->setText(QString::number(params::dbg_last_can_dat[0], 16));
    Dial_dbg.ui.lineEdit_dat1->setText(QString::number(params::dbg_last_can_dat[1], 16));
    Dial_dbg.ui.lineEdit_dat2->setText(QString::number(params::dbg_last_can_dat[2], 16));
    Dial_dbg.ui.lineEdit_dat3->setText(QString::number(params::dbg_last_can_dat[3], 16));
    Dial_dbg.ui.lineEdit_dat4->setText(QString::number(params::dbg_last_can_dat[4], 16));
    Dial_dbg.ui.lineEdit_dat5->setText(QString::number(params::dbg_last_can_dat[5], 16));
    Dial_dbg.ui.lineEdit_dat6->setText(QString::number(params::dbg_last_can_dat[6], 16));
    Dial_dbg.ui.lineEdit_dat7->setText(QString::number(params::dbg_last_can_dat[7], 16));
    Dial_dbg.show();
if(Dial_dbg.exec())
{ 
 ///   qDebug() << "OK";
    params::dbg_last_can_id= Dial_dbg.ui.lineEdit_ID->text().toInt(0, 16);
    params::dbg_last_can_dlc = Dial_dbg.ui.lineEdit_DLC->text().toInt(0, 16);
    params::dbg_last_can_dat[0] = Dial_dbg.ui.lineEdit_dat0->text().toInt(0, 16);
    params::dbg_last_can_dat[1] = Dial_dbg.ui.lineEdit_dat1->text().toInt(0, 16);
    params::dbg_last_can_dat[2] = Dial_dbg.ui.lineEdit_dat2->text().toInt(0, 16);
    params::dbg_last_can_dat[3] = Dial_dbg.ui.lineEdit_dat3->text().toInt(0, 16);
    params::dbg_last_can_dat[4] = Dial_dbg.ui.lineEdit_dat4->text().toInt(0, 16);
    params::dbg_last_can_dat[5] = Dial_dbg.ui.lineEdit_dat5->text().toInt(0, 16);
    params::dbg_last_can_dat[6] = Dial_dbg.ui.lineEdit_dat6->text().toInt(0, 16);
    params::dbg_last_can_dat[7] = Dial_dbg.ui.lineEdit_dat7->text().toInt(0, 16);
    saveSettings();
}
else
{
    qDebug() << "Cancel";

}

 ///  dial_dbg.show();
 ////   qDebug() << "end debug" ;

 ///   CsvDlg tdlg;
  ///  csv_dlg tdlg;
  /// 
  /// 
 ///   PortPropDialog tdlg;
 ////   tdlg.show();


}
void win_snail::on_butt_test()
{
    qDebug() << "start test";
 ///   DialDebug _dial_dbg(this);
    DialLib _dial_dbg(this);
    if (_dial_dbg.exec())
    {
        qDebug() << "OK";
        saveSettings();

    }
    else
    {
        qDebug() << "Cancel";
    }
}

///=====================================================
void win_snail::on_value_led0_changed(int value)
{
    hid_cmd_t t_cmd;
    t_cmd.cmd = CMD_SET_LED0;
    t_cmd.num_bytes = 2;
    t_cmd.dat[0] = value & 0xff;
    t_cmd.dat[1] = (value>>8) & 0xff;

 ///   int value = ui->lightSlider->value();
    qDebug() << "on_value_led0_changed"<< value<< t_cmd.dat[0]<< t_cmd.dat[1];

    put_hid_cmd(&t_cmd);

}
void win_snail::on_value_led1_changed(int value)
{
    hid_cmd_t t_cmd;
    t_cmd.cmd = CMD_SET_LED1;
    t_cmd.num_bytes = 2;
    t_cmd.dat[0] = value & 0xff;
    t_cmd.dat[1] = (value >> 8) & 0xff;

    ///   int value = ui->lightSlider->value();
    qDebug() << "on_value_led1_changed" << value << t_cmd.dat[0] << t_cmd.dat[1];

    put_hid_cmd(&t_cmd);

}

void win_snail::on_butt_con_hid()
{
    qDebug() << "start con";
    if (hid_handle)
        return;
    if (hid_init() == 0) {
        hid_handle = hid_open(DEF_HID_USB_VID, DEF_HID_USB_PID, NULL);
        if (!hid_handle) {
            qDebug() << "unable to open device";
            ///      return 1;
        }
    }
}
void win_snail::sl_can_connected(bool iflag)
{
  m_can_isConnected = iflag;
  if (m_can_isConnected)
    {
    ui->buttConCAN->setStyleSheet("background-color: green;");
    qDebug() << "connected " << ComPortName;
    ui->buttConCAN->setText(tr("Disconnect"));
    p_ReqTimer->start(REQ_TIME_DT);
    cnt_req = 0;

    connect(this, SIGNAL(s_send_msg(can_message_t*)), p_cmd_sender, SLOT(can_send_msg(can_message_t*)));
    }
 else
    {
      ui->buttConCAN->setText(tr("Connect"));
      ui->buttConCAN->setStyleSheet("");
      p_ReqTimer->stop();
      disconnect(this, SIGNAL(s_send_msg(can_message_t*)), p_cmd_sender, SLOT(can_send_msg(can_message_t*)));
      init_con_axis();
      show_con_axis();

    }
}
void win_snail::on_butt_con_can()
{
    qDebug() << "start can";
 if (m_can_isConnected)
    {
        emit s_can_connect(false);
    }
else
    {
        PortPropDialog* port_dialog;
        port_dialog = new PortPropDialog();
        port_dialog->SetProperties(ComPortName);

        port_dialog->show();

        if (port_dialog->exec() == QDialog::Accepted)
        {
            port_dialog->GetProperties(ComPortName);
            saveSettings();
            emit s_set_can_com_name(ComPortName);
            emit s_can_connect(true);
        }
        delete port_dialog;
    }
}
void win_snail::slot_rd_dbg(int axi, int num, dbg_dat_req_t* odat)
{
    qDebug() << "slot_rd_dbg";
   el_timer.start();

    switch (num)
    {
    case HID_REJ:
        rd_hid_dbg(odat);
        break;
    case SPI_REJ:
        qDebug() << "SPI_REJ _rd_dbg";
        spi_mot_cmd_t t_spi_mot_cmd;
        t_spi_mot_cmd.addr = odat->addr;
        t_spi_mot_cmd.cmd = RD_SPI_MOT_REQ;
        t_spi_mot_cmd.len_dat = 2;
        emit s_mot_spi(axi,t_spi_mot_cmd);
   
        break;
    case EEPROM_REJ:
    {
        qDebug() << "EEPROM_REJ _rd_dbg";
        eeprom_cmd_t t_eeprom_cmd;
        t_eeprom_cmd.addr = odat->addr;
        t_eeprom_cmd.cmd = RD_EEPROM_REQ;
        t_eeprom_cmd.num_dates = odat->nbytes;
        emit s_eeprom(axi, t_eeprom_cmd);
    }
        break;
    }
}
void win_snail::rd_hid_dbg(dbg_dat_req_t* odat)
{
    qDebug() << "rd_hid_dbg";
    unsigned char buf[256];
    memset(buf, 0, sizeof(buf));
 int   res = 0;
  int  ii = 0;
  if (hid_handle)
  {
      quint8 tmp_buf[MAX_HID_BUG + 1];

      tmp_buf[0] = 0x0;
      ///           for (int ii = 1; ii < MAX_HID_BUG; ii++)
      ////               tmp_buf[ii] = ii;
      tmp_buf[1] = 0x2;   ///cmd
      tmp_buf[2] = 1; ///numbytes
      tmp_buf[3] = 0;
      tmp_buf[4] = 0;

      int res = hid_write(hid_handle, (const unsigned char*)tmp_buf, 3);
      if (res < 0)
      {
          QString tsstr;
          ////     wchar_t tsstr[256];
          tsstr = QString::fromWCharArray(hid_error(hid_handle));

          qDebug() << "hid_write error : " << tsstr;
      }
}
  res = 0;
ii = 0;

    while (res == 0) {
        res = hid_read(hid_handle, buf, sizeof(buf));
        if (res == 0) {
            qDebug() << "waiting...";
        }
        if (res < 0) {
            qDebug() << "Unable to read(): "<< QString::fromWCharArray(hid_error(hid_handle));
            break;
        }

        ii++;
        if (ii >= 10) { /* 10 tries by 500 ms - 5 seconds of waiting*/
            qDebug() << "read() timeout";
            break;
        }
        Sleep(500);
    }
    if (res)
    {
        odat->data[0] = buf[0];
  ////      emit put_alt_dat_dial(odat);
        qDebug() << "rd data:" << buf[0] << buf[1] << buf[2] << buf[3];

    }

    /*
    device_CMD.UpdateDevice(false);
    dbg_dat_req_t dbg_req;
    dbg_req.addr = odat->addr;
    dbg_req.nbytes = odat->nbytes;
    switch (num)
    {
    case ALT_REJ:
        if (device_CMD.p_dev_thr->dev_cmd.dev_put_req_alt(&dbg_req))
        {
            if (device_CMD.p_dev_thr->dev_cmd.dev_get_alt(odat))
                emit put_alt_dat_dial(odat);
        }
        break;
    case CONTR_REJ:
        qDebug() << "CONTR_REJ" << dbg_req.addr;
        if (device_CMD.p_dev_thr->dev_cmd.dev_put_req_contr(dbg_req.addr))
        {
            if (device_CMD.p_dev_thr->dev_cmd.dev_get_contr(odat))
                emit put_alt_dat_dial(odat);
}

        break;
    }
    device_CMD.UpdateDevice(true);
    */
}
bool win_snail::put_hid_cmd(hid_cmd_t* cmd)
{
    if (hid_handle)
    {
        quint8 tmp_buf[MAX_HID_BUG + 1];
        tmp_buf[0] = 0x0;
        ///           for (int ii = 1; ii < MAX_HID_BUG; ii++)
        ////               tmp_buf[ii] = ii;
        tmp_buf[1] = cmd->cmd;   ///cmd
        tmp_buf[2] = cmd->num_bytes; ///numbytes
        if (cmd->num_bytes > MAX_DAT_CNT)
            cmd->num_bytes = MAX_DAT_CNT;
        for (int ii = 0; ii < cmd->num_bytes; ii++)
            tmp_buf[3 + ii] = cmd->dat[ii];
        int res = hid_write(hid_handle, (const unsigned char*)tmp_buf, cmd->num_bytes + 3);
        if (res < 0)
            return false;
        return true;
    }
    else
        return false;

}

void win_snail::slot_wr_dbg(int axi, int num, dbg_dat_req_t* idat)
{
    qDebug() << "slot_wr_dbg";
    switch (num)
    {
    case HID_REJ:
        if (hid_handle)
        {
            quint8 tmp_buf[MAX_HID_BUG + 1];

            tmp_buf[0] = 0x0;
 ///           for (int ii = 1; ii < MAX_HID_BUG; ii++)
 ////               tmp_buf[ii] = ii;
            tmp_buf[1] = idat->addr;   ///cmd
            tmp_buf[2] = 2; ///numbytes
            tmp_buf[3] = idat->data[0]&0xff;
            tmp_buf[4] = (idat->data[0] >>8)&0xff;

            int res=hid_write(hid_handle, (const unsigned char*)tmp_buf,5);
            if (res < 0)
            {
                QString tsstr;
           ////     wchar_t tsstr[256];
                tsstr = QString::fromWCharArray(hid_error(hid_handle));

                qDebug() << "hid_write error : " << tsstr;
            }
        }
  ///      device_CMD.p_dev_thr->dev_cmd.dev_put_alt(idat);
        break;
    case CAN_REJ:
 ///       device_CMD.p_dev_thr->dev_cmd.dev_put_contr(idat);
        break;
    case SPI_REJ:
        qDebug() << "SPI_REJ _WR_dbg";
        spi_mot_cmd_t t_spi_mot_cmd;
        t_spi_mot_cmd.addr = idat->addr;
        t_spi_mot_cmd.cmd = WR_SPI_MOT;
        t_spi_mot_cmd.len_dat = 2;
        t_spi_mot_cmd.w_val  = idat->data[0];
        emit s_mot_spi(axi,t_spi_mot_cmd);

         break;
    case EEPROM_REJ:
    {
        qDebug() << "EEPROM_REJ _wr_dbg";
        eeprom_cmd_t t_eeprom_cmd;
        t_eeprom_cmd.addr = idat->addr;
        t_eeprom_cmd.cmd = WR_EEPROM_REQ;
        t_eeprom_cmd.num_dates = 1;
        t_eeprom_cmd.data[0] = idat->data[0];
        emit s_eeprom(axi, t_eeprom_cmd);
    }
         break;

    }
}
void win_snail::slot_send_can_dbg(can_message_t* idat)
{
    bool rez;
    qDebug() << "slot_send_can_dbg :";
////???    emit s_SendCmd(idat);

 ///   rez=  m_cmd_sender->canSendMsg(idat);
/*
if(rez)
    qDebug() << "OK ";
else
   qDebug() << "BAD ";
*/
}

void win_snail::saveSettings(void)
{
    QSettings settings(QCoreApplication::applicationDirPath() + "//snail.ini",
        QSettings::IniFormat);
    settings.setValue("PortName", ComPortName);
    settings.setValue("LibPath", lib_path);

    ///================ Colors =======================================================
    settings.setValue("BackgroundColor", PlotProp.BGColor.rgb());
    settings.setValue("SelectColor", PlotProp.SelColor.rgb());
    settings.setValue("RuleColor", params::RuleColor.rgb());
    settings.setValue("CircleColor", PlotProp.CircleColor.rgb());
    settings.setValue("CrossColor", PlotProp.CrossColor.rgb());
    settings.setValue("LibBgColor", params::LibBGColor.rgb());
    settings.setValue("LibGridColor", params::LibGridColor.rgb());
    ///================ thicknesses =======================================================
    settings.setValue("Thickness select", PlotProp.thick_sel);
    settings.setValue("Thickness Rule", params::thick_rule);
    settings.setValue("Thickness circle", PlotProp.thick_circle);
    settings.setValue("Thickness cross", PlotProp.thick_crs);
    settings.setValue("Radius circle", PlotProp.rad_circle);
    ///================ Grid =======================================================
    settings.setValue("Grid X", PlotProp.setka_delt_x);
    settings.setValue("Grid Y", PlotProp.setka_delt_y);
 ///   settings.setValue("Lib Grid X", PlotProp.lib_grid_delt_x);
    settings.setValue("Lib Grid X", params::lib_grid_delt_x);
///    settings.setValue("Lib Grid Y", PlotProp.lib_grid_delt_y);
    settings.setValue("Lib Grid Y", params::lib_grid_delt_y);
    ///======== lib items ========================================
    settings.setValue("LibItemBGColor", params::LibItemBGColor.rgb());
    settings.setValue("LibItemBrdColor", params::LibItemBrdColor.rgb());
    settings.setValue("LibItemBrdThick", params::LibItemBrdThick);
    settings.setValue("LibItemWidth", params::LibItemWidth);
    settings.setValue("LibItemHeight", params::LibItemHeight);
    ///======== dbg val ========================================
    settings.setValue("last_can_id", params::dbg_last_can_id);
    settings.setValue("last_can_dlc", params::dbg_last_can_dlc);
    settings.setValue("last_can_d0", params::dbg_last_can_dat[0]);
    settings.setValue("last_can_d1", params::dbg_last_can_dat[1]);
    settings.setValue("last_can_d2", params::dbg_last_can_dat[2]);
    settings.setValue("last_can_d3", params::dbg_last_can_dat[3]);
    settings.setValue("last_can_d4", params::dbg_last_can_dat[4]);
    settings.setValue("last_can_d5", params::dbg_last_can_dat[5]);
    settings.setValue("last_can_d6", params::dbg_last_can_dat[6]);
    settings.setValue("last_can_d7", params::dbg_last_can_dat[7]);
    ///===========================geometr widg ==========================================
    //qDebug() << "saveSettings";

    QVariant variant;
    variant.setValue<QList<int>>(ui->splitter->sizes());
    settings.setValue("Splitter", variant);
  
    ///================== mot param =============================
    settings.setValue("len_step_x", mot_param.len_step[XX]);
    settings.setValue("mot_rej_x", mot_param.mot_rej[XX]);
    settings.setValue("len_step_y", mot_param.len_step[YY]);
    settings.setValue("mot_rej_y", mot_param.mot_rej[YY]);
    settings.setValue("len_step_z", mot_param.len_step[ZZ]);
    settings.setValue("mot_rej_z", mot_param.mot_rej[ZZ]);


}
void win_snail::loadSettings(void)
{
    QSettings settings(QCoreApplication::applicationDirPath() + "//snail.ini",
        QSettings::IniFormat);
    ComPortName = settings.value("PortName", "COM16").toString();
    lib_path = settings.value("LibPath", "").toString();

    ///================ Colors =======================================================
    PlotProp.BGColor.setRgb(settings.value("BackgroundColor", PlotProp.BGColor.rgb()).toInt());
    PlotProp.SelColor.setRgb(settings.value("SelectColor", PlotProp.SelColor.rgb()).toInt());
    params::RuleColor.setRgb(settings.value("RuleColor", params::RuleColor.rgb()).toInt());
    PlotProp.CircleColor.setRgb(settings.value("CircleColor", PlotProp.CircleColor.rgb()).toInt());
    PlotProp.CrossColor.setRgb(settings.value("CrossColor", PlotProp.CrossColor.rgb()).toInt());
    PlotProp.CrossColor.setRgb(settings.value("LibBgColor", params::LibBGColor.rgb()).toInt());
    PlotProp.CrossColor.setRgb(settings.value("LibGridColor", params::LibGridColor.rgb()).toInt());

    ///================ thicknesses =======================================================
    PlotProp.thick_sel= settings.value("Thickness select", 1).toInt();
    params::thick_rule = settings.value("Thickness rule", 1).toInt();
    PlotProp.thick_circle = settings.value("Thickness circle", DEF_THICK_CIRCLE).toInt();
    PlotProp.thick_crs = settings.value("Thickness cross", 1).toInt();
    PlotProp.rad_circle = settings.value("Radius circle", DEF_RAD_CIRCLE).toInt();
    ///================ Grid =======================================================
    PlotProp.setka_delt_x= settings.value("Grid X", DEF_DELT_X).toInt();
    PlotProp.setka_delt_y = settings.value("Grid Y", DEF_DELT_Y).toInt();

  /////  PlotProp.lib_grid_delt_x = settings.value("Lib Grid X", DEF_DELT_X).toInt();
    params::lib_grid_delt_x = settings.value("Lib Grid X", DEF_DELT_X).toInt();
  ///  PlotProp.lib_grid_delt_y = settings.value("Lib Grid Y", DEF_DELT_Y).toInt();
    params::lib_grid_delt_y = settings.value("Lib Grid Y", DEF_DELT_Y).toInt();
    ///======== lib items ========================================
    params::LibItemBGColor.setRgb(settings.value("LibItemBGColor", params::LibItemBGColor).toInt());
    params::LibItemBrdColor.setRgb(settings.value("LibItemBrdColor", params::LibItemBrdColor).toInt());
    params::LibItemBrdThick = settings.value("LibItemBrdThick", 1).toInt();
    params::LibItemWidth = settings.value("LibItemWidth", 100).toInt();
    params::LibItemHeight = settings.value("LibItemHeight", 50).toInt();
    ///======== dbg val ========================================
   params::dbg_last_can_id = settings.value("last_can_id", 20).toInt();
  params::dbg_last_can_dlc = settings.value("last_can_dlc", 8).toInt();
  params::dbg_last_can_dat[0] = settings.value("last_can_d0", 0).toInt();
  params::dbg_last_can_dat[1] = settings.value("last_can_d1", 0).toInt();
  params::dbg_last_can_dat[2] = settings.value("last_can_d2", 0).toInt();
  params::dbg_last_can_dat[3] = settings.value("last_can_d3", 0).toInt();
  params::dbg_last_can_dat[4] = settings.value("last_can_d4", 0).toInt();
  params::dbg_last_can_dat[5] = settings.value("last_can_d5", 0).toInt();
  params::dbg_last_can_dat[6] = settings.value("last_can_d6", 0).toInt();
  params::dbg_last_can_dat[7] = settings.value("last_can_d7", 0).toInt();
  ///===========================geometr widg ==========================================
  //qDebug() << "loadSettings";

  QList<int> default_splitter_size;
  default_splitter_size << 200 << 200;
  QVariant default_variant;
  default_variant.setValue<QList<int>>(default_splitter_size);
  splitter_sizes = settings.value("Splitter", default_variant).value<QList<int>>();
  default_variant.clear();
 
  ///================== mot param =============================
  mot_param.len_step[XX] = settings.value("len_step_x", DEF_LEN_STEP_X).toInt();
  mot_param.mot_rej[XX] = settings.value("mot_rej_x", DEF_MOT_REJ_X).toInt();
  mot_param.len_step[YY] = settings.value("len_step_y", DEF_LEN_STEP_Y).toInt();
  mot_param.mot_rej[YY] = settings.value("mot_rej_y", DEF_MOT_REJ_Y).toInt();
  mot_param.len_step[ZZ] = settings.value("len_step_z", DEF_LEN_STEP_Z).toInt();
  mot_param.mot_rej[ZZ] = settings.value("mot_rej_z", DEF_MOT_REJ_Z).toInt();

}    

///==========================================================
bool win_snail::eventFilter(QObject* obj, QEvent* event)
{
    qDebug() << "eventFilter";

    return QMainWindow::eventFilter(obj, event);

}
////label_rule
void win_snail::sl_show_rule_coord(QRect& rc)
{
 double t_len = sqrt(rc.width() * rc.width() + rc.height() * rc.height());
 QString rule_coord= QString("[Xb=%1 Yb=%2] [Xe=%3 Ye=%4][Len=%5]").arg(rc.x()).arg(rc.y()).arg(rc.x()+rc.width()).arg(rc.y()+rc.height()).arg(t_len);
ui->label_rule->setText(rule_coord);
}
///actFileNew
///horizontalLayout_menu
void win_snail::createMenus() {
    QMenuBar* menubar = menuBar();
    QMenu* menuFile = menubar->addMenu(tr("&File"));
    QMenu* menuNew = menuFile->addMenu(tr("&New"));
    QMenu* menuOpen = menuFile->addMenu(tr("&Open"));
    QMenu* menuRecent = menuFile->addMenu(tr("&Recent"));
    menuFile->addSeparator();
    actionSet_colors = new QAction("Set colors", this);
    menuFile->addAction(actionSet_colors);
    actionFile_Csv = new QAction("Open csv", this);
    menuOpen->addAction(actionFile_Csv);
    actionFile_Tbl = new QAction("Open tbl", this);
    menuOpen->addAction(actionFile_Tbl);

///====== new =======================================
    actionNew_prj= new QAction("New proj", this);
    actionNew_file = new QAction("New file", this);

    menuNew->addAction(actionNew_prj);
    menuNew->addAction(actionNew_file);

    QMenu* menuCamera = menubar->addMenu(tr("&Camera"));
    actionSelect = new QAction("Select", this);
    menuCamera->addAction(actionSelect);

    QMenu* menuHelp = menubar->addMenu(tr("&Help"));

 ////    menuFile->addAction(new QAction("Open", this));
 //////   menuFile->addAction(new QAction("Close", this));
    ///layout->setMenuBar(mainMenu);
    ui->horizontalLayout_menu->setMenuBar(menubar);
}

///=================================================================
void win_snail::setCurrentFile(const QString& fileName)
{
 curFile = fileName;
 setWindowModified(false);
 QString shownName = "Untitled";

if (!curFile.isEmpty()) {
    shownName = strippedName(curFile);
    recentFiles.removeAll(curFile);
    recentFiles.prepend(curFile);
    updateRecentFileActions();
  
    }

 ////   setWindowTitle(tr("%1[*] - %2").arg(shownName)

  ////     .arg(tr("Spreadsheet")));

 }

 QString win_snail::strippedName(const QString & fullFileName)
{
 return QFileInfo(fullFileName).fileName();
}
void win_snail::updateRecentFileActions()
{
 QMutableStringListIterator i(recentFiles);
  while (i.hasNext()) {
         if (!QFile::exists(i.next()))
            i.remove();
     }
   for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2")
                 .arg(j + 1)
                 .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
         }
    else {
         recentFileActions[j]->setVisible(false);
         }
     }

 ///separatorAction->setVisible(!recentFiles.isEmpty());

 }
void win_snail::openRecentFile()
{
 if (okToContinue()) {
        QAction * action = qobject_cast<QAction*>(sender());
  ////      if(action)
  ////          loadFile(action->data().toString());
   }
 }

bool win_snail::save()
{
if (curFile.isEmpty()) {
     return saveAs();
   }
else {
    return saveFile(curFile);
   }
}

bool win_snail::saveFile(const QString& fileName)
{
#if 0
if (!spreadsheet->writeFile(fileName)) {
       statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
      }
setCurrentFile(fileName);
statusBar()->showMessage(tr("File saved"), 2000);
#endif
return true;
}

bool win_snail::okToContinue()
{
if (isWindowModified()) {
     int r = QMessageBox::warning(this,
     tr("Spreadsheet"), tr("The document has been modified. "
     "Do you want to save your changes?"),
      QMessageBox::Yes | QMessageBox::Default,
      QMessageBox::No,
      QMessageBox::Cancel | QMessageBox::Escape);
     if (r == QMessageBox::Yes) {
        return save();
        }
     else if (r == QMessageBox::Cancel) {
         return false;
         }
    }
   return true;
}

bool win_snail::saveAs()
{
QString fileName = QFileDialog::getSaveFileName(this,
       tr("Project"),
       tr("SProject files (*.dprj)"));
if (fileName.isEmpty())
    return false;
return saveFile(fileName);
}
void win_snail::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "mousePressEvent=" << event->pos();

}
void win_snail::sl_rsv_can_dat(can_message_t msg)
{
 ///   qDebug() << "sl_rsv_dat=" <<idat;
////emit put_str_dial(idat);
///if(msg.data[0]!= PUT_ACK)

emit put_msg_dial(msg);

}
void win_snail::sl_show_json(QByteArray byteArr)
{
  component* pGroup = new component();
  scene->currentItem = pGroup;
  pGroup->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    QString jsonStr = QString(byteArr);
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArr, &err);
    if (err.error == QJsonParseError::NoError && !doc.isNull()) {
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (int index = 0; index < array.size(); index++) {
                QJsonObject ObjectValue = array.at(index).toObject().value("obj").toObject();
                QGraphicsItem* t_item = lib_util.getItem(ObjectValue);
                if (t_item != nullptr) {
                    pGroup->addToGroup(t_item);
                    ///    scene->addItem(t_item);
                }
            }
        }
    }
    scene->addItem(pGroup);
}
component* win_snail::json2component(QByteArray byteArr)
{
   component* pGroup = new component();
 /// pGroup = new component();

 ///   scene->currentItem = pGroup;
    pGroup->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    QString jsonStr = QString(byteArr);
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArr, &err);
    if (err.error == QJsonParseError::NoError && !doc.isNull()) {
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (int index = 0; index < array.size(); index++) {
                QJsonObject ObjectValue = array.at(index).toObject().value("obj").toObject();
                QGraphicsItem* t_item = lib_util.getItem(ObjectValue);
                if (t_item != nullptr) {
                    pGroup->addToGroup(t_item);
                    ///    scene->addItem(t_item);
                }
            }
        }
     return pGroup;
    }
  ///  scene->addItem(pGroup);
    return nullptr;
}

#if 0
bool win_snail::json2component(QByteArray byteArr, component& comp )
{
 ///   component* pGroup = new component();
  ///  scene->currentItem = pGroup;
    comp.setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    QString jsonStr = QString(byteArr);
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArr, &err);
    if (err.error == QJsonParseError::NoError && !doc.isNull()) {
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (int index = 0; index < array.size(); index++) {
                QJsonObject ObjectValue = array.at(index).toObject().value("obj").toObject();
                QGraphicsItem* t_item = lib_util.getItem(ObjectValue);
                if (t_item != nullptr) {
                    comp.addToGroup(t_item);
                    ///    scene->addItem(t_item);
                }
            }
        }
        return true;
    }
 ///   scene->addItem(pGroup);
    return false;
}
#endif
void win_snail::on_butt_load()
{
    qDebug() << "start load";
 ///   component* pComp = new component();
 ///   component t_comp;/// = new component();

///scene->currentItem= pGroup;

///pGroup->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

QString newPath = QFileDialog::getOpenFileName(this, tr("Open JSON"),
        lib_path, tr("JSON files (*.json)"));
if (newPath.isEmpty())
     return;
lib_path = newPath;
QFile jsonFile(lib_path);
if (!jsonFile.open(QIODevice::ReadOnly))
    {
    return;
    }
QByteArray byteArr = jsonFile.readAll();
jsonFile.close();   //

component* pComp = json2component(byteArr);

if (pComp ){
    scene->addItem(pComp);

}
/*
if (json2component(byteArr, t_comp)) {
    scene->addItem(&t_comp);
}
*/
///sl_show_json(byteArr);


#if 0
QString jsonStr = QString(byteArr);
QJsonParseError err;
QJsonDocument doc = QJsonDocument::fromJson(byteArr, &err);
if (err.error == QJsonParseError::NoError && !doc.isNull()) {
    if (doc.isArray()) {
        QJsonArray array = doc.array();
        for (int index = 0; index < array.size(); index++) {
            QJsonObject ObjectValue = array.at(index).toObject().value("obj").toObject();
            QGraphicsItem* t_item = lib_util.getItem(ObjectValue);
            if (t_item != nullptr) {
                pGroup->addToGroup(t_item);
            ///    scene->addItem(t_item);
            }
        }
    }
}
scene->addItem(pGroup);
#endif
}
static qreal t_angl = 0;
static float x_offs = 0;
static float y_offs = 0;

#if 0
switch (scene->selectedItems().at(0)->type()) {
case QGraphicsRectItem::Type: {
    ///ui.rectangleSettings->setVisible(true);
    ///ui.polylineSettings->deselect();
    ///ui.polylineSettings->setVisible(false);
    break;
}
                            cust_line* line = (cust_line*)scene->currentItem;
                            QPointF t_center = line->GetCenter();
                            QGraphicsLineItem

#endif
///=============================================
void win_snail::rotateComp(qreal angle)
{
QPointF t_center = QPointF(0, 0);
qDebug() << "currentItem->type:"<< scene->currentItem->type();

switch(scene->currentItem->type())
    {
    case QGraphicsLineItem::Type: {
        cust_line* line = (cust_line*)scene->currentItem;
        t_center = line->GetCenter();
      }
    break;

    case QGraphicsRectItem::Type: {
        qDebug() << "QGraphicsRectItem";

      }
        break;
    case QGraphicsItemGroup::Type: {
        component* comp = (component*)scene->currentItem;
        t_center = comp->GetCenter();

        qDebug() << "QGraphicsItemGroup";

    }
    break;

    }
scene->currentItem->setTransformOriginPoint(t_center);
scene->currentItem->setRotation(angle);
}

///=============================================
void win_snail::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Escape: {
        qDebug() << "Key_Escape";
        on_esc_key = true;
        }
        break;
    case Qt::Key_A: {
 ///       qDebug() << "Key_A";
 ///       scene->currentItem->moveBy(-20, 0);
        ///sl_xminus();
        }
        break;
    case Qt::Key_S: {
 ///       qDebug() << "Key_S";
///        scene->currentItem->moveBy(0, 20);
       /// sl_yminus();
       }
       break;
    case Qt::Key_W: {
 ///       qDebug() << "Key_W";
 ///       scene->currentItem->moveBy(0, -20);
       /// sl_yplus();
        }
       break;
    case Qt::Key_D: {
  ///      qDebug() << "Key_D";
   ///     scene->currentItem->moveBy(20, 0);
       /// sl_xplus();
        }
        break;
    case Qt::Key_E: {
      ///  sl_zplus();
        }
        break;
    case Qt::Key_F: {
      ///  sl_zminus();
       }
       break;

    case Qt::Key_R: {
     ///   QTransform	transform();
        t_angl -= 5.0;
        rotateComp(t_angl);
        }
        break;
    case Qt::Key_Q: {

        ///      qDebug() << "Key_D";
 ///       scene->currentItem->setTransformOriginPoint(20, 0);
 ///       scene->currentItem->setRotation(-5);
        ///       scene->currentItem->setRotation(-5);
        cust_line* line = (cust_line*)scene->currentItem;
        QPointF t_center= line->GetCenter();
        qDebug() << "line=" << line->line();
        qDebug() << "center=" << t_center;
        scene->currentItem->setTransformOriginPoint(t_center);

        QPointF pnt = scene->currentItem->transformOriginPoint();
        QPointF pos = scene->currentItem->pos();
        QPointF spos = scene->currentItem->scenePos();

        qDebug() << "pnt=" << pnt << "pos=" << pos << "spos=" << spos;
    }
    break;
    case Qt::Key_T: {
        ///      qDebug() << "Key_D";
    ///   pGroup->setTransformOriginPoint(0, 0);
        t_angl += 5.0;
        scene->currentItem->setRotation(t_angl);
  ///      scene->currentItem->rotate rotate(0);
    }
     break;
///==========================================================
    case Qt::Key_B: {

        QTransform transform;
        ///   transform.translate(offset.x(), offset.y());
        scene->currentItem->setTransformOriginPoint(20, 0);
        transform.rotate(-5);
        ////     transform.translate(-offset.x(), -offset.y());
        scene->currentItem->setTransform(transform);

    }
                  break;

    case Qt::Key_Z: {
        x_offs += 5.0;
       scene->currentItem->setTransformOriginPoint(x_offs, y_offs);
 
    }
    break;
    case Qt::Key_X: {
        x_offs -= 5.0;
        scene->currentItem->setTransformOriginPoint(x_offs, y_offs);
    }
    break;
    case Qt::Key_C: {
        y_offs += 5.0;
        scene->currentItem->setTransformOriginPoint(x_offs, y_offs);

        ///   QTransform transform;
           ///   transform.translate(offset.x(), offset.y());
        ////   transform.rotate(-5);
           ////     transform.translate(-offset.x(), -offset.y());
        ////   scene->currentItem->setTransform(transform);
    }
                  break;
    case Qt::Key_V: {
        y_offs -= 5.0;
        scene->currentItem->setTransformOriginPoint(x_offs, y_offs);

        ///   QTransform transform;
           ///   transform.translate(offset.x(), offset.y());
        ////   transform.rotate(-5);
           ////     transform.translate(-offset.x(), -offset.y());
        ////   scene->currentItem->setTransform(transform);
    }
                  break;

///=========================================================
    }

    QMainWindow::keyPressEvent(event);

}
void win_snail::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_D:
        emit s_key_release(X_AXIS_CAN_ID);
        break;
    case Qt::Key_S: 
    case Qt::Key_W:
        emit s_key_release(Y_AXIS_CAN_ID);
         break;
    case Qt::Key_E: 
    case Qt::Key_F:
        emit s_key_release(Z_AXIS_CAN_ID);
        break;
    }
 QMainWindow::keyReleaseEvent(event);
}
///==============================================
///==============================================
void win_snail::on_butt_test1()
{
 ///   req_status_axis();
/*
QPointF _center;
int num_circl = 0;
int num_gr = 0;

foreach(QGraphicsItem * item, scene->items())
{
    qDebug() << "item=" << item->type();
    switch (item->type())
    {
    case QGraphicsEllipseItem::Type:
        num_circl++;
        qDebug() << "QGraphicsEllipseItem" << num_circl;

        break;
    case QGraphicsItemGroup::Type:
        num_gr++;
        qDebug() << "QGraphicsItemGroup"<< num_gr;

        break;
    }
 ///   lib_util.insertItem(item, objObject);
 ///   arrayObj.append(objObject);
 
}


#if 0
if (p_curGroup != nullptr) {

    double radius = p_curGroup->boundingRect().width() / 2.0;
    _center = QPointF(p_curGroup->boundingRect().topLeft().x() + pos().x() + radius, p_curGroup->boundingRect().topLeft().y() + pos().y() + radius);
    ///   QPointF pos = event->scenePos();
   ///qDebug() << pGroup->boundingRect() << radius << this->pos() << pos << event->pos();
    p_curGroup->setTransformOriginPoint(_center);
}
#endif
#if 0
    qDebug() << "start test1";
    ///   cust_rect* rect = new cust_rect();
    MyItem* rect = new MyItem();

    currentItem = rect;
    scene->addItem(currentItem);
    ///connect(rect, &cust_rect::clicked, this, &LibPaintScene::signalSelectItem);
    ///connect(rect, &cust_rect::signalMove, this, &LibPaintScene::slotMove);
 ////   rect->setRect(0, 0, 35, 23);
    rect->setPos(QPoint(20, 40));
#endif
    ///   rect->setBrush(QBrush(Qt::NoBrush));
    ///   rect->setPen(QPen(Qt::red, 2));
    */
}
quint8 tmp_tst = 0;
void win_snail::on_butt_test3()
{
    scene->currentItem->setPos(40, 60);

#if 0
    tmp_tst++;
 
if (tmp_tst & 0x1)
        {
  ///  ui->butt_XMinus_2->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
    ui->butt_XMinus->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
  ///          ui->toolButton_tst->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
   ////         ui->pushButton_tst->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
    ///        ui->Butt_test3->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 128, 108);"));
        }
        else
        {
  ////          ui->butt_XMinus_2->setStyleSheet("background-color: red;");
            ui->butt_XMinus->setStyleSheet("background-color: red;");
  ///          ui->toolButton_tst->setStyleSheet("background-color: red;");
   ///         ui->pushButton_tst->setStyleSheet("background-color: red;");
  ////         ui->Butt_test3->setStyleSheet("background-color: red;");

        }
#endif
}
void win_snail::on_butt_test2()
{
 ///   quint8 mot_rej = ui->combo_rej->currentText().toInt();
///    send_cmd_mot_rej(X_AXIS_CAN_ID, mot_rej);
#if 0
    if (p_curGroup != nullptr) {
        qDebug() << "start test2" << p_curGroup->boundingRect();
        qDebug() << "pos=" << p_curGroup->pos();
///        p_curGroup->moveBy(20, 0);
    }
#endif
    ///   QRectF boundingRect()
    ///   pGroup->setTransformOriginPoint(0, 0);
    ////   pGroup->setRotation(45);
   ///    pGroup->setScale(2);
 ///   view_sc->scale(.5, .5);
  ///  scene->currentItem->moveBy(10, 10);// > setRotation(t_angl);
    scene->currentItem->setPos(60, 40);

}
///====================================================================
void win_snail::sl_go()
{
  ///  mot_cmd_t t_mot_cmd;
    int cur_coord;
    quint8 t_dir = DIR_PLUS;
    quint32 num_step;
    quint16 len_step;
    quint8 axi;
    int need_coord = ui->le_xx->text().toInt();
    if (sender() == ui->butt_go_x) {
        cur_coord = dev_state.coord[XX];
        len_step = mot_param.len_step[XX];
        need_coord = ui->le_xx->text().toInt();
        axi = X_AXIS_CAN_ID;
    }
    else if (sender() == ui->butt_go_y) {
        cur_coord = dev_state.coord[YY];
        len_step = mot_param.len_step[YY];
        need_coord = ui->le_yy->text().toInt();
        axi = Y_AXIS_CAN_ID;

    }
    else if (sender() == ui->butt_go_z) {
        cur_coord = dev_state.coord[ZZ];
        len_step = mot_param.len_step[ZZ];
        need_coord = ui->le_zz->text().toInt();
        axi = Z_AXIS_CAN_ID;
    }

    int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
    if (num_step != 0)
    {
        can_message_t t_can_message;
        t_can_message.id = axi;
        t_can_message.dlc = 8;
        t_can_message.IDE = 0;
        t_can_message.RTR = 0;
        t_can_message.data[0] = GO_CMD;
        t_can_message.data[1] = t_dir;
        t_can_message.data[2] = len_step & 0xff;
        t_can_message.data[3] = (len_step >> 8) & 0xff;
        t_can_message.data[4] = num_step & 0xff;
        t_can_message.data[5] = (num_step >> 8) & 0xff;
        t_can_message.data[6] = (num_step >> 16) & 0xff;
        t_can_message.data[7] = (num_step >> 24) & 0xff;
        msg_queue.enqueue(t_can_message);

/*
        t_mot_cmd.id = axi;
        t_mot_cmd.dir = t_dir;
        t_mot_cmd.len_step = len_step;
        t_mot_cmd.num_step = num_step;
        emit s_mot_go(t_mot_cmd);
        */
    }
}
/*
void win_snail::sl_go_x()
{
 mot_cmd_t t_mot_cmd;
int cur_coord = dev_state.coord[XX];
quint8 t_dir = DIR_PLUS;
quint32 num_step;
quint16 len_step = mot_param.len_step[XX];
int need_coord = ui->le_xx->text().toInt();
int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
if (num_step != 0)
    {
        t_mot_cmd.id = X_AXIS_CAN_ID;
        t_mot_cmd.dir = t_dir;
        t_mot_cmd.len_step = len_step;
        t_mot_cmd.num_step = num_step;
        emit s_mot_go(t_mot_cmd);
     }
}

void win_snail::sl_go_y()
{
    mot_cmd_t t_mot_cmd;
    int cur_coord = dev_state.coord[YY];
    quint8 t_dir = DIR_PLUS;
    quint32 num_step;
    quint16 len_step = mot_param.len_step[YY];/// 0;//// = ui->combo_steps->currentText().toInt();
    int need_coord = ui->le_yy->text().toInt();
    int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
    if (num_step != 0)
    {
        t_mot_cmd.id = Y_AXIS_CAN_ID;
        t_mot_cmd.dir = t_dir;
        t_mot_cmd.len_step = len_step;
        t_mot_cmd.num_step = num_step;
        emit s_mot_go(t_mot_cmd);
    }
}
void win_snail::sl_go_z()
{
    mot_cmd_t t_mot_cmd;
    int cur_coord = dev_state.coord[ZZ];
    quint8 t_dir = DIR_PLUS;
    quint32 num_step;
    quint16 len_step = mot_param.len_step[ZZ];/// 0;//// = ui->combo_steps->currentText().toInt();
    int need_coord = ui->le_zz->text().toInt();
    int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
    if (num_step != 0)
    {
        t_mot_cmd.id = Z_AXIS_CAN_ID;
        t_mot_cmd.dir = t_dir;
        t_mot_cmd.len_step = len_step;
        t_mot_cmd.num_step = num_step;
        emit s_mot_go(t_mot_cmd);
    }
}
*/
///===================================================================
 void win_snail::sl_set_mot_rej()
{
     quint8 mot_rej = ui->combo_rej->currentIndex();/// > currentText().toInt();
    quint8 mot_trq = ui->le_trq->text().toInt();

    if (sender() == ui->butt_set_x)
       {
        qDebug() << "butt_set_x ";
        emit s_set_mot_rej(X_AXIS_CAN_ID, mot_rej,mot_trq);
    }
    else if (sender() == ui->butt_set_y)
    {
        qDebug() << "butt_set_y ";
        emit s_set_mot_rej(Y_AXIS_CAN_ID, mot_rej, mot_trq);
    }
    else if (sender() == ui->butt_set_z)
    {
        qDebug() << "butt_set_z ";
        emit s_set_mot_rej(Z_AXIS_CAN_ID, mot_rej, mot_trq);
    }
       ///   send_cmd_mot_rej(X_AXIS_CAN_ID, mot_rej);

}

///=================== X ===========================
 /*
void win_snail::sl_xplus()
{
qDebug() << "sl_xplus";
el_timer.start();

///    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
 ///   send_cmd_mot_rej(X_AXIS_CAN_ID, mot_rej);
    quint16 len_step = ui->combo_steps->currentText().toInt();
    quint32 num_step = ui->combo_num_steps->currentText().toInt();
 if (num_step == 0)
        num_step = MAX_NUM_STEP;
mot_cmd_t t_mot_cmd;
t_mot_cmd.id = X_AXIS_CAN_ID;
t_mot_cmd.dir = DIR_PLUS;
t_mot_cmd.len_step = len_step;
t_mot_cmd.num_step = num_step;
emit s_mot_go(t_mot_cmd);
ui->lab_rej->setText(QString::number(mot_param.mot_rej[XX]));
 ///   send_cmd_go(X_AXIS_CAN_ID, DIR_PLUS, len_step, num_step);
}
*/
/*
void win_snail::sl_xminus()
{
 qDebug() << "sl_xminus ";
  el_timer.start();
    quint16 len_step = ui->combo_steps->currentText().toInt();
    quint32 num_step =  ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    mot_cmd_t t_mot_cmd;
    t_mot_cmd.id = X_AXIS_CAN_ID;
    t_mot_cmd.dir = DIR_MINUS;
    t_mot_cmd.len_step = len_step;
    t_mot_cmd.num_step = num_step;
    can_message_t* t_can_message = (can_message_t*) & t_mot_cmd;
    msg_queue.enqueue(*t_can_message);
 ///   emit s_mot_go(t_mot_cmd);
    ui->lab_rej->setText(QString::number(mot_param.mot_rej[XX]));

 ///   send_cmd_go(X_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);
}
*/
void win_snail::sl_motor_go()
{
    qDebug() << "sl_motor_go ";
    quint8 dir;
    quint8 axi;
    quint8 num_axi;
    int t_time;
 ///   t_time = el_timer.elapsed();
///    qDebug() << "sl_motor_go:" << t_time;
    el_timer.start();

    if (sender() == ui->butt_XMinus) {
        axi = X_AXIS_CAN_ID;
        dir = DIR_MINUS;
        num_axi = XX;
}
    else if (sender() == ui->butt_XPlus) {
        axi = X_AXIS_CAN_ID;
        dir = DIR_PLUS;
        num_axi = XX;
    }
    else if (sender() == ui->butt_YMinus) {
        axi = Y_AXIS_CAN_ID;
        dir = DIR_MINUS;
        num_axi = YY;
    }
    else if (sender() == ui->butt_YPlus) {
        axi = Y_AXIS_CAN_ID;
        dir = DIR_PLUS;
        num_axi = YY;
    }
    else if (sender() == ui->butt_ZMinus) {
        axi = Z_AXIS_CAN_ID;
        dir = DIR_MINUS;
        num_axi = ZZ;
    }
    else if (sender() == ui->butt_ZPlus) {
        axi = Z_AXIS_CAN_ID;
        dir = DIR_PLUS;
        num_axi = ZZ;
    }
    if (ConAxis.connected_axis[num_axi]) {
 ///       el_timer.start();
        quint16 len_step = ui->combo_steps->currentText().toInt();
        quint32 num_step = ui->combo_num_steps->currentText().toInt();
        if (num_step == 0)
            num_step = MAX_NUM_STEP;
        can_message_t t_can_message;
        t_can_message.id = axi;
        t_can_message.dlc = 8;
        t_can_message.IDE = 0;
        t_can_message.RTR = 0;
        t_can_message.data[0] = GO_CMD;
        t_can_message.data[1] = dir;
        t_can_message.data[2] = len_step & 0xff;
        t_can_message.data[3] = (len_step >> 8) & 0xff;
        t_can_message.data[4] = num_step & 0xff;
        t_can_message.data[5] = (num_step >> 8) & 0xff;
        t_can_message.data[6] = (num_step >> 16) & 0xff;
        t_can_message.data[7] = (num_step >> 24) & 0xff;
        msg_queue.enqueue(t_can_message);
        ///   emit s_mot_go(t_mot_cmd);
        ui->lab_rej->setText(QString::number(mot_param.mot_rej[XX]));
    }
}
    ///   send_cmd_go(X_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);

///=================== Y ===========================
/*
void win_snail::sl_yplus()
{

    qDebug() << "cl_yplus";
    el_timer.start();

///    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
///    send_cmd_mot_rej(Y_AXIS_CAN_ID, mot_rej);

    quint16 len_step =  ui->combo_steps->currentText().toInt();
    quint32 num_step =  ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    mot_cmd_t t_mot_cmd;
    t_mot_cmd.id = Y_AXIS_CAN_ID;
    t_mot_cmd.dir = DIR_PLUS;
    t_mot_cmd.len_step = len_step;
    t_mot_cmd.num_step = num_step;
    emit s_mot_go(t_mot_cmd);
    ui->lab_rej->setText(QString::number(mot_param.mot_rej[YY]));
    ///   send_cmd_go(Y_AXIS_CAN_ID, DIR_PLUS, len_step, num_step);

}
void win_snail::sl_yminus()
{

    qDebug() << "cl_yminus ";
    el_timer.start();

///    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
///    send_cmd_mot_rej(Y_AXIS_CAN_ID, mot_rej);
    quint16 len_step =  ui->combo_steps->currentText().toInt();
    quint32 num_step =  ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    mot_cmd_t t_mot_cmd;
    t_mot_cmd.id = Y_AXIS_CAN_ID;
    t_mot_cmd.dir = DIR_MINUS;
    t_mot_cmd.len_step = len_step;
    t_mot_cmd.num_step = num_step;
    emit s_mot_go(t_mot_cmd);
    ui->lab_rej->setText(QString::number(mot_param.mot_rej[YY]));
    ///    send_cmd_go(Y_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);
}
///=================== Z ===========================
void win_snail::sl_zplus()
{
    qDebug() << "cl_zplus";
 ///   quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
 ///   send_cmd_mot_rej(Z_AXIS_CAN_ID, mot_rej);
    quint16 len_step = ui->combo_steps->currentText().toInt();
    quint32 num_step = ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    mot_cmd_t t_mot_cmd;
    t_mot_cmd.id = Z_AXIS_CAN_ID;
    t_mot_cmd.dir = DIR_PLUS;
    t_mot_cmd.len_step = len_step;
    t_mot_cmd.num_step = num_step;
    emit s_mot_go(t_mot_cmd);
    ui->lab_rej->setText(QString::number(mot_param.mot_rej[ZZ]));

 ///   send_cmd_go(Z_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);

}

void win_snail::sl_zminus()
{
    qDebug() << "cl_zminus ";
 ///   quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
 ///   send_cmd_mot_rej(Z_AXIS_CAN_ID, mot_rej);
    quint16 len_step = ui->combo_steps->currentText().toInt();
    quint32 num_step = ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    mot_cmd_t t_mot_cmd;
    t_mot_cmd.id = Z_AXIS_CAN_ID;
    t_mot_cmd.dir = DIR_MINUS;
    t_mot_cmd.len_step = len_step;
    t_mot_cmd.num_step = num_step;
    emit s_mot_go(t_mot_cmd);
    ui->lab_rej->setText(QString::number(mot_param.mot_rej[ZZ]));

 ///   send_cmd_go(Z_AXIS_CAN_ID, DIR_PLUS, len_step, num_step);

}
*/
void win_snail::sl_doza()
{
    qDebug() << "cl_doza ";
    quint16 len_doza = ui->combo_len_doza->currentText().toInt();
    if (len_doza == 0)
        len_doza = MAX_LEN_DOZA;
    doza_cmd_t t_doza_cmd;
  ///  t_doza_cmd.id = DOZA_CAN_ID;
    t_doza_cmd.cmd = ON_DOZA;
     t_doza_cmd.time = len_doza;
    emit s_put_doza(t_doza_cmd);
}


///================================================================
void win_snail::on_clr()
{
    scene->clear();
    scene->update();
    ////  ui.textEdit_rd_dat->clear();
}
void win_snail::sl_eeprom(int axi, eeprom_cmd_t cmd){
    el_time = el_timer.elapsed();
    qDebug() << "sl_eeprom:" << el_time;

    can_message_t t_can_message;
    switch (axi) {
    case AXI_X:
        t_can_message.id = X_AXIS_CAN_ID;
        break;
    case AXI_Y:
        t_can_message.id = Y_AXIS_CAN_ID;
        break;
    case AXI_Z:
        t_can_message.id = Z_AXIS_CAN_ID;
        break;
 ///   case AXI_DOZA:
 ///       t_can_message.id = DOZA_CAN_ID;
 ///       break;
    default:
        return;
        break;
    }
    if(cmd.cmd== WR_EEPROM_REQ)
       t_can_message.dlc = cmd.num_dates*2 + 3;
    else
       t_can_message.dlc = cmd.num_dates * 2 + 2;

    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    memcpy(t_can_message.data, &cmd, sizeof(eeprom_cmd_t));
    data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS) {
            qDebug() << "sl_eeprom1 [wait_rdy_cnt]:" << wait_rdy_cnt;

            break;
        }
    };
    el_time = el_timer.elapsed();
    qDebug() << "sl_eeprom2:" << el_time;


}
void win_snail::sl_zoom_changed(double value)
{
    ui->lab_zoom->setText(QString("zoom=%1").arg(value));

    ///double currentScale = uitransform().m11();
    ///    qDebug() << "zoom changed:" << value;
    ///ui.lineEdit_zoom->setText(QString::number(value));
}

