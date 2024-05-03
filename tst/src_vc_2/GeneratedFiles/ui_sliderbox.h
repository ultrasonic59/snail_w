/********************************************************************************
** Form generated from reading UI file 'sliderbox.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDERBOX_H
#define UI_SLIDERBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "slider.h"

QT_BEGIN_NAMESPACE

class Ui_SliderBox
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *chkTitle;
    QLabel *lblTitle;
    QSpinBox *txtValue;
    Slider *sliValue;

    void setupUi(QWidget *SliderBox)
    {
        if (SliderBox->objectName().isEmpty())
            SliderBox->setObjectName(QStringLiteral("SliderBox"));
        SliderBox->resize(185, 50);
        verticalLayout = new QVBoxLayout(SliderBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        chkTitle = new QCheckBox(SliderBox);
        chkTitle->setObjectName(QStringLiteral("chkTitle"));

        horizontalLayout_15->addWidget(chkTitle);

        lblTitle = new QLabel(SliderBox);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));

        horizontalLayout_15->addWidget(lblTitle);

        txtValue = new QSpinBox(SliderBox);
        txtValue->setObjectName(QStringLiteral("txtValue"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtValue->sizePolicy().hasHeightForWidth());
        txtValue->setSizePolicy(sizePolicy);
        txtValue->setAlignment(Qt::AlignCenter);
        txtValue->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtValue->setMinimum(10);
        txtValue->setMaximum(200);

        horizontalLayout_15->addWidget(txtValue);

        horizontalLayout_15->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_15);

        sliValue = new Slider(SliderBox);
        sliValue->setObjectName(QStringLiteral("sliValue"));
        sliValue->setMinimum(10);
        sliValue->setMaximum(200);
        sliValue->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliValue);


        retranslateUi(SliderBox);

        QMetaObject::connectSlotsByName(SliderBox);
    } // setupUi

    void retranslateUi(QWidget *SliderBox)
    {
        SliderBox->setWindowTitle(QApplication::translate("SliderBox", "Form", 0));
        chkTitle->setText(QApplication::translate("SliderBox", "Title:", 0));
        lblTitle->setText(QApplication::translate("SliderBox", "Title:", 0));
    } // retranslateUi

};

namespace Ui {
    class SliderBox: public Ui_SliderBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDERBOX_H
