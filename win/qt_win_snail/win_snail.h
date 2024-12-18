#pragma once

#include <QtWidgets/QMainWindow>
#include <QSvgGenerator>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QMessageBox>

////#include <QCamera>
///#include <QCameraInfo>

#include "PlotterWidget.h"
#include "ui_win_snail.h"
///======================================================================
#include <opencv2/opencv.hpp>
#include "hidapi.h"
#include "dial_debug.h"

///#include "my_camera.h"
#include "hid_cmd.h"
#include "port_prop_dialog.h"
#include "cmd_sender.h"
#include "csv/csv_dlg.h"
#include "snail_data.h"
#include "wrk_wrk.h"
#include "CamPlotter.h"
#include "cameradevice.h"
#include "lib_paint_scene.h"
#include "myitem.h"
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

#define LONG_PUSH_TIME	500
#define MOTOR_OFF false
#define MOTOR_ON true

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
    CameraDevice* p_camera;
  ////  QCamera* pt_qcam;
///    MyCamera *pt_camera;

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
    bool m_can_isConnected;

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
    void sl_can_connected(bool iflag);
    ///===== for debug =======
    void on_value_led0_changed(int value);
    void on_value_led1_changed(int value);
    void on_butt_debug();
    void slot_rd_dbg(int num, dbg_dat_req_t* odat);
    void slot_wr_dbg(int num, dbg_dat_req_t* idat);
    void slot_send_can_dbg(can_message_t* idat);
    void on_butt_test();
    void on_butt_test1();
    void on_butt_test2();
    void on_butt_load();

    void sl_rsv_can_dat(char*);


private slots:
    void selectVideoSource();
private slots:
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
protected:
    bool    xminusPushed;
    bool    xminusLongPush ;
    bool    yminusPushed;
    bool    yminusLongPush;
    bool    zminusPushed;
    bool    zminusLongPush;
protected slots:
    void cl_stop();
    void cl_xminus();
    void cl_xminus_rel();
    void cl_xplus();
    void cl_xplus_rel();
    void cl_yminus();
    void cl_yminus_rel();
    void cl_yplus();
    void cl_yplus_rel();
    void cl_zminus();
    void cl_zminus_rel();
    void cl_zplus();
    void cl_zplus_rel();
    void SlotLongPush_xminus();
    void SlotLongPush_xplus();
    void SlotLongPush_yminus();
    void SlotLongPush_yplus();
    void SlotLongPush_zminus();
    void SlotLongPush_zplus();

signals:
    void updateCamView(QImage);
    void s_SendCmd(can_message_t* msg);
    void s_start(int);
    void s_can_connect(bool);
    void s_set_can_com_name(QString);
    void put_str_dial(char*);
private:
    QGraphicsItem* currentItem;
    LibPaintScene* scene;
    QString svg_path;



};
