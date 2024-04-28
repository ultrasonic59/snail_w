#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextBlock>
#include <QTextCursor>
#include <QMessageBox>
#include <QComboBox>
#include <QScrollBar>
#include <QShortcut>
#include <QAction>
#include <QLayout>
#include <QMimeData>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QStandardPaths>

#include "utils/profiles.h"
#include "win_snail.h"
#include <QThread>
#include <QInputDialog>

win_snail::win_snail(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::win_snail_windows)
{
 ////   ui.setupUi(this);
    m_status << "Unknown"
        << "Idle"
        << "Alarm"
        << "Run"
        << "Home"
        << "Hold:0"
        << "Hold:1"
        << "Queue"
        << "Check"
        << "Door"                     // TODO: Update "Door" state
        << "Jog"
        << "Dwell"
        << "Tool"
        << "Busy";
    m_statusCaptions << tr("Unknown")
        << tr("Idle")
        << tr("Alarm")
        << tr("Run")
        << tr("Home")
        << tr("Hold")
        << tr("Hold")
        << tr("Queue")
        << tr("Check")
        << tr("Door")
        << tr("Jog")
        << tr("Dwell")
        << tr("Tool Change");
    m_statusBackColors << "red"
        << "palette(button)"
        << "red"
        << "lime"
        << "lime"
        << "yellow"
        << "yellow"
        << "yellow"
        << "palette(button)"
        << "red"
        << "lime"
        << "yellow"
        << "yellow";

    m_statusForeColors << "white"
        << "palette(text)"
        << "white"
        << "black"
        << "black"
        << "black"
        << "black"
        << "black"
        << "palette(text)"
        << "white"
        << "black"
        << "black"
        << "black";

    m_coord << "G54"
        << "G55"
        << "G56"
        << "G57"
        << "G58"
        << "G59";

  m_settingsFilePath = findConfigPath();
    qDebug() << "settings file path: " << m_settingsFilePath;
    // Loading settings
 ////   preloadSettings();

 ////   m_settings = new frmSettings(this);
 ////   ui->setupUi(this);

}

win_snail::~win_snail()
{}
///===============================================
void win_snail::clearTable()
{
 ///   m_programModel.clear();
 ///   m_programModel.insertRow(0);
}

void win_snail::loadFile(QList<QString> data)
{
 ///   QTime time;
 ////   time.start();

    // Reset tables
    clearTable();
#if 0
    m_probeModel.clear();
    m_programHeightmapModel.clear();

    m_currentModel = &m_programModel;

    // Reset parsers
    m_viewParser.reset();
    m_probeParser.reset();

    // Reset code drawer
    m_currentDrawer = m_codeDrawer;
    m_codeDrawer->update();
    ui->glwVisualizer->fitDrawable(m_codeDrawer);
    updateProgramEstimatedTime(QList<LineSegment*>());

    // Update interface
    ui->chkHeightMapUse->setChecked(false);
    ui->grpHeightMap->setProperty("overrided", false);
    style()->unpolish(ui->grpHeightMap);
    ui->grpHeightMap->ensurePolished();

    // Reset tableview
    QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
    ui->tblProgram->setModel(NULL);

    // Prepare parser
    GcodeParser gp;
    gp.setTraverseSpeed(m_settings->rapidSpeed());
    if (m_codeDrawer->getIgnoreZ())
    {
        gp.reset(QVector3D(qQNaN(), qQNaN(), 0));
    }

    qDebug() << "Prepared to load:" << time.elapsed();
    time.start();

    // Block parser updates on table changes
    m_programLoading = true;

    QString command;
    QString stripped;
    QString trimmed;
    QList<QString> args;
    GCodeItem item;

    // Prepare model
    m_programModel.data().clear();
    m_programModel.data().reserve(data.count());

    QProgressDialog progress(tr("Opening file..."), tr("Abort"), 0, data.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setFixedSize(progress.sizeHint());
    if (data.count() > PROGRESSMINLINES)
    {
        progress.show();
        progress.setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");
    }

    while (!data.isEmpty())
    {
        command = data.takeFirst();

        // Trim command
        trimmed = command.trimmed();

        if (!trimmed.isEmpty())
        {
            // Split command
            stripped = GcodePreprocessorUtils::removeComment(command);
            args = GcodePreprocessorUtils::splitCommand(stripped);

            gp.addCommand(args);

            item.command = trimmed;
            item.state = GCodeItem::InQueue;
            item.line = gp.getCommandNumber();
            item.args = args;

            m_programModel.data().append(item);
        }

        if (progress.isVisible() && (data.count() % PROGRESSSTEP == 0))
        {
            progress.setValue(progress.maximum() - data.count());
            qApp->processEvents();

            if (progress.wasCanceled())
            {
                break;
            }
        }
    }
    progress.close();

    m_programModel.insertRow(m_programModel.rowCount());

    qDebug() << "Model filled:" << time.elapsed();
    time.start();

    updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_settings->arcPrecision(), m_settings->arcDegreeMode()));
    qDebug() << "View parser filled:" << time.elapsed();

    m_programLoading = false;

    // Set table model
    ui->tblProgram->setModel(&m_programModel);
    ui->tblProgram->horizontalHeader()->restoreState(headerState);

    // Update tableview
    connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex, QModelIndex)));
    ui->tblProgram->selectRow(0);

    //  Update code drawer
    m_codeDrawer->update();
    ui->glwVisualizer->fitDrawable(m_codeDrawer);

    resetHeightmap();
    updateControlsState();
#endif
}

QString win_snail::findConfigPath() {
    QString profileNameFromEnvironment;//// = getenv("CANDLE_PROFILE");
    if (profileNameFromEnvironment.length() > 0) {
        return configPathForProfile(profileNameFromEnvironment);
    }

    const auto profiles = getProfileNames();
    if (profiles.length() == 0) {
        // first run, no profiles at all yet
        return configPathForProfile(default_profile_name);
    }
    else if (profiles.length() == 1) {
        // only one profile exists, no point asking which one
        return configPathForProfile(profiles[0]);
    }
    else {
        bool ok;
        const auto pickedItem = QInputDialog::getItem(this, "Choose Profile", "Choose a profile:", profiles, 0, false, &ok);
        if (ok) {
            return configPathForProfile(pickedItem);
        }
        else {
            // user cancelled
            exit(0);
        }
    }
}
void win_snail::preloadSettings()
{
    QSettings set(m_settingsFilePath, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    qApp->setStyleSheet(QString(qApp->styleSheet()).replace(QRegExp("font-size:\\s*\\d+"), "font-size: " + set.value("fontSize", "8").toString()));

    // Update v-sync in glformat
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setSwapInterval(set.value("vsync", false).toBool() ? 1 : 0);
    QGLFormat::setDefaultFormat(fmt);
}
void win_snail::loadSettings()
{
    QSettings set(m_settingsFilePath, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    m_settingsLoading = true;
////???
#if 0
    m_settings->setFontSize(set.value("fontSize", 9).toInt());
    m_settings->setLayoutCompact(set.value("layoutCompact", false).toBool());
    m_settings->setIgnoreErrors(set.value("ignoreErrors", false).toBool());
    m_settings->setAutoLine(set.value("autoLine", true).toBool());
    m_settings->setUseM6(set.value("useM6", false).toBool());
    m_settings->setUseRotaryAxis(set.value("useRotary", false).toBool());
    m_settings->setResetAfterConnect(set.value("resetConnect", true).toBool());
    m_settings->setToolDiameter(set.value("toolDiameter", 3).toDouble());
    m_settings->setToolLength(set.value("toolLength", 15).toDouble());
    m_settings->setAntialiasing(set.value("antialiasing", true).toBool());
    m_settings->setMsaa(set.value("msaa", true).toBool());
    m_settings->setVsync(set.value("vsync", false).toBool());
    m_settings->setZBuffer(set.value("zBuffer", false).toBool());
    m_settings->setSimplify(set.value("simplify", false).toBool());
    m_settings->setSimplifyPrecision(set.value("simplifyPrecision", 0).toDouble());
    m_settings->setGrayscaleSegments(set.value("grayscaleSegments", false).toBool());
    m_settings->setGrayscaleSCode(set.value("grayscaleSCode", true).toBool());
    m_settings->setDrawModeVectors(set.value("drawModeVectors", true).toBool());
    m_settings->setMoveOnRestore(set.value("moveOnRestore", false).toBool());
    m_settings->setRestoreMode(set.value("restoreMode", 0).toInt());
    m_settings->setLineWidth(set.value("lineWidth", 1).toDouble());
    m_settings->setArcLength(set.value("arcLength", 0).toDouble());
    m_settings->setArcDegree(set.value("arcDegree", 0).toDouble());
    m_settings->setArcDegreeMode(set.value("arcDegreeMode", true).toBool());
    m_settings->setShowProgramCommands(set.value("showProgramCommands", 0).toBool());
    m_settings->setShowUICommands(set.value("showUICommands", 0).toBool());
    m_settings->setSpindleSpeedMin(set.value("spindleSpeedMin", 0).toInt());
    m_settings->setSpindleSpeedMax(set.value("spindleSpeedMax", 100).toInt());
    m_settings->setLaserPowerMin(set.value("laserPowerMin", 0).toInt());
    m_settings->setLaserPowerMax(set.value("laserPowerMax", 100).toInt());
    m_settings->setRapidSpeed(set.value("rapidSpeed", 0).toInt());
    m_settings->setHeightmapProbingFeed(set.value("heightmapProbingFeed", 0).toInt());
    m_settings->setAcceleration(set.value("acceleration", 10).toInt());
    m_settings->setToolAngle(set.value("toolAngle", 0).toDouble());
    m_settings->setToolType(set.value("toolType", 0).toInt());
    m_settings->setFps(set.value("fps", 60).toInt());
    m_settings->setQueryStateTime(set.value("queryStateTime", 100).toInt());

    m_settings->setPanelUserCommands(set.value("panelUserCommandsVisible", true).toBool());
    m_settings->setPanelHeightmap(set.value("panelHeightmapVisible", true).toBool());
    m_settings->setPanelSpindle(set.value("panelSpindleVisible", true).toBool());
    m_settings->setPanelOverriding(set.value("panelOverridingVisible", true).toBool());
    m_settings->setPanelJog(set.value("panelJogVisible", true).toBool());

    ui->grpConsole->setMinimumHeight(set.value("consoleMinHeight", 100).toInt());

    ui->chkAutoScroll->setChecked(set.value("autoScroll", true).toBool());

    ui->slbSpindle->setRatio(100);
    ui->slbSpindle->setMinimum(m_settings->spindleSpeedMin());
    ui->slbSpindle->setMaximum(m_settings->spindleSpeedMax());
    ui->slbSpindle->setValue(set.value("spindleSpeed", 100).toInt());

    ui->slbFeedOverride->setChecked(set.value("feedOverride", false).toBool());
    ui->slbFeedOverride->setValue(set.value("feedOverrideValue", 100).toInt());

    ui->slbRapidOverride->setChecked(set.value("rapidOverride", false).toBool());
    ui->slbRapidOverride->setValue(set.value("rapidOverrideValue", 100).toInt());

    ui->slbSpindleOverride->setChecked(set.value("spindleOverride", false).toBool());
    ui->slbSpindleOverride->setValue(set.value("spindleOverrideValue", 100).toInt());

    m_settings->setUnits(set.value("units", 0).toInt());
    m_storedX = set.value("storedX", 0).toDouble();
    m_storedY = set.value("storedY", 0).toDouble();
    m_storedZ = set.value("storedZ", 0).toDouble();

    m_settings->setIPAddress(set.value("ipaddress", "192.168.1.20").toString());
    m_settings->setPort(set.value("ip_port", 30501).toInt());

    ui->cmdRestoreOrigin->setToolTip(QString(tr("Restore origin:\n%1, %2, %3")).arg(m_storedX).arg(m_storedY).arg(m_storedZ));

    m_recentFiles = set.value("recentFiles", QStringList()).toStringList();
    m_recentHeightmaps = set.value("recentHeightmaps", QStringList()).toStringList();
    m_lastFolder = set.value("lastFolder", QDir::homePath()).toString();

    this->restoreGeometry(set.value("formGeometry", QByteArray()).toByteArray());
    m_settings->resize(set.value("formSettingsSize", m_settings->size()).toSize());
    QByteArray splitterState = set.value("splitter", QByteArray()).toByteArray();

    if (splitterState.length() == 0)
    {
        ui->splitter->setStretchFactor(0, 1);
        ui->splitter->setStretchFactor(1, 1);
    }
    else
        ui->splitter->restoreState(splitterState);

    ui->chkAutoScroll->setVisible(ui->splitter->sizes()[1]);
    resizeCheckBoxes();

    ui->cboCommand->setMinimumHeight(ui->cboCommand->height());
    ui->cmdClearConsole->setFixedHeight(ui->cboCommand->height());
    ui->cmdCommandSend->setFixedHeight(ui->cboCommand->height());

    m_storedKeyboardControl = set.value("keyboardControl", false).toBool();

    m_settings->setAutoCompletion(set.value("autoCompletion", true).toBool());
    m_settings->setTouchCommand(set.value("touchCommand", "G21G91G38.2Z-30F80; G0Z1; G38.2Z-2F10").toString());
    m_settings->setSafePositionCommand(set.value("safePositionCommand", "G21G90; G53G0Z10").toString());

    foreach(StyledToolButton * button, this->findChildren<StyledToolButton*>(QRegExp("cmdUser\\d")))
    {
        int i = button->objectName().right(1).toInt();
        m_settings->setUserCommands(i, set.value(QString("userCommands%1").arg(i)).toString());
    }

    ui->cboJogStep->setItems(set.value("jogSteps").toStringList());
    ui->cboJogStep->setCurrentIndex(ui->cboJogStep->findText(set.value("jogStep").toString()));
    ui->cboJogFeed->setItems(set.value("jogFeeds").toStringList());
    ui->cboJogFeed->setCurrentIndex(ui->cboJogFeed->findText(set.value("jogFeed").toString()));

    ui->txtHeightMapBorderX->setValue(set.value("heightmapBorderX", 0).toDouble());
    ui->txtHeightMapBorderY->setValue(set.value("heightmapBorderY", 0).toDouble());
    ui->txtHeightMapBorderWidth->setValue(set.value("heightmapBorderWidth", 1).toDouble());
    ui->txtHeightMapBorderHeight->setValue(set.value("heightmapBorderHeight", 1).toDouble());
    ui->chkHeightMapBorderShow->setChecked(set.value("heightmapBorderShow", false).toBool());

    ui->txtHeightMapGridX->setValue(set.value("heightmapGridX", 1).toDouble());
    ui->txtHeightMapGridY->setValue(set.value("heightmapGridY", 1).toDouble());
    ui->txtHeightMapGridZTop->setValue(set.value("heightmapGridZTop", 1).toDouble());
    ui->txtHeightMapGridZBottom->setValue(set.value("heightmapGridZBottom", -1).toDouble());
    ui->chkHeightMapGridShow->setChecked(set.value("heightmapGridShow", false).toBool());

    ui->txtHeightMapInterpolationStepX->setValue(set.value("heightmapInterpolationStepX", 1).toDouble());
    ui->txtHeightMapInterpolationStepY->setValue(set.value("heightmapInterpolationStepY", 1).toDouble());
    ui->cboHeightMapInterpolationType->setCurrentIndex(set.value("heightmapInterpolationType", 0).toInt());
    ui->chkHeightMapInterpolationShow->setChecked(set.value("heightmapInterpolationShow", false).toBool());

    m_settings->setToolpathNormal(QColor(set.value("ToolpathNormal", QColor(0, 0, 0)).toString()));
    m_settings->setToolpathDrawn(QColor(set.value("ToolpathDrawn", QColor(217, 217, 217)).toString()));
    m_settings->setToolpathHighlight(QColor(set.value("ToolpathHighlight", QColor(145, 130, 230)).toString()));
    m_settings->setToolpathZMovement(QColor(set.value("ToolpathZMovement", QColor(255, 0, 0)).toString()));
    m_settings->setToolpathStart(QColor(set.value("ToolpathStart", QColor(255, 0, 0)).toString()));
    m_settings->setToolpathEnd(QColor(set.value("ToolpathEnd", QColor(0, 255, 0)).toString()));
    m_settings->setVisualizerBackground(QColor(set.value("VisualizerBackground", QColor(255, 255, 255)).toString()));
    m_settings->setVisualizerText(QColor(set.value("VisualizerText", QColor(0, 0, 0)).toString()));
    m_settings->setTool(QColor(set.value("Tool", QColor(255, 153, 0)).toString()));

    ui->comboInterface->setCurrentText(set.value("interface", "ETHERNET").toString());

    updateRecentFilesMenu();

    ui->tblProgram->horizontalHeader()->restoreState(set.value("header", QByteArray()).toByteArray());

    // Update right panel width
    applySettings();
    show();
    ui->scrollArea->updateMinimumWidth();

    // Restore panels state
    ui->grpUserCommands->setChecked(set.value("userCommandsPanel", true).toBool());
    ui->grpHeightMap->setChecked(set.value("heightmapPanel", true).toBool());
    ui->grpSpindle->setChecked(set.value("spindlePanel", true).toBool());
    ui->grpOverriding->setChecked(set.value("feedPanel", true).toBool());

    // Restore last commands list
    ui->cboCommand->addItems(set.value("recentCommands", QStringList()).toStringList());
    ui->cboCommand->setCurrentIndex(-1);

    m_settingsLoading = false;
#endif
}
void win_snail::updateControlsState()
{
///???
    /*
    bool portOpened = SerialIf_IsOpen();

    // Disable interface options (shouldn't be changed while open)
    ui->comboProtocol->setEnabled(!portOpened);
    ui->comboInterface->setEnabled(!portOpened);
    ui->comboBaud->setEnabled(!portOpened && ui->comboInterface->currentText() != "ETHERNET");
    ui->btnReload->setEnabled(!portOpened);

    // Enable rest of gui
    ui->grpState->setEnabled(portOpened);
    ui->grpControl->setEnabled(portOpened);
    ui->widgetUserCommands->setEnabled(portOpened && !m_processingFile);
    ui->widgetSpindle->setEnabled(portOpened);
    ui->widgetJog->setEnabled(portOpened && !m_processingFile);
    ui->cboCommand->setEnabled(portOpened && (!ui->chkKeyboardControl->isChecked()));
    ui->cmdCommandSend->setEnabled(portOpened);

    ui->tabWidget->setTabEnabled(1, portOpened);
    ui->tabWidget->setTabEnabled(2, portOpened);
    ui->tabWidget->setTabEnabled(3, portOpened);
    ui->tabWidget->setTabEnabled(4, portOpened);

    ui->chkTestMode->setEnabled(portOpened && !m_processingFile);
    ui->cmdHome->setEnabled(!m_processingFile);
    ui->cmdTouch->setEnabled(!m_processingFile);
    ui->cmdZeroX->setEnabled(!m_processingFile);
    ui->cmdZeroY->setEnabled(!m_processingFile);
    ui->cmdZeroZ->setEnabled(!m_processingFile);
    ui->cmdRestoreOrigin->setEnabled(!m_processingFile);
    ui->cmdSafePosition->setEnabled(!m_processingFile);
    ui->cmdUnlock->setEnabled(!m_processingFile);
    ui->cmdSpindle->setEnabled(!m_processingFile);

    ui->actFileNew->setEnabled(!m_processingFile);
    ui->actFileOpen->setEnabled(!m_processingFile);
    ui->cmdFileOpen->setEnabled(!m_processingFile);
    ui->cmdFileReset->setEnabled(!m_processingFile && m_programModel.rowCount() > 1);
    ui->cmdFileSend->setEnabled(portOpened && !m_processingFile && m_programModel.rowCount() > 1);
    ui->cmdFilePause->setEnabled(m_processingFile && !ui->chkTestMode->isChecked());
    ui->cmdFileAbort->setEnabled(m_processingFile);
    ui->actFileOpen->setEnabled(!m_processingFile);
    ui->mnuRecent->setEnabled(!m_processingFile && ((m_recentFiles.count() > 0 && !m_heightMapMode)
        || (m_recentHeightmaps.count() > 0 && m_heightMapMode)));
    ui->actFileSave->setEnabled(m_programModel.rowCount() > 1);
    ui->actFileSaveAs->setEnabled(m_programModel.rowCount() > 1);

    ui->tblProgram->setEditTriggers(m_processingFile ? QAbstractItemView::NoEditTriggers :
        QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked
        | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);

    if (!portOpened)
    {
        ui->txtStatus->setText(tr("Not connected"));
        ui->txtStatus->setStyleSheet(QString("background-color: palette(button); color: palette(text);"));
    }

    this->setWindowTitle(m_programFileName.isEmpty() ? qApp->applicationDisplayName() : m_programFileName.mid(m_programFileName.lastIndexOf("/") + 1) + " - " + qApp->applicationDisplayName());

    if (!m_processingFile)
    {
        ui->chkKeyboardControl->setChecked(m_storedKeyboardControl);
    }

#ifdef WINDOWS
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7)
    {
        if (!m_processingFile && m_taskBarProgress) m_taskBarProgress->hide();
    }
#endif

    style()->unpolish(ui->cmdFileOpen);
    style()->unpolish(ui->cmdFileReset);
    style()->unpolish(ui->cmdFileSend);
    style()->unpolish(ui->cmdFilePause);
    style()->unpolish(ui->cmdFileAbort);
    ui->cmdFileOpen->ensurePolished();
    ui->cmdFileReset->ensurePolished();
    ui->cmdFileSend->ensurePolished();
    ui->cmdFilePause->ensurePolished();
    ui->cmdFileAbort->ensurePolished();

    // Heightmap
    m_heightMapBorderDrawer.setVisible(ui->chkHeightMapBorderShow->isChecked() && m_heightMapMode);
    m_heightMapGridDrawer.setVisible(ui->chkHeightMapGridShow->isChecked() && m_heightMapMode);
    m_heightMapInterpolationDrawer.setVisible(ui->chkHeightMapInterpolationShow->isChecked() && m_heightMapMode);

    ui->grpProgram->setTitle(m_heightMapMode ? tr("Heightmap") : tr("G-Code Program"));
    ui->grpProgram->setProperty("overrided", m_heightMapMode);
    style()->unpolish(ui->grpProgram);
    ui->grpProgram->ensurePolished();

    ui->grpHeightMapSettings->setVisible(m_heightMapMode);
    ui->grpHeightMapSettings->setEnabled(!m_processingFile && !ui->chkKeyboardControl->isChecked());

    ui->cboJogStep->setEditable(!ui->chkKeyboardControl->isChecked());
    ui->cboJogFeed->setEditable(!ui->chkKeyboardControl->isChecked());
    ui->cboJogStep->setStyleSheet(QString("font-size: %1").arg(m_settings->fontSize()));
    ui->cboJogFeed->setStyleSheet(ui->cboJogStep->styleSheet());

    ui->chkTestMode->setVisible(!m_heightMapMode);
    ui->chkAutoScroll->setVisible(ui->splitter->sizes()[1] && !m_heightMapMode);

    ui->tblHeightMap->setVisible(m_heightMapMode);
    ui->tblProgram->setVisible(!m_heightMapMode);

    ui->widgetHeightMap->setEnabled(!m_processingFile && m_programModel.rowCount() > 1);
    //ui->widgetHeightMap->setEnabled(false);
    ui->cmdHeightMapMode->setEnabled(!ui->txtHeightMap->text().isEmpty());

    ui->cmdFileSend->setText(m_heightMapMode ? tr("Probe") : tr("Send"));

    ui->chkHeightMapUse->setEnabled(!m_heightMapMode && !ui->txtHeightMap->text().isEmpty());

    ui->actFileSaveTransformedAs->setVisible(ui->chkHeightMapUse->isChecked());

    ui->cmdFileSend->menu()->actions().first()->setEnabled(!ui->cmdHeightMapMode->isChecked());

    m_selectionDrawer.setVisible(!ui->cmdHeightMapMode->isChecked());
    */
}
