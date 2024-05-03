/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <combobox.h>
#include <glwidget.h>
#include <groupbox.h>
#include <scrollarea.h>
#include <styledtoolbutton.h>
#include <widget.h>
#include "comboboxkey.h"
#include "sliderbox.h"

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QAction *actFileOpen;
    QAction *actFileExit;
    QAction *actServiceSettings;
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
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *grpProgram;
    QVBoxLayout *verticalLayout_17;
    QToolButton *cmdIsometric;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboProtocol;
    QLabel *label_4;
    QComboBox *comboInterface;
    QPushButton *btnReload;
    QLabel *label_21;
    QComboBox *comboBaud;
    QPushButton *btnConnect;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *cmdTop;
    QToolButton *cmdFront;
    QToolButton *cmdLeft;
    QToolButton *cmdFit;
    QSplitter *splitter;
    QWidget *frame;
    QVBoxLayout *verticalLayout_8;
    GLWidget *glwVisualizer;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QTableView *tblProgram;
    GroupBox *grpConsole;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *txtConsole;
    QSpacerItem *spacerConsole;
    QHBoxLayout *horizontalLayout_7;
    ComboBox *cboCommand;
    QPushButton *cmdCommandSend;
    QPushButton *cmdClearConsole;
    QTableView *tblHeightMap;
    QGroupBox *grpHeightMapSettings;
    QHBoxLayout *horizontalLayout_20;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_5;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QDoubleSpinBox *txtHeightMapBorderX;
    QDoubleSpinBox *txtHeightMapBorderHeight;
    QLabel *label_9;
    QDoubleSpinBox *txtHeightMapBorderY;
    QLabel *label_7;
    QLabel *label_8;
    QDoubleSpinBox *txtHeightMapBorderWidth;
    QHBoxLayout *horizontalLayout_18;
    QCheckBox *chkHeightMapBorderShow;
    StyledToolButton *cmdHeightMapBorderAuto;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_10;
    QGridLayout *gridLayout_4;
    QLabel *label_12;
    QDoubleSpinBox *txtHeightMapGridX;
    QDoubleSpinBox *txtHeightMapGridZTop;
    QDoubleSpinBox *txtHeightMapGridZBottom;
    QDoubleSpinBox *txtHeightMapGridY;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_19;
    QCheckBox *chkHeightMapGridShow;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_16;
    QGridLayout *gridLayout_6;
    QLabel *label_19;
    QLabel *label_18;
    QDoubleSpinBox *txtHeightMapInterpolationStepX;
    QDoubleSpinBox *txtHeightMapInterpolationStepY;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_17;
    QComboBox *cboHeightMapInterpolationType;
    QHBoxLayout *horizontalLayout_24;
    QCheckBox *chkHeightMapInterpolationShow;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *chkTestMode;
    QCheckBox *chkAutoScroll;
    QToolButton *cmdFileSend;
    QPushButton *cmdFilePause;
    QPushButton *cmdFileAbort;
    QPushButton *cmdFileReset;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cmdFileOpen;
    QSpacerItem *spacerBot;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_27;
    QGroupBox *grpState;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QHBoxLayout *horizontalLayout_8;
    QLCDNumber *txtWPosX;
    QLCDNumber *txtWPosY;
    QLCDNumber *txtWPosZ;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *txtMPosX;
    QLineEdit *txtMPosY;
    QLineEdit *txtMPosZ;
    QHBoxLayout *horizontalLayout_6;
    QLabel *Label;
    QLineEdit *txtStatus;
    QToolButton *cmdReset;
    QHBoxLayout *horizontalLayout_28;
    QGroupBox *grpControl;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_5;
    QToolButton *cmdHome;
    QToolButton *cmdZeroY;
    QToolButton *cmdRestoreOrigin;
    QToolButton *cmdSafePosition;
    QToolButton *cmdZeroZ;
    QToolButton *cmdUnlock;
    QToolButton *cmdTouch;
    QToolButton *cmdZeroX;
    QFrame *line;
    QSplitter *splitPanels;
    ScrollArea *scrollArea;
    Widget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_21;
    GroupBox *grpJog;
    QVBoxLayout *verticalLayout_11;
    QWidget *widgetJog;
    QVBoxLayout *verticalLayout_9;
    QGridLayout *gridLayout_3;
    StyledToolButton *cmdXMinus;
    QHBoxLayout *horizontalLayout_13;
    StyledToolButton *cmdYMinus;
    StyledToolButton *cmdXPlus;
    QHBoxLayout *horizontalLayout_12;
    StyledToolButton *cmdYPlus;
    QHBoxLayout *horizontalLayout_25;
    QSpacerItem *horizontalSpacer;
    StyledToolButton *cmdZPlus;
    QHBoxLayout *horizontalLayout_26;
    QSpacerItem *horizontalSpacer_2;
    StyledToolButton *cmdZMinus;
    QHBoxLayout *horizontalLayout_15;
    StyledToolButton *cmdStop;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_8;
    ComboBoxKey *cboJogStep;
    QLabel *label_20;
    QLabel *label_22;
    ComboBoxKey *cboJogFeed;
    QCheckBox *chkKeyboardControl;
    GroupBox *grpSpindle;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widgetSpindle;
    QHBoxLayout *horizontalLayout_16;
    SliderBox *slbSpindle;
    StyledToolButton *cmdSpindle;
    GroupBox *grpOverriding;
    QHBoxLayout *horizontalLayout_14;
    QWidget *widgetFeed;
    QVBoxLayout *verticalLayout_22;
    SliderBox *slbFeedOverride;
    SliderBox *slbRapidOverride;
    SliderBox *slbSpindleOverride;
    GroupBox *grpUserCommands;
    QHBoxLayout *horizontalLayout_30;
    QWidget *widgetUserCommands;
    QHBoxLayout *horizontalLayout_31;
    QGridLayout *gridLayout_7;
    StyledToolButton *cmdUser1;
    StyledToolButton *cmdUser3;
    StyledToolButton *cmdUser2;
    StyledToolButton *cmdUser0;
    GroupBox *grpHeightMap;
    QVBoxLayout *verticalLayout_16;
    QWidget *widgetHeightMap;
    QVBoxLayout *verticalLayout_15;
    QCheckBox *chkHeightMapUse;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_15;
    QLineEdit *txtHeightMap;
    QHBoxLayout *horizontalLayout_21;
    StyledToolButton *cmdHeightMapCreate;
    StyledToolButton *cmdHeightMapLoad;
    StyledToolButton *cmdHeightMapMode;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_29;
    QMenuBar *menuBar;
    QMenu *mnuFile;
    QMenu *mnuRecent;
    QMenu *mnuService;
    QMenu *mnuHelp;
    QMenu *menuMachine;

    void setupUi(QMainWindow *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QStringLiteral("frmMain"));
        frmMain->resize(1170, 881);
        frmMain->setAcceptDrops(true);
        frmMain->setWindowTitle(QStringLiteral("Candle 2"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/candle_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        frmMain->setWindowIcon(icon);
        frmMain->setStyleSheet(QLatin1String("/*QWidget {\n"
"	font-size: 9pt;\n"
"}*/\n"
"\n"
"QSpinBox, QDoubleSpinBox {\n"
"	padding-top: 1px;\n"
"	padding-bottom: 1px;\n"
"}\n"
"\n"
"QGroupBox {\n"
"}\n"
"\n"
"QGroupBox:disabled {\n"
"	color: palette(shadow);\n"
"}\n"
"\n"
"QGroupBox[overrided=\"true\"] {\n"
"	color: red;\n"
"}\n"
"\n"
"QGroupBox[overrided=\"false\"] {\n"
"	color: palette(windowtext);\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::title {\n"
"	margin-top: 1px;\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::indicator {\n"
"	padding: 0 -2 -0 2;\n"
"	width: 13;\n"
"	height: 13;\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::indicator:checked {	\n"
"	image: url(:/images/collapse.png);\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::indicator:unchecked {	\n"
"	image: url(:/images/expand.png);\n"
"}\n"
"\n"
"QFrame#frameManualControlXY,#frameManualControlZ {\n"
"	border: 1px solid lightgray;\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"QSplitter::handle {\n"
"	background-repeat: no-repeat;\n"
"	background-position: center center;\n"
"}\n"
"\n"
"QSpli"
                        "tter::handle:vertical {\n"
"	background-image: url(\":/images/handle_horizontal.png\");\n"
"}\n"
"/*\n"
"QSplitter::handle:horizontal {\n"
"	background-image: url(\":/images/handle_vertical.png\");\n"
"}\n"
"*/\n"
"QTableView {\n"
"	selection-background-color: #cdcdff;\n"
"	selection-color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QSlider::horizontal {\n"
"	padding-top: 1px;\n"
"	padding-bottom: 1px;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 2px; \n"
"    background: #8f8f91;\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {	\n"
"	background-image: url(:/images/handle2s.png);\n"
"    border: 0px;\n"
"    width: 16px;\n"
"    margin: -7px 0; \n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"	background-image: url(:/images/handle2sh.png);\n"
"}\n"
"\n"
"/*QSlider::sub-page:horizontal {\n"
"    background: red;\n"
"	margin: 1px 0;\n"
"}*/"));
        actFileOpen = new QAction(frmMain);
        actFileOpen->setObjectName(QStringLiteral("actFileOpen"));
        actFileExit = new QAction(frmMain);
        actFileExit->setObjectName(QStringLiteral("actFileExit"));
        actServiceSettings = new QAction(frmMain);
        actServiceSettings->setObjectName(QStringLiteral("actServiceSettings"));
        actFileNew = new QAction(frmMain);
        actFileNew->setObjectName(QStringLiteral("actFileNew"));
        actFileSave = new QAction(frmMain);
        actFileSave->setObjectName(QStringLiteral("actFileSave"));
        actFileSaveAs = new QAction(frmMain);
        actFileSaveAs->setObjectName(QStringLiteral("actFileSaveAs"));
        actAbout = new QAction(frmMain);
        actAbout->setObjectName(QStringLiteral("actAbout"));
        actRecentClear = new QAction(frmMain);
        actRecentClear->setObjectName(QStringLiteral("actRecentClear"));
        actFileSaveTransformedAs = new QAction(frmMain);
        actFileSaveTransformedAs->setObjectName(QStringLiteral("actFileSaveTransformedAs"));
        actionMachine_settings = new QAction(frmMain);
        actionMachine_settings->setObjectName(QStringLiteral("actionMachine_settings"));
        actionHard_Reset = new QAction(frmMain);
        actionHard_Reset->setObjectName(QStringLiteral("actionHard_Reset"));
        actionSave_TLS_Position = new QAction(frmMain);
        actionSave_TLS_Position->setObjectName(QStringLiteral("actionSave_TLS_Position"));
        actionSet_TLS_Position = new QAction(frmMain);
        actionSet_TLS_Position->setObjectName(QStringLiteral("actionSet_TLS_Position"));
        actionDisable_Stepper = new QAction(frmMain);
        actionDisable_Stepper->setObjectName(QStringLiteral("actionDisable_Stepper"));
        centralWidget = new QWidget(frmMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_5 = new QHBoxLayout(centralWidget);
        horizontalLayout_5->setSpacing(9);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(9, 9, 5, 9);
        grpProgram = new QGroupBox(centralWidget);
        grpProgram->setObjectName(QStringLiteral("grpProgram"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        grpProgram->setFont(font);
        grpProgram->setTitle(QStringLiteral("G-Code Program"));
        grpProgram->setFlat(false);
        verticalLayout_17 = new QVBoxLayout(grpProgram);
        verticalLayout_17->setSpacing(7);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(8, 8, 8, 8);
        cmdIsometric = new QToolButton(grpProgram);
        cmdIsometric->setObjectName(QStringLiteral("cmdIsometric"));
        cmdIsometric->setMinimumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/cube.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdIsometric->setIcon(icon1);
        cmdIsometric->setIconSize(QSize(20, 20));

        verticalLayout_17->addWidget(cmdIsometric);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(grpProgram);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        comboProtocol = new QComboBox(grpProgram);
        comboProtocol->setObjectName(QStringLiteral("comboProtocol"));
        comboProtocol->setMinimumSize(QSize(100, 28));
        comboProtocol->setFont(font);
        comboProtocol->setFrame(true);

        horizontalLayout_4->addWidget(comboProtocol);

        label_4 = new QLabel(grpProgram);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        comboInterface = new QComboBox(grpProgram);
        comboInterface->setObjectName(QStringLiteral("comboInterface"));
        comboInterface->setMinimumSize(QSize(90, 28));
        comboInterface->setFont(font);

        horizontalLayout_4->addWidget(comboInterface);

        btnReload = new QPushButton(grpProgram);
        btnReload->setObjectName(QStringLiteral("btnReload"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnReload->sizePolicy().hasHeightForWidth());
        btnReload->setSizePolicy(sizePolicy);
        btnReload->setMinimumSize(QSize(25, 28));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/restart.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnReload->setIcon(icon2);

        horizontalLayout_4->addWidget(btnReload);

        label_21 = new QLabel(grpProgram);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setFont(font);

        horizontalLayout_4->addWidget(label_21);

        comboBaud = new QComboBox(grpProgram);
        comboBaud->setObjectName(QStringLiteral("comboBaud"));
        comboBaud->setMinimumSize(QSize(90, 28));
        comboBaud->setFont(font);

        horizontalLayout_4->addWidget(comboBaud);

        btnConnect = new QPushButton(grpProgram);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        btnConnect->setMinimumSize(QSize(100, 28));
        btnConnect->setFont(font);

        horizontalLayout_4->addWidget(btnConnect);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_17->addLayout(horizontalLayout_4);

        cmdTop = new QToolButton(grpProgram);
        cmdTop->setObjectName(QStringLiteral("cmdTop"));
        cmdTop->setMinimumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/cubeTop.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdTop->setIcon(icon3);
        cmdTop->setIconSize(QSize(20, 20));

        verticalLayout_17->addWidget(cmdTop);

        cmdFront = new QToolButton(grpProgram);
        cmdFront->setObjectName(QStringLiteral("cmdFront"));
        cmdFront->setMinimumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/cubeFront.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFront->setIcon(icon4);
        cmdFront->setIconSize(QSize(20, 20));

        verticalLayout_17->addWidget(cmdFront);

        cmdLeft = new QToolButton(grpProgram);
        cmdLeft->setObjectName(QStringLiteral("cmdLeft"));
        cmdLeft->setMinimumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/cubeLeft.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdLeft->setIcon(icon5);
        cmdLeft->setIconSize(QSize(20, 20));

        verticalLayout_17->addWidget(cmdLeft);

        cmdFit = new QToolButton(grpProgram);
        cmdFit->setObjectName(QStringLiteral("cmdFit"));
        cmdFit->setMinimumSize(QSize(30, 30));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/fit_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFit->setIcon(icon6);
        cmdFit->setIconSize(QSize(20, 20));

        verticalLayout_17->addWidget(cmdFit);

        splitter = new QSplitter(grpProgram);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(12);
        frame = new QWidget(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 200));
        frame->setStyleSheet(QStringLiteral("border: 1px solid gray;"));
        verticalLayout_8 = new QVBoxLayout(frame);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(1, 1, 1, 1);
        glwVisualizer = new GLWidget(frame);
        glwVisualizer->setObjectName(QStringLiteral("glwVisualizer"));

        verticalLayout_8->addWidget(glwVisualizer);

        splitter->addWidget(frame);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_7 = new QVBoxLayout(layoutWidget);
        verticalLayout_7->setSpacing(9);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        tblProgram = new QTableView(layoutWidget);
        tblProgram->setObjectName(QStringLiteral("tblProgram"));
        QFont font1;
        font1.setPointSize(9);
        tblProgram->setFont(font1);
        tblProgram->setContextMenuPolicy(Qt::CustomContextMenu);
        tblProgram->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tblProgram->setSelectionMode(QAbstractItemView::ContiguousSelection);
        tblProgram->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblProgram->setGridStyle(Qt::DashLine);
        tblProgram->horizontalHeader()->setHighlightSections(false);
        tblProgram->horizontalHeader()->setMinimumSectionSize(50);
        tblProgram->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(tblProgram);

        grpConsole = new GroupBox(layoutWidget);
        grpConsole->setObjectName(QStringLiteral("grpConsole"));
        grpConsole->setFont(font);
        grpConsole->setAutoFillBackground(false);
        verticalLayout_3 = new QVBoxLayout(grpConsole);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(8, 8, 8, 8);
        txtConsole = new QPlainTextEdit(grpConsole);
        txtConsole->setObjectName(QStringLiteral("txtConsole"));
        txtConsole->setMinimumSize(QSize(0, 1));
        txtConsole->setFont(font1);
        txtConsole->setReadOnly(true);

        verticalLayout_3->addWidget(txtConsole);

        spacerConsole = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(spacerConsole);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        cboCommand = new ComboBox(grpConsole);
        cboCommand->setObjectName(QStringLiteral("cboCommand"));
        cboCommand->setStyleSheet(QLatin1String("padding-top: 3;\n"
"padding-bottom: 3;\n"
"padding-right: 8;"));
        cboCommand->setEditable(true);
        cboCommand->setMaxVisibleItems(5);
        cboCommand->setMaxCount(10);
        cboCommand->setInsertPolicy(QComboBox::InsertAtTop);

        horizontalLayout_7->addWidget(cboCommand);

        cmdCommandSend = new QPushButton(grpConsole);
        cmdCommandSend->setObjectName(QStringLiteral("cmdCommandSend"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/send_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdCommandSend->setIcon(icon7);
        cmdCommandSend->setIconSize(QSize(16, 16));

        horizontalLayout_7->addWidget(cmdCommandSend);

        cmdClearConsole = new QPushButton(grpConsole);
        cmdClearConsole->setObjectName(QStringLiteral("cmdClearConsole"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/erase_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdClearConsole->setIcon(icon8);
        cmdClearConsole->setIconSize(QSize(16, 16));

        horizontalLayout_7->addWidget(cmdClearConsole);

        horizontalLayout_7->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_7);


        horizontalLayout->addWidget(grpConsole);


        verticalLayout_7->addLayout(horizontalLayout);

        tblHeightMap = new QTableView(layoutWidget);
        tblHeightMap->setObjectName(QStringLiteral("tblHeightMap"));
        tblHeightMap->setAlternatingRowColors(true);
        tblHeightMap->setSelectionMode(QAbstractItemView::SingleSelection);
        tblHeightMap->setGridStyle(Qt::DashLine);
        tblHeightMap->horizontalHeader()->setVisible(false);
        tblHeightMap->horizontalHeader()->setDefaultSectionSize(60);
        tblHeightMap->horizontalHeader()->setHighlightSections(false);
        tblHeightMap->verticalHeader()->setVisible(false);

        verticalLayout_7->addWidget(tblHeightMap);

        splitter->addWidget(layoutWidget);

        verticalLayout_17->addWidget(splitter);

        grpHeightMapSettings = new QGroupBox(grpProgram);
        grpHeightMapSettings->setObjectName(QStringLiteral("grpHeightMapSettings"));
        grpHeightMapSettings->setFont(font);
        horizontalLayout_20 = new QHBoxLayout(grpHeightMapSettings);
        horizontalLayout_20->setSpacing(11);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(8, 8, 8, 8);
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        label_5 = new QLabel(grpHeightMapSettings);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        verticalLayout_18->addWidget(label_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(grpHeightMapSettings);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        txtHeightMapBorderX = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapBorderX->setObjectName(QStringLiteral("txtHeightMapBorderX"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(txtHeightMapBorderX->sizePolicy().hasHeightForWidth());
        txtHeightMapBorderX->setSizePolicy(sizePolicy2);
        txtHeightMapBorderX->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapBorderX->setAlignment(Qt::AlignCenter);
        txtHeightMapBorderX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapBorderX->setMinimum(-999);
        txtHeightMapBorderX->setMaximum(999);

        gridLayout->addWidget(txtHeightMapBorderX, 0, 1, 1, 1);

        txtHeightMapBorderHeight = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapBorderHeight->setObjectName(QStringLiteral("txtHeightMapBorderHeight"));
        sizePolicy2.setHeightForWidth(txtHeightMapBorderHeight->sizePolicy().hasHeightForWidth());
        txtHeightMapBorderHeight->setSizePolicy(sizePolicy2);
        txtHeightMapBorderHeight->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapBorderHeight->setAlignment(Qt::AlignCenter);
        txtHeightMapBorderHeight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapBorderHeight->setMinimum(-999);
        txtHeightMapBorderHeight->setMaximum(999);
        txtHeightMapBorderHeight->setValue(10);

        gridLayout->addWidget(txtHeightMapBorderHeight, 1, 3, 1, 1);

        label_9 = new QLabel(grpHeightMapSettings);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        txtHeightMapBorderY = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapBorderY->setObjectName(QStringLiteral("txtHeightMapBorderY"));
        sizePolicy2.setHeightForWidth(txtHeightMapBorderY->sizePolicy().hasHeightForWidth());
        txtHeightMapBorderY->setSizePolicy(sizePolicy2);
        txtHeightMapBorderY->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapBorderY->setAlignment(Qt::AlignCenter);
        txtHeightMapBorderY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapBorderY->setMinimum(-999);
        txtHeightMapBorderY->setMaximum(999);

        gridLayout->addWidget(txtHeightMapBorderY, 1, 1, 1, 1);

        label_7 = new QLabel(grpHeightMapSettings);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(grpHeightMapSettings);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        txtHeightMapBorderWidth = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapBorderWidth->setObjectName(QStringLiteral("txtHeightMapBorderWidth"));
        sizePolicy2.setHeightForWidth(txtHeightMapBorderWidth->sizePolicy().hasHeightForWidth());
        txtHeightMapBorderWidth->setSizePolicy(sizePolicy2);
        txtHeightMapBorderWidth->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapBorderWidth->setAlignment(Qt::AlignCenter);
        txtHeightMapBorderWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapBorderWidth->setMinimum(-999);
        txtHeightMapBorderWidth->setMaximum(999);
        txtHeightMapBorderWidth->setValue(10);

        gridLayout->addWidget(txtHeightMapBorderWidth, 0, 3, 1, 1);


        verticalLayout_18->addLayout(gridLayout);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        chkHeightMapBorderShow = new QCheckBox(grpHeightMapSettings);
        chkHeightMapBorderShow->setObjectName(QStringLiteral("chkHeightMapBorderShow"));
        chkHeightMapBorderShow->setChecked(true);

        horizontalLayout_18->addWidget(chkHeightMapBorderShow);

        cmdHeightMapBorderAuto = new StyledToolButton(grpHeightMapSettings);
        cmdHeightMapBorderAuto->setObjectName(QStringLiteral("cmdHeightMapBorderAuto"));
        cmdHeightMapBorderAuto->setMinimumSize(QSize(44, 18));

        horizontalLayout_18->addWidget(cmdHeightMapBorderAuto);


        verticalLayout_18->addLayout(horizontalLayout_18);


        horizontalLayout_20->addLayout(verticalLayout_18);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        label_10 = new QLabel(grpHeightMapSettings);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);

        verticalLayout_19->addWidget(label_10);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_12 = new QLabel(grpHeightMapSettings);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 0, 0, 1, 1);

        txtHeightMapGridX = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapGridX->setObjectName(QStringLiteral("txtHeightMapGridX"));
        sizePolicy2.setHeightForWidth(txtHeightMapGridX->sizePolicy().hasHeightForWidth());
        txtHeightMapGridX->setSizePolicy(sizePolicy2);
        txtHeightMapGridX->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapGridX->setAlignment(Qt::AlignCenter);
        txtHeightMapGridX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapGridX->setDecimals(0);
        txtHeightMapGridX->setMinimum(2);
        txtHeightMapGridX->setMaximum(1000);
        txtHeightMapGridX->setValue(2);

        gridLayout_4->addWidget(txtHeightMapGridX, 0, 1, 1, 1);

        txtHeightMapGridZTop = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapGridZTop->setObjectName(QStringLiteral("txtHeightMapGridZTop"));
        sizePolicy2.setHeightForWidth(txtHeightMapGridZTop->sizePolicy().hasHeightForWidth());
        txtHeightMapGridZTop->setSizePolicy(sizePolicy2);
        txtHeightMapGridZTop->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapGridZTop->setAlignment(Qt::AlignCenter);
        txtHeightMapGridZTop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapGridZTop->setMinimum(-999);
        txtHeightMapGridZTop->setMaximum(999);
        txtHeightMapGridZTop->setValue(1);

        gridLayout_4->addWidget(txtHeightMapGridZTop, 0, 5, 1, 1);

        txtHeightMapGridZBottom = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapGridZBottom->setObjectName(QStringLiteral("txtHeightMapGridZBottom"));
        sizePolicy2.setHeightForWidth(txtHeightMapGridZBottom->sizePolicy().hasHeightForWidth());
        txtHeightMapGridZBottom->setSizePolicy(sizePolicy2);
        txtHeightMapGridZBottom->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapGridZBottom->setAlignment(Qt::AlignCenter);
        txtHeightMapGridZBottom->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapGridZBottom->setMinimum(-999);
        txtHeightMapGridZBottom->setMaximum(999);
        txtHeightMapGridZBottom->setValue(-1);

        gridLayout_4->addWidget(txtHeightMapGridZBottom, 1, 5, 1, 1);

        txtHeightMapGridY = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapGridY->setObjectName(QStringLiteral("txtHeightMapGridY"));
        sizePolicy2.setHeightForWidth(txtHeightMapGridY->sizePolicy().hasHeightForWidth());
        txtHeightMapGridY->setSizePolicy(sizePolicy2);
        txtHeightMapGridY->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapGridY->setAlignment(Qt::AlignCenter);
        txtHeightMapGridY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapGridY->setDecimals(0);
        txtHeightMapGridY->setMinimum(2);
        txtHeightMapGridY->setMaximum(1000);
        txtHeightMapGridY->setValue(2);

        gridLayout_4->addWidget(txtHeightMapGridY, 1, 1, 1, 1);

        label_11 = new QLabel(grpHeightMapSettings);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 1, 3, 1, 1);

        label_13 = new QLabel(grpHeightMapSettings);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_4->addWidget(label_13, 1, 0, 1, 1);

        label_14 = new QLabel(grpHeightMapSettings);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 0, 3, 1, 1);


        verticalLayout_19->addLayout(gridLayout_4);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        chkHeightMapGridShow = new QCheckBox(grpHeightMapSettings);
        chkHeightMapGridShow->setObjectName(QStringLiteral("chkHeightMapGridShow"));
        chkHeightMapGridShow->setChecked(true);

        horizontalLayout_19->addWidget(chkHeightMapGridShow);

        horizontalSpacer_6 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_6);


        verticalLayout_19->addLayout(horizontalLayout_19);


        horizontalLayout_20->addLayout(verticalLayout_19);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        label_16 = new QLabel(grpHeightMapSettings);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setFont(font);

        verticalLayout_20->addWidget(label_16);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_19 = new QLabel(grpHeightMapSettings);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_6->addWidget(label_19, 1, 2, 1, 1);

        label_18 = new QLabel(grpHeightMapSettings);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_6->addWidget(label_18, 1, 0, 1, 1);

        txtHeightMapInterpolationStepX = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapInterpolationStepX->setObjectName(QStringLiteral("txtHeightMapInterpolationStepX"));
        sizePolicy2.setHeightForWidth(txtHeightMapInterpolationStepX->sizePolicy().hasHeightForWidth());
        txtHeightMapInterpolationStepX->setSizePolicy(sizePolicy2);
        txtHeightMapInterpolationStepX->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapInterpolationStepX->setAlignment(Qt::AlignCenter);
        txtHeightMapInterpolationStepX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapInterpolationStepX->setDecimals(0);
        txtHeightMapInterpolationStepX->setMinimum(2);
        txtHeightMapInterpolationStepX->setMaximum(1000);
        txtHeightMapInterpolationStepX->setValue(2);

        gridLayout_6->addWidget(txtHeightMapInterpolationStepX, 1, 1, 1, 1);

        txtHeightMapInterpolationStepY = new QDoubleSpinBox(grpHeightMapSettings);
        txtHeightMapInterpolationStepY->setObjectName(QStringLiteral("txtHeightMapInterpolationStepY"));
        sizePolicy2.setHeightForWidth(txtHeightMapInterpolationStepY->sizePolicy().hasHeightForWidth());
        txtHeightMapInterpolationStepY->setSizePolicy(sizePolicy2);
        txtHeightMapInterpolationStepY->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        txtHeightMapInterpolationStepY->setAlignment(Qt::AlignCenter);
        txtHeightMapInterpolationStepY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapInterpolationStepY->setDecimals(0);
        txtHeightMapInterpolationStepY->setMinimum(2);
        txtHeightMapInterpolationStepY->setMaximum(1000);
        txtHeightMapInterpolationStepY->setValue(2);

        gridLayout_6->addWidget(txtHeightMapInterpolationStepY, 1, 3, 1, 1);


        verticalLayout_20->addLayout(gridLayout_6);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_17 = new QLabel(grpHeightMapSettings);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_23->addWidget(label_17);

        cboHeightMapInterpolationType = new QComboBox(grpHeightMapSettings);
        cboHeightMapInterpolationType->setObjectName(QStringLiteral("cboHeightMapInterpolationType"));
        cboHeightMapInterpolationType->setEnabled(false);
        sizePolicy2.setHeightForWidth(cboHeightMapInterpolationType->sizePolicy().hasHeightForWidth());
        cboHeightMapInterpolationType->setSizePolicy(sizePolicy2);

        horizontalLayout_23->addWidget(cboHeightMapInterpolationType);


        verticalLayout_20->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        chkHeightMapInterpolationShow = new QCheckBox(grpHeightMapSettings);
        chkHeightMapInterpolationShow->setObjectName(QStringLiteral("chkHeightMapInterpolationShow"));

        horizontalLayout_24->addWidget(chkHeightMapInterpolationShow);

        horizontalSpacer_8 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_8);


        verticalLayout_20->addLayout(horizontalLayout_24);


        horizontalLayout_20->addLayout(verticalLayout_20);

        horizontalLayout_20->setStretch(0, 1);
        horizontalLayout_20->setStretch(1, 1);
        horizontalLayout_20->setStretch(2, 1);

        verticalLayout_17->addWidget(grpHeightMapSettings);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        chkTestMode = new QCheckBox(grpProgram);
        chkTestMode->setObjectName(QStringLiteral("chkTestMode"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(chkTestMode->sizePolicy().hasHeightForWidth());
        chkTestMode->setSizePolicy(sizePolicy3);
        chkTestMode->setMinimumSize(QSize(22, 0));
        chkTestMode->setFont(font);

        horizontalLayout_3->addWidget(chkTestMode);

        chkAutoScroll = new QCheckBox(grpProgram);
        chkAutoScroll->setObjectName(QStringLiteral("chkAutoScroll"));
        sizePolicy3.setHeightForWidth(chkAutoScroll->sizePolicy().hasHeightForWidth());
        chkAutoScroll->setSizePolicy(sizePolicy3);
        chkAutoScroll->setMinimumSize(QSize(22, 0));
        chkAutoScroll->setFont(font);

        horizontalLayout_3->addWidget(chkAutoScroll);

        cmdFileSend = new QToolButton(grpProgram);
        cmdFileSend->setObjectName(QStringLiteral("cmdFileSend"));
        sizePolicy.setHeightForWidth(cmdFileSend->sizePolicy().hasHeightForWidth());
        cmdFileSend->setSizePolicy(sizePolicy);
        cmdFileSend->setBaseSize(QSize(60, 0));
        cmdFileSend->setFont(font);
        cmdFileSend->setLayoutDirection(Qt::LeftToRight);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFileSend->setIcon(icon9);
        cmdFileSend->setIconSize(QSize(20, 20));
        cmdFileSend->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_3->addWidget(cmdFileSend);

        cmdFilePause = new QPushButton(grpProgram);
        cmdFilePause->setObjectName(QStringLiteral("cmdFilePause"));
        cmdFilePause->setFont(font);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFilePause->setIcon(icon10);
        cmdFilePause->setIconSize(QSize(20, 20));
        cmdFilePause->setCheckable(true);

        horizontalLayout_3->addWidget(cmdFilePause);

        cmdFileAbort = new QPushButton(grpProgram);
        cmdFileAbort->setObjectName(QStringLiteral("cmdFileAbort"));
        cmdFileAbort->setFont(font);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFileAbort->setIcon(icon11);
        cmdFileAbort->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(cmdFileAbort);

        cmdFileReset = new QPushButton(grpProgram);
        cmdFileReset->setObjectName(QStringLiteral("cmdFileReset"));
        cmdFileReset->setFont(font);

        horizontalLayout_3->addWidget(cmdFileReset);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        cmdFileOpen = new QPushButton(grpProgram);
        cmdFileOpen->setObjectName(QStringLiteral("cmdFileOpen"));
        cmdFileOpen->setFont(font);
        cmdFileOpen->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(cmdFileOpen);

        spacerBot = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacerBot);


        verticalLayout_17->addLayout(horizontalLayout_3);


        horizontalLayout_5->addWidget(grpProgram);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(-1, -1, 4, -1);
        grpState = new QGroupBox(centralWidget);
        grpState->setObjectName(QStringLiteral("grpState"));
        grpState->setFont(font);
        grpState->setProperty("overrided", QVariant(false));
        verticalLayout_6 = new QVBoxLayout(grpState);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(8, 8, 8, 9);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(8);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label = new QLabel(grpState);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout_9->addWidget(label);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(8);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        txtWPosX = new QLCDNumber(grpState);
        txtWPosX->setObjectName(QStringLiteral("txtWPosX"));
        txtWPosX->setMinimumSize(QSize(116, 40));
        txtWPosX->setFont(font);
        txtWPosX->setAutoFillBackground(false);
        txtWPosX->setFrameShape(QFrame::Box);
        txtWPosX->setFrameShadow(QFrame::Sunken);
        txtWPosX->setLineWidth(1);
        txtWPosX->setSmallDecimalPoint(true);
        txtWPosX->setDigitCount(7);
        txtWPosX->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_8->addWidget(txtWPosX);

        txtWPosY = new QLCDNumber(grpState);
        txtWPosY->setObjectName(QStringLiteral("txtWPosY"));
        txtWPosY->setMinimumSize(QSize(116, 40));
        txtWPosY->setFont(font);
        txtWPosY->setFrameShadow(QFrame::Sunken);
        txtWPosY->setSmallDecimalPoint(true);
        txtWPosY->setDigitCount(7);
        txtWPosY->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_8->addWidget(txtWPosY);

        txtWPosZ = new QLCDNumber(grpState);
        txtWPosZ->setObjectName(QStringLiteral("txtWPosZ"));
        txtWPosZ->setMinimumSize(QSize(116, 40));
        txtWPosZ->setFont(font);
        txtWPosZ->setFrameShadow(QFrame::Sunken);
        txtWPosZ->setSmallDecimalPoint(true);
        txtWPosZ->setDigitCount(7);
        txtWPosZ->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_8->addWidget(txtWPosZ);


        verticalLayout_4->addLayout(horizontalLayout_8);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(8);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_2 = new QLabel(grpState);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_10->addWidget(label_2);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(8);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        txtMPosX = new QLineEdit(grpState);
        txtMPosX->setObjectName(QStringLiteral("txtMPosX"));
        txtMPosX->setMinimumSize(QSize(0, 30));
        txtMPosX->setFont(font);
        txtMPosX->setAlignment(Qt::AlignCenter);
        txtMPosX->setReadOnly(true);

        horizontalLayout_11->addWidget(txtMPosX);

        txtMPosY = new QLineEdit(grpState);
        txtMPosY->setObjectName(QStringLiteral("txtMPosY"));
        txtMPosY->setMinimumSize(QSize(0, 30));
        txtMPosY->setFont(font);
        txtMPosY->setAlignment(Qt::AlignCenter);
        txtMPosY->setReadOnly(true);

        horizontalLayout_11->addWidget(txtMPosY);

        txtMPosZ = new QLineEdit(grpState);
        txtMPosZ->setObjectName(QStringLiteral("txtMPosZ"));
        txtMPosZ->setMinimumSize(QSize(0, 30));
        txtMPosZ->setFont(font);
        txtMPosZ->setAlignment(Qt::AlignCenter);
        txtMPosZ->setReadOnly(true);

        horizontalLayout_11->addWidget(txtMPosZ);


        verticalLayout_5->addLayout(horizontalLayout_11);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        Label = new QLabel(grpState);
        Label->setObjectName(QStringLiteral("Label"));
        Label->setFont(font);

        horizontalLayout_6->addWidget(Label);

        txtStatus = new QLineEdit(grpState);
        txtStatus->setObjectName(QStringLiteral("txtStatus"));
        txtStatus->setEnabled(false);
        txtStatus->setMinimumSize(QSize(0, 34));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        txtStatus->setFont(font2);
        txtStatus->setStyleSheet(QStringLiteral("QLineEdit {color: palette(text);}"));
        txtStatus->setAlignment(Qt::AlignCenter);
        txtStatus->setReadOnly(true);

        horizontalLayout_6->addWidget(txtStatus);

        cmdReset = new QToolButton(grpState);
        cmdReset->setObjectName(QStringLiteral("cmdReset"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(cmdReset->sizePolicy().hasHeightForWidth());
        cmdReset->setSizePolicy(sizePolicy4);
        cmdReset->setMinimumSize(QSize(52, 52));
        cmdReset->setIcon(icon2);
        cmdReset->setIconSize(QSize(30, 30));
        cmdReset->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_6->addWidget(cmdReset);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_27->addWidget(grpState);


        verticalLayout_2->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(-1, -1, 4, -1);
        grpControl = new QGroupBox(centralWidget);
        grpControl->setObjectName(QStringLiteral("grpControl"));
        grpControl->setFont(font);
        grpControl->setProperty("overrided", QVariant(false));
        verticalLayout = new QVBoxLayout(grpControl);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(8, 8, 8, 9);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(8);
        cmdHome = new QToolButton(grpControl);
        cmdHome->setObjectName(QStringLiteral("cmdHome"));
        cmdHome->setMinimumSize(QSize(54, 54));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdHome->setIcon(icon12);
        cmdHome->setIconSize(QSize(30, 30));
        cmdHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdHome, 0, 1, 1, 1);

        cmdZeroY = new QToolButton(grpControl);
        cmdZeroY->setObjectName(QStringLiteral("cmdZeroY"));
        cmdZeroY->setMinimumSize(QSize(54, 54));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/images/axis_zero.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdZeroY->setIcon(icon13);
        cmdZeroY->setIconSize(QSize(30, 30));
        cmdZeroY->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdZeroY, 0, 5, 1, 1);

        cmdRestoreOrigin = new QToolButton(grpControl);
        cmdRestoreOrigin->setObjectName(QStringLiteral("cmdRestoreOrigin"));
        cmdRestoreOrigin->setMinimumSize(QSize(54, 54));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/images/origin.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRestoreOrigin->setIcon(icon14);
        cmdRestoreOrigin->setIconSize(QSize(30, 30));
        cmdRestoreOrigin->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdRestoreOrigin, 2, 1, 1, 1);

        cmdSafePosition = new QToolButton(grpControl);
        cmdSafePosition->setObjectName(QStringLiteral("cmdSafePosition"));
        cmdSafePosition->setMinimumSize(QSize(54, 54));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/images/safe_z.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSafePosition->setIcon(icon15);
        cmdSafePosition->setIconSize(QSize(30, 30));
        cmdSafePosition->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdSafePosition, 2, 3, 1, 1);

        cmdZeroZ = new QToolButton(grpControl);
        cmdZeroZ->setObjectName(QStringLiteral("cmdZeroZ"));
        cmdZeroZ->setMinimumSize(QSize(54, 54));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/images/zero_z.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdZeroZ->setIcon(icon16);
        cmdZeroZ->setIconSize(QSize(30, 30));
        cmdZeroZ->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdZeroZ, 0, 7, 1, 1);

        cmdUnlock = new QToolButton(grpControl);
        cmdUnlock->setObjectName(QStringLiteral("cmdUnlock"));
        cmdUnlock->setMinimumSize(QSize(54, 54));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/images/unlock.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUnlock->setIcon(icon17);
        cmdUnlock->setIconSize(QSize(30, 30));
        cmdUnlock->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdUnlock, 2, 7, 1, 1);

        cmdTouch = new QToolButton(grpControl);
        cmdTouch->setObjectName(QStringLiteral("cmdTouch"));
        cmdTouch->setMinimumSize(QSize(54, 54));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/images/search_for_z.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdTouch->setIcon(icon18);
        cmdTouch->setIconSize(QSize(30, 30));
        cmdTouch->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdTouch, 2, 5, 1, 1);

        cmdZeroX = new QToolButton(grpControl);
        cmdZeroX->setObjectName(QStringLiteral("cmdZeroX"));
        cmdZeroX->setEnabled(true);
        cmdZeroX->setMinimumSize(QSize(54, 54));
        cmdZeroX->setIcon(icon13);
        cmdZeroX->setIconSize(QSize(30, 30));
        cmdZeroX->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_5->addWidget(cmdZeroX, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_5);


        horizontalLayout_28->addWidget(grpControl);


        verticalLayout_2->addLayout(horizontalLayout_28);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        splitPanels = new QSplitter(centralWidget);
        splitPanels->setObjectName(QStringLiteral("splitPanels"));
        splitPanels->setStyleSheet(QLatin1String("QSplitter::handle {\n"
"	background-image: url(\":/images/handle_small.png\");\n"
"}"));
        splitPanels->setOrientation(Qt::Vertical);
        splitPanels->setHandleWidth(10);
        splitPanels->setChildrenCollapsible(false);
        scrollArea = new ScrollArea(splitPanels);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy5);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new Widget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 374, 656));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy6);
        verticalLayout_21 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 4, 0);
        grpJog = new GroupBox(scrollAreaWidgetContents);
        grpJog->setObjectName(QStringLiteral("grpJog"));
        grpJog->setFont(font);
        grpJog->setFocusPolicy(Qt::NoFocus);
        grpJog->setCheckable(false);
        grpJog->setProperty("overrided", QVariant(false));
        verticalLayout_11 = new QVBoxLayout(grpJog);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(8, 8, 8, 8);
        widgetJog = new QWidget(grpJog);
        widgetJog->setObjectName(QStringLiteral("widgetJog"));
        verticalLayout_9 = new QVBoxLayout(widgetJog);
        verticalLayout_9->setSpacing(10);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(8);
        gridLayout_3->setVerticalSpacing(4);
        cmdXMinus = new StyledToolButton(widgetJog);
        cmdXMinus->setObjectName(QStringLiteral("cmdXMinus"));
        sizePolicy4.setHeightForWidth(cmdXMinus->sizePolicy().hasHeightForWidth());
        cmdXMinus->setSizePolicy(sizePolicy4);
        cmdXMinus->setMinimumSize(QSize(44, 44));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/images/1401561986_chevron-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdXMinus->setIcon(icon19);
        cmdXMinus->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(cmdXMinus, 2, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        cmdYMinus = new StyledToolButton(widgetJog);
        cmdYMinus->setObjectName(QStringLiteral("cmdYMinus"));
        sizePolicy4.setHeightForWidth(cmdYMinus->sizePolicy().hasHeightForWidth());
        cmdYMinus->setSizePolicy(sizePolicy4);
        cmdYMinus->setMinimumSize(QSize(44, 44));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/images/1401562173_chevron-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdYMinus->setIcon(icon20);
        cmdYMinus->setIconSize(QSize(30, 30));

        horizontalLayout_13->addWidget(cmdYMinus);


        gridLayout_3->addLayout(horizontalLayout_13, 3, 1, 1, 1);

        cmdXPlus = new StyledToolButton(widgetJog);
        cmdXPlus->setObjectName(QStringLiteral("cmdXPlus"));
        sizePolicy4.setHeightForWidth(cmdXPlus->sizePolicy().hasHeightForWidth());
        cmdXPlus->setSizePolicy(sizePolicy4);
        cmdXPlus->setMinimumSize(QSize(44, 44));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/images/1401562173_chevron-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdXPlus->setIcon(icon21);
        cmdXPlus->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(cmdXPlus, 2, 2, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        cmdYPlus = new StyledToolButton(widgetJog);
        cmdYPlus->setObjectName(QStringLiteral("cmdYPlus"));
        sizePolicy4.setHeightForWidth(cmdYPlus->sizePolicy().hasHeightForWidth());
        cmdYPlus->setSizePolicy(sizePolicy4);
        cmdYPlus->setMinimumSize(QSize(44, 44));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/images/1401562173_chevron-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdYPlus->setIcon(icon22);
        cmdYPlus->setIconSize(QSize(30, 30));

        horizontalLayout_12->addWidget(cmdYPlus);


        gridLayout_3->addLayout(horizontalLayout_12, 0, 1, 1, 1);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(0);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer);

        cmdZPlus = new StyledToolButton(widgetJog);
        cmdZPlus->setObjectName(QStringLiteral("cmdZPlus"));
        sizePolicy4.setHeightForWidth(cmdZPlus->sizePolicy().hasHeightForWidth());
        cmdZPlus->setSizePolicy(sizePolicy4);
        cmdZPlus->setMinimumSize(QSize(44, 44));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/images/1401562699_icon-arrow-up-b.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdZPlus->setIcon(icon23);
        cmdZPlus->setIconSize(QSize(28, 28));

        horizontalLayout_25->addWidget(cmdZPlus);


        gridLayout_3->addLayout(horizontalLayout_25, 0, 3, 1, 1);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(0);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_2);

        cmdZMinus = new StyledToolButton(widgetJog);
        cmdZMinus->setObjectName(QStringLiteral("cmdZMinus"));
        sizePolicy4.setHeightForWidth(cmdZMinus->sizePolicy().hasHeightForWidth());
        cmdZMinus->setSizePolicy(sizePolicy4);
        cmdZMinus->setMinimumSize(QSize(44, 44));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/images/1401562699_icon-arrow-down-b.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdZMinus->setIcon(icon24);
        cmdZMinus->setIconSize(QSize(28, 28));

        horizontalLayout_26->addWidget(cmdZMinus);


        gridLayout_3->addLayout(horizontalLayout_26, 3, 3, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        cmdStop = new StyledToolButton(widgetJog);
        cmdStop->setObjectName(QStringLiteral("cmdStop"));
        sizePolicy4.setHeightForWidth(cmdStop->sizePolicy().hasHeightForWidth());
        cmdStop->setSizePolicy(sizePolicy4);
        cmdStop->setMinimumSize(QSize(36, 36));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/images/brake.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdStop->setIcon(icon25);
        cmdStop->setIconSize(QSize(30, 30));

        horizontalLayout_15->addWidget(cmdStop);


        gridLayout_3->addLayout(horizontalLayout_15, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 3, 1, 1);


        verticalLayout_9->addLayout(gridLayout_3);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setVerticalSpacing(7);
        cboJogStep = new ComboBoxKey(widgetJog);
        cboJogStep->setObjectName(QStringLiteral("cboJogStep"));
        cboJogStep->setEditable(true);
        cboJogStep->setInsertPolicy(QComboBox::NoInsert);

        gridLayout_8->addWidget(cboJogStep, 0, 1, 1, 1);

        label_20 = new QLabel(widgetJog);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setFont(font);

        gridLayout_8->addWidget(label_20, 0, 0, 1, 1);

        label_22 = new QLabel(widgetJog);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setFont(font);

        gridLayout_8->addWidget(label_22, 1, 0, 1, 1);

        cboJogFeed = new ComboBoxKey(widgetJog);
        cboJogFeed->setObjectName(QStringLiteral("cboJogFeed"));
        cboJogFeed->setEditable(true);
        cboJogFeed->setInsertPolicy(QComboBox::NoInsert);

        gridLayout_8->addWidget(cboJogFeed, 1, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout_8);

        chkKeyboardControl = new QCheckBox(widgetJog);
        chkKeyboardControl->setObjectName(QStringLiteral("chkKeyboardControl"));

        verticalLayout_9->addWidget(chkKeyboardControl);


        verticalLayout_11->addWidget(widgetJog);


        verticalLayout_21->addWidget(grpJog);

        grpSpindle = new GroupBox(scrollAreaWidgetContents);
        grpSpindle->setObjectName(QStringLiteral("grpSpindle"));
        grpSpindle->setEnabled(true);
        grpSpindle->setFont(font);
        grpSpindle->setCheckable(true);
        grpSpindle->setProperty("overrided", QVariant(false));
        horizontalLayout_2 = new QHBoxLayout(grpSpindle);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(8, 8, 8, 8);
        widgetSpindle = new QWidget(grpSpindle);
        widgetSpindle->setObjectName(QStringLiteral("widgetSpindle"));
        horizontalLayout_16 = new QHBoxLayout(widgetSpindle);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        slbSpindle = new SliderBox(widgetSpindle);
        slbSpindle->setObjectName(QStringLiteral("slbSpindle"));

        horizontalLayout_16->addWidget(slbSpindle);

        cmdSpindle = new StyledToolButton(widgetSpindle);
        cmdSpindle->setObjectName(QStringLiteral("cmdSpindle"));
        cmdSpindle->setEnabled(true);
        sizePolicy4.setHeightForWidth(cmdSpindle->sizePolicy().hasHeightForWidth());
        cmdSpindle->setSizePolicy(sizePolicy4);
        cmdSpindle->setMinimumSize(QSize(44, 44));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/images/cutter.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSpindle->setIcon(icon26);
        cmdSpindle->setIconSize(QSize(28, 28));
        cmdSpindle->setCheckable(true);

        horizontalLayout_16->addWidget(cmdSpindle);


        horizontalLayout_2->addWidget(widgetSpindle);


        verticalLayout_21->addWidget(grpSpindle);

        grpOverriding = new GroupBox(scrollAreaWidgetContents);
        grpOverriding->setObjectName(QStringLiteral("grpOverriding"));
        grpOverriding->setEnabled(true);
        grpOverriding->setFont(font);
        grpOverriding->setCheckable(true);
        grpOverriding->setProperty("overrided", QVariant(false));
        horizontalLayout_14 = new QHBoxLayout(grpOverriding);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(8, 8, 8, 8);
        widgetFeed = new QWidget(grpOverriding);
        widgetFeed->setObjectName(QStringLiteral("widgetFeed"));
        verticalLayout_22 = new QVBoxLayout(widgetFeed);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        slbFeedOverride = new SliderBox(widgetFeed);
        slbFeedOverride->setObjectName(QStringLiteral("slbFeedOverride"));

        verticalLayout_22->addWidget(slbFeedOverride);

        slbRapidOverride = new SliderBox(widgetFeed);
        slbRapidOverride->setObjectName(QStringLiteral("slbRapidOverride"));

        verticalLayout_22->addWidget(slbRapidOverride);

        slbSpindleOverride = new SliderBox(widgetFeed);
        slbSpindleOverride->setObjectName(QStringLiteral("slbSpindleOverride"));

        verticalLayout_22->addWidget(slbSpindleOverride);


        horizontalLayout_14->addWidget(widgetFeed);


        verticalLayout_21->addWidget(grpOverriding);

        grpUserCommands = new GroupBox(scrollAreaWidgetContents);
        grpUserCommands->setObjectName(QStringLiteral("grpUserCommands"));
        grpUserCommands->setEnabled(true);
        grpUserCommands->setFont(font);
        grpUserCommands->setCheckable(true);
        grpUserCommands->setProperty("overrided", QVariant(false));
        horizontalLayout_30 = new QHBoxLayout(grpUserCommands);
        horizontalLayout_30->setSpacing(9);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(8, 8, 8, 8);
        widgetUserCommands = new QWidget(grpUserCommands);
        widgetUserCommands->setObjectName(QStringLiteral("widgetUserCommands"));
        horizontalLayout_31 = new QHBoxLayout(widgetUserCommands);
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        horizontalLayout_31->setContentsMargins(0, 0, 0, 0);
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(8);
        cmdUser1 = new StyledToolButton(widgetUserCommands);
        cmdUser1->setObjectName(QStringLiteral("cmdUser1"));
        cmdUser1->setEnabled(true);
        cmdUser1->setMinimumSize(QSize(44, 44));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/images/num2.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUser1->setIcon(icon27);
        cmdUser1->setIconSize(QSize(30, 30));

        gridLayout_7->addWidget(cmdUser1, 0, 1, 1, 1);

        cmdUser3 = new StyledToolButton(widgetUserCommands);
        cmdUser3->setObjectName(QStringLiteral("cmdUser3"));
        cmdUser3->setEnabled(true);
        cmdUser3->setMinimumSize(QSize(44, 44));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/images/num4.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUser3->setIcon(icon28);
        cmdUser3->setIconSize(QSize(30, 30));

        gridLayout_7->addWidget(cmdUser3, 0, 3, 1, 1);

        cmdUser2 = new StyledToolButton(widgetUserCommands);
        cmdUser2->setObjectName(QStringLiteral("cmdUser2"));
        cmdUser2->setEnabled(true);
        cmdUser2->setMinimumSize(QSize(44, 44));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/images/num3.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUser2->setIcon(icon29);
        cmdUser2->setIconSize(QSize(30, 30));

        gridLayout_7->addWidget(cmdUser2, 0, 2, 1, 1);

        cmdUser0 = new StyledToolButton(widgetUserCommands);
        cmdUser0->setObjectName(QStringLiteral("cmdUser0"));
        cmdUser0->setEnabled(true);
        cmdUser0->setMinimumSize(QSize(44, 44));
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/images/num1.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUser0->setIcon(icon30);
        cmdUser0->setIconSize(QSize(30, 30));

        gridLayout_7->addWidget(cmdUser0, 0, 0, 1, 1);


        horizontalLayout_31->addLayout(gridLayout_7);


        horizontalLayout_30->addWidget(widgetUserCommands);


        verticalLayout_21->addWidget(grpUserCommands);

        grpHeightMap = new GroupBox(scrollAreaWidgetContents);
        grpHeightMap->setObjectName(QStringLiteral("grpHeightMap"));
        grpHeightMap->setEnabled(true);
        grpHeightMap->setFont(font);
        grpHeightMap->setCheckable(true);
        grpHeightMap->setProperty("overrided", QVariant(false));
        verticalLayout_16 = new QVBoxLayout(grpHeightMap);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(8, 8, 8, 9);
        widgetHeightMap = new QWidget(grpHeightMap);
        widgetHeightMap->setObjectName(QStringLiteral("widgetHeightMap"));
        verticalLayout_15 = new QVBoxLayout(widgetHeightMap);
        verticalLayout_15->setSpacing(7);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        chkHeightMapUse = new QCheckBox(widgetHeightMap);
        chkHeightMapUse->setObjectName(QStringLiteral("chkHeightMapUse"));

        verticalLayout_15->addWidget(chkHeightMapUse);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_15 = new QLabel(widgetHeightMap);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_22->addWidget(label_15);

        txtHeightMap = new QLineEdit(widgetHeightMap);
        txtHeightMap->setObjectName(QStringLiteral("txtHeightMap"));
        txtHeightMap->setFocusPolicy(Qt::NoFocus);
        txtHeightMap->setAlignment(Qt::AlignCenter);
        txtHeightMap->setReadOnly(true);

        horizontalLayout_22->addWidget(txtHeightMap);


        verticalLayout_15->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        cmdHeightMapCreate = new StyledToolButton(widgetHeightMap);
        cmdHeightMapCreate->setObjectName(QStringLiteral("cmdHeightMapCreate"));
        sizePolicy3.setHeightForWidth(cmdHeightMapCreate->sizePolicy().hasHeightForWidth());
        cmdHeightMapCreate->setSizePolicy(sizePolicy3);
        cmdHeightMapCreate->setMinimumSize(QSize(0, 25));

        horizontalLayout_21->addWidget(cmdHeightMapCreate);

        cmdHeightMapLoad = new StyledToolButton(widgetHeightMap);
        cmdHeightMapLoad->setObjectName(QStringLiteral("cmdHeightMapLoad"));
        sizePolicy3.setHeightForWidth(cmdHeightMapLoad->sizePolicy().hasHeightForWidth());
        cmdHeightMapLoad->setSizePolicy(sizePolicy3);
        cmdHeightMapLoad->setMinimumSize(QSize(0, 25));

        horizontalLayout_21->addWidget(cmdHeightMapLoad);


        verticalLayout_15->addLayout(horizontalLayout_21);

        cmdHeightMapMode = new StyledToolButton(widgetHeightMap);
        cmdHeightMapMode->setObjectName(QStringLiteral("cmdHeightMapMode"));
        sizePolicy3.setHeightForWidth(cmdHeightMapMode->sizePolicy().hasHeightForWidth());
        cmdHeightMapMode->setSizePolicy(sizePolicy3);
        cmdHeightMapMode->setMinimumSize(QSize(42, 25));
        cmdHeightMapMode->setCheckable(true);

        verticalLayout_15->addWidget(cmdHeightMapMode);


        verticalLayout_16->addWidget(widgetHeightMap);


        verticalLayout_21->addWidget(grpHeightMap);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitPanels->addWidget(scrollArea);
        layoutWidget1 = new QWidget(splitPanels);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        horizontalLayout_29 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(0, 0, 4, 0);
        splitPanels->addWidget(layoutWidget1);

        verticalLayout_2->addWidget(splitPanels);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalLayout_5->setStretch(0, 100);
        horizontalLayout_5->setStretch(1, 1);
        frmMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(frmMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1170, 21));
        mnuFile = new QMenu(menuBar);
        mnuFile->setObjectName(QStringLiteral("mnuFile"));
        mnuRecent = new QMenu(mnuFile);
        mnuRecent->setObjectName(QStringLiteral("mnuRecent"));
        mnuService = new QMenu(menuBar);
        mnuService->setObjectName(QStringLiteral("mnuService"));
        mnuHelp = new QMenu(menuBar);
        mnuHelp->setObjectName(QStringLiteral("mnuHelp"));
        menuMachine = new QMenu(menuBar);
        menuMachine->setObjectName(QStringLiteral("menuMachine"));
        frmMain->setMenuBar(menuBar);
        QWidget::setTabOrder(chkTestMode, chkAutoScroll);
        QWidget::setTabOrder(chkAutoScroll, cmdFileSend);
        QWidget::setTabOrder(cmdFileSend, cmdFilePause);
        QWidget::setTabOrder(cmdFilePause, cmdFileAbort);
        QWidget::setTabOrder(cmdFileAbort, cmdTop);
        QWidget::setTabOrder(cmdTop, cmdIsometric);
        QWidget::setTabOrder(cmdIsometric, cmdFront);
        QWidget::setTabOrder(cmdFront, cmdLeft);
        QWidget::setTabOrder(cmdLeft, cmdFit);
        QWidget::setTabOrder(cmdFit, txtHeightMapBorderX);
        QWidget::setTabOrder(txtHeightMapBorderX, txtHeightMapBorderWidth);
        QWidget::setTabOrder(txtHeightMapBorderWidth, txtHeightMapBorderY);
        QWidget::setTabOrder(txtHeightMapBorderY, txtHeightMapBorderHeight);
        QWidget::setTabOrder(txtHeightMapBorderHeight, chkHeightMapBorderShow);
        QWidget::setTabOrder(chkHeightMapBorderShow, cmdHeightMapBorderAuto);
        QWidget::setTabOrder(cmdHeightMapBorderAuto, txtHeightMapGridX);
        QWidget::setTabOrder(txtHeightMapGridX, txtHeightMapGridZTop);
        QWidget::setTabOrder(txtHeightMapGridZTop, txtHeightMapGridY);
        QWidget::setTabOrder(txtHeightMapGridY, txtHeightMapGridZBottom);
        QWidget::setTabOrder(txtHeightMapGridZBottom, chkHeightMapGridShow);
        QWidget::setTabOrder(chkHeightMapGridShow, txtHeightMapInterpolationStepX);
        QWidget::setTabOrder(txtHeightMapInterpolationStepX, txtHeightMapInterpolationStepY);
        QWidget::setTabOrder(txtHeightMapInterpolationStepY, cboHeightMapInterpolationType);
        QWidget::setTabOrder(cboHeightMapInterpolationType, chkHeightMapInterpolationShow);
        QWidget::setTabOrder(chkHeightMapInterpolationShow, txtMPosX);
        QWidget::setTabOrder(txtMPosX, txtMPosY);
        QWidget::setTabOrder(txtMPosY, txtMPosZ);
        QWidget::setTabOrder(txtMPosZ, scrollArea);
        QWidget::setTabOrder(scrollArea, chkHeightMapUse);
        QWidget::setTabOrder(chkHeightMapUse, cmdHeightMapCreate);
        QWidget::setTabOrder(cmdHeightMapCreate, cmdHeightMapLoad);
        QWidget::setTabOrder(cmdHeightMapLoad, cmdHeightMapMode);
        QWidget::setTabOrder(cmdHeightMapMode, grpSpindle);
        QWidget::setTabOrder(grpSpindle, cmdSpindle);
        QWidget::setTabOrder(cmdSpindle, grpOverriding);
        QWidget::setTabOrder(grpOverriding, cmdXMinus);
        QWidget::setTabOrder(cmdXMinus, cmdXPlus);
        QWidget::setTabOrder(cmdXPlus, cmdYPlus);
        QWidget::setTabOrder(cmdYPlus, cmdYMinus);
        QWidget::setTabOrder(cmdYMinus, cmdZPlus);
        QWidget::setTabOrder(cmdZPlus, cmdZMinus);
        QWidget::setTabOrder(cmdZMinus, chkKeyboardControl);
        QWidget::setTabOrder(chkKeyboardControl, txtConsole);
        QWidget::setTabOrder(txtConsole, cboCommand);
        QWidget::setTabOrder(cboCommand, cmdCommandSend);
        QWidget::setTabOrder(cmdCommandSend, cmdClearConsole);

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
        mnuService->addAction(actServiceSettings);
        mnuHelp->addAction(actAbout);
        menuMachine->addAction(actionMachine_settings);
        menuMachine->addAction(actionHard_Reset);
        menuMachine->addAction(actionSet_TLS_Position);
        menuMachine->addAction(actionDisable_Stepper);

        retranslateUi(frmMain);
        QObject::connect(chkKeyboardControl, SIGNAL(toggled(bool)), tblProgram, SLOT(setDisabled(bool)));
        QObject::connect(chkKeyboardControl, SIGNAL(toggled(bool)), slbSpindle, SLOT(setDisabled(bool)));
        QObject::connect(chkKeyboardControl, SIGNAL(toggled(bool)), widgetFeed, SLOT(setDisabled(bool)));
        QObject::connect(chkKeyboardControl, SIGNAL(toggled(bool)), tblHeightMap, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QMainWindow *frmMain)
    {
        actFileOpen->setText(QApplication::translate("frmMain", "&Open", 0));
        actFileExit->setText(QApplication::translate("frmMain", "E&xit", 0));
        actServiceSettings->setText(QApplication::translate("frmMain", "&Settings", 0));
        actFileNew->setText(QApplication::translate("frmMain", "&New", 0));
        actFileSave->setText(QApplication::translate("frmMain", "&Save", 0));
        actFileSaveAs->setText(QApplication::translate("frmMain", "Save &as...", 0));
        actAbout->setText(QApplication::translate("frmMain", "&About", 0));
        actRecentClear->setText(QApplication::translate("frmMain", "&Clear", 0));
        actFileSaveTransformedAs->setText(QApplication::translate("frmMain", "Save &transformed as...", 0));
        actionMachine_settings->setText(QApplication::translate("frmMain", "Machine settings", 0));
        actionHard_Reset->setText(QApplication::translate("frmMain", "Hard Reset", 0));
#ifndef QT_NO_TOOLTIP
        actionHard_Reset->setToolTip(QApplication::translate("frmMain", "<html><head/><body><p>Perform Hard Reset of machine control</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionSave_TLS_Position->setText(QApplication::translate("frmMain", "Set TLS Position", 0));
        actionSet_TLS_Position->setText(QApplication::translate("frmMain", "Set TLS Position", 0));
        actionDisable_Stepper->setText(QApplication::translate("frmMain", "Disable Stepper", 0));
#ifndef QT_NO_TOOLTIP
        cmdIsometric->setToolTip(QApplication::translate("frmMain", "Isometric view", 0));
#endif // QT_NO_TOOLTIP
        cmdIsometric->setText(QString());
        label_3->setText(QApplication::translate("frmMain", "Protocol:", 0));
        comboProtocol->setCurrentText(QString());
        label_4->setText(QApplication::translate("frmMain", "Interface:", 0));
        btnReload->setText(QString());
        label_21->setText(QApplication::translate("frmMain", "Baud", 0));
        btnConnect->setText(QApplication::translate("frmMain", "Connect", 0));
#ifndef QT_NO_TOOLTIP
        cmdTop->setToolTip(QApplication::translate("frmMain", "Top view", 0));
#endif // QT_NO_TOOLTIP
        cmdTop->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdFront->setToolTip(QApplication::translate("frmMain", "Front view", 0));
#endif // QT_NO_TOOLTIP
        cmdFront->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdLeft->setToolTip(QApplication::translate("frmMain", "Left view", 0));
#endif // QT_NO_TOOLTIP
        cmdLeft->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdFit->setToolTip(QApplication::translate("frmMain", "Fit", 0));
#endif // QT_NO_TOOLTIP
        cmdFit->setText(QString());
        grpConsole->setTitle(QApplication::translate("frmMain", "Console", 0));
#ifndef QT_NO_TOOLTIP
        cmdCommandSend->setToolTip(QApplication::translate("frmMain", "Send command", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdClearConsole->setToolTip(QApplication::translate("frmMain", "Clear console", 0));
#endif // QT_NO_TOOLTIP
        grpHeightMapSettings->setTitle(QApplication::translate("frmMain", "Heightmap settings", 0));
        label_5->setText(QApplication::translate("frmMain", "Border:", 0));
        label_6->setText(QApplication::translate("frmMain", "X:", 0));
        label_9->setText(QApplication::translate("frmMain", "H:", 0));
        label_7->setText(QApplication::translate("frmMain", "Y:", 0));
        label_8->setText(QApplication::translate("frmMain", "W:", 0));
        chkHeightMapBorderShow->setText(QApplication::translate("frmMain", "Show border", 0));
        cmdHeightMapBorderAuto->setText(QApplication::translate("frmMain", "Auto", 0));
        label_10->setText(QApplication::translate("frmMain", "Probe grid:", 0));
        label_12->setText(QApplication::translate("frmMain", "X:", 0));
        label_11->setText(QApplication::translate("frmMain", "Zb:", 0));
        label_13->setText(QApplication::translate("frmMain", "Y:", 0));
        label_14->setText(QApplication::translate("frmMain", "Zt:", 0));
        chkHeightMapGridShow->setText(QApplication::translate("frmMain", "Show grid", 0));
        label_16->setText(QApplication::translate("frmMain", "Interpolation grid:", 0));
        label_19->setText(QApplication::translate("frmMain", "Y:", 0));
        label_18->setText(QApplication::translate("frmMain", "X:", 0));
        label_17->setText(QApplication::translate("frmMain", "Type:", 0));
        cboHeightMapInterpolationType->clear();
        cboHeightMapInterpolationType->insertItems(0, QStringList()
         << QApplication::translate("frmMain", "Bicubic", 0)
        );
        chkHeightMapInterpolationShow->setText(QApplication::translate("frmMain", "Show", 0));
        chkTestMode->setText(QApplication::translate("frmMain", "Check mode", 0));
        chkAutoScroll->setText(QApplication::translate("frmMain", "Autoscroll", 0));
        cmdFileSend->setText(QApplication::translate("frmMain", "Send", 0));
        cmdFilePause->setText(QApplication::translate("frmMain", "Pause", 0));
        cmdFileAbort->setText(QApplication::translate("frmMain", "Stop", 0));
        cmdFileReset->setText(QApplication::translate("frmMain", "Reset", 0));
        cmdFileOpen->setText(QApplication::translate("frmMain", "Open", 0));
        grpState->setTitle(QApplication::translate("frmMain", "State", 0));
        label->setText(QApplication::translate("frmMain", "Work Coordinates:", 0));
        label_2->setText(QApplication::translate("frmMain", "Machine Coordinates:", 0));
#ifndef QT_NO_TOOLTIP
        txtMPosX->setToolTip(QApplication::translate("frmMain", "X", 0));
#endif // QT_NO_TOOLTIP
        txtMPosX->setText(QApplication::translate("frmMain", "0", 0));
#ifndef QT_NO_TOOLTIP
        txtMPosY->setToolTip(QApplication::translate("frmMain", "Y", 0));
#endif // QT_NO_TOOLTIP
        txtMPosY->setText(QApplication::translate("frmMain", "0", 0));
#ifndef QT_NO_TOOLTIP
        txtMPosZ->setToolTip(QApplication::translate("frmMain", "Z", 0));
#endif // QT_NO_TOOLTIP
        txtMPosZ->setText(QApplication::translate("frmMain", "0", 0));
        Label->setText(QApplication::translate("frmMain", "Status:", 0));
        txtStatus->setProperty("status", QVariant(QString()));
        cmdReset->setText(QApplication::translate("frmMain", "Reset", 0));
        grpControl->setTitle(QApplication::translate("frmMain", "Control", 0));
        cmdHome->setText(QApplication::translate("frmMain", "HOME", 0));
        cmdZeroY->setText(QApplication::translate("frmMain", "Zero Y", 0));
        cmdRestoreOrigin->setText(QApplication::translate("frmMain", "Origin", 0));
        cmdSafePosition->setText(QApplication::translate("frmMain", "Safe", 0));
        cmdZeroZ->setText(QApplication::translate("frmMain", "Zero Z", 0));
        cmdUnlock->setText(QApplication::translate("frmMain", "Unlock", 0));
        cmdTouch->setText(QApplication::translate("frmMain", "Probe", 0));
        cmdZeroX->setText(QApplication::translate("frmMain", "Zero X", 0));
        grpJog->setTitle(QApplication::translate("frmMain", "Jog", 0));
#ifndef QT_NO_TOOLTIP
        cmdXMinus->setToolTip(QApplication::translate("frmMain", "X-", 0));
#endif // QT_NO_TOOLTIP
        cmdXMinus->setText(QApplication::translate("frmMain", "...", 0));
#ifndef QT_NO_TOOLTIP
        cmdYMinus->setToolTip(QApplication::translate("frmMain", "Y-", 0));
#endif // QT_NO_TOOLTIP
        cmdYMinus->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdXPlus->setToolTip(QApplication::translate("frmMain", "X+", 0));
#endif // QT_NO_TOOLTIP
        cmdXPlus->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdYPlus->setToolTip(QApplication::translate("frmMain", "Y+", 0));
#endif // QT_NO_TOOLTIP
        cmdYPlus->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdZPlus->setToolTip(QApplication::translate("frmMain", "Z+", 0));
#endif // QT_NO_TOOLTIP
        cmdZPlus->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdZMinus->setToolTip(QApplication::translate("frmMain", "Z-", 0));
#endif // QT_NO_TOOLTIP
        cmdZMinus->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdStop->setToolTip(QApplication::translate("frmMain", "Stop", 0));
#endif // QT_NO_TOOLTIP
        cmdStop->setText(QString());
        cboJogStep->clear();
        cboJogStep->insertItems(0, QStringList()
         << QApplication::translate("frmMain", "Continuously", 0)
         << QApplication::translate("frmMain", "0.01", 0)
         << QApplication::translate("frmMain", "0.1", 0)
         << QApplication::translate("frmMain", "1", 0)
         << QApplication::translate("frmMain", "2", 0)
         << QApplication::translate("frmMain", "5", 0)
         << QApplication::translate("frmMain", "10", 0)
         << QApplication::translate("frmMain", "20", 0)
         << QApplication::translate("frmMain", "50", 0)
         << QApplication::translate("frmMain", "100", 0)
         << QApplication::translate("frmMain", "200", 0)
        );
        label_20->setText(QApplication::translate("frmMain", "Step:", 0));
        label_22->setText(QApplication::translate("frmMain", "Feed:", 0));
        cboJogFeed->clear();
        cboJogFeed->insertItems(0, QStringList()
         << QApplication::translate("frmMain", "10", 0)
         << QApplication::translate("frmMain", "20", 0)
         << QApplication::translate("frmMain", "50", 0)
         << QApplication::translate("frmMain", "100", 0)
         << QApplication::translate("frmMain", "200", 0)
         << QApplication::translate("frmMain", "500", 0)
         << QApplication::translate("frmMain", "1000", 0)
         << QApplication::translate("frmMain", "2000", 0)
        );
        chkKeyboardControl->setText(QApplication::translate("frmMain", "Keyboard control", 0));
        grpSpindle->setTitle(QApplication::translate("frmMain", "Spindle", 0));
#ifndef QT_NO_TOOLTIP
        cmdSpindle->setToolTip(QApplication::translate("frmMain", "Spindle on/off", 0));
#endif // QT_NO_TOOLTIP
        grpOverriding->setTitle(QApplication::translate("frmMain", "Overriding", 0));
        grpUserCommands->setTitle(QApplication::translate("frmMain", "User commands", 0));
#ifndef QT_NO_TOOLTIP
        cmdUser1->setToolTip(QApplication::translate("frmMain", "Spindle on/off", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdUser3->setToolTip(QApplication::translate("frmMain", "Spindle on/off", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdUser2->setToolTip(QApplication::translate("frmMain", "Spindle on/off", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdUser0->setToolTip(QApplication::translate("frmMain", "Spindle on/off", 0));
#endif // QT_NO_TOOLTIP
        grpHeightMap->setTitle(QApplication::translate("frmMain", "Heightmap", 0));
        chkHeightMapUse->setText(QApplication::translate("frmMain", "Use heightmap", 0));
        label_15->setText(QApplication::translate("frmMain", "Map:", 0));
        txtHeightMap->setText(QString());
        txtHeightMap->setPlaceholderText(QApplication::translate("frmMain", "Absent", 0));
        cmdHeightMapCreate->setText(QApplication::translate("frmMain", "Create", 0));
        cmdHeightMapLoad->setText(QApplication::translate("frmMain", "Open", 0));
        cmdHeightMapMode->setText(QApplication::translate("frmMain", "Edit mode", 0));
        mnuFile->setTitle(QApplication::translate("frmMain", "&File", 0));
        mnuRecent->setTitle(QApplication::translate("frmMain", "&Recent files", 0));
        mnuService->setTitle(QApplication::translate("frmMain", "Edit", 0));
        mnuHelp->setTitle(QApplication::translate("frmMain", "&Help", 0));
        menuMachine->setTitle(QApplication::translate("frmMain", "Machine", 0));
        Q_UNUSED(frmMain);
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
