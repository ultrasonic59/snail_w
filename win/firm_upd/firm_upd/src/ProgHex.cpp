#include <QTextStream>
#include <QThread>
#include <QDebug>
#include "progHex.h"


CprogHex::CprogHex(QObject *parent) : 
			QObject(parent),
	        linAddr(0),
			can_id(0),
			COM_port_name("COM1")
{
m_pSerialPort = new QSerialPort(this);

}

bool CprogHex::getStat() 
{
    return m_isConnected;

}

bool CprogHex::isConnected() const
{
    return m_isConnected;

}

QByteArray CprogHex::SendRes(QByteArray sentData)
{
m_pSerialPort->write(sentData);
m_pSerialPort->waitForBytesWritten(WRITE_WAIT_DELAY);
////    this->thread()->msleep(50);
m_pSerialPort->waitForReadyRead(READ_WAIT_DELAY);
return m_pSerialPort->readAll();
}

void CprogHex::config_port()
{
m_pSerialPort->setPortName(COM_port_name);
m_pSerialPort->setBaudRate(DEFAULT_BAUD_RATE);
m_pSerialPort->setDataBits(QSerialPort::Data8);
m_pSerialPort->setParity(QSerialPort::NoParity);
m_pSerialPort->setStopBits(QSerialPort::OneStop);
m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
}

void CprogHex::connectToDev()
{
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

quint8 CprogHex::getLineType(QString line)
{
return	line.mid(6, 2).toULong(0, 16);
}

#define HEX_OK			0
#define END_OF_FILE		1
#define ERR_TYPE_REC	3

quint8 CprogHex::hex2bin(QString line )
{
quint8 index=0;
if (line.length()==0)
	return 0;
for(quint8 ii=0;ii<line.length();ii+=2)
{
cur_bin_data.bytes[index]=line.mid(ii, 2).toUShort(0, 16);
qDebug() << cur_bin_data.bytes[index]; 
index++;
}
cur_bin_data.len_data=index;
return index;
}
quint8 CprogHex::sendCanCmd(can_cmd_t *dat)
{


return 0;
}

quint8 CprogHex::progFlashChunc(quint8 *data, quint8 len)
{
can_cmd_t t_can_cmd;
t_can_cmd.num_bytes=len+1;
if(len>MAX_PROG_CHUNC_SIZE)
	len=MAX_PROG_CHUNC_SIZE;
t_can_cmd.data[OFFS_CAN_CMD]=PROG_CHUNC;
t_can_cmd.data[OFFS_CAN_NUM_BYTES]=len;
memcpy(t_can_cmd.data+OFFS_CAN_DATA,data,len);
return sendCanCmd(&t_can_cmd);
}

quint8 CprogHex::setProgAddr(quint32 addres)
{
can_cmd_t t_can_cmd;
t_can_cmd.num_bytes=sizeof(quint32)+1;
t_can_cmd.data[OFFS_CAN_CMD]=PROG_ADDR;
memcpy(t_can_cmd.data+OFFS_CAN_ADDR,&addres,sizeof(quint32));
return sendCanCmd(&t_can_cmd);
}
quint8 CprogHex::erraseAddr(quint32 addres)
{
can_cmd_t t_can_cmd;
t_can_cmd.num_bytes=sizeof(quint32)+1;
t_can_cmd.data[OFFS_CAN_CMD]=ERRASE_ADDR;
memcpy(t_can_cmd.data+OFFS_CAN_ADDR,&addres,sizeof(quint32));
return sendCanCmd(&t_can_cmd);
}
quint8 CprogHex::progFlashLine()
{
quint8 offs_dat=0;
quint8 num_bytes=cur_bin_data.len_data;
while(num_bytes > 0) {
if(num_bytes > MAX_PROG_CHUNC_SIZE){
	progFlashChunc(cur_bin_data.bytes+offs_dat, MAX_PROG_CHUNC_SIZE);
	num_bytes -= MAX_PROG_CHUNC_SIZE;
	offs_dat += MAX_PROG_CHUNC_SIZE;
	}
else{
	progFlashChunc(cur_bin_data.bytes+offs_dat, num_bytes);
	num_bytes=0;
	}
}
return HEX_OK;
}

quint8 CprogHex::parseHexLine(QString line)
{
quint8 rez=0;
quint8 crc8=0;
line.remove(':');
for(int cc =0; cc < line.length(); cc +=2)
	{
	crc8 += line.mid(cc, 2).toUShort(0, 16);
	}
////QThread::msleep(1);
if(crc8 == 0)
   {
	quint8 lenData= line.mid(0, 2).toULong(0, 16);
	quint8 lineType= line.mid(6, 2).toULong(0, 16);
	quint32 offsAddr=line.mid(2, 4).toULong(0, 16);
	quint32 tData	=line.mid(8, lenData * 2).toULong(0, 16);
	quint32 Address = linAddr  + offsAddr;
	switch(lineType)
		{
		case 0: /// Data
			setProgAddr(Address);
			hex2bin(line.mid(8, lenData * 2) );
			rez = progFlashLine();
			break;
		case 1: //
			rez = END_OF_FILE;
			qDebug() << "END_OF_FILE " ;
			break;

		case 2: // Extended Segment Address Record
	////		segAddr = tData << 4; // *16
			rez = HEX_OK;
			qDebug() << "Extended Segment Address Record " ;
			break;

		case 3: // Start Segment Address Record
////				sRes ="[Start Segment Address: 0x" + DWORD2Hex(dwData) + "]\n";
			qDebug() << "Start Segment Address Record " ;

			break;

		case 4: // Extended Linear Address Record
			linAddr = tData << 16; // *65536
			qDebug() << "Extended Linear Address Record " ;
			break;
		case 5: // Start Linear Address Record
////				sRes ="[Start Linear Address: 0x" + DWORD2Hex(dwData) + "]\n";
			qDebug() << "Start Linear Address Record " ;
			break;

		default:
			rez = ERR_TYPE_REC;
			qDebug() << "Unknown type record: " << lineType;
		////	sRes ="<Unknown type record>\n";
			break;
		}
	////	nextAddr = Address + lenData;
	/////		qDebug() << "nextAddr :" << nextAddr<< "Address :"<<Address <<"lenData" << lenData;
   }
else
   {
	qDebug() << "Error crc " ;
   }
return rez;
}


bool CprogHex::progr(QFile *pFile)
{
QString tstr;
quint32 cur_pos=0;
QTextStream in(pFile);
if(erraseAddr(ADDR_FLASH_APP)!= HEX_OK)
	return false;
while(!in.atEnd())
	{
	tstr=in.readLine();
	parseHexLine(tstr);
	cur_pos += tstr.length();
////	qDebug() << "cur_pos: " << cur_pos;
	emit sig_set_pb_val(cur_pos);
	}
return true;
}

