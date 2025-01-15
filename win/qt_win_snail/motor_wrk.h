#pragma once
#include <QObject>
#include <QThread>
#include "can_message.h"
#include "cmd_sender.h"

class Cmotor_wrk : public QObject
{
	Q_OBJECT
public:
	explicit Cmotor_wrk(CcmdSender* sender, dev_state_t* p_dev_state);
	////bool getAllData(sensors_data_t *data ) ;
private:
	CcmdSender* p_cmd_sender;
public:
    bool data_ready;
    dev_state_t* p_dev_state;
    quint16 len_step[NUM_AXIS];
    quint8 mot_rej[NUM_AXIS];

public slots:
	void SlSendCmd(can_message_t *msg);
///protected slots:
    void cl_stop();
    void cl_xminus();
    void cl_xminus_rel();
    void cl_xplus();
    void cl_xplus_rel();
    void cl_yminus();
    void cl_yminus_rel();
    void cl_yplus();
    void cl_yplus_rel();
    void cl_zminus();
    void cl_zminus_rel();
    void cl_zplus();
    void cl_zplus_rel();
    void cl_go_x();
    void cl_go_y();
    void cl_go_z();
    void cl_go_home();
    void cl_clr_x();
    void cl_clr_y();
    void cl_clr_z();

protected:
    void send_cmd_go(quint32 id, quint8 dir, quint16 len_step, quint32 num_step);
    void send_cmd_stop(quint32 id);
    void send_cmd_mot_rej(quint32 id, quint8 rej);
    void send_cmd_set_coord(quint32 id, quint32 coord);
signals:
    void s_SendCmd(can_message_t* msg);

};

