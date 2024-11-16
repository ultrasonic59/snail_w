#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QtGui>
#include <QtScript>

class DebugWidget : public QTextEdit
{
	Q_OBJECT

public :
	DebugWidget(QWidget *parent=0);

	static QScriptValue scriptPrintFunction(QScriptContext *context, QScriptEngine *engine);

public slots:
};

#endif
