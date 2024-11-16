/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *edInput;
    QLabel *label_2;
    QLineEdit *edOutput;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbUpperDemo;
    QRadioButton *rbConnectDemo;
    QRadioButton *rbConnectFuncDemo;
    QTextEdit *txtScript;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *bnRun;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(706, 504);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(MainWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        edInput = new QLineEdit(MainWidget);
        edInput->setObjectName(QString::fromUtf8("edInput"));

        verticalLayout->addWidget(edInput);

        label_2 = new QLabel(MainWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        edOutput = new QLineEdit(MainWidget);
        edOutput->setObjectName(QString::fromUtf8("edOutput"));
        edOutput->setReadOnly(true);

        verticalLayout->addWidget(edOutput);

        label_3 = new QLabel(MainWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rbUpperDemo = new QRadioButton(MainWidget);
        rbUpperDemo->setObjectName(QString::fromUtf8("rbUpperDemo"));
        rbUpperDemo->setChecked(true);

        horizontalLayout_2->addWidget(rbUpperDemo);

        rbConnectDemo = new QRadioButton(MainWidget);
        rbConnectDemo->setObjectName(QString::fromUtf8("rbConnectDemo"));

        horizontalLayout_2->addWidget(rbConnectDemo);

        rbConnectFuncDemo = new QRadioButton(MainWidget);
        rbConnectFuncDemo->setObjectName(QString::fromUtf8("rbConnectFuncDemo"));

        horizontalLayout_2->addWidget(rbConnectFuncDemo);


        verticalLayout->addLayout(horizontalLayout_2);

        txtScript = new QTextEdit(MainWidget);
        txtScript->setObjectName(QString::fromUtf8("txtScript"));

        verticalLayout->addWidget(txtScript);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bnRun = new QPushButton(MainWidget);
        bnRun->setObjectName(QString::fromUtf8("bnRun"));

        horizontalLayout->addWidget(bnRun);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
        label->setText(QCoreApplication::translate("MainWidget", "\320\222\321\205\320\276\320\264:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWidget", "\320\222\321\213\321\205\320\276\320\264:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWidget", "\320\241\320\272\321\200\320\270\320\277\321\202:", nullptr));
        rbUpperDemo->setText(QCoreApplication::translate("MainWidget", "upper_demo.js", nullptr));
        rbConnectDemo->setText(QCoreApplication::translate("MainWidget", "connect_demo.js", nullptr));
        rbConnectFuncDemo->setText(QCoreApplication::translate("MainWidget", "connect_func_demo.js", nullptr));
        bnRun->setText(QCoreApplication::translate("MainWidget", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
