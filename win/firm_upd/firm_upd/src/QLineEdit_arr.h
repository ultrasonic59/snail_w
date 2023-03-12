#ifndef QLINEEDIT_ARR_H
#define QLINEEDIT_ARR_H

#include <QLineEdit>


class QLineEdit_arr : public QLineEdit
{
protected:

	virtual void keyPressEvent(QKeyEvent * e);
	virtual void focusInEvent(QFocusEvent * e);

public:
	QLineEdit_arr(QWidget *parent);
	~QLineEdit_arr();

};

#endif // QLINEEDIT_ARR_H
