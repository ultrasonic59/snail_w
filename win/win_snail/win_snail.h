#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "ui_win_snail.h"
#include <QSettings>
#include <QTimer>
#include <QBasicTimer>
#include <QStringList>
#include <QList>
#include <QTime>
#include <QMenu>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QProgressDialog>
#include <exception>
#include <atomic>

#include "parser/gcodeviewparse.h"
#include "drawers/origindrawer.h"
#include "drawers/gcodedrawer.h"
#include "drawers/tooldrawer.h"
#include "drawers/heightmapborderdrawer.h"
#include "drawers/heightmapgriddrawer.h"
#include "drawers/heightmapinterpolationdrawer.h"
#include "drawers/shaderdrawable.h"
#include "drawers/selectiondrawer.h"

#include "drawers/heightmapinterpolationdrawer.h"
#include "drawers/selectiondrawer.h"
#include "tables/gcodetablemodel.h"
#include "tables/heightmaptablemodel.h"
#include "utils/interpolation.h"

#include "frmsettings.h"
#include "frmabout.h"
#include "utils/safequeue.h"

//// #define sNan  65536

// GRBL Status
#define UNKNOWN             0
#define IDLE                1
#define ALARM               2
#define RUN                 3
#define HOME                4
#define HOLD0               5
#define HOLD1               6
#define QUEUE               7
#define CHECK               8
#define DOOR                9
#define JOG                 10
#define DWELL               11
#define TOOLCHANGE          12

#define PROGRESSMINLINES    10000

#define PROGRESSSTEP        1000
namespace Ui
{
    class win_snail_windows;
}


struct CommandAttributes
{
    int length;
    int consoleIndex;
    int tableIndex;
    QString command;
};


struct CommandQueue
{
    QString command;
    int tableIndex;
    bool showInConsole;
};

struct CommandQueue2
{
    QString command;
    int tableIndex;
    int consoleIndex;
    int length;
};


typedef enum
{
    PROT_GRBL1_1 = 0, PROT_GRBL2, PROT_GRIP
} Protocol_e;


class CancelException : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Operation was cancelled by user";
    }
};

class win_snail : public QMainWindow
{
    Q_OBJECT

public:
    win_snail(QWidget *parent = nullptr);
    ~win_snail();

private:
    Ui::win_snail_windows *ui;
private slots:
    void updateHeightMapInterpolationDrawer(bool reset = false);

private:
    void loadFile(QString fileName);
    void loadFile(QList<QString> data);
    QString findConfigPath();
    QString GetErrorMsg(int err_code);
    void resizeTableHeightMapSections();
    void resizeCheckBoxes();
    void on_actFileExit_triggered();
    void on_cmdFileOpen_clicked();
    QTime updateProgramEstimatedTime(QList<LineSegment*> lines);
    void onTableCellChanged(QModelIndex i1, QModelIndex i2);
    void onTableCurrentChanged(QModelIndex idx1, QModelIndex idx2);
    void onTableInsertLine();
    void onTableDeleteLines();
    void updateLayouts();
    bool saveChanges(bool heightMapMode);
    void addRecentFile(QString fileName);
    void updateRecentFilesMenu();
    void addRecentHeightmap(QString fileName);
    void resetHeightmap();
    void on_grpHeightMap_toggled(bool arg1);
    void updateHeightMapBorderDrawer();
    QRectF borderRectFromTextboxes();
    void on_txtHeightMapBorderX_valueChanged(double arg1);
    QRectF borderRectFromExtremes();
    void updateHeightMapGrid(double arg1);
    bool updateHeightMapGrid();
    void on_chkHeightMapBorderShow_toggled(bool checked);
    void updateControlsState();
    void updateParser();
    void on_cmdHeightMapBorderAuto_clicked();
    void on_txtHeightMapBorderWidth_valueChanged(double arg1);
    void on_cmdHeightMapCreate_clicked();
    void on_txtHeightMapBorderY_valueChanged(double arg1);
    void on_txtHeightMapBorderY_valueChanged(double arg1);
    void on_txtHeightMapBorderHeight_valueChanged(double arg1);
    void on_chkHeightMapGridShow_toggled(bool checked);
    void on_txtHeightMapGridX_valueChanged(double arg1);
    void on_txtHeightMapGridY_valueChanged(double arg1);
    void on_txtHeightMapGridZBottom_valueChanged(double arg1);
    void on_txtHeightMapGridY_valueChanged(double arg1);
    void on_txtHeightMapGridZBottom_valueChanged(double arg1);
    void on_txtHeightMapGridZTop_valueChanged(double arg1);
    void on_cmdHeightMapMode_toggled(bool checked);
    void on_chkHeightMapInterpolationShow_toggled(bool checked);
    void on_cmdHeightMapLoad_clicked();
    void on_txtHeightMapInterpolationStepX_valueChanged(double arg1);
    void on_txtHeightMapInterpolationStepY_valueChanged(double arg1);
    void on_chkHeightMapUse_clicked(bool checked);
    void on_cmdHeightMapCreate_clicked();
    void on_cmdHeightMapBorderAuto_clicked();
    void on_cmdFileAbort_clicked();
    void on_cmdSpindle_clicked(bool checked);
    bool saveHeightMap(QString fileName);

   void clearTable();
    void preloadSettings();
    void loadSettings();
 ///   void saveSettings();
 ///   bool saveChanges(bool heightMapMode);
 ///   void updateControlsState();
 /// 
    GCodeTableModel* m_currentModel;

    GcodeViewParse m_viewParser;
    GcodeViewParse m_probeParser;

    OriginDrawer* m_originDrawer;

    GcodeDrawer* m_codeDrawer;
    GcodeDrawer* m_probeDrawer;
    GcodeDrawer* m_currentDrawer;

    ToolDrawer m_toolDrawer;
    HeightMapBorderDrawer m_heightMapBorderDrawer;
    HeightMapGridDrawer m_heightMapGridDrawer;
    HeightMapInterpolationDrawer m_heightMapInterpolationDrawer;
    SelectionDrawer m_selectionDrawer;
    GCodeTableModel m_programModel;
    GCodeTableModel m_probeModel;
    GCodeTableModel m_programHeightmapModel;
    HeightMapTableModel m_heightMapModel;
    bool m_programLoading;
    bool m_settingsLoading;
    Protocol_e m_Protocol;
    frmSettings* m_settings;
    frmAbout m_frmAbout;

private:
    QString m_settingsFilePath;
    QString m_programFileName;
    QString m_heightMapFileName;
    QString m_lastFolder;

    bool m_fileChanged = false;
    bool m_heightMapChanged = false;

    bool m_toolChangeActive = false;

    QTimer m_timerSpindleUpdate;
    QTimer m_timerStateQuery;
    QBasicTimer m_timerToolAnimation;

    QTimer m_timerRead;
    QTimer m_timerSend;
    QStringList m_status;
    QStringList m_statusCaptions;
    QStringList m_statusBackColors;
    QStringList m_statusForeColors;

    QStringList m_coord;
    QMenu* m_tableMenu;
    QList<CommandAttributes> m_CommandAttributesList;
    QList<CommandQueue> m_CommandQueueList;
    QTime m_startTime;
    SafeQueue<CommandQueue2> mCommandsWait;
    SafeQueue<CommandQueue2> mCommandsSent;

    QMessageBox* m_senderErrorBox;
    // Stored origin
    double m_storedX = 0;
    double m_storedY = 0;
    double m_storedZ = 0;
    QString m_storedParserStatus;

    // Console window
    int m_storedConsoleMinimumHeight;
    int m_storedConsoleHeight;
    int m_consolePureHeight;

    // Flags
    bool m_settingZeroXY = false;
    bool m_settingZeroX = false;
    bool m_settingZeroZ = false;
    bool m_homing = false;
    bool m_updateSpindleSpeed = false;
    bool m_updateParserStatus = false;
    bool m_updateFeed = false;

    bool m_reseting = false;
    bool m_resetCompleted = true;
    bool m_aborting = false;
    bool m_statusReceived = false;

    bool m_processingFile = false;
    bool m_transferCompleted = false;
    bool m_fileEndSent = false;

    bool m_heightMapMode;
    bool m_cellChanged;

    // Indices
    int m_fileCommandIndex;
    int m_fileProcessedCommandIndex;
    int m_probeIndex;

    // Current values
    int m_lastDrawnLineIndex;
    int m_lastGrblStatus;
    double m_originalFeed;

    // Keyboard
    bool m_keyPressed = false;
    bool m_jogBlock = false;
    bool m_absoluteCoordinates;
    bool m_storedKeyboardControl;

    // Spindle
    bool m_spindleCW = true;
    bool m_spindleCommandSpeed = false;
    // Jog
    QVector3D m_jogVector;
    QStringList m_recentFiles;
    QStringList m_recentHeightmaps;

    // Size of internal GRBL buffer
    static const int GRBL_BUFFERLENGTH = 127;

   QSerialPort m_serialHandWheel;

};
