#pragma once
#include <QObject>
#include <QThread>
#include "can_message.h"
#include "cmd_sender.h"

class Cmotor_wrk : public QObject
{
	Q_OBJECT
public:
	explicit Cmotor_wrk(CcmdSender* sender, dev_state_t* p_dev_state, mot_param_t* mot_par = nullptr);
	////bool getAllData(sensors_data_t *data ) ;
private:
	CcmdSender* p_cmd_sender;
public:
    bool data_ready;
    dev_state_t* p_dev_state;
    mot_param_t* p_mot_param;

public slots:
	void SlSendCmd(can_message_t *msg);
///protected slots:
    void sl_stop();
    ///void cl_xminus();
    void sl_xminus_rel();
    ///void cl_xplus();
    void sl_xplus_rel();
    ///void cl_yminus();
    void sl_yminus_rel();
    ///void cl_yplus();
    void sl_yplus_rel();
    ///void cl_zminus();
    void sl_zminus_rel();
    //void cl_zplus();
    void sl_zplus_rel();
   /// void cl_go_xx();
    ///void cl_go_yy();
    ///void cl_go_zz();
    void sl_go_home();

    void sl_mot_go(mot_cmd_t mot_cmd);

    void sl_clr_x();
    void sl_clr_y();
    void sl_clr_z();
    void sl_set_rej(quint32 id, quint8 rej);

protected:
    void send_cmd_go(quint32 id, quint8 dir, quint16 len_step, quint32 num_step);
    void send_cmd_stop(quint32 id);
    void send_cmd_mot_rej(quint32 id, quint8 rej);
    void send_cmd_set_coord(quint32 id, quint32 coord);
signals:
    void s_SendCmd(can_message_t* msg);

};

