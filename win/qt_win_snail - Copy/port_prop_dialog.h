#ifndef PORT_PROP_DIALOG_H
#define PORT_PROP_DIALOG_H

#include <QDialog>
#include "ui_port_prop_dialog.h"
#include <QtSerialPort/QSerialPort>


class PortPropDialog : public QDialog
{
protected:
	Ui::Port_Prop_Dialog ui;

public:
	PortPropDialog(QWidget *parent = 0);
	~PortPropDialog();
	QString LastPortName;

	void GetProperties(QString &PortName);
	void SetProperties(QString PortName);
};

#endif // PORT_PROP_DIALOG_H
