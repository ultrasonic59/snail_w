#include "debugwidget.h"

DebugWidget::DebugWidget(QWidget *parent) 
 : QTextEdit(parent)
{

}

QScriptValue DebugWidget::scriptPrintFunction(QScriptContext *context, QScriptEngine *engine)
{
	QString result;
	for (int i = 0; i < context->argumentCount(); ++i) {
		if (i > 0){
			result.append(" ");
		}
		result.append(context->argument(i).toString());
	}

	QScriptValue calleeData = context->callee().data();
	QTextEdit *edit = qobject_cast<QTextEdit*>(calleeData.toQObject());
	edit->append(result);

	return engine->undefinedValue();
}
