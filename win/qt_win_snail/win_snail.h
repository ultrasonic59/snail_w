#pragma once

#include <QtWidgets/QMainWindow>
#include <QSvgGenerator>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QQueue>

#include "PlotterWidget.h"
#include "ui_qt_win_snail.h"
///======================================================================
#include <opencv2/opencv.hpp>
#include "hidapi.h"
#include "dial_debug.h"

#include "hid_cmd.h"
#include "port_prop_dialog.h"
#include "cmd_sender.h"
#include "csv/csv_dlg.h"

#include "tbl/tbl_dlg.h"

#include "snail_data.h"
#include "motor_wrk.h"
#include "CamPlotter.h"
#include "cameradevice.h"
#include "paint_scene.h"
#include "component.h"
#include "lib_util.h"

///======================================================================
/// #define PLOT_TIME_DT  50
extern QElapsedTimer el_timer;
extern int	el_time;

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
/// #define MAX_NUM_STEP 10000000

#define REQ_TIME_DT   20

#define MAX_NUM_AXIS   4
/*
#define X_AXI          0
#define Y_AXI          1
#define Z_AXI          2
#define DOZA_AXI       3
*/
QT_BEGIN_NAMESPACE
namespace Ui { class win_snail; };
QT_END_NAMESPACE

using namespace cv;
#define MAX_CNT_CONN 20
struct conn_axis {
    bool connected_axis[MAX_NUM_AXIS];
    bool prev_connected_axis[MAX_NUM_AXIS];
    int cnt_no_conn[MAX_NUM_AXIS];

};




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
    QList<int> splitter_sizes;
    bool put_hid_cmd(hid_cmd_t* cmd);
    void rd_hid_dbg(dbg_dat_req_t* odat);

public:
    plotterwidget* p_CamView;
    CamPlotter* p_cam_plotter;
    PlotProperties PlotProp;
    quint32 cnf_flags;
private:
    QThread* pCamThread;

public:
    c_snail_data snail_data;
private:
    QPen Pen;

 ////   VideoCapture _cap;
    int frame_width;
    int frame_height;
   Mat _frame;
 ///   QImage    _Image;
    QTimer* p_PlotTimer;
private:
    QThread* pSenderThread;
    CcmdSender* p_cmd_sender;
 
protected:
    void timerEvent(QTimerEvent* e);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent* event);

    QPoint last_pn;
    QRect sel_rc;
private:
    Ui::win_snail *ui;
private:
    CameraDevice* p_camera;

protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void setupActions();

    void saveSettings(void);
    void loadSettings(void);
 ////   void verify_data(void);
    QString ComPortName;

protected:
    QTimer* p_ReqTimer;
    conn_axis ConAxis;
 ///  bool connected_axis[MAX_NUM_AXIS];
    QQueue < can_message_t> msg_queue;
    void show_con_axis(void);
    void check_con_axis(void);
    void set_con_axis(quint8 axi);
    void init_con_axis(void);

  ///  void req_status_axis();
private slots:
    void req_timer_timeout(void);
    void req_status_axis();

private :
    bool eventFilter(QObject* obj, QEvent* event);
    void createMenus();
    bool m_can_isConnected;
    bool on_esc_key;
private:
    QAction* actionProj;
    QAction* actionFile;
    QAction* actionSelect;
    QAction* actionFile_Csv;
    QAction* actionFile_Tbl;
    QAction* actionSet_colors;
    QAction* actionNew_prj;
    QAction* actionNew_file;
    QAction* separatorAction;
public:
    mot_param_t mot_param;

private:
    QStringList recentFiles;
    QString curFile;
    enum { MaxRecentFiles = 5 };
    QAction * recentFileActions[MaxRecentFiles];
    QString strippedName(const QString& fullFileName);
    void setCurrentFile(const QString& fileName);
    void updateRecentFileActions();
    void rotateComp(qreal angle);

public slots:
    void on_butt_con_hid();
    void on_butt_con_can();
    void sl_can_connected(bool iflag);
    ///===== for debug =======
    void on_value_led0_changed(int value);
    void on_value_led1_changed(int value);
    void on_butt_debug();
    void slot_rd_dbg(int axi,int num, dbg_dat_req_t* odat);
    void slot_wr_dbg(int axi,int num, dbg_dat_req_t* idat);
    void slot_send_can_dbg(can_message_t* idat);

    void on_butt_test();
    void on_butt_test1();
    void on_butt_test2();
    void on_butt_test3();

    void on_butt_load();

    void sl_rsv_can_dat(can_message_t);
    void sl_state_changed(quint8);
    void sl_show_json(QByteArray byteArr);

private slots:
    void selectVideoSource();
private slots:
    void sl_show_rule_coord(QRect& rc);
    void sl_setDrawProp();
    void sl_openCsvFile();
    void sl_openTblFile();

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
    void sl_set_mot_rej();
/*
protected:
    bool    xminusPushed;
    bool    xminusLongPush ;
    bool    yminusPushed;
    bool    yminusLongPush;
    bool    zminusPushed;
    bool    zminusLongPush;
    */
protected slots:
    void sl_go();

 ///   void sl_go_x();
 ///   void sl_go_y();
///    void sl_go_z();

    void sl_motor_go();
 ///   void sl_xplus();
 ///   void sl_yplus();
 ///   void sl_yminus();
 ///   void sl_zplus();
 ///   void sl_zminus();
    void sl_doza();

 /*
protected slots:
    void cl_stop();
    void cl_xminus_rel();
     void cl_xplus_rel();
    void cl_yminus_rel();
    void cl_yplus_rel();
     void cl_zminus_rel();
    void cl_zplus_rel();
    void cl_go_home();
*/
signals:
    void updateCamView(QImage);
    void s_SendCmd(can_message_t* msg);
    void s_start(int);
    void s_can_connect(bool);
    void s_set_can_com_name(QString);
    void put_str_dial(char*);
    void put_msg_dial(can_message_t);

    void s_mot_go(mot_cmd_t);
    void s_set_mot_rej(quint32, quint8, quint8);
    void s_mot_spi(int axi,spi_mot_cmd_t);
    void s_eeprom(int axi, eeprom_cmd_t);
    void s_key_release(int axi);
    void s_put_doza(doza_cmd_t);
    void s_send_msg(can_message_t* msg);

private:
    PaintScene* scene;
    LibGraphicView* view_sc;
    QString lib_path;
    LibUtil lib_util;
    void showConState();
    quint8  prev_states[NUM_AXIS];                       /// 

public:
    bool data_ready;
    can_message_t rsv_msg;
    dev_state_t dev_state;
protected:
    /*
    void send_cmd_go(quint32 id, quint8 dir, quint16 len_step, quint32 num_step);
    void send_cmd_stop(quint32 id);
    void send_cmd_mot_rej(quint32 id,quint8 rej);
    void send_cmd_set_coord(quint32 id, quint32 coord); */

    void mousePressEvent(QMouseEvent* event);
    QThread* pMotorThread;
    Cmotor_wrk* p_motor_wrk;

protected slots:
    void on_clr();
    void sl_mouse_pos(QPointF pnt);
    void sl_eeprom(int axi, eeprom_cmd_t cmd);
    void sl_zoom_changed(double value);
public:
  ///  bool json2component(QByteArray byteArr, component& comp);
  ///  bool json2component(QByteArray byteArr, component* pGroup);
    component* json2component(QByteArray byteArr);

};
