#include "PlotterWidget.h"
#include "qpainter.h"
#include <QPaintEvent>
#include <Qdebug>


plotterwidget::plotterwidget(QWidget *parent)/// :
								///QWidget(parent, f)////,
								////pPlotter(nullptr)
{

}
plotterwidget::~plotterwidget(void)
{
////	pPlotter = nullptr;
}
#if 1
void plotterwidget::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
	QRect cr = contentsRect();
painter.drawPixmap(cr, QPixmap::fromImage(image));
painter.end();

}
#endif

void plotterwidget::_setImage(QImage ipm)
{
image=ipm;
////	 qDebug() << " _setImage " ;
//// UpdatePlot();
//qDebug() << "updating plotter widget image..";
update();
}
#if 1
void plotterwidget::resizeEvent(QResizeEvent *event)
{
QWidget::resizeEvent(event);  // 
}
#endif