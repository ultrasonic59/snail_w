/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Conn;
    QPushButton *pushButton_refresh;
    QComboBox *comboBox_ports;
    QLabel *label_port;
    QPushButton *pushButton_prog;
    QPushButton *ind_conn;
    QLabel *label_axis;
    QComboBox *comboBox_axis;
    QProgressBar *progressBar;
    QLineEdit *lineEdit_file_path;
    QPushButton *pushButt_file;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(497, 156);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Conn = new QPushButton(centralWidget);
        pushButton_Conn->setObjectName(QStringLiteral("pushButton_Conn"));
        pushButton_Conn->setGeometry(QRect(190, 20, 91, 28));
        pushButton_refresh = new QPushButton(centralWidget);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        pushButton_refresh->setGeometry(QRect(150, 20, 33, 29));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_refresh->setIcon(icon);
        comboBox_ports = new QComboBox(centralWidget);
        comboBox_ports->setObjectName(QStringLiteral("comboBox_ports"));
        comboBox_ports->setGeometry(QRect(70, 20, 73, 22));
        comboBox_ports->setMinimumSize(QSize(0, 22));
        label_port = new QLabel(centralWidget);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setGeometry(QRect(10, 20, 43, 30));
        QFont font;
        font.setPointSize(10);
        label_port->setFont(font);
        pushButton_prog = new QPushButton(centralWidget);
        pushButton_prog->setObjectName(QStringLiteral("pushButton_prog"));
        pushButton_prog->setGeometry(QRect(400, 70, 71, 28));
        ind_conn = new QPushButton(centralWidget);
        ind_conn->setObjectName(QStringLiteral("ind_conn"));
        ind_conn->setGeometry(QRect(290, 20, 31, 28));
        label_axis = new QLabel(centralWidget);
        label_axis->setObjectName(QStringLiteral("label_axis"));
        label_axis->setGeometry(QRect(330, 20, 43, 30));
        label_axis->setFont(font);
        comboBox_axis = new QComboBox(centralWidget);
        comboBox_axis->setObjectName(QStringLiteral("comboBox_axis"));
        comboBox_axis->setGeometry(QRect(380, 29, 91, 22));
        comboBox_axis->setMinimumSize(QSize(0, 22));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 110, 503, 24));
        progressBar->setValue(24);
        lineEdit_file_path = new QLineEdit(centralWidget);
        lineEdit_file_path->setObjectName(QStringLiteral("lineEdit_file_path"));
        lineEdit_file_path->setGeometry(QRect(1, 70, 341, 27));
        lineEdit_file_path->setFont(font);
        pushButt_file = new QPushButton(centralWidget);
        pushButt_file->setObjectName(QStringLiteral("pushButt_file"));
        pushButt_file->setGeometry(QRect(350, 70, 40, 31));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButt_file->sizePolicy().hasHeightForWidth());
        pushButt_file->setSizePolicy(sizePolicy);
        pushButt_file->setMaximumSize(QSize(40, 16777215));
        pushButt_file->setFont(font);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Firmware_update", 0));
        pushButton_Conn->setText(QApplication::translate("MainWindow", "Connect", 0));
        label_port->setText(QApplication::translate("MainWindow", "Port:", 0));
        pushButton_prog->setText(QApplication::translate("MainWindow", "Progr", 0));
        ind_conn->setText(QString());
        label_axis->setText(QApplication::translate("MainWindow", "Axis:", 0));
        comboBox_axis->setCurrentText(QString());
        pushButt_file->setText(QApplication::translate("MainWindow", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
