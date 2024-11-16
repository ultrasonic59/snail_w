#include "mainwindow.h"

MainWindow::MainWindow()
{
	m_menu = menuBar ();
	m_status = statusBar();


	m_script=new QTextEdit(this);
	m_output=new QTextEdit(this);
	m_output->setReadOnly(true);
	
	QSplitter *splitter = new QSplitter(Qt::Vertical,this);
	splitter->addWidget(m_script);
	splitter->addWidget(m_output);

	setCentralWidget(splitter);

	//	create menu.
	m_fileMenu = m_menu->addMenu(tr("&File"));
	
	m_go_act= m_fileMenu->addAction(tr("G&o") );
	m_go_act->setShortcut(tr("Ctrl+G"));
	m_go_act->setStatusTip(tr("Script execute(Go)"));
	
	m_exit_act = m_fileMenu->addAction(tr("E&xit" ));
	m_exit_act->setShortcut(tr("Ctrl+Q"));
	m_exit_act->setStatusTip(tr("Exit the application"));

	//	action connect.
	connect(m_exit_act, SIGNAL(triggered()), 
	         qApp, SLOT(closeAllWindows()));

	connect(m_go_act, SIGNAL(triggered()), 
	         this, SLOT(excuteScript()));

    setWindowTitle(tr("ScriptWindow"));
	
	resize(400, 300);
}

void MainWindow::excuteScript()
{
	QString sscript=m_script->toPlainText();
	if(!sscript.isEmpty()){
		QScriptEngine engine;
		QScriptValue scriptTextEdit = engine.newQObject(m_output);
		engine.globalObject().setProperty("debugPrint", scriptTextEdit);
		m_output->append( engine.evaluate(sscript).toString() );
	}
}

