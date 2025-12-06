#ifndef _CSV_DLG_H___
#define _CSV_DLG_H___

#include <QtWidgets/QtWidgets>
#include <QObject>
#include <QFile>
#include <QList>

#include "ui_csv_dlg.h"
#include "snail_data.h"

#define CSV_NUM_COL 7

namespace Ui {
    class csv_dlg;
}

class csv_dlg : public QDialog
{
	Q_OBJECT

protected:
	Ui::csv_dlg ui;

public:
	csv_dlg(QWidget* parent = 0, c_snail_data *sn_data=nullptr);
	virtual ~csv_dlg();
	QWidget* pParent;
public :
	c_snail_data* p_sn_data;
private:
	QStandardItemModel* csvModel;
	bool conv_data();
	void set_dat_col(int num_row, int num_col, QString rec);
	element_data_t t_element_data;
	QString fileName_csv;
private slots:
	void SlotOpenFile();
	void SlotSaveFile();

};

#endif ///_CSV_DLG_H__