#include "cust_line.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QDebug>
#include "dotsignal.h"

cust_line::cust_line(QObject *parent) :
    QObject(parent)
{
    setAcceptHoverEvents(true);
    setFlags(ItemIsSelectable|ItemSendsGeometryChanges);
}

cust_line::~cust_line()
{

}

QPointF cust_line::previousPosition() const
{
    return m_previousPosition;
}

void cust_line::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void cust_line::setPath(const QPainterPath &path)
{
    QGraphicsPathItem::setPath(path);
}

void cust_line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_leftMouseButtonPressed) {
        auto dx = event->scenePos().x() - m_previousPosition.x();
        auto dy = event->scenePos().y() - m_previousPosition.y();
        moveBy(dx,dy);
        setPreviousPosition(event->scenePos());
        emit signalMove(this, dx, dy);
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void cust_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = true;
        setPreviousPosition(event->scenePos());
        emit clicked(this);
    }
    QGraphicsItem::mousePressEvent(event);
}

void cust_line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = false;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void cust_line::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
#if 0
    QPointF clickPos = event->pos();
    QLineF checkLineFirst(clickPos.x() - 5, clickPos.y() - 5, clickPos.x() + 5, clickPos.y() + 5);
    QLineF checkLineSecond(clickPos.x() + 5, clickPos.y() - 5, clickPos.x() - 5, clickPos.y() + 5);
    QPainterPath oldPath = path();
    QPainterPath newPath;
    for(int i = 0; i < oldPath.elementCount(); i++){
        QLineF checkableLine(oldPath.elementAt(i), oldPath.elementAt(i+1));
        if(checkableLine.intersect(checkLineFirst,0) == 1 || checkableLine.intersect(checkLineSecond,0) == 1){
            if(i == 0){
                newPath.moveTo(oldPath.elementAt(i));
                newPath.lineTo(clickPos);
            } else {
                newPath.lineTo(oldPath.elementAt(i));
                newPath.lineTo(clickPos);
            }
        } else {
            if(i == 0){
                newPath.moveTo(oldPath.elementAt(i));
            } else {
                newPath.lineTo(oldPath.elementAt(i));
            }
        }
        if(i == (oldPath.elementCount() - 2)) {
            newPath.lineTo(oldPath.elementAt(i + 1));
            i++;
        }
    }
    setPath(newPath);
    updateDots();
    QGraphicsItem::mouseDoubleClickEvent(event);
#endif
}

void cust_line::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(!listDotes.isEmpty()){
        foreach (DotSignal *dot, listDotes) {
            dot->deleteLater();
        }
        listDotes.clear();
    }
    QGraphicsItem::hoverLeaveEvent(event);
}

void cust_line::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void cust_line::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        QPointF point = linePath.elementAt(i);
        DotSignal *dot = new DotSignal(point, this);
        connect(dot, &DotSignal::signalMove, this, &cust_line::slotMove);
        connect(dot, &DotSignal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
        dot->setDotFlags(DotSignal::Movable);
        listDotes.append(dot);
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void cust_line::slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy)
{
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        if(listDotes.at(i) == signalOwner){
            QPointF pathPoint = linePath.elementAt(i);
            linePath.setElementPositionAt(i, pathPoint.x() + dx, pathPoint.y() + dy);
            m_pointForCheck = i;
        }
    }
    setPath(linePath);
}

void cust_line::checkForDeletePoints()
{
    if(m_pointForCheck != -1){
        QPainterPath linePath = path();

        QPointF pathPoint = linePath.elementAt(m_pointForCheck);
        if(m_pointForCheck > 0){
            QLineF lineToNear(linePath.elementAt(m_pointForCheck-1),pathPoint);
            if(lineToNear.length() < 6.0) {
                QPainterPath newPath;
                newPath.moveTo(linePath.elementAt(0));
                for(int i = 1; i < linePath.elementCount(); i++){
                    if(i != m_pointForCheck){
                        newPath.lineTo(linePath.elementAt(i));
                    }
                }
                setPath(newPath);
            }
        }
        if(m_pointForCheck < linePath.elementCount() - 1){
            QLineF lineToNear(linePath.elementAt(m_pointForCheck+1),pathPoint);
            if(lineToNear.length() < 6.0) {
                QPainterPath newPath;
                newPath.moveTo(linePath.elementAt(0));
                for(int i = 1; i < linePath.elementCount(); i++){
                    if(i != m_pointForCheck){
                        newPath.lineTo(linePath.elementAt(i));
                    }
                }
                setPath(newPath);
            }
        }
        updateDots();
        m_pointForCheck = -1;
    }
}

void cust_line::updateDots()
{
    if(!listDotes.isEmpty()){
        foreach (DotSignal *dot, listDotes) {
            dot->deleteLater();
        }
        listDotes.clear();
    }
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        QPointF point = linePath.elementAt(i);
        DotSignal *dot = new DotSignal(point, this);
        connect(dot, &DotSignal::signalMove, this, &cust_line::slotMove);
        connect(dot, &DotSignal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
        dot->setDotFlags(DotSignal::Movable);
        listDotes.append(dot);
    }
}
