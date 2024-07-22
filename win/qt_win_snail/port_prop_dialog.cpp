#include "port_prop_dialog.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

PortPropDialog::PortPropDialog(QWidget *parent) : 
	QDialog(parent, Qt::Window),
	ui()
{
ui.setupUi(this);
ui.comboBox_p->clear();
}

PortPropDialog::~PortPropDialog()
{

}



void PortPropDialog::GetProperties(QString &PortName)
{
PortName=ui.comboBox_p->currentText();
}

void PortPropDialog::SetProperties(QString PortName)
{
LastPortName = PortName;
////ui.comboBox_p->clear();
 foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
	if(info.description() != "")
		{
		ui.comboBox_p->addItem(info.portName());
		if(LastPortName == info.portName())
			ui.comboBox_p->setCurrentIndex( ui.comboBox_p->count() - 1 );		// переключаем на выбранный порт ?
		}
	}


}