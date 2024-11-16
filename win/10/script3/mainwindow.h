#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtScript>
#include <QScriptEngineDebugger>
#include "debugwidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();


private slots:
	void excuteScript();
	void debugScript();

private:

private:
	QMenuBar *m_menu;
	QMenu *m_fileMenu;
	QAction *m_go_act;
	QAction *m_go_debug;
	QAction *m_exit_act;

	QStatusBar *m_status;


	QTextEdit *m_script;
	DebugWidget *m_output;

	//	script engine.
	QScriptEngine *m_engine;
};


#endif
