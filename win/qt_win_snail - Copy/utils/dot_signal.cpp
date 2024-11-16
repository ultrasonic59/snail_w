#include "dot_signal.h"
#include <QBrush>
#include <QColor>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include "params.h"
#define RECT_SZ 8

Dot_Signal::Dot_Signal(QGraphicsItem *parentItem, QObject *parent) :
    QObject(parent)
{
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
 ///   setBrush(QBrush(Qt::black));
 ///   setBrush(QBrush(Qt::yellow));
 ////   setRect(-RECT_SZ,-RECT_SZ, RECT_SZ*2, RECT_SZ*2);
    setPos(QPoint(0,0));
    parentItem = 0;
    setPreviousPosition(QPoint(0, 0));

    setDotFlags(0);
}

Dot_Signal::Dot_Signal(QPointF pos, QGraphicsItem *parentItem, QObject *parent) :
    QObject(parent)
{
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
 ///   setBrush(QBrush(Qt::black));
 ///   setBrush(QBrush(Qt::yellow));
 ///   setRect(-RECT_SZ, -RECT_SZ, RECT_SZ * 2, RECT_SZ * 2);
    setPos(pos);
    setPreviousPosition(pos);
    setDotFlags(0);
}

Dot_Signal::~Dot_Signal()
{

}

QPointF Dot_Signal::previousPosition() const
{
    return m_previousPosition;
}

void Dot_Signal::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void Dot_Signal::setDotFlags(unsigned int flags)
{
    m_flags = flags;
}

void Dot_Signal::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void Dot_Signal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(m_flags & Movable){
        QPoint gr_pos = params::closest_to_grid(event->scenePos());
        setPreviousPosition(gr_pos);
    } else {
        QGraphicsItem::mousePressEvent(event);
    }
   
}

void Dot_Signal::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalMouseRelease();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Dot_Signal::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
 ///   setBrush(QBrush(Qt::red));
}

void Dot_Signal::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
 ///   setBrush(QBrush(Qt::green));
}
