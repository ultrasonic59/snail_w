#include <QThread>
#include <QDebug>
#include "cmd_sender.h"

extern void addfcs16( unsigned char *cp, int len );
extern int checkfcs16(unsigned char *cp, const int len );

CcmdSender::CcmdSender(QObject *parent) : 
			QObject(parent),
			m_isConnected(false),
			COM_port_name("COM10")
{
m_pSerialPort = new QSerialPort(this);
out_buffer=new char[MAX_BUFF_SIZE];
}
bool CcmdSender::isConnected() const
{
    return m_isConnected;

}
bool CcmdSender::CheckSetResvData(QByteArray in_data,sent_dat_t *out_data)
{
quint16 ii=0;
quint16 jj=0;
quint8 ch;
quint8 *tmpbuf= new quint8[in_data.size()];
do
	{
	ch=in_data[ii];
	ii++;
	}
while((ii < in_data.size()) && (ch != PPP_FRAME));	// ищем начало фрейма
	
if(ii==in_data.size())
	return false;
while(ii < in_data.size())
    {
	if((in_data[ii] == (char)PPP_ESCAPE)&&(ii+1 <in_data.size()))
		{
		tmpbuf[jj]= in_data[++ii] ^ PPP_ESCAPE_BIT;
		ii++;
		}
	else if(in_data[ii] != (char)PPP_FRAME)
		{
		tmpbuf[jj++]= in_data[ii++];
		}
	else
		break;
	}
if(!checkfcs16((unsigned char*)tmpbuf, jj - 2 ))
	return false;
memcpy((quint8*)out_data,tmpbuf,jj-2);
delete tmpbuf;
return true;
}

QByteArray CcmdSender::SetSendData(sent_dat_t *sentData)
{
quint8 *p_char_send_dat = new quint8[sentData->len+16];
memcpy(p_char_send_dat,(quint8*)sentData,sentData->len+4);
addfcs16(p_char_send_dat, sentData->len+4);	

quint16 out_size = 0;
out_buffer[out_size++] = PPP_FRAME;
for(int ii = 0; ii < sentData->len+6; ii++)
	{
	if( p_char_send_dat[ii] == PPP_FRAME || p_char_send_dat[ii] == PPP_ESCAPE )			// Замена "FLAG" или "ESC" на ESC-последовательность
		{
		out_buffer[out_size++] = PPP_ESCAPE;
		out_buffer[out_size++] = p_char_send_dat[ii] ^ PPP_ESCAPE_BIT;
		}
	else
		out_buffer[out_size++] = p_char_send_dat[ii];
	}
out_buffer[out_size++] = PPP_FRAME;
QByteArray rez(out_buffer,out_size);
delete p_char_send_dat;
return rez;
}

bool CcmdSender::SendRes(sent_dat_t *sent_data,sent_dat_t *res_data)
{
QByteArray sentData=SetSendData(sent_data);
m_pSerialPort->write(sentData);
if(!m_pSerialPort->waitForBytesWritten(WRITE_WAIT_DELAY))
	return false;
if(!m_pSerialPort->waitForReadyRead(READ_WAIT_DELAY))
	return false;
QByteArray resvData=m_pSerialPort->readAll();
if(!CheckSetResvData(resvData,res_data))
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
if (m_pSerialPort->open(QSerialPort::ReadWrite))
	{
    m_isConnected = getStat();
    if (m_isConnected)
        {
        qDebug() << "dev connected";
        }
    else
        {
        qDebug() << "no dev!";
        }
    }
    else
    {
        qDebug() << "dev no connected";
        m_isConnected = false;
    }
}
void CcmdSender::OnOffAirCmd(bool on_off)
{
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_PUT;
send_dat.cmd=NUM_SET_CL3;
send_dat.len=1;
if(on_off)
	send_dat.buff[0]=1;
else
	send_dat.buff[0]=0;

if(SendRes(&send_dat,&resv_dat))
	{
	qDebug() << "OnOffAirCmd "<< resv_dat.cmd;
	}
}
void CcmdSender::OnOffRedCmd(bool on_off)
{
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_PUT;
send_dat.cmd=NUM_SET_RED;
send_dat.len=1;
if(on_off)
	send_dat.buff[0]=1;
else
	send_dat.buff[0]=0;

if(SendRes(&send_dat,&resv_dat))
	{
	qDebug() << "OnOffRedCmd "<< resv_dat.cmd;
	}
}
void CcmdSender::OnOffGreenCmd(bool on_off)
{
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_PUT;
send_dat.cmd=NUM_SET_GREEN;
send_dat.len=1;
if(on_off)
	send_dat.buff[0]=1;
else
	send_dat.buff[0]=0;

if(SendRes(&send_dat,&resv_dat))
	{
	qDebug() << "OnOffGreenCmd "<< resv_dat.cmd;
	}
}

void CcmdSender::OnOffGazCmd(bool on_off)
{
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_PUT;
send_dat.cmd=NUM_SET_CL7;
send_dat.len=1;
if(on_off)
	send_dat.buff[0]=1;
else
	send_dat.buff[0]=0;

if(SendRes(&send_dat,&resv_dat))
	{
	qDebug() << "OnOffGazCmd "<< resv_dat.cmd;
	}

}
void CcmdSender::ChangeAirCmd(quint16 val)
{
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_PUT;
send_dat.cmd=NUM_SET_AIR;
send_dat.len=2;
memcpy(&send_dat.buff[0],&val,sizeof(quint16));

if(SendRes(&send_dat,&resv_dat))
{
qDebug() << "ChangeAirCmd"<< resv_dat.cmd;

}
}


bool CcmdSender::getStat() 
{
#if 1
sent_dat_t send_dat;
sent_dat_t resv_dat;
send_dat.type=CDC_CMD_REQ;
send_dat.cmd=GET_STAT;
send_dat.len=0;
if(SendRes(&send_dat,&resv_dat))
	{
	qDebug() << "OnOffAirCmd "<< resv_dat.cmd;
	return true;  ///
	}
#endif
return false;  ///
}
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

