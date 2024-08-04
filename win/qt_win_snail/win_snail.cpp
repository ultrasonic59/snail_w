#include "win_snail.h"
////#include "hidapi.h"
#include <QCameraInfo>
////#include "csv/csvdlg.h"
////#include "csv/csv_dlg.h"
////#include "port_prop_dialog.h"


win_snail::win_snail(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win_snail())
    , tdlg(this)
    , dial_dbg(this)
    
{
    ui->setupUi(this);
///====================================
    qRegisterMetaType<cv::Mat>("cv::Mat");
    p_CamView = ui->CamWidget;
    pt_camera = new MyCamera(0, &snail_data);
    connect(pt_camera, SIGNAL(frameUpdated(cv::Mat&, QImage::Format)), ui->CamWidget, SLOT(updateImage(cv::Mat&, QImage::Format)));
 ///===================================================
    connect(p_CamView, SIGNAL(sSetPoint(point_data_t *)), this, SLOT(slSetPoint(point_data_t*)));

 ////   createThreads();
    setupActions();
    qDebug() << QCameraInfo::availableCameras().count(); 
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

///=======================================================
  connect(ui->buttDebug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));
 connect(ui->buttConHid, SIGNAL(clicked()), this, SLOT(on_butt_con_hid()));
 connect(ui->buttConCAN, SIGNAL(clicked()), this, SLOT(on_butt_con_can()));

  connect(ui->lightSlider, SIGNAL(valueChanged(int)), this, SLOT(on_value_changed(int)));
  ///===================================================
  m_pThread = new QThread(this);
  m_cmd_sender = new CcmdSender;
  m_cmd_sender->moveToThread(m_pThread);
  connect(m_pThread, SIGNAL(finished()), m_cmd_sender, SLOT(deleteLater()));
  m_pThread->start();
  ///============================================
  wrk_Thread = new QThread(this);
 p_wrk=new Cwrk_wrk(m_cmd_sender);
 p_wrk->moveToThread(wrk_Thread);
 connect(wrk_Thread, SIGNAL(finished()), p_wrk, SLOT(deleteLater()));
 wrk_Thread->start();
 connect(this, SIGNAL(sSendCmd(can_message_t*)), p_wrk, SLOT(SlSendCmd(can_message_t *)));

///=======================================================


}

win_snail::~win_snail()
{
 saveSettings();
//// delete ui;
}
void win_snail::setCamImage(QImage ipm)
{
 ////   p_CamView->_setImage(ipm);
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
    ui->actionSelect->setStatusTip(tr("Select video source"));
    connect(ui->actionSelect, SIGNAL(triggered()), this, SLOT(__selectVideoSource()));
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
}
void win_snail::__selectVideoSource()
{
    pt_camera->selectDevice();
    pt_camera->open();
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
void win_snail::on_butt_debug()
{
    qDebug() << "start debug" ;
  ////  DialDebug dial_dbg(this);

   dial_dbg.show();
 ////   qDebug() << "end debug" ;

 ///   CsvDlg tdlg;
  ///  csv_dlg tdlg;
  /// 
  /// 
 ///   PortPropDialog tdlg;
 ////   tdlg.show();


}
void win_snail::on_value_changed(int value)
{
    hid_cmd_t t_cmd;
    t_cmd.cmd = CMD_SET_LED;
    t_cmd.num_bytes = 2;
    t_cmd.dat[0] = value & 0xff;
    t_cmd.dat[1] = (value>>8) & 0xff;

 ///   int value = ui->lightSlider->value();
    qDebug() << "on_value_changed"<< value<< t_cmd.dat[0]<< t_cmd.dat[1];

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
void win_snail::on_butt_con_can()
{
    qDebug() << "start can";
    if (m_cmd_sender->isConnected())
    {
        m_cmd_sender->disconnectToDev();
        ui->buttConCAN->setText(tr("Connect"));
        ui->buttConCAN->setStyleSheet("");
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
            m_cmd_sender->COM_port_name = ComPortName;		// 

            m_cmd_sender->connectToDev();
            if (m_cmd_sender->isConnected())
            {
                ui->buttConCAN->setStyleSheet("background-color: green;");
                qDebug() << "connected " << ComPortName;
                ui->buttConCAN->setText(tr("Disconnect"));
            }
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
    rez=  m_cmd_sender->canSendMsg(idat);
if(rez)
    qDebug() << "OK ";
else
   qDebug() << "BAD ";

}
void win_snail::saveSettings(void)
{
    QSettings settings(QCoreApplication::applicationDirPath() + "//snail.ini",
        QSettings::IniFormat);
    settings.setValue("PortName", ComPortName);
}
void win_snail::loadSettings(void)
{
    QSettings settings(QCoreApplication::applicationDirPath() + "//snail.ini",
        QSettings::IniFormat);

    ComPortName = settings.value("PortName", "COM16").toString();

}

void win_snail::slSetPoint(point_data_t* pd)
{
    qDebug() << "slSetPoint";
    snail_data.insertPoint(*pd);


}
///=================== X ===========================
void win_snail::on_cmdXPlus_pressed()
{
    qDebug() << "on_cmdXPlus_pressed";
    can_message_t t_can_message;
    t_can_message.id = 0x20;
    t_can_message.dlc = 8;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;

sSendCmd(&t_can_message);
  ////  m_jogVector += QVector3D(1, 0, 0);
  ///  jogStep();
}

void win_snail::on_cmdXPlus_released()
{
    qDebug() << "on_cmdXPlus_released";

  ////  m_jogVector -= QVector3D(1, 0, 0);
 ////   jogStep();
}

void win_snail::on_cmdXMinus_pressed()
{
    qDebug() << "on_cmdXMinus_pressed";
 ////   m_jogVector += QVector3D(-1, 0, 0);
  ////  jogStep();
}

void win_snail::on_cmdXMinus_released()
{
    qDebug() << "on_cmdXMinus_released";
    ///   m_jogVector -= QVector3D(-1, 0, 0);
    ///   jogStep();
}
bool win_snail::eventFilter(QObject* obj, QEvent* event)
{
    qDebug() << "eventFilter";

    return QMainWindow::eventFilter(obj, event);

}

///=================================================================
#if 0
QImage Mat2QImage(cv::Mat cvImg)
{
    QImage qImg = QImage();
    if (cvImg.cols == 0)
        return qImg;

    cv::cvtColor(cvImg, cvImg, COLOR_BGR2RGB); // color format conversion
////    cv::cvtColor(cvImg, cvImg, COLOR_GRAY2RGB); // color format conversion
  ////cv::cvtColor(cvImg, cvImg, COLOR_BGR2GRAY); // color format conversion
    qImg = QImage((const unsigned char*)(cvImg.data),
        cvImg.cols, cvImg.rows,
        cvImg.cols * cvImg.channels(),
        QImage::Format_RGB888);

    return qImg;
}
#endif