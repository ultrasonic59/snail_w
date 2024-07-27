#include <QThread>
#include <QDebug>
#include "cmd_sender.h"

////extern void addfcs16( unsigned char *cp, int len );
/////extern int checkfcs16(unsigned char *cp, const int len );

CcmdSender::CcmdSender(QObject *parent) : 
			QObject(parent),
			m_isConnected(false),
			COM_port_name("COM16")
{
m_pSerialPort = new QSerialPort(this);
out_buffer=new char[MAX_BUFF_SIZE];
}
bool CcmdSender::isConnected() const
{
    return m_isConnected;

}
bool CcmdSender::SendRes(char *sent_data,char *res_data)
{
if ((sent_data == 0) || (res_data == 0))
	return false;
m_pSerialPort->write(sent_data);
if(!m_pSerialPort->waitForBytesWritten(WRITE_WAIT_DELAY))
	return false;
if(!m_pSerialPort->waitForReadyRead(READ_WAIT_DELAY))
	return false;
quint64 len = m_pSerialPort->read(res_data, 256);
if (len == 0)
	return false;
return true;

}

void CcmdSender::config_port()
{
m_pSerialPort->setPortName(COM_port_name);
m_pSerialPort->setBaudRate(DEFAULT_BAUD_RATE);
m_pSerialPort->setDataBits(QSerialPort::Data8);
m_pSerialPort->setParity(QSerialPort::NoParity);
m_pSerialPort->setStopBits(QSerialPort::OneStop);
m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
}
void CcmdSender::disconnectToDev()
{
m_pSerialPort->close();
m_isConnected=false;
}

void CcmdSender::connectToDev()
{
config_port();
m_isConnected = false;
bool tmp_rez = false;
if (!m_pSerialPort->open(QSerialPort::ReadWrite))
     return;
	tmp_rez = getVers(vers);
	if (!tmp_rez)
		return;
	tmp_rez = setBaudRate(DEFAULT_CAN_BR);
	if (!tmp_rez)
		return;
	tmp_rez = canOpen();
	if (!tmp_rez)
		return;
m_isConnected = true;
 }
bool CcmdSender::getVers(char *vers) 
{
	char snd_dat[16];
	char rsv_dat[64] = { 0 };
	snd_dat[0] = CMD_VERS;
	snd_dat[1] = '\r';
	snd_dat[2] = 0;

	if(SendRes(snd_dat, rsv_dat))
	{
	////qDebug() << "getVers "<< rsv_dat;
	if (vers)
		strcpy(vers, rsv_dat);
	return true;  ///
	}

return false;  ///
}
bool CcmdSender::canOpen(void)
{
	char snd_dat[6];
	char rsv_dat[8] = { 0 };
	snd_dat[0] = CMD_OPEN;
	snd_dat[1] = '\r';
	snd_dat[2] = 0;
	if (SendRes(snd_dat, rsv_dat))
	{
		return true;  ///
	}
return false;  ///
}
bool CcmdSender::canClose(void)
{
	char snd_dat[6];
	char rsv_dat[8] = { 0 };
	snd_dat[0] = CMD_CLOSE;
	snd_dat[1] = '\r';
	snd_dat[2] = 0;
	if (SendRes(snd_dat, rsv_dat))
	{
		return true;  ///
	}
return false;  ///
}
///=================================================

static char* put_hex_digit(char* str, quint8 val) {
	char c;
	val &= 0x0f;
	if (val < 10) {
		c = val + '0';
	}
	else {
		c = val + 'A' - 10;
	}
*str++ = c;
return str;
}
static char* put_hex_byte(char* str, quint8 val) {
	str = put_hex_digit(str, val >> 4);
	str = put_hex_digit(str, val);
	return str;
}

///==================================================
bool CcmdSender::canSendMsg(can_message_t* msg) {
	char snd_dat[64];
	char* t_str = snd_dat;
	char rsv_dat[64] = { 0 };
	*t_str++ = CMD_SEND;
	t_str = put_hex_digit(t_str, msg->id >> 8);
	t_str = put_hex_byte(t_str, msg->id & 0xff);
	t_str = put_hex_digit(t_str, msg->dlc);
	for (quint8 ii = 0; ii < msg->dlc; ii++) {
		t_str = put_hex_byte(t_str, msg->data[ii]);
	}
*t_str++ = '\r';
*t_str++ = 0;
if (SendRes(snd_dat, rsv_dat))
	{
		return true;  ///
	}
	return false;  ///

}

const char* slcan_get_baud_string(quint32 bps) {
	switch (bps) {
	case   10000: return "S0\r";
	case   20000: return "S1\r";
	case   50000: return "S2\r";
	case  100000: return "S3\r";
	case  125000: return "S4\r";
	case  250000: return "S5\r";
	case  500000: return "S6\r";
	case  800000: return "S7\r";
	case 1000000: return "S8\r";
	}
	return 0;
}

bool CcmdSender::setBaudRate(quint32 bps)
{
	char snd_dat[16];
	char rsv_dat[16] = { 0 };
	strcpy(snd_dat, slcan_get_baud_string(bps));
	
	if (SendRes(snd_dat, rsv_dat))
	{
		return true;  ///
	}

	return false;  ///
}

#if 0
bool CcmdSender::getAllData(sensors_data_t *data ) 
{
#if 1
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_REQ;
send_dat.cmd=GET_ALL_DATA;
send_dat.len=0;
if(SendRes(&send_dat,&resv_dat))
	{
////	qDebug() << "GET_ALL_DATA "<< resv_dat.cmd;
	if(resv_dat.cmd==GET_ALL_DATA)
		{
		memcpy(data,&resv_dat.buff,resv_dat.len);
		return true;  ///
		}
	}
#endif
return false;  ///
}
#endif
