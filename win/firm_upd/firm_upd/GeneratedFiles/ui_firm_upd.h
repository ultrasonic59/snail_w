/********************************************************************************
** Form generated from reading UI file 'firm_upd.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRM_UPD_H
#define UI_FIRM_UPD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_firm_upd
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_prog;
    QProgressBar *progressBar;
    QLineEdit *lineEdit_file_path;
    QPushButton *pushButt_file;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_port;
    QComboBox *comboBox_ports;
    QPushButton *pushButton_refresh;
    QPushButton *pushButton_Conn;
    QPushButton *ind_conn;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_axis;
    QComboBox *comboBox_axis;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButt_debug;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *firm_upd)
    {
        if (firm_upd->objectName().isEmpty())
            firm_upd->setObjectName(QStringLiteral("firm_upd"));
        firm_upd->resize(687, 242);
        centralWidget = new QWidget(firm_upd);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_prog = new QPushButton(centralWidget);
        pushButton_prog->setObjectName(QStringLiteral("pushButton_prog"));
        pushButton_prog->setGeometry(QRect(610, 70, 71, 28));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 110, 681, 24));
        progressBar->setValue(24);
        lineEdit_file_path = new QLineEdit(centralWidget);
        lineEdit_file_path->setObjectName(QStringLiteral("lineEdit_file_path"));
        lineEdit_file_path->setGeometry(QRect(1, 70, 571, 27));
        QFont font;
        font.setPointSize(10);
        lineEdit_file_path->setFont(font);
        pushButt_file = new QPushButton(centralWidget);
        pushButt_file->setObjectName(QStringLiteral("pushButt_file"));
        pushButt_file->setGeometry(QRect(579, 70, 31, 31));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButt_file->sizePolicy().hasHeightForWidth());
        pushButt_file->setSizePolicy(sizePolicy);
        pushButt_file->setMaximumSize(QSize(40, 16777215));
        pushButt_file->setFont(font);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 624, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_port = new QLabel(widget);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setFont(font);

        horizontalLayout->addWidget(label_port);

        comboBox_ports = new QComboBox(widget);
        comboBox_ports->setObjectName(QStringLiteral("comboBox_ports"));
        comboBox_ports->setMinimumSize(QSize(0, 22));

        horizontalLayout->addWidget(comboBox_ports);

        pushButton_refresh = new QPushButton(widget);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_refresh->setIcon(icon);

        horizontalLayout->addWidget(pushButton_refresh);

        pushButton_Conn = new QPushButton(widget);
        pushButton_Conn->setObjectName(QStringLiteral("pushButton_Conn"));

        horizontalLayout->addWidget(pushButton_Conn);

        ind_conn = new QPushButton(widget);
        ind_conn->setObjectName(QStringLiteral("ind_conn"));

        horizontalLayout->addWidget(ind_conn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_axis = new QLabel(widget);
        label_axis->setObjectName(QStringLiteral("label_axis"));
        label_axis->setFont(font);

        horizontalLayout->addWidget(label_axis);

        comboBox_axis = new QComboBox(widget);
        comboBox_axis->setObjectName(QStringLiteral("comboBox_axis"));
        comboBox_axis->setMinimumSize(QSize(0, 22));

        horizontalLayout->addWidget(comboBox_axis);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButt_debug = new QPushButton(widget);
        pushButt_debug->setObjectName(QStringLiteral("pushButt_debug"));

        horizontalLayout->addWidget(pushButt_debug);

        firm_upd->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(firm_upd);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        firm_upd->setStatusBar(statusBar);

        retranslateUi(firm_upd);

        QMetaObject::connectSlotsByName(firm_upd);
    } // setupUi

    void retranslateUi(QMainWindow *firm_upd)
    {
        firm_upd->setWindowTitle(QApplication::translate("firm_upd", "firm_upd", 0));
        pushButton_prog->setText(QApplication::translate("firm_upd", "Progr", 0));
        pushButt_file->setText(QApplication::translate("firm_upd", "...", 0));
        label_port->setText(QApplication::translate("firm_upd", "Port:", 0));
        pushButton_Conn->setText(QApplication::translate("firm_upd", "Connect", 0));
        ind_conn->setText(QString());
        label_axis->setText(QApplication::translate("firm_upd", "Axis:", 0));
        comboBox_axis->setCurrentText(QString());
        pushButt_debug->setText(QApplication::translate("firm_upd", "Debug", 0));
    } // retranslateUi

};

namespace Ui {
    class firm_upd: public Ui_firm_upd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRM_UPD_H
