#ifndef _PROG_HEX_H_
#define _PROG_HEX_H_

#include <QObject>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "can_cmd.h"

#define ADDR_FLASH_APP 0x080010000

#define DEFAULT_BAUD_RATE QSerialPort::Baud115200

#define WRITE_WAIT_DELAY 100
#define READ_WAIT_DELAY 5000

///==== Can cmd ====================
#define GET_STAT     0x2
#define ERRASE_ADDR  0x3
#define PROG_ADDR    0x4
#define PROG_CHUNC   0x5

#define MAX_PROG_CHUNC_SIZE 6

#define MAX_NUM_BYTES 32
typedef struct bin_dat_s{
quint8 len_data;
quint8 bytes[MAX_NUM_BYTES];
}bin_data_t;

class CprogHex : public QObject
{
	Q_OBJECT
public:
	explicit CprogHex(QObject *parent = 0);
    bool isConnected() const;
	QString COM_port_name;
	void config_port();
    void connectToDev();

private:
    quint8 getLineType(QString line);
	quint8 parseHexLine(QString line);
	quint8 hex2bin(QString line );
	quint8 progFlashLine();
	quint8 progFlashChunc(quint8 *dat, quint8 len);
    quint8 setProgAddr(quint32 addres);
	quint8 erraseAddr(quint32 addres);
	quint8 sendCanCmd(can_cmd_t *dat);

	quint32	linAddr;
	bin_data_t cur_bin_data;
private:
    QSerialPort *m_pSerialPort;
    bool m_isConnected;
 
 ////   void connectToDev();
	bool getStat(); 
	QByteArray SendRes(QByteArray sentData);

public:
	bool progr(QFile *pFile);
	quint32 can_id;
signals:
	void sig_set_pb_val(quint32 val);
};

#endif // _PROG_HEX_H_
