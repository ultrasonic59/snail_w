#include "boardsizedlg.h"

BoardSizeDlg::BoardSizeDlg(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

}

BoardSizeDlg::~BoardSizeDlg()
{

}

QSize BoardSizeDlg::boardSize() const
{
	return QSize(spinBoxWidth->value(),spinBoxHeight->value());
}