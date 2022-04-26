/********************************************************************************
** Form generated from reading UI file 'snail.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAIL_H
#define UI_SNAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qscaledgraphview.h"

QT_BEGIN_NAMESPACE

class Ui_SnailClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScaledGraphView *graphicsView;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QListView *listView;
    QPushButton *btnUploadPoints;
    QPushButton *btnAdjGrid;
    QPushButton *btnAdjustImg;
    QPushButton *btnLoad;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SnailClass)
    {
        if (SnailClass->objectName().isEmpty())
            SnailClass->setObjectName(QStringLiteral("SnailClass"));
        SnailClass->resize(1046, 777);
        centralWidget = new QWidget(SnailClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QScaledGraphView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);

        btnUploadPoints = new QPushButton(centralWidget);
        btnUploadPoints->setObjectName(QStringLiteral("btnUploadPoints"));

        verticalLayout->addWidget(btnUploadPoints);

        btnAdjGrid = new QPushButton(centralWidget);
        btnAdjGrid->setObjectName(QStringLiteral("btnAdjGrid"));

        verticalLayout->addWidget(btnAdjGrid);

        btnAdjustImg = new QPushButton(centralWidget);
        btnAdjustImg->setObjectName(QStringLiteral("btnAdjustImg"));

        verticalLayout->addWidget(btnAdjustImg);

        btnLoad = new QPushButton(centralWidget);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));

        verticalLayout->addWidget(btnLoad);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 5);
        gridLayout->setColumnStretch(1, 1);
        SnailClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SnailClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1046, 21));
        SnailClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SnailClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SnailClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SnailClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setAutoFillBackground(true);
        SnailClass->setStatusBar(statusBar);

        retranslateUi(SnailClass);

        QMetaObject::connectSlotsByName(SnailClass);
    } // setupUi

    void retranslateUi(QMainWindow *SnailClass)
    {
        SnailClass->setWindowTitle(QApplication::translate("SnailClass", "Snail", 0));
        btnUploadPoints->setText(QApplication::translate("SnailClass", "Upload", 0));
        btnAdjGrid->setText(QApplication::translate("SnailClass", "Grid", 0));
        btnAdjustImg->setText(QApplication::translate("SnailClass", "Adjust", 0));
        btnLoad->setText(QApplication::translate("SnailClass", "Load", 0));
    } // retranslateUi

};

namespace Ui {
    class SnailClass: public Ui_SnailClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAIL_H
