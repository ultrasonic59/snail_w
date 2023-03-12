#ifndef QLINEEDIT_SEL_H
#define QLINEEDIT_SEL_H

#include <QLineEdit>
#include <WidgetSelectorShell.h>

class QLineEdit_sel : public WidgetSelectorShell<QLineEdit>
{
protected:

	const int frame_thick;
	bool is_selected;

	virtual void keyPressEvent(QKeyEvent * e);
    virtual void paintEvent(QPaintEvent *);
	virtual void SetWidgetSelected(const bool selected);


public:
	QLineEdit_sel(QWidget *parent);
	virtual ~QLineEdit_sel();

};

#endif // QLINEEDIT_SEL_H
