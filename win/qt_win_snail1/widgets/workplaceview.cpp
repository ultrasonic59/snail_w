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
