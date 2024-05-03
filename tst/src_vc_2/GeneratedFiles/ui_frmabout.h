/********************************************************************************
** Form generated from reading UI file 'frmabout.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMABOUT_H
#define UI_FRMABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_frmAbout
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame;
    QLabel *lblAbout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QPlainTextEdit *txtLicense;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdOk;

    void setupUi(QDialog *frmAbout)
    {
        if (frmAbout->objectName().isEmpty())
            frmAbout->setObjectName(QStringLiteral("frmAbout"));
        frmAbout->resize(431, 500);
        frmAbout->setStyleSheet(QLatin1String("QWidget {\n"
"	font-size: 9pt;\n"
"}"));
        verticalLayout = new QVBoxLayout(frmAbout);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(14);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        frame = new QFrame(frmAbout);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(100, 100));
        frame->setStyleSheet(QStringLiteral("image: url(:/images/candle_256.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frame);

        lblAbout = new QLabel(frmAbout);
        lblAbout->setObjectName(QStringLiteral("lblAbout"));
        lblAbout->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lblAbout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        label_2 = new QLabel(frmAbout);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        txtLicense = new QPlainTextEdit(frmAbout);
        txtLicense->setObjectName(QStringLiteral("txtLicense"));
        QFont font;
        font.setPointSize(9);
        txtLicense->setFont(font);
        txtLicense->setReadOnly(true);

        verticalLayout->addWidget(txtLicense);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdOk = new QPushButton(frmAbout);
        cmdOk->setObjectName(QStringLiteral("cmdOk"));

        horizontalLayout->addWidget(cmdOk);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(frmAbout);

        QMetaObject::connectSlotsByName(frmAbout);
    } // setupUi

    void retranslateUi(QDialog *frmAbout)
    {
        frmAbout->setWindowTitle(QApplication::translate("frmAbout", "About", 0));
        lblAbout->setText(QApplication::translate("frmAbout", "<html><head/><body><p>Candle 2<br/>Version: 2.0<br/>License: GNU GENERAL PUBLIC LICENSE<a href=\"https://github.com/Schildkroet/Candle2/\"><span style=\" text-decoration: underline; color:#0000ff;\"></span><br/></a>\302\251 2015-2016 Hayrullin Denis Ravilevich<br/>\302\251 2018-2019 Patrick F.</p><p>Visit: <a href=\"https://github.com/Schildkroet/Candle2/\"><span style=\" text-decoration: underline; color:#0000ff;\">https://github.com/Schildkroet/Candle2/</span></a></p></body></html>", 0));
        label_2->setText(QApplication::translate("frmAbout", "<html><head/><body><p><span style=\" font-weight:600;\">The program is provided AS IS without any guarantees or warranty. Use at your own risk.</span></p></body></html>", 0));
        cmdOk->setText(QApplication::translate("frmAbout", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class frmAbout: public Ui_frmAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMABOUT_H
