#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QtGui>
#include <QtScript>

class DebugWidget : public QTextEdit
{
	Q_OBJECT
	// define the visible property
	Q_PROPERTY( bool visible WRITE setVisible READ isVisible )

public :
	DebugWidget(QWidget *parent=0);
	Q_INVOKABLE void output_invoke(const QString &text);
	void output_noinvoke(const QString &text);

	static QScriptValue scriptPrintFunction(QScriptContext *context, QScriptEngine *engine);

protected :
	Q_INVOKABLE void output2_invoke(const QString &text);

private :
	Q_INVOKABLE void output3_invoke(const QString &text);

public slots:
	void output(const QString &text);

protected slots:
	void output2(const QString &text);

private slots:
	void output3(const QString &text);
};


#endif
