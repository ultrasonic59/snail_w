#include "mainwindow.h"
#include "tempwin.h"

Q_SCRIPT_DECLARE_QMETAOBJECT(SDialog, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(SPushButton, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(STextEdit, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(SLabel, QWidget*)


MainWindow::MainWindow()
{
	m_menu = menuBar ();
	m_status = statusBar();

	m_script=new QTextEdit(this);
	m_output=new DebugWidget(this);
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
	
	m_go_debug= m_fileMenu->addAction(tr("D&ebug") );
	m_go_debug->setShortcut(tr("Ctrl+D"));
	m_go_debug->setStatusTip(tr("Script debug execute(Debug)"));
	
	m_exit_act = m_fileMenu->addAction(tr("E&xit" ));
	m_exit_act->setShortcut(tr("Ctrl+Q"));
	m_exit_act->setStatusTip(tr("Exit the application"));

	connect(m_exit_act, SIGNAL(triggered()), 
	         qApp, SLOT(closeAllWindows()));

	connect(m_go_act, SIGNAL(triggered()), 
	         this, SLOT(excuteScript()));

	connect(m_go_debug, SIGNAL(triggered()), 
	         this, SLOT(debugScript()));

    setWindowTitle(tr("ScriptWindow"));


	//	create script engine.
	m_engine=new QScriptEngine();

	QScriptValue objectwin= m_engine->scriptValueFromQMetaObject<SDialog>();
	m_engine->globalObject().setProperty("Dialog", objectwin);

	QScriptValue objectbutton= m_engine->scriptValueFromQMetaObject<SPushButton>();
	m_engine->globalObject().setProperty("Button", objectbutton);

	QScriptValue objecttextedit= m_engine->scriptValueFromQMetaObject<STextEdit>();
	m_engine->globalObject().setProperty("TextEdit", objecttextedit);

	QScriptValue objectlabel= m_engine->scriptValueFromQMetaObject<SLabel>();
	m_engine->globalObject().setProperty("Label", objectlabel);

	resize(400, 300);
}
void MainWindow::excuteScript()
{
	QString sscript=m_script->toPlainText();
	if(!sscript.isEmpty()){

		QScriptValue printfunc = m_engine->newFunction(DebugWidget::scriptPrintFunction);
		printfunc.setData(m_engine->newQObject(m_output));
		m_engine->globalObject().setProperty("print", printfunc);

		//	script execute.
		QScriptValue sval=m_engine->evaluate(sscript);
		if(!sval.isNull() && !sval.isUndefined()){
			m_output->append( sval.toString() );
		}
		m_output->append( "--- end script." );
	}
}
void MainWindow::debugScript()
{
	QString sscript=m_script->toPlainText();
	if(!sscript.isEmpty()){
		//	debugger
		QScriptEngine engine;
		QScriptEngineDebugger debugger;
		debugger.attachTo(m_engine);
		debugger.action(QScriptEngineDebugger::InterruptAction)->trigger();

		//	script execute.
		QScriptValue sval=m_engine->evaluate(sscript);
		if(!sval.isNull() && !sval.isUndefined()){
			m_output->append( sval.toString() );
		}
		m_output->append( "--- end script." );
	}
}
