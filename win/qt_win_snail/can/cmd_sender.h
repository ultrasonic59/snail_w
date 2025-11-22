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
#include "can_cmd.h"

#define DEF_LEN_STEP_X  100
#define DEF_LEN_STEP_Y  100
#define DEF_LEN_STEP_Z  100

#define DEF_MOT_REJ_X  2
#define DEF_MOT_REJ_Y  2
#define DEF_MOT_REJ_Z  2

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

#define WR_SPI_MOT            0x12
#define RD_SPI_MOT_REQ        0x13
#define RD_SPI_MOT_ANS        0x14
#define GET_ENCODER_CMD       0x15
#define PUT_ENCODER_CMD       0x16

///========== SET_PARAM ====================
#define SET_COORD             0x1
#define MOTOR_REJ             0x2

#define DIR_PLUS            0
#define DIR_MINUS           1
///============================================
#define X_AXIS_CAN_ID     ((0x1 << XX) << 5)   ///0x20
#define Y_AXIS_CAN_ID     ((0x1 << YY) << 5)   ///0x40
#define Z_AXIS_CAN_ID     ((0x1 << ZZ) << 5)  /// 0x80
#define DOZA_CAN_ID       ((0x1 << DZ) << 5)   ///0x100
#define NUM_AXIS          (3)    ///x,y,z 

struct  go_cmd_t {
	quint8  cmd;                       /// 
	quint8  dirs;                     /// Dirs X,Y,Z ....
	quint16  step_per;                 /// period step
	quint32  steps;                 /// steps X,Y , Z 
};
#define STATE_IDLE           0
#define STATE_READY          1
#define STATE_MOVE           2
#define STATE_ERROR          3
#define STATE_BOOT           4
#define STATE_MASK           0xF
#define CONC_MASK            0x30

#define CONC0_FLG            (0x1<<4)
#define CONC1_FLG            (0x1<<5)

#define MAX_NUM_STEP 10000000
#define MAX_LEN_DOZA 65000

struct  mot_cmd_t {
	quint32 id;
	quint8 dir;
	quint16 len_step;
	quint32 num_step;
};
struct  mot_param_t {
	quint16 len_step[NUM_AXIS];
	quint8 mot_rej[NUM_AXIS];
};
struct  spi_mot_cmd_t {
	uint8_t   cmd;                         /// 
	uint8_t   addr;                        /// 
	uint8_t   len_dat;                     ///bytes 
	uint8_t   b_val;
	uint32_t  w_val;                      /// 
};
#pragma pack (push, 1)
struct  eeprom_cmd_t {
	uint8_t   cmd;                         /// 
	quint8 num_dates;
	quint8 addr;
	quint16 data[EEPROM_MAX_NUM_DATES];
};
#pragma pack (pop)

#pragma pack (push, 1)
struct  doza_cmd_t {
	quint8   cmd;                         /// 
	quint16 time;
};
#pragma pack (pop)

struct  ack_t {
	quint8  ack_cmd;                         /// 
	quint8  axis;                        /// X,Y , Z 
};

struct  put_ack_t{
	qint8  cmd;                         /// 
	ack_t   ack;                         /// 
};

struct  dev_state_t {
quint8  states[NUM_AXIS];                       /// 
qint32  coord[NUM_AXIS];                 /// steps X,Y , Z 
qint32  coord_enc[NUM_AXIS];                 /// enc X,Y , Z 
qint16  temper[NUM_AXIS];                 /// temper motor X,Y , Z 

};
typedef struct  encoder_cmd_s_ {
	quint8  cmd;                         /// 
	quint8  axis;                        /// X,Y , Z 
	qint32  coord;                     /// 
	quint16 temp_val;
}encoder_cmd_t;

class CcmdSender : public QObject
{
	Q_OBJECT
public:
////	explicit CcmdSender(QObject *parent = 0);
	explicit CcmdSender(bool* p_data_ready = 0, can_message_t* p_rsv_msg=nullptr
		, dev_state_t* p_dev_state=nullptr);
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
	void s_rsv_can_dat(can_message_t);
	void s_state_changed();

};




#endif // _CMD_SENDER_H_
