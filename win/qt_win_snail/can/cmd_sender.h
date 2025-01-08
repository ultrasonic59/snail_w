#ifndef _CMD_SENDER_H_
#define _CMD_SENDER_H_

#include <QObject>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "can_message.h"


#define DEFAULT_BAUD_RATE QSerialPort::Baud115200

#define WRITE_WAIT_DELAY 100
#define READ_WAIT_DELAY 5000
#define MAX_BUFF_SIZE  4096
#define MAX_FRAME_LEN				4096
#define DEFAULT_CAN_BR       500000

#define CMD_VERS1  				'v'
#define CMD_VERS  				'V'
#define CMD_OPEN  				'O'
#define CMD_CLOSE  				'C'
#define CMD_SEND  				't'
///===========================================================
#define GO_CMD                0x1
#define GET_STAT_CMD          0x2
#define PUT_STAT_CMD          0x3
#define PUT_ACK               0x4
#define SET_PARAM             0x5
#define CHECK_CONN            0x6
#define ACK_CONN              0x7
#define RD_EEPROM_REQ         0x8
#define RD_EEPROM_ANS         0x9
#define WR_EEPROM_REQ         0xA
#define WR_EEPROM_ANS         0xB
#define RD_FLASH_REQ          0xC
#define RD_FLASH_ANS          0xD

#define STOP_CMD              0xF
#define PRG_PARAM             0x10
#define ON_DOZA               0x11
///========== SET_PARAM ====================
#define SET_COORD             0x1
#define MOTOR_REJ             0x2

#define DIR_PLUS            0
#define DIR_MINUS           1
///============================================
#define X_AXIS_CAN_ID   ((0x1 << 0) << 5)   ///0x20
#define Y_AXIS_CAN_ID   ((0x1 << 1) << 5)   ///0x40
#define Z_AXIS_CAN_ID    ((0x1 << 2) << 5)  /// 0x80
#define DOZA_CAN_ID          ((0x1 << 3) << 5)   ///0x100
#define NUM_AXIS   (3+1)    ///x,y,z +doza

struct  go_cmd_t {
	quint8  cmd;                       /// 
	quint8  dirs;                     /// Dirs X,Y,Z ....
	quint16  step_per;                 /// period step
	quint32  steps;                 /// steps X,Y , Z 
};

struct  dev_state_t {
quint8  states[NUM_AXIS];                       /// 
qint32  coord[NUM_AXIS];                 /// steps X,Y , Z 
};

class CcmdSender : public QObject
{
	Q_OBJECT
public:
////	explicit CcmdSender(QObject *parent = 0);
	explicit CcmdSender(bool* p_data_ready = 0, can_message_t* p_rsv_msg=nullptr, dev_state_t* p_dev_state=nullptr);
	bool isConnected() const;
	QString COM_port_name;
	void config_port();
    void connectToDev();
	void disconnectToDev();
	////bool getAllData(sensors_data_t *data ) ;
	bool* p_data_ready;
	can_message_t* p_rsv_msg;
	dev_state_t *p_dev_state;
private:
    QSerialPort *m_pSerialPort;
    bool m_isConnected;
	bool getVers(char *vers); 
	bool setBaudRate(quint32 br);
	bool canOpen(void);
	bool canClose(void);

	bool SendRes(char *sent_data,char *res_data);
	char *out_buffer;
	char vers[256];
	bool wait_ans;
public:
	bool canSendMsg(can_message_t* msg);
	bool canSendCmdGo(quint32 id, go_cmd_t cmd);
public slots:
	void sl_set_com_name(QString);
	void sl_connect(bool);
	void SlSendCmd(can_message_t* msg);

private slots:
	void handleRead();
	void handleError(QSerialPort::SerialPortError serialPortError);

signals:
	void s_connected(bool);
	void s_rsv_can_dat(char*);
	void s_state_changed();

};




#endif // _CMD_SENDER_H_
