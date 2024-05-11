#include "win_snail.h"
////#include "hidapi.h"
#include <QCameraInfo>

////QImage Mat2QImage(cv::Mat cvImg);

win_snail::win_snail(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win_snail())
    , dial_dbg(this)
    
{
    ui->setupUi(this);
    createThreads();
    setupActions();
    qDebug() << QCameraInfo::availableCameras().count(); 
    int camid = 0; // video device id
#if 0
    if (hid_init() == 0)
        {
        devs = hid_enumerate(0x0, 0x0);
        cur_dev = devs;
        while (cur_dev) {
     ///      qDebug()<<"Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number;
     ///       qDebug("\n");
            qDebug()<<"  Manufacturer: " << cur_dev->manufacturer_string;
            qDebug() << "  Product:      "<< cur_dev->product_string;
            qDebug() << "  Release:      "<< cur_dev->release_number;
            qDebug() << "  Interface:    "<< cur_dev->interface_number;
              cur_dev = cur_dev->next;
        }
        hid_free_enumeration(devs);
         }
#endif
#if 1
    if (hid_init() == 0) {
        hid_handle = hid_open(DEF_HID_USB_VID, DEF_HID_USB_PID, NULL);
        if (!hid_handle) {
            qDebug() << "unable to open device";
            ///      return 1;
        }
    }
#endif
#if 0
    if (!_cap.open(camid))
    {
        qDebug() << "camera open failed.";
        return;
    }
   int fps = _cap.get(cv::CAP_PROP_FPS);
   qDebug() << "fps"<< fps;

frame_width = _cap.get(cv::CAP_PROP_FRAME_WIDTH);
 qDebug() << "frame_width" << frame_width;
frame_height = _cap.get(cv::CAP_PROP_FRAME_HEIGHT);
 qDebug() << "frame_height" << frame_height;


    p_CamView = ui->CamWidget;
    connect(this, SIGNAL(updateCamView(QImage)), this, SLOT(setCamImage(QImage)));
    startTimer(100);
#endif
///=======================================================
  connect(ui->buttDebug, SIGNAL(clicked()), this, SLOT(on_butt_debug()));
  connect(ui->buttCon, SIGNAL(clicked()), this, SLOT(on_butt_con()));

///=======================================================

}

win_snail::~win_snail()
{
    delete ui;
}
void win_snail::setCamImage(QImage ipm)
{
    p_CamView->_setImage(ipm);
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
 ///   pt_qvideosource->open();
}
void win_snail::createThreads()
{
 ////   qRegisterMetaType<cv::Mat>("cv::Mat");

    pt_camera = new MyCamera;
/*
    connect(pt_qvideosource, SIGNAL(frameUpdated(cv::Mat, QImage::Format)), ui->displayW, SLOT(updateImage(cv::Mat, QImage::Format)));
    connect(ui->actionRotate, SIGNAL(triggered()), pt_qvideosource, SLOT(nextTransform()));
    connect(ui->actionResolution, SIGNAL(triggered()), pt_qvideosource, SLOT(setViewfinderSettings()));
    */
}
void win_snail::on_butt_debug()
{
    qDebug() << "start debug" ;
    dial_dbg.show();
 ////   qDebug() << "end debug" ;

}
void win_snail::on_butt_con()
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


 ///   dial_dbg.show();
 ///   qDebug() << "end debug";

}
void win_snail::slot_rd_dbg(int num, dbg_dat_req_t* odat)
{
    qDebug() << "slot_rd_dbg";
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

void win_snail::slot_wr_dbg(int num, dbg_dat_req_t* idat)
{
    qDebug() << "slot_wr_dbg";
    switch (num)
    {
    case HID_REJ:
        if (hid_handle)
        {
            quint8 tmp_buf[MAX_HID_BUG + 1];
            tmp_buf[0] = 0;
            tmp_buf[1] = idat->data[0];
            hid_write(hid_handle, tmp_buf, 2);
            qDebug() << "hid_write"<< tmp_buf[1];

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