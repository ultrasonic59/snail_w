#include "COMPort.h"

COMPortProperites::COMPortProperites() :
					NewPortName(),
					SavedPortName(),
					flowControl(QSerialPort::NoFlowControl),
					baudRate(QSerialPort::Baud115200),
					stopBits(QSerialPort::OneStop),
					bufferSize(4048),
					openMode(QIODevice::ReadWrite),
					breakEnabled(false),

					WriteTimeout(1000),
					ReadTimeout(3000)
{
}

COMPortStates::COMPortStates() :
				PortName(),
				connected(false),
				error(QSerialPort::NoError)
{
}




COMPort::COMPort(QObject *paren_obj, COMPortProperites *new_COMpr) :
					COMstate(),
					COMpr(new_COMpr),
					serial(paren_obj)
{
}


COMPort::~COMPort(void)
{
}


bool COMPort::IsConnected() const
{
	return COMstate.connected;
}

void COMPort::setPortName(QString name)
{
	COMstate.PortName =name;
}
void COMPort::SetConnected(bool conn)
{
COMstate.connected=conn;
}


bool COMPort::SetPort()
{
	bool result = false;

	if(COMstate.PortName != COMpr->NewPortName)
	{
		if(COMstate.PortName != "")
		{
			COMstate.connected = false;
			serial.clear();
			serial.close();
			COMstate.error = serial.error();
		}
		COMstate.PortName = COMpr->NewPortName;

		if(COMstate.PortName != "")
		{
			serial.setPortName(COMstate.PortName);
			serial.setFlowControl(COMpr->flowControl);
			serial.setBaudRate(COMpr->baudRate);
			serial.setStopBits(COMpr->stopBits);
			serial.setReadBufferSize(COMpr->bufferSize);


			if (!serial.open(QIODevice::ReadWrite))
			{	
				COMstate.connected = false;
				COMstate.PortName = "";
				COMstate.error = serial.error();
			}
			else
			{
				serial.setBreakEnabled(COMpr->breakEnabled);
				COMstate.connected = true;
				result = true;
				serial.clearError();
				COMstate.error = serial.error();
			}
		}
		else
		{
			COMstate.connected = false;
			result = true;
		}
	}

	return result;
}


bool COMPort::Write(char *dat, qint64 numBytes)
{
	if(!COMstate.connected)					// блокировка от записи во время другой записи или чтения
		return false;

	serial.write(dat, numBytes);
	serial.waitForBytesWritten(COMpr->WriteTimeout);

	return true;
}


qint64 COMPort::Read(char *datbufer, qint64 numBytes)
{
	if(!COMstate.connected)					// блокировка от чтения во время другой записи или чтения
		return -1;

	return serial.read(datbufer, numBytes);
}


qint64 COMPort::GetBytesAwaible()
{
	return serial.bytesAvailable();
}


void COMPort::ClearPort()
{
	serial.clear();
}





