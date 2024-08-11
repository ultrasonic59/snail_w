#include "CamPlotter.h"
#include <QtGui/QPainter>
#include <QColor>
#include <QPointF>
#include <QDebug>

CamPlotter::CamPlotter(PlotProperties *Plot_Prop) :
								image(1000, 1000, QImage::Format_ARGB32),
								pPlot_Prop(Plot_Prop)
{
}
CamPlotter::~CamPlotter(void)
{

}
void CamPlotter::ConnectToWidget(QWidget* _PlotWidgetNew)
{
	pPlotWidget = _PlotWidgetNew;
}
bool CamPlotter::setPlotRect(const QRect& fullRect)
{
NeedResize = false;
if (fullRect.width() != pixmap_width)
	{
	pixmap_width = fullRect.width();
	NeedResize = true;
	}
if (fullRect.height() != pixmap_height)
	{
	pixmap_height = fullRect.height();
	NeedResize = true;
	}
	if (!NeedResize)
		return true;
	QImage timage(pixmap_width, pixmap_height, QImage::Format_ARGB32);
	image=timage;
return false;
}
