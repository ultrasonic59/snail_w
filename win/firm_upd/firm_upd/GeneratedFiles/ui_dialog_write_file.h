/********************************************************************************
** Form generated from reading UI file 'dialog_write_file.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_WRITE_FILE_H
#define UI_DIALOG_WRITE_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_write_file
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_dir;
    QLabel *lab_path;
    QLabel *lab_file_path;
    QLineEdit *lineEdit_file_path;
    QPushButton *pushButt_file;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Dialog_write_file)
    {
        if (Dialog_write_file->objectName().isEmpty())
            Dialog_write_file->setObjectName(QStringLiteral("Dialog_write_file"));
        Dialog_write_file->resize(528, 141);
        verticalLayout = new QVBoxLayout(Dialog_write_file);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(10, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_dir = new QLineEdit(Dialog_write_file);
        lineEdit_dir->setObjectName(QStringLiteral("lineEdit_dir"));
        QFont font;
        font.setPointSize(10);
        lineEdit_dir->setFont(font);

        gridLayout->addWidget(lineEdit_dir, 1, 1, 1, 1);

        lab_path = new QLabel(Dialog_write_file);
        lab_path->setObjectName(QStringLiteral("lab_path"));
        QFont font1;
        font1.setPointSize(11);
        lab_path->setFont(font1);

        gridLayout->addWidget(lab_path, 1, 0, 1, 1);

        lab_file_path = new QLabel(Dialog_write_file);
        lab_file_path->setObjectName(QStringLiteral("lab_file_path"));
        lab_file_path->setFont(font1);

        gridLayout->addWidget(lab_file_path, 0, 0, 1, 1);

        lineEdit_file_path = new QLineEdit(Dialog_write_file);
        lineEdit_file_path->setObjectName(QStringLiteral("lineEdit_file_path"));
        lineEdit_file_path->setFont(font);

        gridLayout->addWidget(lineEdit_file_path, 0, 1, 1, 1);

        pushButt_file = new QPushButton(Dialog_write_file);
        pushButt_file->setObjectName(QStringLiteral("pushButt_file"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButt_file->sizePolicy().hasHeightForWidth());
        pushButt_file->setSizePolicy(sizePolicy);
        pushButt_file->setMaximumSize(QSize(40, 16777215));
        pushButt_file->setFont(font);

        gridLayout->addWidget(pushButt_file, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(10, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(10, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_apply = new QPushButton(Dialog_write_file);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setFont(font);

        horizontalLayout->addWidget(pushButton_apply);

        pushButton_cancel = new QPushButton(Dialog_write_file);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setFont(font);

        horizontalLayout->addWidget(pushButton_cancel);

        horizontalSpacer_2 = new QSpacerItem(10, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(lineEdit_file_path, pushButt_file);
        QWidget::setTabOrder(pushButt_file, lineEdit_dir);
        QWidget::setTabOrder(lineEdit_dir, pushButton_apply);
        QWidget::setTabOrder(pushButton_apply, pushButton_cancel);

        retranslateUi(Dialog_write_file);
        QObject::connect(pushButton_apply, SIGNAL(clicked()), Dialog_write_file, SLOT(accept()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), Dialog_write_file, SLOT(reject()));
        QObject::connect(pushButt_file, SIGNAL(clicked()), Dialog_write_file, SLOT(on_file_path()));

        QMetaObject::connectSlotsByName(Dialog_write_file);
    } // setupUi

    void retranslateUi(QDialog *Dialog_write_file)
    {
        Dialog_write_file->setWindowTitle(QApplication::translate("Dialog_write_file", "dialog_write_file", 0));
        lab_path->setText(QApplication::translate("Dialog_write_file", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \320\262 \320\277\321\200\320\270\320\261\320\276\321\200\320\265", 0));
        lab_file_path->setText(QApplication::translate("Dialog_write_file", "\320\244\320\260\320\271\320\273", 0));
        pushButt_file->setText(QApplication::translate("Dialog_write_file", "...", 0));
        pushButton_apply->setText(QApplication::translate("Dialog_write_file", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", 0));
        pushButton_cancel->setText(QApplication::translate("Dialog_write_file", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_write_file: public Ui_Dialog_write_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_WRITE_FILE_H
