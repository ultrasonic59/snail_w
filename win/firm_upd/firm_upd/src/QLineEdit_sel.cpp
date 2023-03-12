#include "QLineEdit_sel.h"
#include <QPainter>


QLineEdit_sel::QLineEdit_sel(QWidget *parent)
	: WidgetSelectorShell<QLineEdit>(parent),
		frame_thick(2),
		is_selected(false)

{
}

QLineEdit_sel::~QLineEdit_sel()
{
}


void QLineEdit_sel::keyPressEvent(QKeyEvent * e)
{	
	bool default_event = true;

	if(e->modifiers() == Qt::NoModifier)
	{
		switch (e->key()) 
		{
		case Qt::Key_Left:

			if(cursorPosition() > 0)
			{
				QLineEdit::keyPressEvent(e);
				default_event = false;
			}
			break;

		case Qt::Key_Right:

			if(cursorPosition() < text().size())
			{
				QLineEdit::keyPressEvent(e);
				default_event = false;
			}
			break;

		default:;
		}
	}

	if(default_event)
		WidgetSelectorShell<QLineEdit>::keyPressEvent(e);
}


void QLineEdit_sel::SetWidgetSelected(const bool selected)
{
	WidgetSelectorShell<QLineEdit>::SetWidgetSelected(selected);

	if(is_selected != selected)
	{
		is_selected = selected;
		update();
	}
}


void QLineEdit_sel::paintEvent(QPaintEvent * event)
{
	QLineEdit::paintEvent(event);

	if(is_selected)
	{
		QRect cRect = event->rect();
		QRect bRect = geometry();

		if((cRect.width() == bRect.width()) && (cRect.height() == bRect.height()))
		{
			QPainter p(this);
			cRect.adjust(frame_thick/2, frame_thick/2, -frame_thick/2, -frame_thick/2);

			QPen pen( QColor(0, 75, 255));	// 30, 144, 255
			pen.setWidth(frame_thick);
			p.setPen(pen);

			p.drawRect(cRect);
		}
	}
}
