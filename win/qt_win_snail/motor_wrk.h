#pragma once
#include <QObject>
#include <QThread>
#include "can_message.h"
#include "cmd_sender.h"
#include "dial_debug.h"
extern QElapsedTimer el_timer;
extern int	el_time;

class Cmotor_wrk : public QObject
{
	Q_OBJECT
public:
	explicit Cmotor_wrk(CcmdSender* sender, dev_state_t* p_dev_state
        ,  bool* p_data_ready = nullptr, mot_param_t* mot_par = nullptr);
	////bool getAllData(sensors_data_t *data ) ;
private:
	CcmdSender* p_cmd_sender;
public:
    bool *p_data_ready;
    dev_state_t* p_dev_state;
    mot_param_t* p_mot_param;

public slots:
	void SlSendCmd(can_message_t *msg);
///protected slots:
    void sl_stop_all();
     void sl_axi_rel(int axi);

    void sl_x_rel();
    void sl_y_rel();
    void sl_z_rel();
    void sl_go_home();

    void sl_mot_go(mot_cmd_t mot_cmd);
    void sl_mot_spi(int axi,spi_mot_cmd_t);
    void sl_put_doza(doza_cmd_t cmd);
    void sl_stop_doza();

    void sl_clr_x();
    void sl_clr_y();
    void sl_clr_z();
    void sl_set_rej(quint32 id, quint8 rej,  quint8 trq);

protected:
    void send_cmd_go(quint32 id, quint8 dir, quint16 len_step, quint32 num_step);
    void send_cmd_stop(quint32 id);
    void send_cmd_mot_rej(quint32 id, quint8 rej, quint8 trq);
    void send_cmd_set_coord(quint32 id, quint32 coord);
signals:
    void s_SendCmd(can_message_t* msg);

};

