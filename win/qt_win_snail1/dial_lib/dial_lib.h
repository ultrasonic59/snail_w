#ifndef _DIAL_LIB_H_
#define _DIAL_LIB_H_

#include <QtWidgets/QtWidgets>
#include "PlotProperties.h"

#include "ui_dial_lib.h"
 #include "dev_interf.h"
#include "can_message.h"
#include "lib_paint_scene.h"
#include "snail_types.h"

namespace Ui {
    class Dial_lib;
}


class DialLib : public QDialog
{
Q_OBJECT

protected:
	Ui::Dial_lib ui;

public:
	DialLib(QWidget *parent= 0, PlotProperties* Plot_Prop = 0);
	virtual ~DialLib();
	QWidget* pParent;
	PlotProperties* pPlot_Prop;
	en_rej cur_rej;
	en_item_type cur_item;
signals:
	void SignalTest();

private slots:
	void  on_butt_select();
	void  on_butt_place();
	void indexChanged(int index);
	void setBGColor(const QColor& color);
	void setBorderColor(const QColor& color);

///	void  slot_send_can_msg();

	void  SlotTest();
public slots:
    void clear_textEdit();

private: 
///	en_rej cur_rej;
	void  show_rej();
	void  show_params();

private:
	LibPaintScene* scene;
	QTimer* timer;
	void resizeEvent(QResizeEvent* event);
	QString path;

private slots:
	void slotTimer();
private slots:
	void on_butSave_clicked();
	void on_butOpen_clicked();
	void checkSelection();
	void checkActionStates();
	void selectItem(QGraphicsItem* item);
	void selectNewItem(QGraphicsItem* item);
///	void slotHelp();
};

#endif // DIAL_ED_PAR_H