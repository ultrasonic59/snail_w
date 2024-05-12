#pragma once

#include <QtWidgets/QMainWindow>
////#include <QCamera>

#include "PlotterWidget.h"
#include "ui_win_snail.h"
///======================================================================
#include <opencv2/opencv.hpp>
#include "hidapi.h"
#include "dial_debug.h"

#include "my_camera.h"
#define MAX_HID_BUG                     16
#define DEF_HID_USB_VID                  0x1A86
#define DEF_HID_USB_PID                  0xFE07

QT_BEGIN_NAMESPACE
namespace Ui { class win_snail; };
QT_END_NAMESPACE

using namespace cv;

class win_snail : public QMainWindow
{
    Q_OBJECT

public:
    win_snail(QWidget *parent = nullptr);
    ~win_snail();
public:
 ////   plotterwidget* p_CamView;
private:
    QLabel* _label;
    QPen pen;

 ////   VideoCapture _cap;
    int frame_width;
    int frame_height;
   Mat _frame;
    QImage    _image;
   hid_device* hid_handle;
 ///   struct hid_device_info* devs;
  ///struct hid_device_info* cur_dev;

public slots:
    void setCamImage(QImage ipm);

protected:
    void timerEvent(QTimerEvent* e);

private:
    Ui::win_snail *ui;
private:
  ////  QCamera* pt_qcam;
    MyCamera *pt_camera;
protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void setupActions();
    void createThreads();
protected:
    DialDebug dial_dbg;
public slots:
    void on_butt_con();
    ///===== for debug =======
    void on_butt_debug();
    void slot_rd_dbg(int num, dbg_dat_req_t* odat);
    void slot_wr_dbg(int num, dbg_dat_req_t* idat);

private slots:
    void __selectVideoSource();

signals:
    void updateCamView(QImage);

};
