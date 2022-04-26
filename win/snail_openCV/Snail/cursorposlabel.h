#ifndef CURSORPOSLABEL_H
#define CURSORPOSLABEL_H

#include <QLabel>

class CursorPosLabel : public QLabel
{
	Q_OBJECT

public:
	CursorPosLabel(QWidget *parent);
	~CursorPosLabel();

private:
public  slots:
	
		void ChangeLabelText(const QString& newtext);	
};

#endif // CURSORPOSLABEL_H
