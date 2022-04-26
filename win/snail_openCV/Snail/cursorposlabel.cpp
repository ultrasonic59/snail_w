#include "cursorposlabel.h"

CursorPosLabel::CursorPosLabel(QWidget *parent)
	: QLabel(parent)
{
	setFrameStyle(QFrame::Panel | QFrame::Sunken);
	QFont legend_font("Arial", 14);
	setText("Load Board Image");
	setFont(legend_font);
}

void CursorPosLabel::ChangeLabelText(const QString& newText)
{
	setText(newText);
}
CursorPosLabel::~CursorPosLabel()
{

}
