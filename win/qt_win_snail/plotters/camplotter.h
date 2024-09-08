#pragma once

#include <QWidget>
#include <QPen>
#include "PlotProperties.h"
#include "PlotterWidget.h"
#include <qcustomvideosurface.h>
#include <opencv2/core.hpp>
#include "snail_consts.h"



using namespace cv;

class CamPlotter : public QObject
{
	Q_OBJECT
public:
	CamPlotter(PlotProperties* Plot_Prop=0, c_snail_data* p_snail_data=0);
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
	////virtual bool setPlotRect(const QRect&);
	void drawPoints(const Mat& _mat);
	void drawCrs(const Mat& _mat);
	void drawSelRect(const Mat& _mat);
	void drawRuleLine(const Mat& _mat);

	c_snail_data* p_snail_data;
	///quint16 setka_delt_x;
	///quint16 setka_delt_y;
	QRect sel_rect;
protected:
	QPoint getMouseInsideCoord(QPoint inPos);
	QPoint last_pn;
	Mat mat_img;
	bool redraw_sel_rc;
private:
	quint32 m_flags;


public slots:
////		void slot_resize(int,int);
///	void sl_set_vscroll_val(int);
///	void set_zoom_rect(QRect t_rect);
	////	void sl_set_sel_rect(QRect rc);
	void sl_update_image(QImage& img, QImage::Format _format);
	void slSetPoint(QPoint* pn);
	void slMovePoint(QPoint* pn);
	void slClrPoint(QPoint* pn);
	void sl_set_sel_rect(QRect t_rect);

signals:
////	void updateCamImage(QImage);
	void s_update_image(QImage& img, QImage::Format _format);
	void s_show_rule_coord(QRect& rc);

	///	void s_rect_changet(QRect rc);
///	void s_set_vscroll_val(int);
};
