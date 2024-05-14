/********************************************************************************
** Form generated from reading UI file 'win_snail.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIN_SNAIL_H
#define UI_WIN_SNAIL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include <plotterwidget.h>
#include <styledtoolbutton.h>
#include "comboboxkey.h"

QT_BEGIN_NAMESPACE

class Ui_win_snail
{
public:
    QAction *actFileOpen;
    QAction *actFileExit;
    QAction *actionSelect;
    QAction *actFileNew;
    QAction *actFileSave;
    QAction *actFileSaveAs;
    QAction *actAbout;
    QAction *actRecentClear;
    QAction *actFileSaveTransformedAs;
    QAction *actionMachine_settings;
    QAction *actionHard_Reset;
    QAction *actionSave_TLS_Position;
    QAction *actionSet_TLS_Position;
    QAction *actionDisable_Stepper;
    QWidget *centralWidget;
    QWidget *widgetJog;
    QGridLayout *gridLayout;
    StyledToolButton *cmdYPlus;
    StyledToolButton *cmdZMinus;
    StyledToolButton *cmdXPlus;
    StyledToolButton *cmdZPlus;
    QLabel *label_20;
    ComboBoxKey *cboJogStep;
    QCheckBox *chkKeyboardControl;
    StyledToolButton *cmdStop;
    StyledToolButton *cmdYMinus;
    ComboBoxKey *cboJogFeed;
    StyledToolButton *cmdXMinus;
    QFrame *frame;
    QSplitter *splitter;
    plotterwidget *CamWidget;
    QWidget *widget;
    QPushButton *buttDebug;
    QPushButton *buttCon;
    QSlider *lightSlider;
    QMenuBar *menuBar;
    QMenu *mnuFile;
    QMenu *mnuRecent;
    QMenu *mnuService;
    QMenu *mnuHelp;
    QMenu *menuMachine;

    void setupUi(QMainWindow *win_snail)
    {
        if (win_snail->objectName().isEmpty())
            win_snail->setObjectName(QString::fromUtf8("win_snail"));
        win_snail->resize(768, 789);
        win_snail->setAcceptDrops(true);
        win_snail->setWindowTitle(QString::fromUtf8("win_snail"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/candle_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        win_snail->setWindowIcon(icon);
        win_snail->setStyleSheet(QString::fromUtf8(""));
        actFileOpen = new QAction(win_snail);
        actFileOpen->setObjectName(QString::fromUtf8("actFileOpen"));
        actFileExit = new QAction(win_snail);
        actFileExit->setObjectName(QString::fromUtf8("actFileExit"));
        actionSelect = new QAction(win_snail);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actFileNew = new QAction(win_snail);
        actFileNew->setObjectName(QString::fromUtf8("actFileNew"));
        actFileSave = new QAction(win_snail);
        actFileSave->setObjectName(QString::fromUtf8("actFileSave"));
        actFileSaveAs = new QAction(win_snail);
        actFileSaveAs->setObjectName(QString::fromUtf8("actFileSaveAs"));
        actAbout = new QAction(win_snail);
        actAbout->setObjectName(QString::fromUtf8("actAbout"));
        actRecentClear = new QAction(win_snail);
        actRecentClear->setObjectName(QString::fromUtf8("actRecentClear"));
        actFileSaveTransformedAs = new QAction(win_snail);
        actFileSaveTransformedAs->setObjectName(QString::fromUtf8("actFileSaveTransformedAs"));
        actionMachine_settings = new QAction(win_snail);
        actionMachine_settings->setObjectName(QString::fromUtf8("actionMachine_settings"));
        actionHard_Reset = new QAction(win_snail);
        actionHard_Reset->setObjectName(QString::fromUtf8("actionHard_Reset"));
        actionSave_TLS_Position = new QAction(win_snail);
        actionSave_TLS_Position->setObjectName(QString::fromUtf8("actionSave_TLS_Position"));
        actionSet_TLS_Position = new QAction(win_snail);
        actionSet_TLS_Position->setObjectName(QString::fromUtf8("actionSet_TLS_Position"));
        actionDisable_Stepper = new QAction(win_snail);
        actionDisable_Stepper->setObjectName(QString::fromUtf8("actionDisable_Stepper"));
        centralWidget = new QWidget(win_snail);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widgetJog = new QWidget(centralWidget);
        widgetJog->setObjectName(QString::fromUtf8("widgetJog"));
        widgetJog->setGeometry(QRect(600, 520, 162, 237));
        widgetJog->setStyleSheet(QString::fromUtf8("background-color: rgb(128, 255, 128);"));
        gridLayout = new QGridLayout(widgetJog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cmdYPlus = new StyledToolButton(widgetJog);
        cmdYPlus->setObjectName(QString::fromUtf8("cmdYPlus"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmdYPlus->sizePolicy().hasHeightForWidth());
        cmdYPlus->setSizePolicy(sizePolicy);
        cmdYPlus->setMinimumSize(QSize(44, 44));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("resource/chevron-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("resource/chevron-up.png"), QSize(), QIcon::Normal, QIcon::On);
        cmdYPlus->setIcon(icon1);
        cmdYPlus->setIconSize(QSize(30, 30));

        gridLayout->addWidget(cmdYPlus, 0, 3, 1, 1);

        cmdZMinus = new StyledToolButton(widgetJog);
        cmdZMinus->setObjectName(QString::fromUtf8("cmdZMinus"));
        sizePolicy.setHeightForWidth(cmdZMinus->sizePolicy().hasHeightForWidth());
        cmdZMinus->setSizePolicy(sizePolicy);
        cmdZMinus->setMinimumSize(QSize(44, 44));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("resource/icon-arrow-down-b.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdZMinus->setIcon(icon2);
        cmdZMinus->setIconSize(QSize(28, 28));

        gridLayout->addWidget(cmdZMinus, 2, 4, 1, 1);

        cmdXPlus = new StyledToolButton(widgetJog);
        cmdXPlus->setObjectName(QString::fromUtf8("cmdXPlus"));
        sizePolicy.setHeightForWidth(cmdXPlus->sizePolicy().hasHeightForWidth());
        cmdXPlus->setSizePolicy(sizePolicy);
        cmdXPlus->setMinimumSize(QSize(44, 44));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("resource/chevron-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdXPlus->setIcon(icon3);
        cmdXPlus->setIconSize(QSize(30, 30));

        gridLayout->addWidget(cmdXPlus, 1, 4, 1, 1);

        cmdZPlus = new StyledToolButton(widgetJog);
        cmdZPlus->setObjectName(QString::fromUtf8("cmdZPlus"));
        sizePolicy.setHeightForWidth(cmdZPlus->sizePolicy().hasHeightForWidth());
        cmdZPlus->setSizePolicy(sizePolicy);
        cmdZPlus->setMinimumSize(QSize(44, 44));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("resource/icon-arrow-up-b.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdZPlus->setIcon(icon4);
        cmdZPlus->setIconSize(QSize(28, 28));

        gridLayout->addWidget(cmdZPlus, 0, 4, 1, 1);

        label_20 = new QLabel(widgetJog);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_20->setFont(font);

        gridLayout->addWidget(label_20, 3, 0, 1, 1);

        cboJogStep = new ComboBoxKey(widgetJog);
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->addItem(QString());
        cboJogStep->setObjectName(QString::fromUtf8("cboJogStep"));
        cboJogStep->setEditable(true);
        cboJogStep->setInsertPolicy(QComboBox::NoInsert);

        gridLayout->addWidget(cboJogStep, 3, 1, 1, 4);

        chkKeyboardControl = new QCheckBox(widgetJog);
        chkKeyboardControl->setObjectName(QString::fromUtf8("chkKeyboardControl"));

        gridLayout->addWidget(chkKeyboardControl, 5, 0, 1, 5);

        cmdStop = new StyledToolButton(widgetJog);
        cmdStop->setObjectName(QString::fromUtf8("cmdStop"));
        sizePolicy.setHeightForWidth(cmdStop->sizePolicy().hasHeightForWidth());
        cmdStop->setSizePolicy(sizePolicy);
        cmdStop->setMinimumSize(QSize(36, 36));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("resource/brake.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdStop->setIcon(icon5);
        cmdStop->setIconSize(QSize(30, 30));

        gridLayout->addWidget(cmdStop, 1, 3, 1, 1);

        cmdYMinus = new StyledToolButton(widgetJog);
        cmdYMinus->setObjectName(QString::fromUtf8("cmdYMinus"));
        sizePolicy.setHeightForWidth(cmdYMinus->sizePolicy().hasHeightForWidth());
        cmdYMinus->setSizePolicy(sizePolicy);
        cmdYMinus->setMinimumSize(QSize(44, 44));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("resource/chevron-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdYMinus->setIcon(icon6);
        cmdYMinus->setIconSize(QSize(30, 30));

        gridLayout->addWidget(cmdYMinus, 2, 3, 1, 1);

        cboJogFeed = new ComboBoxKey(widgetJog);
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->addItem(QString());
        cboJogFeed->setObjectName(QString::fromUtf8("cboJogFeed"));
        cboJogFeed->setEditable(true);
        cboJogFeed->setInsertPolicy(QComboBox::NoInsert);

        gridLayout->addWidget(cboJogFeed, 4, 1, 1, 4);

        cmdXMinus = new StyledToolButton(widgetJog);
        cmdXMinus->setObjectName(QString::fromUtf8("cmdXMinus"));
        sizePolicy.setHeightForWidth(cmdXMinus->sizePolicy().hasHeightForWidth());
        cmdXMinus->setSizePolicy(sizePolicy);
        cmdXMinus->setMinimumSize(QSize(44, 44));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("resource/chevron-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdXMinus->setIcon(icon7);
        cmdXMinus->setIconSize(QSize(30, 30));

        gridLayout->addWidget(cmdXMinus, 1, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(600, 49, 161, 151));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(-21, 0, 611, 761));
        splitter->setOrientation(Qt::Vertical);
        CamWidget = new plotterwidget(splitter);
        CamWidget->setObjectName(QString::fromUtf8("CamWidget"));
        CamWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(150, 128, 128);"));
        splitter->addWidget(CamWidget);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(120, 158, 128);"));
        splitter->addWidget(widget);
        buttDebug = new QPushButton(centralWidget);
        buttDebug->setObjectName(QString::fromUtf8("buttDebug"));
        buttDebug->setGeometry(QRect(680, 0, 41, 23));
        buttCon = new QPushButton(centralWidget);
        buttCon->setObjectName(QString::fromUtf8("buttCon"));
        buttCon->setGeometry(QRect(720, 0, 41, 23));
        lightSlider = new QSlider(centralWidget);
        lightSlider->setObjectName(QString::fromUtf8("lightSlider"));
        lightSlider->setGeometry(QRect(600, 490, 160, 21));
        lightSlider->setOrientation(Qt::Horizontal);
        win_snail->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(win_snail);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 768, 26));
        mnuFile = new QMenu(menuBar);
        mnuFile->setObjectName(QString::fromUtf8("mnuFile"));
        mnuRecent = new QMenu(mnuFile);
        mnuRecent->setObjectName(QString::fromUtf8("mnuRecent"));
        mnuService = new QMenu(menuBar);
        mnuService->setObjectName(QString::fromUtf8("mnuService"));
        mnuHelp = new QMenu(menuBar);
        mnuHelp->setObjectName(QString::fromUtf8("mnuHelp"));
        menuMachine = new QMenu(menuBar);
        menuMachine->setObjectName(QString::fromUtf8("menuMachine"));
        win_snail->setMenuBar(menuBar);
        QWidget::setTabOrder(cmdXPlus, cmdYPlus);
        QWidget::setTabOrder(cmdYPlus, cmdYMinus);
        QWidget::setTabOrder(cmdYMinus, cmdZPlus);
        QWidget::setTabOrder(cmdZPlus, cmdZMinus);
        QWidget::setTabOrder(cmdZMinus, chkKeyboardControl);

        menuBar->addAction(mnuFile->menuAction());
        menuBar->addAction(mnuService->menuAction());
        menuBar->addAction(menuMachine->menuAction());
        menuBar->addAction(mnuHelp->menuAction());
        mnuFile->addAction(actFileNew);
        mnuFile->addAction(actFileOpen);
        mnuFile->addAction(mnuRecent->menuAction());
        mnuFile->addSeparator();
        mnuFile->addAction(actFileSave);
        mnuFile->addAction(actFileSaveAs);
        mnuFile->addAction(actFileSaveTransformedAs);
        mnuFile->addSeparator();
        mnuFile->addAction(actFileExit);
        mnuRecent->addSeparator();
        mnuRecent->addAction(actRecentClear);
        mnuService->addAction(actionSelect);
        mnuHelp->addAction(actAbout);
        menuMachine->addAction(actionMachine_settings);
        menuMachine->addAction(actionHard_Reset);
        menuMachine->addAction(actionSet_TLS_Position);
        menuMachine->addAction(actionDisable_Stepper);

        retranslateUi(win_snail);

        QMetaObject::connectSlotsByName(win_snail);
    } // setupUi

    void retranslateUi(QMainWindow *win_snail)
    {
        actFileOpen->setText(QCoreApplication::translate("win_snail", "&Open", nullptr));
        actFileExit->setText(QCoreApplication::translate("win_snail", "E&xit", nullptr));
        actionSelect->setText(QCoreApplication::translate("win_snail", "Select", nullptr));
        actFileNew->setText(QCoreApplication::translate("win_snail", "&New", nullptr));
        actFileSave->setText(QCoreApplication::translate("win_snail", "&Save", nullptr));
        actFileSaveAs->setText(QCoreApplication::translate("win_snail", "Save &as...", nullptr));
        actAbout->setText(QCoreApplication::translate("win_snail", "&About", nullptr));
        actRecentClear->setText(QCoreApplication::translate("win_snail", "&Clear", nullptr));
        actFileSaveTransformedAs->setText(QCoreApplication::translate("win_snail", "Save &transformed as...", nullptr));
        actionMachine_settings->setText(QCoreApplication::translate("win_snail", "Machine settings", nullptr));
        actionHard_Reset->setText(QCoreApplication::translate("win_snail", "Hard Reset", nullptr));
#if QT_CONFIG(tooltip)
        actionHard_Reset->setToolTip(QCoreApplication::translate("win_snail", "<html><head/><body><p>Perform Hard Reset of machine control</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave_TLS_Position->setText(QCoreApplication::translate("win_snail", "Set TLS Position", nullptr));
        actionSet_TLS_Position->setText(QCoreApplication::translate("win_snail", "Set TLS Position", nullptr));
        actionDisable_Stepper->setText(QCoreApplication::translate("win_snail", "Disable Stepper", nullptr));
#if QT_CONFIG(tooltip)
        cmdYPlus->setToolTip(QCoreApplication::translate("win_snail", "Y+", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdYPlus->setText(QString());
#if QT_CONFIG(tooltip)
        cmdZMinus->setToolTip(QCoreApplication::translate("win_snail", "Z-", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdZMinus->setText(QString());
#if QT_CONFIG(tooltip)
        cmdXPlus->setToolTip(QCoreApplication::translate("win_snail", "X+", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdXPlus->setText(QString());
#if QT_CONFIG(tooltip)
        cmdZPlus->setToolTip(QCoreApplication::translate("win_snail", "Z+", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdZPlus->setText(QString());
        label_20->setText(QCoreApplication::translate("win_snail", "Step:", nullptr));
        cboJogStep->setItemText(0, QCoreApplication::translate("win_snail", "Continuously", nullptr));
        cboJogStep->setItemText(1, QCoreApplication::translate("win_snail", "0.01", nullptr));
        cboJogStep->setItemText(2, QCoreApplication::translate("win_snail", "0.1", nullptr));
        cboJogStep->setItemText(3, QCoreApplication::translate("win_snail", "1", nullptr));
        cboJogStep->setItemText(4, QCoreApplication::translate("win_snail", "2", nullptr));
        cboJogStep->setItemText(5, QCoreApplication::translate("win_snail", "5", nullptr));
        cboJogStep->setItemText(6, QCoreApplication::translate("win_snail", "10", nullptr));
        cboJogStep->setItemText(7, QCoreApplication::translate("win_snail", "20", nullptr));
        cboJogStep->setItemText(8, QCoreApplication::translate("win_snail", "50", nullptr));
        cboJogStep->setItemText(9, QCoreApplication::translate("win_snail", "100", nullptr));
        cboJogStep->setItemText(10, QCoreApplication::translate("win_snail", "200", nullptr));

        chkKeyboardControl->setText(QCoreApplication::translate("win_snail", "Keyboard control", nullptr));
#if QT_CONFIG(tooltip)
        cmdStop->setToolTip(QCoreApplication::translate("win_snail", "Stop", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdStop->setText(QString());
#if QT_CONFIG(tooltip)
        cmdYMinus->setToolTip(QCoreApplication::translate("win_snail", "Y-", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdYMinus->setText(QString());
        cboJogFeed->setItemText(0, QCoreApplication::translate("win_snail", "10", nullptr));
        cboJogFeed->setItemText(1, QCoreApplication::translate("win_snail", "20", nullptr));
        cboJogFeed->setItemText(2, QCoreApplication::translate("win_snail", "50", nullptr));
        cboJogFeed->setItemText(3, QCoreApplication::translate("win_snail", "100", nullptr));
        cboJogFeed->setItemText(4, QCoreApplication::translate("win_snail", "200", nullptr));
        cboJogFeed->setItemText(5, QCoreApplication::translate("win_snail", "500", nullptr));
        cboJogFeed->setItemText(6, QCoreApplication::translate("win_snail", "1000", nullptr));
        cboJogFeed->setItemText(7, QCoreApplication::translate("win_snail", "2000", nullptr));

#if QT_CONFIG(tooltip)
        cmdXMinus->setToolTip(QCoreApplication::translate("win_snail", "X-", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdXMinus->setText(QCoreApplication::translate("win_snail", "...", nullptr));
        buttDebug->setText(QCoreApplication::translate("win_snail", "Debug", nullptr));
        buttCon->setText(QCoreApplication::translate("win_snail", "Conn", nullptr));
        mnuFile->setTitle(QCoreApplication::translate("win_snail", "&File", nullptr));
        mnuRecent->setTitle(QCoreApplication::translate("win_snail", "&Recent files", nullptr));
        mnuService->setTitle(QCoreApplication::translate("win_snail", "Camera", nullptr));
        mnuHelp->setTitle(QCoreApplication::translate("win_snail", "&Help", nullptr));
        menuMachine->setTitle(QCoreApplication::translate("win_snail", "Machine", nullptr));
        (void)win_snail;
    } // retranslateUi

};

namespace Ui {
    class win_snail: public Ui_win_snail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIN_SNAIL_H
