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

///============================================
#define X_AXIS_CAN_ID   ((0x1 << 0) << 5)   ///0x20
#define Y_AXIS_CAN_ID   ((0x1 << 1) << 5)   ///0x40
#define Z_AXIS_CAN_ID    ((0x1 << 2) << 5)  /// 0x80

typedef struct  go_cmd_s_ {
	uint8_t  cmd;                       /// 
	uint8_t  dirs;                     /// Dirs X,Y,Z ....
	uint16_t  step_per;                 /// period step
	uint32_t  steps;                 /// steps X,Y , Z 
}go_cmd_t;


class CcmdSender : public QObject
{
	Q_OBJECT
public:
	explicit CcmdSender(QObject *parent = 0);
    bool isConnected() const;
	QString COM_port_name;
	void config_port();
    void connectToDev();
	void disconnectToDev();
	////bool getAllData(sensors_data_t *data ) ;

private:
    QSerialPort *m_pSerialPort;
    bool m_isConnected;
	bool getVers(char *vers); 
	bool setBaudRate(quint32 br);
	bool canOpen(void);
	bool canClose(void);
///	bool canSendMsg(can_message_t *msg);

	////bool getAllData(sensors_data_t *data ) ;
///	QByteArray SendRes(sent_dat_t *sent_data);
	bool SendRes(char *sent_data,char *res_data);
///	bool CheckSetResvData(QByteArray in_data,sent_dat_t *out_data);
	char *out_buffer;
	char vers[256];
///	QByteArray SetSendData(sent_dat_t *sentData);

public:
	bool canSendMsg(can_message_t* msg);
	bool canSendCmdGo(quint32 id, go_cmd_t cmd);

///signals:
///	void sig_set_pb_val(quint32 val);
};




#endif // _CMD_SENDER_H_
