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
#include "CamPlotter.h"

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

////#define DEF_DELT_X 10
///#define DEF_DELT_Y 10

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
    hid_device* hid_handle;
private:
    struct hid_device_info* devs;
    struct hid_device_info* cur_dev;
protected:
    bool put_hid_cmd(hid_cmd_t* cmd);

public:
    plotterwidget* p_CamView;
    ///quint16 setka_delt_x;
    ///quint16 setka_delt_y;
    CamPlotter* p_cam_plotter;
    PlotProperties PlotProp;
    quint32 cnf_flags;
private:
    QThread* pCamThread;

public:
    c_snail_data snail_data;
 ///   Mat  mat_cam;
///    Mat  mat_setka;
///    Mat  mat_lines;

private:
    QLabel* _label;
    QPen pen;

 ////   VideoCapture _cap;
    int frame_width;
    int frame_height;
   Mat _frame;
    QImage    _image;
 ///  hid_device* hid_handle;
private:
    QThread* m_pThread;
    QThread* wrk_Thread;
    CcmdSender* m_cmd_sender;
    Cwrk_wrk* p_wrk;
    ////QPoint getMouseInsideCoord(QPoint inPos);
////public slots:
////    void setCamImage(QImage ipm);
 
protected:
    void timerEvent(QTimerEvent* e);
    QPoint last_pn;
    QRect sel_rc;
private:
    Ui::win_snail *ui;
private:
  ////  QCamera* pt_qcam;
    MyCamera *pt_camera;
protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void setupActions();
 ////   void createThreads();

    void saveSettings(void);
    void loadSettings(void);
 ////   void verify_data(void);
    QString ComPortName;

protected:
////    DialDebug dial_dbg;
  ////     csv_dlg CsvDlg;
private :
    bool eventFilter(QObject* obj, QEvent* event);
    void createMenus();
private:
    QAction* actionProj;
    QAction* actionFile;
    QAction* actionSelect;
    QAction* actionFile_Csv;
    QAction* actionSet_colors;
    QAction* actionNew_prj;
    QAction* actionNew_file;
    QAction* separatorAction;
public:

private:
    QStringList recentFiles;
    QString curFile;
    enum { MaxRecentFiles = 5 };
    QAction * recentFileActions[MaxRecentFiles];
    QString strippedName(const QString& fullFileName);
    void setCurrentFile(const QString& fileName);
    void updateRecentFileActions();

public slots:
    void on_butt_con_hid();
    void on_butt_con_can();
    ///===== for debug =======
    void on_value_led0_changed(int value);
    void on_value_led1_changed(int value);
    void on_butt_debug();
    void slot_rd_dbg(int num, dbg_dat_req_t* odat);
    void slot_wr_dbg(int num, dbg_dat_req_t* idat);
    void slot_send_can_dbg(can_message_t* idat);
    void on_butt_test();

private slots:
    void __selectVideoSource();
private slots:
    void on_cmdXPlus_pressed();
    void on_cmdXPlus_released();
    void on_cmdXMinus_pressed();
    void on_cmdXMinus_released();
    void sl_show_rule_coord(QRect& rc);
    void sl_setDrawProp();
    void sl_openCsvFile();
    void sl_newPrj();
    void sl_newFile();

    void on_butt_cross();
    void on_butt_sel();
    void on_butt_rule();
    void on_butt_grid();
    void on_butt_pnt();
    void openRecentFile();
    bool save();
    bool saveFile(const QString& fileName);
    bool okToContinue();
    bool saveAs();


signals:
    void updateCamView(QImage);
    void sSendCmd(can_message_t* msg);

};
