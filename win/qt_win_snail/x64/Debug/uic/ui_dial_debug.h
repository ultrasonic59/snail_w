/********************************************************************************
** Form generated from reading UI file 'dial_debug.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAL_DEBUG_H
#define UI_DIAL_DEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dial_debug
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_addr;
    QLabel *label;
    QLineEdit *lineEdit_wr_dat;
    QPushButton *pushButt_wr;
    QPushButton *pushButton;
    QLineEdit *lineEdit_count;
    QTextEdit *textEdit_rd_dat;
    QComboBox *comboBox_rej;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_test;

    void setupUi(QDialog *Dial_debug)
    {
        if (Dial_debug->objectName().isEmpty())
            Dial_debug->setObjectName(QString::fromUtf8("Dial_debug"));
        Dial_debug->resize(426, 428);
        QFont font;
        font.setPointSize(9);
        Dial_debug->setFont(font);
        buttonBox = new QDialogButtonBox(Dial_debug);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(340, 10, 81, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_addr = new QLineEdit(Dial_debug);
        lineEdit_addr->setObjectName(QString::fromUtf8("lineEdit_addr"));
        lineEdit_addr->setGeometry(QRect(340, 140, 81, 21));
        QFont font1;
        font1.setPointSize(10);
        lineEdit_addr->setFont(font1);
        label = new QLabel(Dial_debug);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(360, 120, 41, 16));
        lineEdit_wr_dat = new QLineEdit(Dial_debug);
        lineEdit_wr_dat->setObjectName(QString::fromUtf8("lineEdit_wr_dat"));
        lineEdit_wr_dat->setGeometry(QRect(340, 230, 81, 22));
        pushButt_wr = new QPushButton(Dial_debug);
        pushButt_wr->setObjectName(QString::fromUtf8("pushButt_wr"));
        pushButt_wr->setGeometry(QRect(340, 260, 81, 28));
        pushButton = new QPushButton(Dial_debug);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 200, 81, 28));
        lineEdit_count = new QLineEdit(Dial_debug);
        lineEdit_count->setObjectName(QString::fromUtf8("lineEdit_count"));
        lineEdit_count->setGeometry(QRect(340, 171, 81, 21));
        textEdit_rd_dat = new QTextEdit(Dial_debug);
        textEdit_rd_dat->setObjectName(QString::fromUtf8("textEdit_rd_dat"));
        textEdit_rd_dat->setGeometry(QRect(10, 10, 321, 391));
        textEdit_rd_dat->setFont(font1);
        comboBox_rej = new QComboBox(Dial_debug);
        comboBox_rej->setObjectName(QString::fromUtf8("comboBox_rej"));
        comboBox_rej->setGeometry(QRect(340, 90, 81, 21));
        comboBox_rej->setFont(font1);
        pushButton_clear = new QPushButton(Dial_debug);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(339, 317, 81, 28));
        pushButton_test = new QPushButton(Dial_debug);
        pushButton_test->setObjectName(QString::fromUtf8("pushButton_test"));
        pushButton_test->setGeometry(QRect(350, 370, 61, 23));

        retranslateUi(Dial_debug);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dial_debug, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dial_debug, SLOT(reject()));
        QObject::connect(pushButton, SIGNAL(clicked()), Dial_debug, SLOT(slot_butt_rd()));
        QObject::connect(pushButt_wr, SIGNAL(clicked()), Dial_debug, SLOT(slot_butt_wr()));
        QObject::connect(pushButton_clear, SIGNAL(clicked()), Dial_debug, SLOT(clear_textEdit()));

        QMetaObject::connectSlotsByName(Dial_debug);
    } // setupUi

    void retranslateUi(QDialog *Dial_debug)
    {
        Dial_debug->setWindowTitle(QCoreApplication::translate("Dial_debug", "Dial_debug", nullptr));
        label->setText(QCoreApplication::translate("Dial_debug", "Addr", nullptr));
        pushButt_wr->setText(QCoreApplication::translate("Dial_debug", "Wr", nullptr));
        pushButton->setText(QCoreApplication::translate("Dial_debug", "Rd", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Dial_debug", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        pushButton_test->setText(QCoreApplication::translate("Dial_debug", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dial_debug: public Ui_Dial_debug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAL_DEBUG_H
