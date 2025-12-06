#include "motor_wrk.h"
#include <Qdebug>
#include <QMessageBox>

Cmotor_wrk::Cmotor_wrk(CcmdSender* sender, dev_state_t* dev_state, bool* data_ready,mot_param_t* mot_par)
                      :p_cmd_sender(sender),p_dev_state(dev_state)
                       ,p_mot_param(mot_par), p_data_ready(data_ready)
{
/*
    len_step[XX] = DEF_LEN_STEP_X;
    len_step[YY] = DEF_LEN_STEP_Y;
    len_step[ZZ] = DEF_LEN_STEP_Z;
    mot_rej[XX] = DEF_MOT_REJ_X;
    mot_rej[YY] = DEF_MOT_REJ_Y;
    mot_rej[ZZ] = DEF_MOT_REJ_Z;
    */
    connect(this, SIGNAL(s_SendCmd(can_message_t*)), p_cmd_sender, SLOT(SlSendCmd(can_message_t*)));

}
///==============================================================

#define MAX_WAIT_HOME 10000

void Cmotor_wrk::send_cmd_go(quint32 id, quint8 dir, quint16 len_step, quint32 num_step)
{
    el_time = el_timer.elapsed();
    qDebug() << "send_cmd_go:" << el_time;

    can_message_t t_can_message;
    t_can_message.id = id;
    t_can_message.dlc = 8;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = GO_CMD;
    t_can_message.data[1] = dir;
    t_can_message.data[2] = len_step & 0xff;
    t_can_message.data[3] = (len_step >> 8) & 0xff;
    t_can_message.data[4] = num_step & 0xff;
    t_can_message.data[5] = (num_step >> 8) & 0xff;
    t_can_message.data[6] = (num_step >> 16) & 0xff;
    t_can_message.data[7] = (num_step >> 24) & 0xff;
    *p_data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (*p_data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS) {
            qDebug() << "send_cmd_go [wait_rdy_cnt]:" << wait_rdy_cnt;
            break;
        }
    };
    el_time = el_timer.elapsed();
    qDebug() << "send_cmd_go1:" << el_time;
}

void Cmotor_wrk::send_cmd_stop(quint32 id)
{
    can_message_t t_can_message;
    t_can_message.id = id;
    t_can_message.dlc = 1;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = STOP_CMD;
    *p_data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (*p_data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}
void Cmotor_wrk::send_cmd_mot_rej(quint32 id, quint8 rej, quint8 trq) {
    can_message_t t_can_message;
    t_can_message.id = id;
    t_can_message.dlc = 6;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = SET_PARAM;
    t_can_message.data[1] = MOTOR_REJ;
    t_can_message.data[2] = 0;
    t_can_message.data[3] = 1;
    t_can_message.data[4] = rej;
    t_can_message.data[5] = trq;
    t_can_message.data[6] = 0;
    t_can_message.data[7] = 0;
    *p_data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (*p_data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}
void Cmotor_wrk::send_cmd_set_coord(quint32 id, quint32 coord) {
    can_message_t t_can_message;
    t_can_message.id = id;
    t_can_message.dlc = 8;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = SET_PARAM;
    t_can_message.data[1] = SET_COORD;
    t_can_message.data[2] = 0;
    t_can_message.data[3] = 4;
    t_can_message.data[4] = coord & 0xff;
    t_can_message.data[5] = (coord >> 8) & 0xff;
    t_can_message.data[6] = (coord >> 16) & 0xff;;
    t_can_message.data[7] = (coord >> 24) & 0xff;;
    *p_data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (*p_data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}
///========================================================
void Cmotor_wrk::sl_put_doza(doza_cmd_t cmd) {
    can_message_t t_can_message;
    t_can_message.id = DOZA_CAN_ID;
    t_can_message.dlc = 3;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    memcpy(t_can_message.data, &cmd, sizeof(doza_cmd_t));
    *p_data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (*p_data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}

void Cmotor_wrk::sl_mot_spi(int axi, spi_mot_cmd_t cmd) {
    can_message_t t_can_message;
    switch (axi) {
    case AXI_X:
        t_can_message.id = X_AXIS_CAN_ID;
        break;
    case AXI_Y:
        t_can_message.id = Y_AXIS_CAN_ID;
        break;
     case AXI_Z:
        t_can_message.id = Z_AXIS_CAN_ID;
        break;
 ///  case AXI_DOZA:
 ///       t_can_message.id = DOZA_CAN_ID;
 ///        break;
   default:
       return;
       break;

}
    if(cmd.len_dat==1)
      t_can_message.dlc = cmd.len_dat+2;
    else
        t_can_message.dlc = cmd.len_dat + 6;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    memcpy(t_can_message.data, &cmd, sizeof(spi_mot_cmd_t));
    *p_data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (*p_data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}

///=================================================
void Cmotor_wrk::sl_mot_go(mot_cmd_t mot_cmd)
{
send_cmd_go(mot_cmd.id, mot_cmd.dir, mot_cmd.len_step, mot_cmd.num_step);
}
///=================== ===========================
void Cmotor_wrk::sl_go_home()
{
#if 1
 ////   quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    send_cmd_go(X_AXIS_CAN_ID, DIR_MINUS, p_mot_param->len_step[XX], MAX_NUM_STEP);
    send_cmd_go(Y_AXIS_CAN_ID, DIR_MINUS, p_mot_param->len_step[YY], MAX_NUM_STEP);
    int wait_end_cnt = 0;
    while (!((p_dev_state->states[XX] & CONC0_FLG) && (p_dev_state->states[YY] & CONC0_FLG)))
       {
        wait_end_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_end_cnt > MAX_WAIT_HOME)
            break;
       };
    if (wait_end_cnt < MAX_WAIT_HOME)
       {
        sl_clr_x();
        sl_clr_y();
       }
    else
        QMessageBox::information(nullptr, "Error!", "go home");
#endif
}
///=================================================
void Cmotor_wrk::sl_set_rej(quint32 id, quint8 rej, quint8 trq)
{
    qDebug() << "sl_set_rej";
   send_cmd_mot_rej(id, rej,trq);
   if(id== X_AXIS_CAN_ID)
      p_mot_param->mot_rej[XX] = rej;
   else if(id == Y_AXIS_CAN_ID)
       p_mot_param->mot_rej[YY] = rej;
   else if(id == Z_AXIS_CAN_ID)
       p_mot_param->mot_rej[ZZ] = rej;

}
void Cmotor_wrk::sl_axi_rel(int axi)
{
    qDebug() << "sl_axi_rel"<< axi;
    send_cmd_stop(axi);
}
///=================== X ===========================
void Cmotor_wrk::sl_x_rel()
{
    qDebug() << "sl_x_rel";
    send_cmd_stop(X_AXIS_CAN_ID);
}

void Cmotor_wrk::sl_clr_x()
{
    send_cmd_set_coord(X_AXIS_CAN_ID, 0);
}
///=================== Y ===========================
void Cmotor_wrk::sl_y_rel()
{
    qDebug() << "sl_y_rel";
    send_cmd_stop(Y_AXIS_CAN_ID);
}
void Cmotor_wrk::sl_clr_y()
{
    send_cmd_set_coord(Y_AXIS_CAN_ID, 0);
}
///=================== Z ===========================
void Cmotor_wrk::sl_z_rel()
{
    qDebug() << "sl_z_rel";
    send_cmd_stop(Z_AXIS_CAN_ID);
}

void Cmotor_wrk::sl_clr_z()
{
    send_cmd_set_coord(Z_AXIS_CAN_ID, 0);
}
///==================================================
void Cmotor_wrk::sl_stop_all()
{
////send_cmd_stop(X_AXIS_CAN_ID| Y_AXIS_CAN_ID|Z_AXIS_CAN_ID|DOZA_CAN_ID);
 ////   send_cmd_stop(X_AXIS_CAN_ID);
    qDebug() << "sl_stop_all0";

   send_cmd_stop(X_AXIS_CAN_ID| Y_AXIS_CAN_ID| Z_AXIS_CAN_ID);
    qDebug() << "sl_stop_all";

}

void Cmotor_wrk::SlSendCmd(can_message_t* msg)
{
	qDebug() << "SlSendCmd";

}

void Cmotor_wrk::sl_stop_doza()
{
    qDebug() << "sl_stop_doza";
    send_cmd_stop(DOZA_CAN_ID);
}

///==========================================================