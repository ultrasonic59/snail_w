/********************************************************************************
** Form generated from reading UI file 'Qttest1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST1_H
#define UI_QTTEST1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qttest1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qttest1Class)
    {
        if (Qttest1Class->objectName().isEmpty())
            Qttest1Class->setObjectName(QString::fromUtf8("Qttest1Class"));
        Qttest1Class->resize(600, 400);
        menuBar = new QMenuBar(Qttest1Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Qttest1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qttest1Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Qttest1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Qttest1Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Qttest1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Qttest1Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Qttest1Class->setStatusBar(statusBar);

        retranslateUi(Qttest1Class);

        QMetaObject::connectSlotsByName(Qttest1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Qttest1Class)
    {
        Qttest1Class->setWindowTitle(QCoreApplication::translate("Qttest1Class", "Qttest1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Qttest1Class: public Ui_Qttest1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST1_H
