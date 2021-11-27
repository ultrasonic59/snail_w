/********************************************************************************
** Form generated from reading UI file 'frmsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSETTINGS_H
#define UI_FRMSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "widgets/colorpicker.h"
#include "widgets/groupbox.h"
#include "widgets/scrollarea.h"
#include "widgets/widget.h"

QT_BEGIN_NAMESPACE

class Ui_frmSettings
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listCategories;
    ScrollArea *scrollSettings;
    Widget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    GroupBox *grpConnection;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cboPort;
    QToolButton *cmdRefresh;
    QLabel *label_2;
    QComboBox *cboBaud;
    GroupBox *grpGRBL;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QLabel *label_9;
    QSpinBox *txtQueryStateTime;
    QDoubleSpinBox *txtSafeZ;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QSpinBox *txtRapidSpeed;
    QLabel *label_14;
    QSpinBox *txtAcceleration;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QSpinBox *txtSpindleSpeedMin;
    QLabel *label_13;
    QSpinBox *txtSpindleSpeedMax;
    QLabel *label_17;
    QLineEdit *txtTouchCommand;
    QGridLayout *gridLayout_4;
    QLabel *label_18;
    QSpinBox *txtHeightMapProbingFeed;
    QLabel *label_15;
    QComboBox *cboUnits;
    GroupBox *grpParser;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_32;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radArcLengthMode;
    QDoubleSpinBox *txtArcLength;
    QSpacerItem *horizontalSpacer_15;
    QRadioButton *radArcDegreeMode;
    QDoubleSpinBox *txtArcDegree;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_35;
    GroupBox *grpVisualizer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *txtLineWidth;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *chkAntialiasing;
    QCheckBox *radMSAA;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *chkSimplify;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_8;
    QDoubleSpinBox *txtSimplifyPrecision;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *cboFps;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *chkZBuffer;
    QSpacerItem *horizontalSpacer_10;
    GroupBox *grpTool;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *cboToolType;
    QLabel *lblToolAngle;
    QLabel *lblToolLength;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *txtToolDiameter;
    QDoubleSpinBox *txtToolLength;
    QDoubleSpinBox *txtToolAngle;
    GroupBox *grpConsole;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkShowProgramCommands;
    QCheckBox *chkShowUICommands;
    QCheckBox *chkAutocompletion;
    GroupBox *grpPanels;
    QGridLayout *gridLayout_3;
    QCheckBox *chkPanelHeightmap;
    QCheckBox *chkPanelFeed;
    QCheckBox *chkPanelSpindle;
    QCheckBox *chkPanelJog;
    GroupBox *grpColors;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_6;
    QLabel *label_20;
    QLabel *label_21;
    ColorPicker *clpToolpathZMovement;
    QLabel *label_24;
    ColorPicker *clpToolpathHighlight;
    ColorPicker *clpToolpathStart;
    QLabel *label_25;
    QLabel *label_26;
    ColorPicker *clpToolpathEnd;
    QLabel *label_27;
    ColorPicker *clpVisualizerBackground;
    ColorPicker *clpVisualizerText;
    QLabel *label_22;
    QLabel *label_28;
    QLabel *label_19;
    ColorPicker *clpTool;
    QSpacerItem *verticalSpacer;
    QLabel *label_16;
    ColorPicker *clpToolpathDrawn;
    ColorPicker *clpToolpathNormal;
    QLabel *label_23;
    GroupBox *groupBox;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_29;
    QComboBox *cboFontSize;
    QLabel *label_30;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_31;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdDefaults;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdOK;
    QPushButton *cmdCancel;

    void setupUi(QDialog *frmSettings)
    {
        if (frmSettings->objectName().isEmpty())
            frmSettings->setObjectName(QStringLiteral("frmSettings"));
        frmSettings->resize(578, 490);
        frmSettings->setStyleSheet(QLatin1String("/*QWidget {\n"
"	font-size: 9pt;\n"
"}*/\n"
"\n"
"QSpinBox, QDoubleSpinBox {\n"
"	padding-top: 1px;\n"
"	padding-bottom: 1px;\n"
"}\n"
"\n"
"QGroupBox {\n"
"	border: none;\n"
"	padding-top: 16;\n"
"	font-weight: bold;\n"
"}"));
        frmSettings->setModal(true);
        verticalLayout_6 = new QVBoxLayout(frmSettings);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        listCategories = new QListWidget(frmSettings);
        listCategories->setObjectName(QStringLiteral("listCategories"));
        listCategories->setStyleSheet(QLatin1String("QListWidget::item {\n"
"	height: 1.75em;\n"
"}"));
        listCategories->setSpacing(1);

        horizontalLayout_2->addWidget(listCategories);

        scrollSettings = new ScrollArea(frmSettings);
        scrollSettings->setObjectName(QStringLiteral("scrollSettings"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollSettings->sizePolicy().hasHeightForWidth());
        scrollSettings->setSizePolicy(sizePolicy);
        scrollSettings->setFrameShape(QFrame::NoFrame);
        scrollSettings->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollSettings->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollSettings->setWidgetResizable(true);
        scrollAreaWidgetContents = new Widget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -159, 399, 1199));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        grpConnection = new GroupBox(scrollAreaWidgetContents);
        grpConnection->setObjectName(QStringLiteral("grpConnection"));
        verticalLayout = new QVBoxLayout(grpConnection);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(grpConnection);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        cboPort = new QComboBox(grpConnection);
        cboPort->setObjectName(QStringLiteral("cboPort"));
        cboPort->setEditable(true);

        horizontalLayout_3->addWidget(cboPort);

        cmdRefresh = new QToolButton(grpConnection);
        cmdRefresh->setObjectName(QStringLiteral("cmdRefresh"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmdRefresh->sizePolicy().hasHeightForWidth());
        cmdRefresh->setSizePolicy(sizePolicy1);
        cmdRefresh->setStyleSheet(QStringLiteral("padding: 0 1 0 2;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/restart.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);

        horizontalLayout_3->addWidget(cmdRefresh);

        label_2 = new QLabel(grpConnection);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        cboBaud = new QComboBox(grpConnection);
        cboBaud->setObjectName(QStringLiteral("cboBaud"));
        cboBaud->setEditable(true);

        horizontalLayout_3->addWidget(cboBaud);

        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_4->addWidget(grpConnection);

        grpGRBL = new GroupBox(scrollAreaWidgetContents);
        grpGRBL->setObjectName(QStringLiteral("grpGRBL"));
        verticalLayout_5 = new QVBoxLayout(grpGRBL);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_11 = new QLabel(grpGRBL);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        label_9 = new QLabel(grpGRBL);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 0, 3, 1, 1);

        txtQueryStateTime = new QSpinBox(grpGRBL);
        txtQueryStateTime->setObjectName(QStringLiteral("txtQueryStateTime"));
        QFont font;
        font.setPointSize(9);
        txtQueryStateTime->setFont(font);
        txtQueryStateTime->setAlignment(Qt::AlignCenter);
        txtQueryStateTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtQueryStateTime->setMaximum(9999);

        gridLayout_2->addWidget(txtQueryStateTime, 0, 1, 1, 1);

        txtSafeZ = new QDoubleSpinBox(grpGRBL);
        txtSafeZ->setObjectName(QStringLiteral("txtSafeZ"));
        txtSafeZ->setAlignment(Qt::AlignCenter);
        txtSafeZ->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtSafeZ->setDecimals(3);
        txtSafeZ->setMinimum(-999);
        txtSafeZ->setMaximum(999);

        gridLayout_2->addWidget(txtSafeZ, 0, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_10 = new QLabel(grpGRBL);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_4->addWidget(label_10);

        txtRapidSpeed = new QSpinBox(grpGRBL);
        txtRapidSpeed->setObjectName(QStringLiteral("txtRapidSpeed"));
        txtRapidSpeed->setFont(font);
        txtRapidSpeed->setAlignment(Qt::AlignCenter);
        txtRapidSpeed->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtRapidSpeed->setMaximum(99999);

        horizontalLayout_4->addWidget(txtRapidSpeed);

        label_14 = new QLabel(grpGRBL);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_4->addWidget(label_14);

        txtAcceleration = new QSpinBox(grpGRBL);
        txtAcceleration->setObjectName(QStringLiteral("txtAcceleration"));
        txtAcceleration->setFont(font);
        txtAcceleration->setAlignment(Qt::AlignCenter);
        txtAcceleration->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtAcceleration->setMaximum(99999);

        horizontalLayout_4->addWidget(txtAcceleration);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_12 = new QLabel(grpGRBL);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_9->addWidget(label_12);

        txtSpindleSpeedMin = new QSpinBox(grpGRBL);
        txtSpindleSpeedMin->setObjectName(QStringLiteral("txtSpindleSpeedMin"));
        txtSpindleSpeedMin->setFont(font);
        txtSpindleSpeedMin->setAlignment(Qt::AlignCenter);
        txtSpindleSpeedMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtSpindleSpeedMin->setMaximum(99999);

        horizontalLayout_9->addWidget(txtSpindleSpeedMin);

        label_13 = new QLabel(grpGRBL);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_9->addWidget(label_13);

        txtSpindleSpeedMax = new QSpinBox(grpGRBL);
        txtSpindleSpeedMax->setObjectName(QStringLiteral("txtSpindleSpeedMax"));
        txtSpindleSpeedMax->setFont(font);
        txtSpindleSpeedMax->setAlignment(Qt::AlignCenter);
        txtSpindleSpeedMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtSpindleSpeedMax->setMaximum(99999);

        horizontalLayout_9->addWidget(txtSpindleSpeedMax);


        verticalLayout_5->addLayout(horizontalLayout_9);

        label_17 = new QLabel(grpGRBL);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setStyleSheet(QLatin1String("padding-left: -4;\n"
"padding-top: 3;"));

        verticalLayout_5->addWidget(label_17);

        txtTouchCommand = new QLineEdit(grpGRBL);
        txtTouchCommand->setObjectName(QStringLiteral("txtTouchCommand"));
        txtTouchCommand->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(txtTouchCommand);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(12);
        label_18 = new QLabel(grpGRBL);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_4->addWidget(label_18, 0, 0, 1, 1);

        txtHeightMapProbingFeed = new QSpinBox(grpGRBL);
        txtHeightMapProbingFeed->setObjectName(QStringLiteral("txtHeightMapProbingFeed"));
        txtHeightMapProbingFeed->setFont(font);
        txtHeightMapProbingFeed->setAlignment(Qt::AlignCenter);
        txtHeightMapProbingFeed->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtHeightMapProbingFeed->setMaximum(99999);

        gridLayout_4->addWidget(txtHeightMapProbingFeed, 0, 1, 1, 1);

        label_15 = new QLabel(grpGRBL);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 1, 0, 1, 1);

        cboUnits = new QComboBox(grpGRBL);
        cboUnits->setObjectName(QStringLiteral("cboUnits"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cboUnits->sizePolicy().hasHeightForWidth());
        cboUnits->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(cboUnits, 1, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);


        verticalLayout_4->addWidget(grpGRBL);

        grpParser = new GroupBox(scrollAreaWidgetContents);
        grpParser->setObjectName(QStringLiteral("grpParser"));
        verticalLayout_8 = new QVBoxLayout(grpParser);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_32 = new QLabel(grpParser);
        label_32->setObjectName(QStringLiteral("label_32"));

        horizontalLayout_11->addWidget(label_32);

        horizontalSpacer_14 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_14);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        radArcLengthMode = new QRadioButton(grpParser);
        radArcLengthMode->setObjectName(QStringLiteral("radArcLengthMode"));
        radArcLengthMode->setChecked(true);

        horizontalLayout_8->addWidget(radArcLengthMode);

        txtArcLength = new QDoubleSpinBox(grpParser);
        txtArcLength->setObjectName(QStringLiteral("txtArcLength"));
        txtArcLength->setEnabled(true);
        txtArcLength->setAlignment(Qt::AlignCenter);
        txtArcLength->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtArcLength->setDecimals(2);
        txtArcLength->setMaximum(99);

        horizontalLayout_8->addWidget(txtArcLength);

        horizontalSpacer_15 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        radArcDegreeMode = new QRadioButton(grpParser);
        radArcDegreeMode->setObjectName(QStringLiteral("radArcDegreeMode"));

        horizontalLayout_8->addWidget(radArcDegreeMode);

        txtArcDegree = new QDoubleSpinBox(grpParser);
        txtArcDegree->setObjectName(QStringLiteral("txtArcDegree"));
        txtArcDegree->setEnabled(false);
        txtArcDegree->setAlignment(Qt::AlignCenter);
        txtArcDegree->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtArcDegree->setDecimals(2);
        txtArcDegree->setMaximum(180);

        horizontalLayout_8->addWidget(txtArcDegree);

        horizontalSpacer_11 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);


        verticalLayout_8->addLayout(horizontalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_35 = new QLabel(grpParser);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setStyleSheet(QStringLiteral("color: blue;"));
        label_35->setWordWrap(true);

        horizontalLayout_12->addWidget(label_35);


        verticalLayout_8->addLayout(horizontalLayout_12);


        verticalLayout_4->addWidget(grpParser);

        grpVisualizer = new GroupBox(scrollAreaWidgetContents);
        grpVisualizer->setObjectName(QStringLiteral("grpVisualizer"));
        verticalLayout_2 = new QVBoxLayout(grpVisualizer);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(grpVisualizer);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        txtLineWidth = new QDoubleSpinBox(grpVisualizer);
        txtLineWidth->setObjectName(QStringLiteral("txtLineWidth"));
        txtLineWidth->setAlignment(Qt::AlignCenter);
        txtLineWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtLineWidth->setDecimals(1);
        txtLineWidth->setMaximum(9);

        horizontalLayout_5->addWidget(txtLineWidth);

        horizontalSpacer_7 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        chkAntialiasing = new QCheckBox(grpVisualizer);
        chkAntialiasing->setObjectName(QStringLiteral("chkAntialiasing"));

        horizontalLayout_5->addWidget(chkAntialiasing);

        radMSAA = new QCheckBox(grpVisualizer);
        radMSAA->setObjectName(QStringLiteral("radMSAA"));
        radMSAA->setEnabled(false);

        horizontalLayout_5->addWidget(radMSAA);

        horizontalSpacer_12 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        chkSimplify = new QCheckBox(grpVisualizer);
        chkSimplify->setObjectName(QStringLiteral("chkSimplify"));

        horizontalLayout_6->addWidget(chkSimplify);

        horizontalSpacer_5 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        label_8 = new QLabel(grpVisualizer);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setEnabled(false);

        horizontalLayout_6->addWidget(label_8);

        txtSimplifyPrecision = new QDoubleSpinBox(grpVisualizer);
        txtSimplifyPrecision->setObjectName(QStringLiteral("txtSimplifyPrecision"));
        txtSimplifyPrecision->setEnabled(false);
        txtSimplifyPrecision->setAlignment(Qt::AlignCenter);
        txtSimplifyPrecision->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtSimplifyPrecision->setDecimals(2);
        txtSimplifyPrecision->setMaximum(99);

        horizontalLayout_6->addWidget(txtSimplifyPrecision);

        horizontalSpacer_13 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_13);

        horizontalSpacer_9 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(grpVisualizer);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        cboFps = new QComboBox(grpVisualizer);
        cboFps->setObjectName(QStringLiteral("cboFps"));
        cboFps->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhFormattedNumbersOnly);
        cboFps->setEditable(true);

        horizontalLayout_7->addWidget(cboFps);

        horizontalSpacer_8 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        chkZBuffer = new QCheckBox(grpVisualizer);
        chkZBuffer->setObjectName(QStringLiteral("chkZBuffer"));

        horizontalLayout_7->addWidget(chkZBuffer);

        horizontalSpacer_10 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_4->addWidget(grpVisualizer);

        grpTool = new GroupBox(scrollAreaWidgetContents);
        grpTool->setObjectName(QStringLiteral("grpTool"));
        gridLayout = new QGridLayout(grpTool);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(grpTool);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(grpTool);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        cboToolType = new QComboBox(grpTool);
        cboToolType->setObjectName(QStringLiteral("cboToolType"));
        sizePolicy2.setHeightForWidth(cboToolType->sizePolicy().hasHeightForWidth());
        cboToolType->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(cboToolType, 0, 1, 1, 1);

        lblToolAngle = new QLabel(grpTool);
        lblToolAngle->setObjectName(QStringLiteral("lblToolAngle"));
        lblToolAngle->setEnabled(false);

        gridLayout->addWidget(lblToolAngle, 0, 4, 1, 1);

        lblToolLength = new QLabel(grpTool);
        lblToolLength->setObjectName(QStringLiteral("lblToolLength"));

        gridLayout->addWidget(lblToolLength, 1, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        txtToolDiameter = new QDoubleSpinBox(grpTool);
        txtToolDiameter->setObjectName(QStringLiteral("txtToolDiameter"));
        sizePolicy2.setHeightForWidth(txtToolDiameter->sizePolicy().hasHeightForWidth());
        txtToolDiameter->setSizePolicy(sizePolicy2);
        txtToolDiameter->setAlignment(Qt::AlignCenter);
        txtToolDiameter->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtToolDiameter->setDecimals(3);
        txtToolDiameter->setMaximum(99);

        gridLayout->addWidget(txtToolDiameter, 1, 1, 1, 1);

        txtToolLength = new QDoubleSpinBox(grpTool);
        txtToolLength->setObjectName(QStringLiteral("txtToolLength"));
        sizePolicy2.setHeightForWidth(txtToolLength->sizePolicy().hasHeightForWidth());
        txtToolLength->setSizePolicy(sizePolicy2);
        txtToolLength->setAlignment(Qt::AlignCenter);
        txtToolLength->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtToolLength->setDecimals(3);
        txtToolLength->setMaximum(999);

        gridLayout->addWidget(txtToolLength, 1, 5, 1, 1);

        txtToolAngle = new QDoubleSpinBox(grpTool);
        txtToolAngle->setObjectName(QStringLiteral("txtToolAngle"));
        sizePolicy2.setHeightForWidth(txtToolAngle->sizePolicy().hasHeightForWidth());
        txtToolAngle->setSizePolicy(sizePolicy2);
        txtToolAngle->setAlignment(Qt::AlignCenter);
        txtToolAngle->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txtToolAngle->setDecimals(3);
        txtToolAngle->setMaximum(180);

        gridLayout->addWidget(txtToolAngle, 0, 5, 1, 1);


        verticalLayout_4->addWidget(grpTool);

        grpConsole = new GroupBox(scrollAreaWidgetContents);
        grpConsole->setObjectName(QStringLiteral("grpConsole"));
        verticalLayout_3 = new QVBoxLayout(grpConsole);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        chkShowProgramCommands = new QCheckBox(grpConsole);
        chkShowProgramCommands->setObjectName(QStringLiteral("chkShowProgramCommands"));

        verticalLayout_3->addWidget(chkShowProgramCommands);

        chkShowUICommands = new QCheckBox(grpConsole);
        chkShowUICommands->setObjectName(QStringLiteral("chkShowUICommands"));

        verticalLayout_3->addWidget(chkShowUICommands);

        chkAutocompletion = new QCheckBox(grpConsole);
        chkAutocompletion->setObjectName(QStringLiteral("chkAutocompletion"));

        verticalLayout_3->addWidget(chkAutocompletion);


        verticalLayout_4->addWidget(grpConsole);

        grpPanels = new GroupBox(scrollAreaWidgetContents);
        grpPanels->setObjectName(QStringLiteral("grpPanels"));
        gridLayout_3 = new QGridLayout(grpPanels);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        chkPanelHeightmap = new QCheckBox(grpPanels);
        chkPanelHeightmap->setObjectName(QStringLiteral("chkPanelHeightmap"));

        gridLayout_3->addWidget(chkPanelHeightmap, 0, 0, 1, 1);

        chkPanelFeed = new QCheckBox(grpPanels);
        chkPanelFeed->setObjectName(QStringLiteral("chkPanelFeed"));

        gridLayout_3->addWidget(chkPanelFeed, 0, 1, 1, 1);

        chkPanelSpindle = new QCheckBox(grpPanels);
        chkPanelSpindle->setObjectName(QStringLiteral("chkPanelSpindle"));

        gridLayout_3->addWidget(chkPanelSpindle, 1, 0, 1, 1);

        chkPanelJog = new QCheckBox(grpPanels);
        chkPanelJog->setObjectName(QStringLiteral("chkPanelJog"));

        gridLayout_3->addWidget(chkPanelJog, 1, 1, 1, 1);


        verticalLayout_4->addWidget(grpPanels);

        grpColors = new GroupBox(scrollAreaWidgetContents);
        grpColors->setObjectName(QStringLiteral("grpColors"));
        verticalLayout_7 = new QVBoxLayout(grpColors);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_20 = new QLabel(grpColors);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_6->addWidget(label_20, 7, 2, 1, 1);

        label_21 = new QLabel(grpColors);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setWordWrap(true);

        gridLayout_6->addWidget(label_21, 5, 0, 1, 1);

        clpToolpathZMovement = new ColorPicker(grpColors);
        clpToolpathZMovement->setObjectName(QStringLiteral("clpToolpathZMovement"));

        gridLayout_6->addWidget(clpToolpathZMovement, 7, 3, 1, 1);

        label_24 = new QLabel(grpColors);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_6->addWidget(label_24, 2, 0, 1, 1);

        clpToolpathHighlight = new ColorPicker(grpColors);
        clpToolpathHighlight->setObjectName(QStringLiteral("clpToolpathHighlight"));

        gridLayout_6->addWidget(clpToolpathHighlight, 7, 1, 1, 1);

        clpToolpathStart = new ColorPicker(grpColors);
        clpToolpathStart->setObjectName(QStringLiteral("clpToolpathStart"));

        gridLayout_6->addWidget(clpToolpathStart, 8, 1, 1, 1);

        label_25 = new QLabel(grpColors);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_6->addWidget(label_25, 7, 0, 1, 1);

        label_26 = new QLabel(grpColors);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_6->addWidget(label_26, 8, 0, 1, 1);

        clpToolpathEnd = new ColorPicker(grpColors);
        clpToolpathEnd->setObjectName(QStringLiteral("clpToolpathEnd"));

        gridLayout_6->addWidget(clpToolpathEnd, 8, 3, 1, 1);

        label_27 = new QLabel(grpColors);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_6->addWidget(label_27, 8, 2, 1, 1);

        clpVisualizerBackground = new ColorPicker(grpColors);
        clpVisualizerBackground->setObjectName(QStringLiteral("clpVisualizerBackground"));

        gridLayout_6->addWidget(clpVisualizerBackground, 2, 1, 1, 1);

        clpVisualizerText = new ColorPicker(grpColors);
        clpVisualizerText->setObjectName(QStringLiteral("clpVisualizerText"));

        gridLayout_6->addWidget(clpVisualizerText, 2, 3, 1, 1);

        label_22 = new QLabel(grpColors);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_6->addWidget(label_22, 1, 0, 1, 1);

        label_28 = new QLabel(grpColors);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_6->addWidget(label_28, 2, 2, 1, 1);

        label_19 = new QLabel(grpColors);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_6->addWidget(label_19, 3, 0, 1, 1);

        clpTool = new ColorPicker(grpColors);
        clpTool->setObjectName(QStringLiteral("clpTool"));

        gridLayout_6->addWidget(clpTool, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_6->addItem(verticalSpacer, 4, 0, 1, 1);

        label_16 = new QLabel(grpColors);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_6->addWidget(label_16, 6, 2, 1, 1);

        clpToolpathDrawn = new ColorPicker(grpColors);
        clpToolpathDrawn->setObjectName(QStringLiteral("clpToolpathDrawn"));

        gridLayout_6->addWidget(clpToolpathDrawn, 6, 3, 1, 1);

        clpToolpathNormal = new ColorPicker(grpColors);
        clpToolpathNormal->setObjectName(QStringLiteral("clpToolpathNormal"));

        gridLayout_6->addWidget(clpToolpathNormal, 6, 1, 1, 1);

        label_23 = new QLabel(grpColors);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_6->addWidget(label_23, 6, 0, 1, 1);


        verticalLayout_7->addLayout(gridLayout_6);


        verticalLayout_4->addWidget(grpColors);

        groupBox = new GroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_10 = new QHBoxLayout(groupBox);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout_10->addWidget(label_29);

        cboFontSize = new QComboBox(groupBox);
        cboFontSize->setObjectName(QStringLiteral("cboFontSize"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cboFontSize->sizePolicy().hasHeightForWidth());
        cboFontSize->setSizePolicy(sizePolicy3);
        cboFontSize->setEditable(true);
        cboFontSize->setMaxCount(10);
        cboFontSize->setMinimumContentsLength(1);

        horizontalLayout_10->addWidget(cboFontSize);

        label_30 = new QLabel(groupBox);
        label_30->setObjectName(QStringLiteral("label_30"));

        horizontalLayout_10->addWidget(label_30);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        label_31 = new QLabel(groupBox);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setStyleSheet(QStringLiteral("color: blue;"));

        horizontalLayout_10->addWidget(label_31);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);


        verticalLayout_4->addWidget(groupBox);

        scrollSettings->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollSettings);


        verticalLayout_6->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cmdDefaults = new QPushButton(frmSettings);
        cmdDefaults->setObjectName(QStringLiteral("cmdDefaults"));
        cmdDefaults->setAutoDefault(false);

        horizontalLayout->addWidget(cmdDefaults);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdOK = new QPushButton(frmSettings);
        cmdOK->setObjectName(QStringLiteral("cmdOK"));
        cmdOK->setAutoDefault(false);

        horizontalLayout->addWidget(cmdOK);

        cmdCancel = new QPushButton(frmSettings);
        cmdCancel->setObjectName(QStringLiteral("cmdCancel"));
        cmdCancel->setAutoDefault(false);

        horizontalLayout->addWidget(cmdCancel);


        verticalLayout_6->addLayout(horizontalLayout);

        QWidget::setTabOrder(listCategories, scrollSettings);
        QWidget::setTabOrder(scrollSettings, cboPort);
        QWidget::setTabOrder(cboPort, cmdRefresh);
        QWidget::setTabOrder(cmdRefresh, cboBaud);
        QWidget::setTabOrder(cboBaud, txtQueryStateTime);
        QWidget::setTabOrder(txtQueryStateTime, txtSafeZ);
        QWidget::setTabOrder(txtSafeZ, txtRapidSpeed);
        QWidget::setTabOrder(txtRapidSpeed, txtAcceleration);
        QWidget::setTabOrder(txtAcceleration, txtSpindleSpeedMin);
        QWidget::setTabOrder(txtSpindleSpeedMin, txtSpindleSpeedMax);
        QWidget::setTabOrder(txtSpindleSpeedMax, txtTouchCommand);
        QWidget::setTabOrder(txtTouchCommand, txtHeightMapProbingFeed);
        QWidget::setTabOrder(txtHeightMapProbingFeed, cboUnits);
        QWidget::setTabOrder(cboUnits, radArcLengthMode);
        QWidget::setTabOrder(radArcLengthMode, txtArcLength);
        QWidget::setTabOrder(txtArcLength, radArcDegreeMode);
        QWidget::setTabOrder(radArcDegreeMode, txtArcDegree);
        QWidget::setTabOrder(txtArcDegree, txtLineWidth);
        QWidget::setTabOrder(txtLineWidth, chkAntialiasing);
        QWidget::setTabOrder(chkAntialiasing, radMSAA);
        QWidget::setTabOrder(radMSAA, chkSimplify);
        QWidget::setTabOrder(chkSimplify, txtSimplifyPrecision);
        QWidget::setTabOrder(txtSimplifyPrecision, cboFps);
        QWidget::setTabOrder(cboFps, chkZBuffer);
        QWidget::setTabOrder(chkZBuffer, cboToolType);
        QWidget::setTabOrder(cboToolType, txtToolAngle);
        QWidget::setTabOrder(txtToolAngle, txtToolDiameter);
        QWidget::setTabOrder(txtToolDiameter, txtToolLength);
        QWidget::setTabOrder(txtToolLength, chkShowProgramCommands);
        QWidget::setTabOrder(chkShowProgramCommands, chkShowUICommands);
        QWidget::setTabOrder(chkShowUICommands, chkAutocompletion);
        QWidget::setTabOrder(chkAutocompletion, chkPanelHeightmap);
        QWidget::setTabOrder(chkPanelHeightmap, chkPanelFeed);
        QWidget::setTabOrder(chkPanelFeed, chkPanelSpindle);
        QWidget::setTabOrder(chkPanelSpindle, chkPanelJog);
        QWidget::setTabOrder(chkPanelJog, cboFontSize);
        QWidget::setTabOrder(cboFontSize, cmdDefaults);
        QWidget::setTabOrder(cmdDefaults, cmdOK);
        QWidget::setTabOrder(cmdOK, cmdCancel);

        retranslateUi(frmSettings);
        QObject::connect(chkSimplify, SIGNAL(toggled(bool)), label_8, SLOT(setEnabled(bool)));
        QObject::connect(chkSimplify, SIGNAL(toggled(bool)), txtSimplifyPrecision, SLOT(setEnabled(bool)));
        QObject::connect(chkAntialiasing, SIGNAL(toggled(bool)), radMSAA, SLOT(setEnabled(bool)));
        QObject::connect(radArcDegreeMode, SIGNAL(toggled(bool)), txtArcDegree, SLOT(setEnabled(bool)));
        QObject::connect(radArcLengthMode, SIGNAL(toggled(bool)), txtArcLength, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(frmSettings);
    } // setupUi

    void retranslateUi(QDialog *frmSettings)
    {
        frmSettings->setWindowTitle(QApplication::translate("frmSettings", "Settings", 0));
        grpConnection->setTitle(QApplication::translate("frmSettings", "Connection", 0));
        label->setText(QApplication::translate("frmSettings", "Port:", 0));
        cmdRefresh->setText(QApplication::translate("frmSettings", "...", 0));
        label_2->setText(QApplication::translate("frmSettings", "Baud:", 0));
        cboBaud->clear();
        cboBaud->insertItems(0, QStringList()
         << QApplication::translate("frmSettings", "9600", 0)
         << QApplication::translate("frmSettings", "14400", 0)
         << QApplication::translate("frmSettings", "19200", 0)
         << QApplication::translate("frmSettings", "38400", 0)
         << QApplication::translate("frmSettings", "57600", 0)
         << QApplication::translate("frmSettings", "115200", 0)
        );
        cboBaud->setCurrentText(QApplication::translate("frmSettings", "9600", 0));
        grpGRBL->setTitle(QApplication::translate("frmSettings", "GRBL", 0));
        label_11->setText(QApplication::translate("frmSettings", "Query period:", 0));
        label_9->setText(QApplication::translate("frmSettings", "Safe Z:", 0));
        label_10->setText(QApplication::translate("frmSettings", "Rapid speed:", 0));
        label_14->setText(QApplication::translate("frmSettings", "Acceleration:", 0));
        label_12->setText(QApplication::translate("frmSettings", "Spindle speed min.:", 0));
        label_13->setText(QApplication::translate("frmSettings", "max.:", 0));
        label_17->setText(QApplication::translate("frmSettings", "Z-probe commands:", 0));
        txtTouchCommand->setPlaceholderText(QApplication::translate("frmSettings", "Command 1; command 2; ...", 0));
        label_18->setText(QApplication::translate("frmSettings", "Heightmap probing feed:", 0));
        label_15->setText(QApplication::translate("frmSettings", "Report units:", 0));
        cboUnits->clear();
        cboUnits->insertItems(0, QStringList()
         << QApplication::translate("frmSettings", "Metric", 0)
         << QApplication::translate("frmSettings", "Imperial", 0)
        );
        grpParser->setTitle(QApplication::translate("frmSettings", "Parser", 0));
        label_32->setText(QApplication::translate("frmSettings", "Arc approximation segment size:", 0));
        radArcLengthMode->setText(QApplication::translate("frmSettings", "by length", 0));
        radArcDegreeMode->setText(QApplication::translate("frmSettings", "by angle (deg.)", 0));
        label_35->setText(QApplication::translate("frmSettings", "(used in the visualizer and the procedure of transformation files in accordance with the height map)", 0));
        grpVisualizer->setTitle(QApplication::translate("frmSettings", "Visualizer", 0));
        label_5->setText(QApplication::translate("frmSettings", "Line width:", 0));
        chkAntialiasing->setText(QApplication::translate("frmSettings", "Smoothing", 0));
        radMSAA->setText(QApplication::translate("frmSettings", "MSAA", 0));
        chkSimplify->setText(QApplication::translate("frmSettings", "Simplify geometry", 0));
        label_8->setText(QApplication::translate("frmSettings", "Segment length:", 0));
        label_7->setText(QApplication::translate("frmSettings", "FPS lock:", 0));
        cboFps->clear();
        cboFps->insertItems(0, QStringList()
         << QApplication::translate("frmSettings", "30", 0)
         << QApplication::translate("frmSettings", "60", 0)
         << QApplication::translate("frmSettings", "120", 0)
        );
        chkZBuffer->setText(QApplication::translate("frmSettings", "Z-buffer", 0));
        grpTool->setTitle(QApplication::translate("frmSettings", "Tool model", 0));
        label_3->setText(QApplication::translate("frmSettings", "Type:", 0));
        label_4->setText(QApplication::translate("frmSettings", "Diameter:", 0));
        cboToolType->clear();
        cboToolType->insertItems(0, QStringList()
         << QApplication::translate("frmSettings", "Flat", 0)
         << QApplication::translate("frmSettings", "Conic", 0)
        );
        lblToolAngle->setText(QApplication::translate("frmSettings", "Angle:", 0));
        lblToolLength->setText(QApplication::translate("frmSettings", "Length:", 0));
        grpConsole->setTitle(QApplication::translate("frmSettings", "Console", 0));
        chkShowProgramCommands->setText(QApplication::translate("frmSettings", "Show G-code program commands", 0));
        chkShowUICommands->setText(QApplication::translate("frmSettings", "Show UI commands", 0));
        chkAutocompletion->setText(QApplication::translate("frmSettings", "Command auto-completion", 0));
        grpPanels->setTitle(QApplication::translate("frmSettings", "Panels", 0));
        chkPanelHeightmap->setText(QApplication::translate("frmSettings", "Heightmap", 0));
        chkPanelFeed->setText(QApplication::translate("frmSettings", "Feed", 0));
        chkPanelSpindle->setText(QApplication::translate("frmSettings", "Spindle", 0));
        chkPanelJog->setText(QApplication::translate("frmSettings", "Jog", 0));
        grpColors->setTitle(QApplication::translate("frmSettings", "Colors", 0));
        label_20->setText(QApplication::translate("frmSettings", "Z-movement:", 0));
        label_21->setText(QApplication::translate("frmSettings", "Toolpath", 0));
        label_24->setText(QApplication::translate("frmSettings", "Background:", 0));
        label_25->setText(QApplication::translate("frmSettings", "Highlight:", 0));
        label_26->setText(QApplication::translate("frmSettings", "Start point:", 0));
        label_27->setText(QApplication::translate("frmSettings", "End point:", 0));
        label_22->setText(QApplication::translate("frmSettings", "Visualizer", 0));
        label_28->setText(QApplication::translate("frmSettings", "Text:", 0));
        label_19->setText(QApplication::translate("frmSettings", "Tool:", 0));
        label_16->setText(QApplication::translate("frmSettings", "Drawn:", 0));
        label_23->setText(QApplication::translate("frmSettings", "Normal:", 0));
        groupBox->setTitle(QApplication::translate("frmSettings", "Font", 0));
        label_29->setText(QApplication::translate("frmSettings", "Size:", 0));
        cboFontSize->clear();
        cboFontSize->insertItems(0, QStringList()
         << QApplication::translate("frmSettings", "8", 0)
         << QApplication::translate("frmSettings", "9", 0)
         << QApplication::translate("frmSettings", "10", 0)
         << QApplication::translate("frmSettings", "11", 0)
         << QApplication::translate("frmSettings", "12", 0)
        );
        cboFontSize->setCurrentText(QApplication::translate("frmSettings", "8", 0));
        label_30->setText(QApplication::translate("frmSettings", "pt", 0));
        label_31->setText(QApplication::translate("frmSettings", "(restart needed)", 0));
        cmdDefaults->setText(QApplication::translate("frmSettings", "Set to defaults", 0));
        cmdOK->setText(QApplication::translate("frmSettings", "OK", 0));
        cmdCancel->setText(QApplication::translate("frmSettings", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class frmSettings: public Ui_frmSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSETTINGS_H
