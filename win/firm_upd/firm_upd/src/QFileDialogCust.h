#ifndef QFILEDIALOGCUST_H
#define QFILEDIALOGCUST_H

#include <QFileDialog>

class QFileDialogCust : public QFileDialog
{
public:
	QFileDialogCust(QWidget *parent);
	QFileDialogCust();
	~QFileDialogCust();


public Q_SLOTS:
    void show();

};

#endif // QFILEDIALOGCUST_H
