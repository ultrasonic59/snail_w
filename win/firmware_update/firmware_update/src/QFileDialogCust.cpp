#include "QFileDialogCust.h"

QFileDialogCust::QFileDialogCust(QWidget *parent)
	: QFileDialog(parent)
{
	setLabelText(QFileDialog::Reject, tr("zzzzz \320\236\321\202\320\274\320\265\320\275\320\260"));
}
QFileDialogCust::QFileDialogCust()
{
	setLabelText(QFileDialog::Reject, tr("zzzzz1 \320\236\321\202\320\274\320\265\320\275\320\260"));
}

QFileDialogCust::~QFileDialogCust()
{
}


void QFileDialogCust::show()
{
	QFileDialog::show();
	focusPreviousChild();
}
