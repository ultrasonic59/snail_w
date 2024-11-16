#pragma once
#include <QObject>
#include "can_message.h"
#include "cmd_sender.h"

class Cwrk_wrk : public QObject
{
	Q_OBJECT
public:
	explicit Cwrk_wrk(CcmdSender* sender);
	////bool getAllData(sensors_data_t *data ) ;

private:
	CcmdSender* p_cmd_sender;

///	char* out_buffer;
///	char vers[256];
	///	QByteArray SetSendData(sent_dat_t *sentData);

public:
	///signals:
	///	void sig_set_pb_val(quint32 val);
public slots:
	void SlSendCmd(can_message_t *msg);

};

