/********************************************************************************
** Form generated from reading UI file 'port_prop_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORT_PROP_DIALOG_H
#define UI_PORT_PROP_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Port_Prop_Dialog
{
public:
    QLabel *label_port;
    QComboBox *comboBox_p;
    QPushButton *pushButton_apply;

    void setupUi(QDialog *Port_Prop_Dialog)
    {
        if (Port_Prop_Dialog->objectName().isEmpty())
            Port_Prop_Dialog->setObjectName(QString::fromUtf8("Port_Prop_Dialog"));
        Port_Prop_Dialog->resize(319, 56);
        label_port = new QLabel(Port_Prop_Dialog);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        label_port->setGeometry(QRect(7, 10, 41, 31));
        QFont font;
        font.setPointSize(10);
        label_port->setFont(font);
        comboBox_p = new QComboBox(Port_Prop_Dialog);
        comboBox_p->setObjectName(QString::fromUtf8("comboBox_p"));
        comboBox_p->setGeometry(QRect(70, 10, 91, 31));
        pushButton_apply = new QPushButton(Port_Prop_Dialog);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(180, 10, 93, 31));

        retranslateUi(Port_Prop_Dialog);
        QObject::connect(pushButton_apply, SIGNAL(clicked()), Port_Prop_Dialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(Port_Prop_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Port_Prop_Dialog)
    {
        Port_Prop_Dialog->setWindowTitle(QCoreApplication::translate("Port_Prop_Dialog", "Set Com Port", nullptr));
        label_port->setText(QCoreApplication::translate("Port_Prop_Dialog", "Port:", nullptr));
        pushButton_apply->setText(QCoreApplication::translate("Port_Prop_Dialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Port_Prop_Dialog: public Ui_Port_Prop_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORT_PROP_DIALOG_H
