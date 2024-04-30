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
#if 0
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
#endif

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

void win_snail::updateControlsState()
{
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

}
void win_snail::on_actFileNew_triggered()
{
    qDebug() << "changes:" << m_fileChanged << m_heightMapChanged;

    if (!saveChanges(m_heightMapMode))
        return;

    if (!m_heightMapMode)
    {
        // Reset tables
        clearTable();
        m_probeModel.clear();
        m_programHeightmapModel.clear();
        m_currentModel = &m_programModel;

        // Reset parsers
        m_viewParser.reset();
        m_probeParser.reset();

        // Reset code drawer
        m_codeDrawer->update();
        m_currentDrawer = m_codeDrawer;
        ui->glwVisualizer->fitDrawable();
        updateProgramEstimatedTime(QList<LineSegment*>());

        m_programFileName = "";
        ui->chkHeightMapUse->setChecked(false);
        ui->grpHeightMap->setProperty("overrided", false);
        style()->unpolish(ui->grpHeightMap);
        ui->grpHeightMap->ensurePolished();

        // Reset tableview
        QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
        ui->tblProgram->setModel(NULL);

        // Set table model
        ui->tblProgram->setModel(&m_programModel);
        ui->tblProgram->horizontalHeader()->restoreState(headerState);

        // Update tableview
        connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex, QModelIndex)));
        ui->tblProgram->selectRow(0);

        // Clear selection marker
        m_selectionDrawer.setEndPosition(QVector3D(sNan, sNan, sNan));
        m_selectionDrawer.update();

        resetHeightmap();
    }
    else
    {
        m_heightMapModel.clear();
        on_cmdFileReset_clicked();
        ui->txtHeightMap->setText(tr("Untitled"));
        m_heightMapFileName.clear();

        updateHeightMapBorderDrawer();
        updateHeightMapGrid();

        m_heightMapChanged = false;
    }

    updateControlsState();
}
void win_snail::on_cmdFileReset_clicked()
{
    m_fileCommandIndex = 0;
    m_fileProcessedCommandIndex = 0;
    m_lastDrawnLineIndex = 0;
    m_probeIndex = -1;
    if (!m_heightMapMode)
    {
     ////   QTime time;
        QElapsedTimer time;
        time.start();

        QList<LineSegment*> list = m_viewParser.getLineSegmentList();

        QList<int> indexes;
        for (int i = 0; i < list.count(); i++)
        {
            list[i]->setDrawn(false);
            indexes.append(i);
        }

        m_codeDrawer->update(indexes);

        qDebug() << "Drawn false:" << time.elapsed();

        time.start();

        ui->tblProgram->setUpdatesEnabled(false);

        for (int i = 0; i < m_currentModel->data().count() - 1; i++)
        {
            m_currentModel->data()[i].state = GCodeItem::InQueue;
            m_currentModel->data()[i].response = QString();
        }

        ui->tblProgram->setUpdatesEnabled(true);

        qDebug() << "Table updated:" << time.elapsed();

        ui->tblProgram->scrollTo(m_currentModel->index(0, 0));
        ui->tblProgram->clearSelection();
        ui->tblProgram->selectRow(0);

        ui->glwVisualizer->setSpendTime(QTime(0, 0, 0));
    }
    else
    {
        ui->txtHeightMapGridX->setEnabled(true);
        ui->txtHeightMapGridY->setEnabled(true);
        ui->txtHeightMapGridZBottom->setEnabled(true);
        ui->txtHeightMapGridZTop->setEnabled(true);

        delete m_heightMapInterpolationDrawer.data();
        m_heightMapInterpolationDrawer.setData(NULL);

        m_heightMapModel.clear();
        updateHeightMapGrid();
    }
}
void win_snail::on_actFileSave_triggered()
{
    if (!m_heightMapMode)
    {
        // G-code saving
        if (m_programFileName.isEmpty())
        {
            on_actFileSaveAs_triggered();
        }
        else
        {
            saveProgramToFile(m_programFileName, &m_programModel);
            m_fileChanged = false;
        }
    }
    else
    {
        // Height map saving
        if (m_heightMapFileName.isEmpty())
        {
            on_actFileSaveAs_triggered();
        }
        else
        {
            saveHeightMap(m_heightMapFileName);
        }
    }
}
void win_snail::on_actFileSaveAs_triggered()
{
    if (!m_heightMapMode)
    {
        QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("G-Code files (*.nc *.ncc *.ngc *.tap *.txt *.gcode)")));

        if (!fileName.isEmpty()) if (saveProgramToFile(fileName, &m_programModel))
        {
            m_programFileName = fileName;
            m_fileChanged = false;

            addRecentFile(fileName);
            updateRecentFilesMenu();

            updateControlsState();
        }
    }
    else
    {
        QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("Heightmap files (*.map)")));

        if (!fileName.isEmpty()) if (saveHeightMap(fileName))
        {
            ui->txtHeightMap->setText(fileName.mid(fileName.lastIndexOf("/") + 1));
            m_heightMapFileName = fileName;
            m_heightMapChanged = false;

            addRecentHeightmap(fileName);
            updateRecentFilesMenu();

            updateControlsState();
        }
    }
}
bool win_snail::saveProgramToFile(QString fileName, GCodeTableModel* model)
{
    QFile file(fileName);
    QDir dir;

    qDebug() << "Saving program";

    if (file.exists())
        dir.remove(file.fileName());

    if (!file.open(QIODevice::WriteOnly))
        return false;

    QTextStream textStream(&file);

    for (int i = 0; i < model->rowCount() - 1; i++)
    {
        textStream << model->data(model->index(i, 1)).toString() << "\r\n";
    }

    file.close();

    return true;
}
void win_snail::updateParser()
{
  ////  QTime time;
    QElapsedTimer time;
    qDebug() << "Updating parser:" << m_currentModel << m_currentDrawer;
    time.start();

    GcodeViewParse* parser = m_currentDrawer->viewParser();

    GcodeParser gp;
    gp.setTraverseSpeed(m_settings->rapidSpeed());
    if (m_codeDrawer->getIgnoreZ()) gp.reset(QVector3D(qQNaN(), qQNaN(), 0));

    ui->tblProgram->setUpdatesEnabled(false);

    QString stripped;
    QList<QString> args;

    QProgressDialog progress(tr("Updating..."), tr("Abort"), 0, m_currentModel->rowCount() - 2, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setFixedSize(progress.sizeHint());

    if (m_currentModel->rowCount() > PROGRESSMINLINES)
    {
        progress.show();
        progress.setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");
    }

    for (int i = 0; i < m_currentModel->rowCount() - 1; i++)
    {
        // Get stored args
        args = m_currentModel->data().at(i).args;

        // Store args if none
        if (args.isEmpty())
        {
            stripped = GcodePreprocessorUtils::removeComment(m_currentModel->data().at(i).command);
            args = GcodePreprocessorUtils::splitCommand(stripped);
            m_currentModel->data()[i].args = args;
        }

        // Add command to parser
        gp.addCommand(args);

        // Update table model
        m_currentModel->data()[i].state = GCodeItem::InQueue;
        m_currentModel->data()[i].response = QString();
        m_currentModel->data()[i].line = gp.getCommandNumber();

        if (progress.isVisible() && (i % PROGRESSSTEP == 0))
        {
            progress.setValue(i);
            qApp->processEvents();

            if (progress.wasCanceled())
                break;
        }
    }

    progress.close();

    ui->tblProgram->setUpdatesEnabled(true);

    parser->reset();

    updateProgramEstimatedTime(parser->getLinesFromParser(&gp, m_settings->arcPrecision(), m_settings->arcDegreeMode()));
    m_currentDrawer->update();
    ui->glwVisualizer->updateExtremes(m_currentDrawer);
    updateControlsState();

    if (m_currentModel == &m_programModel)
    {
        m_fileChanged = true;
    }

    qDebug() << "Update parser time: " << time.elapsed();
}
