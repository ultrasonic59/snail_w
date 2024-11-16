#include "wrk_wrk.h"
#include <Qdebug>

Cwrk_wrk::Cwrk_wrk(CcmdSender* sender):p_cmd_sender(sender)
{

}
void Cwrk_wrk::SlSendCmd(can_message_t* msg)
{
	qDebug() << "SlSendCmd";

}