#include "win_snail.h"
///#include <QCameraInfo>
#include "ViewProperties.h"
#include <QColorDialog>
#include <QtScript/QScriptValue>

#include "dial_lib.h"
#include "params.h"

win_snail::win_snail(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win_snail())
    , cnf_flags(0)
    ,xminusPushed(false)
    ,xminusLongPush(false)
    ,yminusPushed(false)
    ,yminusLongPush(false)
    ,zminusPushed(false)
    ,zminusLongPush(false)
    , m_can_isConnected(false)

  {
    ui->setupUi(this);
///====================================
  qRegisterMetaType<cv::Mat>("cv::Mat");
 
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
connect(ui->ButtonTest, SIGNAL(clicked()), this, SLOT(on_butt_test()));

 connect(ui->buttDebug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));
 connect(ui->buttConHid, SIGNAL(clicked()), this, SLOT(on_butt_con_hid()));
 ///==================CAN =============================================
 connect(ui->buttConCAN, SIGNAL(clicked()), this, SLOT(on_butt_con_can()));

  connect(ui->lightSlider0, SIGNAL(valueChanged(int)), this, SLOT(on_value_led0_changed(int)));
  connect(ui->lightSlider1, SIGNAL(valueChanged(int)), this, SLOT(on_value_led1_changed(int)));
  ///===================================================
  m_pThread = new QThread(this);
  m_cmd_sender = new CcmdSender;
  m_cmd_sender->moveToThread(m_pThread);
  connect(m_pThread, SIGNAL(finished()), m_cmd_sender, SLOT(deleteLater()));
  m_pThread->start();
  connect(this, SIGNAL(s_SendCmd(can_message_t*)), m_cmd_sender, SLOT(SlSendCmd(can_message_t*)));
  connect(m_cmd_sender, SIGNAL(s_rsv_can_dat(char*)), this, SLOT(sl_rsv_can_dat(char*)));

  ///============================================
 wrk_Thread = new QThread(this);
 p_wrk=new Cwrk_wrk(m_cmd_sender);
 p_wrk->moveToThread(wrk_Thread);
 connect(wrk_Thread, SIGNAL(finished()), p_wrk, SLOT(deleteLater()));
 wrk_Thread->start();
 ////connect(this, SIGNAL(s_SendCmd(can_message_t*)), p_wrk, SLOT(SlSendCmd(can_message_t *)));

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


   connect(p_CamView, SIGNAL(sel_rect_changet(QRect)), p_cam_plotter, SLOT(sl_set_sel_rect(QRect)), Qt::QueuedConnection);
   connect(p_cam_plotter, SIGNAL(s_show_rule_coord(QRect&)), this, SLOT(sl_show_rule_coord(QRect&)));

 connect(pCamThread, SIGNAL(finished()), p_cam_plotter, SLOT(deleteLater()));
 ///connect(ui->buttDebug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));

 connect(ui->pushButtonCross, SIGNAL(clicked()), this, SLOT(on_butt_cross()));
 connect(ui->pushButtonSel, SIGNAL(clicked()), this, SLOT(on_butt_sel()));
 connect(ui->pushButtonRule, SIGNAL(clicked()), this, SLOT(on_butt_rule()));
 connect(ui->pushButtonPnt, SIGNAL(clicked()), this, SLOT(on_butt_pnt()));

 connect(ui->pushButtonGrid, SIGNAL(clicked()), this, SLOT(on_butt_grid()));
 ///======================= upr motor ========================================
 connect(ui->butt_Stop, SIGNAL(clicked()), this, SLOT(cl_stop()));

 connect(ui->butt_XMinus, SIGNAL(clicked()), this, SLOT(cl_xminus()));
 connect(ui->butt_XMinus, SIGNAL(released()), this, SLOT(cl_xminus_rel()));
 connect(ui->butt_XPlus, SIGNAL(clicked()), this, SLOT(cl_xplus()));
 connect(ui->butt_XPlus, SIGNAL(released()), this, SLOT(cl_xplus_rel()));

 connect(ui->butt_YMinus, SIGNAL(pressed()), this, SLOT(cl_yminus()));
 connect(ui->butt_YMinus, SIGNAL(released()), this, SLOT(cl_yminus_rel()));
 connect(ui->butt_YPlus, SIGNAL(pressed()), this, SLOT(cl_yplus()));
 connect(ui->butt_YPlus, SIGNAL(released()), this, SLOT(cl_yplus_rel()));

 connect(ui->butt_ZMinus, SIGNAL(clicked()), this, SLOT(cl_zminus()));
 connect(ui->butt_ZMinus, SIGNAL(released()), this, SLOT(cl_zminus_rel()));
 connect(ui->butt_ZPlus, SIGNAL(clicked()), this, SLOT(cl_zplus()));
 connect(ui->butt_ZPlus, SIGNAL(released()), this, SLOT(cl_zplus_rel()));
 ///==========================================================================
 connect(this, SIGNAL(s_can_connect(bool)), m_cmd_sender, SLOT(sl_connect(bool)));
 connect(m_cmd_sender, SIGNAL(s_connected(bool)), this, SLOT(sl_can_connected(bool)));
 connect(this, SIGNAL(s_set_can_com_name(QString)), m_cmd_sender, SLOT(sl_set_com_name(QString)));

 pCamThread->start();


}

win_snail::~win_snail()
{
 saveSettings();
 m_pThread->quit();
 m_pThread->wait(200);
 pCamThread->quit();
 pCamThread->wait(200);
 wrk_Thread->quit();
 wrk_Thread->wait(200);
 delete ui;
}
#if 0
void win_snail::setCamImage(QImage ipm)
{
 ////   p_CamView->_setImage(ipm);
}
#endif
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
  connect(actionNew_prj, SIGNAL(triggered()), this, SLOT(sl_newPrj()));
  connect(actionNew_file, SIGNAL(triggered()), this, SLOT(sl_newFile()));


///====    actionFile_csv ========
#if 0
    ui->actionFile_csv->setStatusTip(tr("Open csv file"));
    connect(ui->actionFile_csv, SIGNAL(triggered()), this, SLOT(sl_openCsvFile()));

    ui->actionSelect->setStatusTip(tr("Select video source"));
    connect(ui->actionSelect, SIGNAL(triggered()), this, SLOT(__selectVideoSource()));

    connect(ui->actionSet_colors, SIGNAL(triggered()), this, SLOT(sl_setDrawProp()));
#endif
 ////  ui->
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
  csv_dlg CsvDlg(this);

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
    DialDebug _dial_dbg(this);
 ///   DialLib _dial_dbg(this, &PlotProp);
if(_dial_dbg.exec())
{ 
    qDebug() << "OK";

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
    }
 else
    {
      ui->buttConCAN->setText(tr("Connect"));
      ui->buttConCAN->setStyleSheet("");
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
void win_snail::slot_rd_dbg(int num, dbg_dat_req_t* odat)
{
    qDebug() << "slot_rd_dbg";
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

void win_snail::slot_wr_dbg(int num, dbg_dat_req_t* idat)
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
    }

    /*
    device_CMD.UpdateDevice(false);
    switch (num)
    {
    case ALT_REJ:
        device_CMD.p_dev_thr->dev_cmd.dev_put_alt(idat);
        break;
    case CONTR_REJ:
        device_CMD.p_dev_thr->dev_cmd.dev_put_contr(idat);
        break;
    }
    device_CMD.UpdateDevice(true);
    */
}
void win_snail::slot_send_can_dbg(can_message_t* idat)
{
    bool rez;
    qDebug() << "slot_send_can_dbg :";
    emit s_SendCmd(idat);
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

}
void win_snail::loadSettings(void)
{
    QSettings settings(QCoreApplication::applicationDirPath() + "//snail.ini",
        QSettings::IniFormat);

    ComPortName = settings.value("PortName", "COM16").toString();
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


}    

/// /==============================================================
void win_snail::cl_stop()
{

}
///=================== X ===========================
void win_snail::SlotLongPush_xminus()
{
#if 0
    quint16 t_speed = MAX_SPEED / 2;
    if (LeftButPushed)
    {
        LeftLongPush = true;
        ///		t_speed = Params::calc_speed_mot((p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed * Params::debug_speed) / 100);	///%
           ////	qDebug() << "Fwd slow speed" <<t_freq;
        ////		udp_put_motor_cmd_go(DIR_UP, t_speed);
        emit s_put_motor(DIR_UP, t_speed);

    }
#endif
}
void win_snail::SlotLongPush_xplus()
{
#if 0
    quint16 t_speed = MAX_SPEED / 2;
    if (LeftButPushed)
    {
        LeftLongPush = true;
        ///		t_speed = Params::calc_speed_mot((p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed * Params::debug_speed) / 100);	///%
           ////	qDebug() << "Fwd slow speed" <<t_freq;
        ////		udp_put_motor_cmd_go(DIR_UP, t_speed);
        emit s_put_motor(DIR_UP, t_speed);

    }
#endif
}

void win_snail::cl_xplus()
{
    qDebug() << "cl_xplus";
    can_message_t t_can_message;
    t_can_message.id = X_AXIS_CAN_ID;
    t_can_message.dlc = 8;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;

    emit s_SendCmd(&t_can_message);
  ////  m_jogVector += QVector3D(1, 0, 0);
  ///  jogStep();
}

void win_snail::cl_xplus_rel()
{
    qDebug() << "cl_xplus_rel";

  ////  m_jogVector -= QVector3D(1, 0, 0);
 ////   jogStep();
}

void win_snail::cl_xminus()
{
    qDebug() << "cl_xminus ";
    ///	if (OnMotor)
    ///		return;
  ///  quint16 t_speed = MAX_SPEED / 2;
    xminusPushed = true;
    xminusLongPush = false;
    QTimer::singleShot(LONG_PUSH_TIME, this, SLOT(SlotLongPush_xminus()));
    ///	t_speed = Params::calc_speed_mot(p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed);	///100%
    ///	udp_put_motor_cmd_go(DIR_UP, t_speed);
  ///  emit s_put_motor(DIR_UP, t_speed);
 ///   OnMotor = true;
}
void win_snail::cl_xminus_rel()
{
    qDebug() << "cl_xminus_rel ";
    xminusPushed = false;
    if (xminusLongPush)
    {
        ///       emit s_put_motor(DIR_UP, 0);

               ///		udp_put_motor_cmd_stop();
        ///       OnMotor = false;
               ////	qDebug() << "Fwd stop" ;
    }
}
///=================== Y ===========================
void win_snail::SlotLongPush_yminus()
{
#if 0
    quint16 t_speed = MAX_SPEED / 2;
    if (LeftButPushed)
    {
        LeftLongPush = true;
        ///		t_speed = Params::calc_speed_mot((p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed * Params::debug_speed) / 100);	///%
           ////	qDebug() << "Fwd slow speed" <<t_freq;
        ////		udp_put_motor_cmd_go(DIR_UP, t_speed);
        emit s_put_motor(DIR_UP, t_speed);

    }
#endif
}
void win_snail::SlotLongPush_yplus()
{
#if 0
    quint16 t_speed = MAX_SPEED / 2;
    if (LeftButPushed)
    {
        LeftLongPush = true;
        ///		t_speed = Params::calc_speed_mot((p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed * Params::debug_speed) / 100);	///%
           ////	qDebug() << "Fwd slow speed" <<t_freq;
        ////		udp_put_motor_cmd_go(DIR_UP, t_speed);
        emit s_put_motor(DIR_UP, t_speed);

    }
#endif
}

void win_snail::cl_yplus()
{
    quint16 len_step = 40;
    quint32 num_step = 400;

    qDebug() << "cl_yplus";
    can_message_t t_can_message;
    t_can_message.id = Y_AXIS_CAN_ID;
    t_can_message.dlc = 8;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = GO_CMD;
    t_can_message.data[1] = DIR_PLUS;
    t_can_message.data[2] = len_step&0xff;
    t_can_message.data[3] = (len_step>>8) & 0xff;
    t_can_message.data[4] = num_step  & 0xff;
    t_can_message.data[5] = (num_step >> 8) & 0xff;
    t_can_message.data[6] = (num_step >> 16) & 0xff;
    t_can_message.data[7] = (num_step >> 24) & 0xff;
    emit s_SendCmd(&t_can_message);
    ////  m_jogVector += QVector3D(1, 0, 0);
    ///  jogStep();
}

void win_snail::cl_yplus_rel()
{
    qDebug() << "cl_yplus_rel";

    ////  m_jogVector -= QVector3D(1, 0, 0);
   ////   jogStep();
}

void win_snail::cl_yminus()
{
quint16 len_step = 40;
quint32 num_step = 400;

  qDebug() << "cl_yminu ";
 can_message_t t_can_message;
 t_can_message.id = Y_AXIS_CAN_ID;
 t_can_message.dlc = 8;
 t_can_message.IDE = 0;
 t_can_message.RTR = 0;
 t_can_message.data[0] = GO_CMD;
 t_can_message.data[1] = DIR_MINUS;
 t_can_message.data[2] = len_step & 0xff;
 t_can_message.data[3] = (len_step >> 8) & 0xff;
 t_can_message.data[4] = num_step & 0xff;
 t_can_message.data[5] = (num_step >> 8) & 0xff;
 t_can_message.data[6] = (num_step >> 16) & 0xff;
 t_can_message.data[7] = (num_step >> 24) & 0xff;
 emit s_SendCmd(&t_can_message);

    xminusPushed = true;
    xminusLongPush = false;
    QTimer::singleShot(LONG_PUSH_TIME, this, SLOT(SlotLongPush_yminus()));

}
void win_snail::cl_yminus_rel()
{
    qDebug() << "cl_yminus_rel ";
    xminusPushed = false;
    if (xminusLongPush)
    {
        ///       emit s_put_motor(DIR_UP, 0);

               ///		udp_put_motor_cmd_stop();
        ///       OnMotor = false;
               ////	qDebug() << "Fwd stop" ;
    }
}

///=================== Z ===========================
void win_snail::SlotLongPush_zminus()
{
#if 0
    quint16 t_speed = MAX_SPEED / 2;
    if (LeftButPushed)
    {
        LeftLongPush = true;
        ///		t_speed = Params::calc_speed_mot((p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed * Params::debug_speed) / 100);	///%
           ////	qDebug() << "Fwd slow speed" <<t_freq;
        ////		udp_put_motor_cmd_go(DIR_UP, t_speed);
        emit s_put_motor(DIR_UP, t_speed);

    }
#endif
}
void win_snail::SlotLongPush_zplus()
{
#if 0
    quint16 t_speed = MAX_SPEED / 2;
    if (LeftButPushed)
    {
        LeftLongPush = true;
        ///		t_speed = Params::calc_speed_mot((p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed * Params::debug_speed) / 100);	///%
           ////	qDebug() << "Fwd slow speed" <<t_freq;
        ////		udp_put_motor_cmd_go(DIR_UP, t_speed);
        emit s_put_motor(DIR_UP, t_speed);

    }
#endif
}
void win_snail::cl_zplus()
{
    qDebug() << "cl_zplus";
    can_message_t t_can_message;
    t_can_message.id = 0x20;
    t_can_message.dlc = 8;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;

    emit s_SendCmd(&t_can_message);
    ////  m_jogVector += QVector3D(1, 0, 0);
    ///  jogStep();
}

void win_snail::cl_zplus_rel()
{
    qDebug() << "cl_zplus_rel";

    ////  m_jogVector -= QVector3D(1, 0, 0);
   ////   jogStep();
}

void win_snail::cl_zminus()
{
    qDebug() << "cl_zminus ";
    ///	if (OnMotor)
    ///		return;
  ///  quint16 t_speed = MAX_SPEED / 2;
    xminusPushed = true;
    xminusLongPush = false;
    QTimer::singleShot(LONG_PUSH_TIME, this, SLOT(SlotLongPush_zminus()));
    ///	t_speed = Params::calc_speed_mot(p_dev_data->curr_par_session.par_dev.controller_par.wrk_speed);	///100%
    ///	udp_put_motor_cmd_go(DIR_UP, t_speed);
  ///  emit s_put_motor(DIR_UP, t_speed);
 ///   OnMotor = true;
}
void win_snail::cl_zminus_rel()
{
    qDebug() << "cl_zminus_rel ";
    xminusPushed = false;
    if (xminusLongPush)
    {
        ///       emit s_put_motor(DIR_UP, 0);

               ///		udp_put_motor_cmd_stop();
        ///       OnMotor = false;
               ////	qDebug() << "Fwd stop" ;
    }
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

void win_snail::sl_rsv_can_dat(char* idat)
{
 ///   qDebug() << "sl_rsv_dat=" <<idat;
emit put_str_dial(idat);

}
