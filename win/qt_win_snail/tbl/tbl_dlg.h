#ifndef _TBL_DLG_H___
#define _TBL_DLG_H___

#include <QtWidgets/QtWidgets>
#include <QObject>
#include <QFile>
#include <QList>

#include "ui_tbl_dlg.h"
#include "snail_data.h"

#define TBL_NUM_COL 7

namespace Ui {
    class tbl_dlg;
}

class tbl_dlg : public QDialog
{
	Q_OBJECT

protected:
	Ui::tbl_dlg ui;

public:
	tbl_dlg(QWidget* parent = 0, c_snail_data *sn_data=nullptr);
	virtual ~tbl_dlg();
	QWidget* pParent;
public :
	c_snail_data* p_sn_data;
private:
	QStandardItemModel* csvModel;
///	element_data_t t_element_data;
	QString fileName_tbl;
private slots:
	void SlotOpenFile();
	void SlotSaveFile();

};

#endif ///_TBL_DLG_H__