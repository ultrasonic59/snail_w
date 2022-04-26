#ifndef BOARDSIZEDLG_H
#define BOARDSIZEDLG_H

#include <QDialog>
#include "ui_BoardSizeDlg.h"
class BoardSizeDlg : public QDialog,public Ui::boardSizeDlg
{
	Q_OBJECT

public:
	BoardSizeDlg(QWidget *parent);
	~BoardSizeDlg();
	QSize boardSize() const;

private:
	
};

#endif // BOARDSIZEDLG_H
