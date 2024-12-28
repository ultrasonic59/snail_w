#pragma once

#include <QMutex>
#include <QtSerialPort/QSerialPort>
#include <QThread>


struct COMPortProperites
{
	QString NewPortName;
	QString SavedPortName;

	QSerialPort::FlowControl flowControl;
	QSerialPort::BaudRate baudRate;
	QSerialPort::StopBits stopBits;
	qint64 bufferSize;
	QIODevice::OpenMode openMode;
	bool breakEnabled;

	int WriteTimeout;
	int ReadTimeout;


	COMPortProperites();
};

struct COMPortStates
{
	QString PortName;
	bool connected;
	QSerialPort::SerialPortError error;

	COMPortStates();
};

class COMPort
{
///protected:
public:

	COMPortStates COMstate;
	COMPortProperites *COMpr;
	QSerialPort serial;

public:

	COMPort(QObject *paren_obj, COMPortProperites *new_COMpr);
	virtual ~COMPort(void);

	bool IsConnected() const;
	void SetConnected(bool conn);

	void setPortName(QString name);
	bool SetPort();

	bool Write(char *dat, qint64 numBytes);
	qint64 Read(char *datbufer, qint64 numBytes);

	void ClearPort();
	qint64 GetBytesAwaible();

};

