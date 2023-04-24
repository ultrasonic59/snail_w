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
#include "debug_data.h"

#define ADDR_FLASH_APP 0x080010000

#define DEFAULT_BAUD_RATE QSerialPort::Baud115200

#define WRITE_WAIT_DELAY 100
#define READ_WAIT_DELAY 5000
////=============Addr eeprom ==========================================
#define ADDR_EEPROM_BOOT_WORK   0x0
#define VAL_EEPROM_WORK  0xAA55
#define ADDR_KS_APP             0x1
#define ADDR_EEPROM_SIZEL_APP  0x2
#define ADDR_EEPROM_SIZEH_APP  0x3

///==== Can cmd ====================
////#define GET_STAT     0x2
////#define ERRASE_ADDR  0x3
////#define PROG_ADDR    0x4

////#define PROG_CHUNC   0x5

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
    bool isOpened() const;
	quint8 get_curr_state();
	QString COM_port_name;
	void config_port();
    void connectToDev();
	bool SetBootMode();
private:
    quint8 getLineType(QString line);
	quint8 parseHexLine(QString line);
	quint8 hex2bin(QString line );
	quint8 progFlashLine();
	quint8 progFlashChunc(quint8 *dat, quint8 len);
    quint8 setProgAddr(quint32 addres);
	quint8 erraseAddr(quint32 addres);
	quint8 checkErraseAddr(quint32 addres);

	quint8 getDevStat(quint8 &stat);
	quint8 SendResCanCmd(can_cmd_t *idat,can_cmd_t *odat=nullptr);

	quint32	linAddr;
	bin_data_t cur_bin_data;
	quint16 t_ks;
	quint32 size_app;
private:
    QSerialPort *m_pSerialPort;
    bool m_isConnected;
    bool m_isOpened;
  ////   void connectToDev();
	bool getStat(); 
	QByteArray SendRes(QByteArray sentData);
	quint32 can_id;
	quint8 state_dev;
public:
	bool progr(QFile *pFile);
	void set_can_id(QString id);
	void SetConnected(bool conn);
	void rd_eeprom(dat_req_t* data );
	void wr_eeprom(dat_req_t* data );
	bool wr_eeprom(quint16 addr, quint16 data );

	void rd_flash(dat_req_t* data );
	void clr_ks(void)
		{
		t_ks=0;
		}

signals:
	void sig_set_pb_val(quint32 val);
};

#endif // _PROG_HEX_H_
