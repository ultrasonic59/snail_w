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
#include "hid_cmd.h"
#include "port_prop_dialog.h"
#include "cmd_sender.h"
#include "csv/csv_dlg.h"
#include "snail_data.h"
#include "wrk_wrk.h"

///======================================================================

#define MAX_HID_BUG                     64
////#define DEF_HID_USB_VID                  0x1A86
////#define DEF_HID_USB_PID                  0xFE07
////#define DEF_HID_USB_PID                  0x5537
///#define DEF_HID_USB_PID                  0xFE00
///#define DEF_HID_USB_VID                 0x04d9/// 0x0483
///#define DEF_HID_USB_PID                 0x1503 /// 0x5711
#define DEF_HID_USB_VID                 0x04d8/// 0x0483
#define DEF_HID_USB_PID                 0x900a /// 0x5711


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
    plotterwidget* p_CamView;
    hid_device* hid_handle;
    quint16 setka_delt_x;
    quint16 setka_delt_y;

public:
    c_snail_data snail_data;
 ///   Mat  mat_cam;
    Mat  mat_setka;
    Mat  mat_lines;

private:
    QLabel* _label;
    QPen pen;

 ////   VideoCapture _cap;
    int frame_width;
    int frame_height;
   Mat _frame;
    QImage    _image;
 ///  hid_device* hid_handle;
    struct hid_device_info* devs;
  struct hid_device_info* cur_dev;
private:
    QThread* m_pThread;
    QThread* wrk_Thread;
    CcmdSender* m_cmd_sender;
    Cwrk_wrk* p_wrk;

public slots:
    void setCamImage(QImage ipm);
    void slSetPoint(point_data_t *pd);
    void slClrPoint(QPoint* pn);
    void slMovePoint(point_data_t* pd);

protected:
    void timerEvent(QTimerEvent* e);
    QPoint last_pn;
private:
    Ui::win_snail *ui;
private:
  ////  QCamera* pt_qcam;
    MyCamera *pt_camera;
protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void setupActions();
 ////   void createThreads();
    bool put_hid_cmd(hid_cmd_t* cmd);

    void saveSettings(void);
    void loadSettings(void);
 ////   void verify_data(void);
    QString ComPortName;

protected:
    DialDebug dial_dbg;
       csv_dlg tdlg;
private :
    bool eventFilter(QObject* obj, QEvent* event);

public slots:
    void on_butt_con_hid();
    void on_butt_con_can();
    ///===== for debug =======
    void on_value_changed(int value);
    void on_butt_debug();
    void slot_rd_dbg(int num, dbg_dat_req_t* odat);
    void slot_wr_dbg(int num, dbg_dat_req_t* idat);
    void slot_send_can_dbg(can_message_t* idat);

private slots:
    void __selectVideoSource();
private slots:
    void on_cmdXPlus_pressed();
    void on_cmdXPlus_released();
    void on_cmdXMinus_pressed();
    void on_cmdXMinus_released();


signals:
    void updateCamView(QImage);
    void sSendCmd(can_message_t* msg);

};
