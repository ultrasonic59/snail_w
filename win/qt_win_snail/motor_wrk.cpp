#include "motor_wrk.h"
#include <Qdebug>
#include <QMessageBox>

Cmotor_wrk::Cmotor_wrk(CcmdSender* sender, dev_state_t* dev_state)
                      :p_cmd_sender(sender),p_dev_state(dev_state)
{
    len_step[XX] = DEF_LEN_STEP_X;
    len_step[YY] = DEF_LEN_STEP_Y;
    len_step[ZZ] = DEF_LEN_STEP_Z;
    mot_rej[XX] = DEF_MOT_REJ_X;
    mot_rej[YY] = DEF_MOT_REJ_Y;
    mot_rej[ZZ] = DEF_MOT_REJ_Z;
}
///==============================================================

#define MAX_WAIT_HOME 10000
#define MAX_WAIT_ANS 100
#define MSLEEP_TIME 10

void Cmotor_wrk::send_cmd_go(quint32 id, quint8 dir, quint16 len_step, quint32 num_step)
{
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
    data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}
void Cmotor_wrk::send_cmd_stop(quint32 id)
{
    can_message_t t_can_message;
    t_can_message.id = id;
    t_can_message.dlc = 1;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = STOP_CMD;
    data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}
void Cmotor_wrk::send_cmd_mot_rej(quint32 id, quint8 rej) {
    can_message_t t_can_message;
    t_can_message.id = id;
    t_can_message.dlc = 5;
    t_can_message.IDE = 0;
    t_can_message.RTR = 0;
    t_can_message.data[0] = SET_PARAM;
    t_can_message.data[1] = MOTOR_REJ;
    t_can_message.data[2] = 0;
    t_can_message.data[3] = 1;
    t_can_message.data[4] = rej;
    t_can_message.data[5] = 0;
    t_can_message.data[6] = 0;
    t_can_message.data[7] = 0;
    data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (data_ready == false)
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
    data_ready = false;
    emit s_SendCmd(&t_can_message);
    int wait_rdy_cnt = 0;
    while (data_ready == false)
    {
        wait_rdy_cnt++;
        QThread::msleep(MSLEEP_TIME);
        if (wait_rdy_cnt > MAX_WAIT_ANS)
            break;
    };
}
///=================== X ===========================
void Cmotor_wrk::cl_go_x()
{
    int cur_coord = p_dev_state->coord[XX];
    quint8 t_dir = DIR_PLUS;
    quint32 num_step;
 ///   quint16 len_step = len_step[XX];/// 0;//// = ui->combo_steps->currentText().toInt();
    int need_coord = 0;/// ui->le_xx->text().toInt();
    int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
    if (num_step != 0)
        send_cmd_go(X_AXIS_CAN_ID, t_dir, len_step[XX], num_step);
}
///=================== y ===========================
void Cmotor_wrk::cl_go_y()
{
    int cur_coord = p_dev_state->coord[XX];
    quint8 t_dir = DIR_PLUS;
    quint32 num_step;
  ///  quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    int need_coord = 0;/// ui->le_yy->text().toInt();
    int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
    if (num_step != 0)
        send_cmd_go(Y_AXIS_CAN_ID, t_dir, len_step[YY], num_step);
}
///=================== z ===========================
void Cmotor_wrk::cl_go_z()
{
    int cur_coord = p_dev_state->coord[XX];
    quint8 t_dir = DIR_PLUS;
    quint32 num_step;
 ///   quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    int need_coord = 0;/// ui->le_zz->text().toInt();
    int t_num_step = need_coord - cur_coord;
    if (t_num_step > 0)
    {
        num_step = t_num_step;
        t_dir = DIR_PLUS;
    }
    else
    {
        num_step = -t_num_step;
        t_dir = DIR_MINUS;
    }
    if (num_step != 0)
        send_cmd_go(Z_AXIS_CAN_ID, t_dir, len_step[ZZ], num_step);
}
void Cmotor_wrk::cl_go_home()
{
 ////   quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    send_cmd_go(X_AXIS_CAN_ID, DIR_MINUS, len_step[XX], MAX_NUM_STEP);
    send_cmd_go(Y_AXIS_CAN_ID, DIR_MINUS, len_step[YY], MAX_NUM_STEP);
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
        cl_clr_x();
        cl_clr_y();
       }
    else
        QMessageBox::information(nullptr, "Error!", "go home");
}
///=================== X ===========================
void Cmotor_wrk::cl_xplus()
{
    qDebug() << "cl_xplus";
    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
    send_cmd_mot_rej(X_AXIS_CAN_ID, mot_rej);
    quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    quint32 num_step = 0;/// ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    send_cmd_go(X_AXIS_CAN_ID, DIR_PLUS, len_step, num_step);
}
void Cmotor_wrk::cl_xplus_rel()
{
    qDebug() << "cl_xplus_rel";
    send_cmd_stop(X_AXIS_CAN_ID);
}
void Cmotor_wrk::cl_xminus()
{
    qDebug() << "cl_xminus ";
    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
    send_cmd_mot_rej(X_AXIS_CAN_ID, mot_rej);

    quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    quint32 num_step = 0;/// ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    send_cmd_go(X_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);

    ////   xminusPushed = true;
    ////   xminusLongPush = false;
    ////   QTimer::singleShot(LONG_PUSH_TIME, this, SLOT(SlotLongPush_xminus()));
}
void Cmotor_wrk::cl_xminus_rel()
{
    qDebug() << "cl_xminus_rel ";
    send_cmd_stop(X_AXIS_CAN_ID);
}
///=================== Y ===========================
void Cmotor_wrk::cl_yplus()
{
    qDebug() << "cl_yplus";
    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
    send_cmd_mot_rej(Y_AXIS_CAN_ID, mot_rej);

    quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    quint32 num_step = 0;/// ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    send_cmd_go(Y_AXIS_CAN_ID, DIR_PLUS, len_step, num_step);
}
void Cmotor_wrk::cl_yplus_rel()
{
    qDebug() << "cl_yplus_rel";
    send_cmd_stop(Y_AXIS_CAN_ID);
}
void Cmotor_wrk::cl_yminus()
{
    qDebug() << "cl_yminus ";
    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
    send_cmd_mot_rej(Y_AXIS_CAN_ID, mot_rej);

    quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    quint32 num_step = 0;/// ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;

    send_cmd_go(Y_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);
}
void Cmotor_wrk::cl_yminus_rel()
{
    qDebug() << "cl_yminus_rel ";
    send_cmd_stop(Y_AXIS_CAN_ID);
}
///=================== Z ===========================
void Cmotor_wrk::cl_zplus()
{
    qDebug() << "cl_zplus";
    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
    send_cmd_mot_rej(Z_AXIS_CAN_ID, mot_rej);
    quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    quint32 num_step = 0;/// ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    send_cmd_go(Z_AXIS_CAN_ID, DIR_MINUS, len_step, num_step);
}
void Cmotor_wrk::cl_zplus_rel()
{
    qDebug() << "cl_zplus_rel";
    send_cmd_stop(Z_AXIS_CAN_ID);

}

void Cmotor_wrk::cl_zminus()
{
    qDebug() << "cl_zminus ";
    quint8 mot_rej = 0;/// ui->combo_rej->currentText().toInt();
    send_cmd_mot_rej(Z_AXIS_CAN_ID, mot_rej);
    quint16 len_step = 0;/// ui->combo_steps->currentText().toInt();
    quint32 num_step = 0;/// ui->combo_num_steps->currentText().toInt();
    if (num_step == 0)
        num_step = MAX_NUM_STEP;
    send_cmd_go(Z_AXIS_CAN_ID, DIR_PLUS, len_step, num_step);
}
void Cmotor_wrk::cl_zminus_rel()
{
    qDebug() << "cl_zminus_rel ";
    send_cmd_stop(Z_AXIS_CAN_ID);
}
void Cmotor_wrk::cl_clr_x()
{
    send_cmd_set_coord(X_AXIS_CAN_ID, 0);
}
void Cmotor_wrk::cl_clr_y()
{
    send_cmd_set_coord(Y_AXIS_CAN_ID, 0);
}
void Cmotor_wrk::cl_clr_z()
{
    send_cmd_set_coord(Z_AXIS_CAN_ID, 0);
}
void Cmotor_wrk::cl_stop()
{
    ///send_cmd_stop(X_AXIS_CAN_ID| Y_AXIS_CAN_ID|Z_AXIS_CAN_ID|DOZA_CAN_ID);
    send_cmd_stop(X_AXIS_CAN_ID);
}

void Cmotor_wrk::SlSendCmd(can_message_t* msg)
{
	qDebug() << "SlSendCmd";

}