#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtScript>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();


private slots:
	void excuteScript();

private:
	//	gui parts.
	QMenuBar *m_menu;
	QMenu *m_fileMenu;
	QAction *m_go_act;
	QAction *m_exit_act;

	QStatusBar *m_status;

	QTextEdit *m_script;
	QTextEdit *m_output;
};


#endif