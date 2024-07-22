#ifndef _CMD_SENDER_H_
#define _CMD_SENDER_H_

#include <QObject>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
////#include "sensors_data.h"


#define DEFAULT_BAUD_RATE QSerialPort::Baud115200

#define WRITE_WAIT_DELAY 100
#define READ_WAIT_DELAY 5000
#define MAX_BUFF_SIZE  4096
#define MAX_FRAME_LEN				4096

#define CMD_PUT_DAT  				0x3
#define CMD_REQ_DAT  				0x4
#define CMD_PUT_CMD  				0x6	
///================================================
#define PPP_FRAME		0x7E					// разделитель кадров

#define PPP_ESCAPE		0x7D					// доп. разделитель в случае бинарного формата
#define PPP_ESCAPE_BIT	0x20
///===============================================
#define CDC_CMD_PUT                 0x3         /// 
#define CDC_CMD_REQ                 0x4         /// 

#define NUM_SET_AIR                 0x11        /// 
#define NUM_SET_GAZ                 0x12        /// 
#define NUM_SET_CL3                 0x13        /// 
#define NUM_SET_CL7                 0x14        /// 
#define STOP_ALL					0x15        
#define NUM_SET_RED                 0x16        /// 
#define NUM_SET_GREEN               0x17        /// 

#define GET_TEMP_GAZ                0x21
#define GET_TEMP_AIR                0x22
#define GET_RASH_AIR                0x23
#define GET_STAT					0x24
#define GET_ALL_DATA                0x25

///============================================
struct sent_dat_t
{
quint8 type;
quint8 cmd;
quint16 len;
quint8 buff[MAX_FRAME_LEN];
#if 0
	quint16 GetFullLength() const
	{
		if(type == CMD_REQ_DAT)
			return 2*sizeof(quint8) + sizeof(quint16) + sizeof(quint16);

		return 2*sizeof(quint8) + sizeof(quint16) + len + sizeof(quint16);
	}
#endif
};

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
	bool getStat(); 
	////bool getAllData(sensors_data_t *data ) ;
///	QByteArray SendRes(sent_dat_t *sent_data);
	bool SendRes(sent_dat_t *sent_data,sent_dat_t *res_data);
	bool CheckSetResvData(QByteArray in_data,sent_dat_t *out_data);
	char *out_buffer;
	QByteArray SetSendData(sent_dat_t *sentData);

public:
////	void OnOffAirCmd(bool on_off);
////	void OnOffGazCmd(bool on_off);
///	void ChangeAirCmd(quint16 val);
///	void OnOffRedCmd(bool on_off);
///	void OnOffGreenCmd(bool on_off);

///signals:
///	void sig_set_pb_val(quint32 val);
};




#endif // _CMD_SENDER_H_
