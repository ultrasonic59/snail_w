#include "workplaceview.h"

WorkplaceView::WorkplaceView(QWidget *parent) : QGraphicsView(parent)
{

}

void WorkplaceView::enterEvent(QEvent *event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::CrossCursor);
}

void WorkplaceView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::CrossCursor);
}
void WorkplaceView::wheelEvent(QWheelEvent* event) {
    qreal scaleFactorX = (event->angleDelta().y() > 0) ? 1.2 : 1.0 / 1.2;
    qreal scaleFactorY = (event->angleDelta().y() > 0) ? 1.2 : 1.0 / 1.2;
    scale(scaleFactorX, scaleFactorY);
}
