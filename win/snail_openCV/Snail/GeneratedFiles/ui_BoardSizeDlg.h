/********************************************************************************
** Form generated from reading UI file 'BoardSizeDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARDSIZEDLG_H
#define UI_BOARDSIZEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_boardSizeDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxWidth;
    QSpinBox *spinBoxHeight;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *boardSizeDlg)
    {
        if (boardSizeDlg->objectName().isEmpty())
            boardSizeDlg->setObjectName(QStringLiteral("boardSizeDlg"));
        boardSizeDlg->resize(365, 141);
        verticalLayout = new QVBoxLayout(boardSizeDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(boardSizeDlg);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(boardSizeDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBoxWidth = new QSpinBox(boardSizeDlg);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(1);
        spinBoxWidth->setMaximum(10000);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxWidth);

        spinBoxHeight = new QSpinBox(boardSizeDlg);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(1);
        spinBoxHeight->setMaximum(10000);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxHeight);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(boardSizeDlg);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(boardSizeDlg);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(boardSizeDlg);
        QObject::connect(okButton, SIGNAL(clicked()), boardSizeDlg, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), boardSizeDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(boardSizeDlg);
    } // setupUi

    void retranslateUi(QDialog *boardSizeDlg)
    {
        boardSizeDlg->setWindowTitle(QApplication::translate("boardSizeDlg", "Set board size in MM", 0));
        label->setText(QApplication::translate("boardSizeDlg", "Width", 0));
        label_2->setText(QApplication::translate("boardSizeDlg", "Heght", 0));
        okButton->setText(QApplication::translate("boardSizeDlg", "OK", 0));
        cancelButton->setText(QApplication::translate("boardSizeDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class boardSizeDlg: public Ui_boardSizeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARDSIZEDLG_H
