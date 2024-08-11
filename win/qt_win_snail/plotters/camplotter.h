#pragma once

#include <QWidget>
#include <QPen>
#include "PlotProperties.h"
#include "PlotterWidget.h"

class CamPlotter : public QObject
{
	Q_OBJECT
public:
	CamPlotter(PlotProperties* Plot_Prop=0);
	virtual ~CamPlotter(void);

protected:
	bool NeedResize;
	int pixmap_width;
	int pixmap_height;
	QPen pen;
	QImage image;
	PlotProperties* pPlot_Prop;
	QWidget* pPlotWidget;
public:
	void ConnectToWidget(QWidget*);
	virtual bool setPlotRect(const QRect&);

public slots:
	////	void slot_resize(int,int);
///	void sl_set_vscroll_val(int);
///	void set_zoom_rect(QRect t_rect);
	////	void sl_set_sel_rect(QRect rc);

signals:
	void updateCamImage(QImage);
///	void s_rect_changet(QRect rc);
///	void s_set_vscroll_val(int);
};
