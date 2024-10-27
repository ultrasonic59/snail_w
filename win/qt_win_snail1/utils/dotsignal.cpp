#include "dotsignal.h"
#include <QBrush>
#include <QColor>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include "params.h"
#define RECT_SZ 8
DotSignal::DotSignal(QGraphicsItem *parentItem, QObject *parent) :
    QObject(parent)
{
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
 ///   setBrush(QBrush(Qt::black));
    setBrush(QBrush(Qt::yellow));
    setRect(-RECT_SZ,-RECT_SZ, RECT_SZ*2, RECT_SZ*2);
    setPos(QPoint(0,0));
    parentItem = 0;
    setPreviousPosition(QPoint(0, 0));

    setDotFlags(0);
}

DotSignal::DotSignal(QPointF pos, QGraphicsItem *parentItem, QObject *parent) :
    QObject(parent)
{
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
 ///   setBrush(QBrush(Qt::black));
    setBrush(QBrush(Qt::yellow));
    setRect(-RECT_SZ, -RECT_SZ, RECT_SZ * 2, RECT_SZ * 2);
    setPos(pos);
    setPreviousPosition(pos);
    setDotFlags(0);
}

DotSignal::~DotSignal()
{

}

QPointF DotSignal::previousPosition() const
{
    return m_previousPosition;
}

void DotSignal::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void DotSignal::setDotFlags(unsigned int flags)
{
    m_flags = flags;
}

void DotSignal::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   
    if(m_flags & Movable){
        QPoint gr_pos = params::closest_to_grid(event->scenePos());

        auto dx = gr_pos.x() - m_previousPosition.x();
        auto dy = gr_pos.y() - m_previousPosition.y();
        moveBy(dx,dy);
        setPreviousPosition(gr_pos);
        emit signalMove(this, dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent(event);
    }
    
}

void DotSignal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(m_flags & Movable){
        QPoint gr_pos = params::closest_to_grid(event->scenePos());
        setPreviousPosition(gr_pos);
    } else {
        QGraphicsItem::mousePressEvent(event);
    }
   
}

void DotSignal::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalMouseRelease();
    QGraphicsItem::mouseReleaseEvent(event);
}

void DotSignal::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    setBrush(QBrush(Qt::red));
}

void DotSignal::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    setBrush(QBrush(Qt::green));
}
