#include "QLineEdit_arr.h"
#include <QKeyEvent>
#include <QFocusEvent>


QLineEdit_arr::QLineEdit_arr(QWidget *parent)
	:	QLineEdit(parent)

{
}

QLineEdit_arr::~QLineEdit_arr()
{
}


void QLineEdit_arr::keyPressEvent(QKeyEvent * e)
{
	if(e->key() == Qt::Key_Up)
		focusPreviousChild();
	else if(e->key() == Qt::Key_Down)
		focusNextChild();
	else
		QLineEdit::keyPressEvent(e);
}

void QLineEdit_arr::focusInEvent(QFocusEvent * e)
{
	QLineEdit::focusInEvent(e);
	deselect();
}
