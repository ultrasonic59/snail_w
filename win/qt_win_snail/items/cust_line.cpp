#include "cust_line.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QDebug>
#include <QCursor>
#include "dot_signal.h"
#include "params.h"


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
 ///   emit previousPositionChanged();
}

void cust_line::setPath(const QPainterPath &path)
{
    QGraphicsPathItem::setPath(path);
}
#define DELT_NEAR 5

bool nearPoints(QPointF pt1, QPointF pt2)
{
if ((pt1.x() >= pt2.x() - DELT_NEAR) && (pt1.x() < pt2.x() + DELT_NEAR))
    {
    if ((pt1.y() >= pt2.y() - DELT_NEAR) && (pt1.y() < pt2.y() + DELT_NEAR))
       {
        return true;
       }
    }
return false;
}
void cust_line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
QPainterPath linePath = path();
QPoint pt = params::closest_to_grid(event->pos());
if (m_leftMouseButtonPressed) {
if (nearPoints(linePath.elementAt(0),m_previousPosition))
    {
    linePath.setElementPositionAt(0, pt.x(), pt.y());
    setPreviousPosition(pt);
 ///           qDebug() << "elementAt(0)"<< pt<< linePath.elementAt(1);
    }
else if (nearPoints(linePath.elementAt(1),m_previousPosition))
    {
    linePath.setElementPositionAt(1, pt.x(), pt.y());
    setPreviousPosition(pt);
    ///qDebug() << "elementAt(1)";
    }
#if 1
else
   {
   auto dx = pt.x() - m_previousPosition.x();
   auto dy = pt.y() - m_previousPosition.y();
 ///           setPreviousPosition(pt);
           qDebug() << "dx="<< dx << "dy=" << dy;
           qDebug() << "pt=" << pt;
           qDebug() << "m_previousPosition=" << m_previousPosition;

            moveBy(dx, dy);
            ///       setPreviousPosition(event->scenePos());
            setPreviousPosition(pt);
            emit signalMove(this, dx, dy);
    }
#endif
    setPath(linePath);
    }
 QGraphicsItem::mouseMoveEvent(event);
}

void cust_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 ///QPoint pt = params::closest_to_grid(event->pos());
 QPointF pt = event->pos();

    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = true;
///        setPreviousPosition(event->scenePos());
        setPreviousPosition(pt);
        emit signalPress(this);
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
    /*
    if(!listDotes.isEmpty()){
        foreach (Dot_Signal *dot, listDotes) {
            dot->deleteLater();
        }
        listDotes.clear();
    }
*/
 QGraphicsItem::hoverLeaveEvent(event);
}

void cust_line::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
///====================================================
    QPainterPath linePath = path();

#if 0
    QPainterPath t_path = path();
///================================================
    QPainterPath linePath = path();
    for (int i = 0; i < linePath.elementCount(); i++) {
              if(listDotes.at(i) == signalOwner)
        {
            QPointF pathPoint = linePath.elementAt(i);
            linePath.setElementPositionAt(i, pathPoint.x() + dx, pathPoint.y() + dy);
            m_pointForCheck = i;
        }
    }
#else
int num_points= linePath.elementCount();
///qDebug() << "num_points=" << num_points;
qreal left_p;
qreal right_p;
qreal top_p;
qreal bot_p;

if (num_points == 2)
{
if (linePath.elementAt(0).x < linePath.elementAt(1).x)
    {
    left_p = linePath.elementAt(0).x;
    right_p = linePath.elementAt(1).x;
    }
else
    {
    left_p = linePath.elementAt(1).x;
    right_p = linePath.elementAt(0).x;
    }
if (linePath.elementAt(0).y < linePath.elementAt(1).y)
{
    top_p = linePath.elementAt(0).y;
    bot_p = linePath.elementAt(1).y;
}
else
{
    top_p = linePath.elementAt(1).y;
    bot_p = linePath.elementAt(0).y;
}
QPointF pt = event->pos();              // The current position of the mouse
qreal drx = pt.x() - right_p;    // Distance between the mouse and the right
qreal dlx = pt.x() - left_p;     // Distance between the mouse and the left

qreal dby = pt.y() - top_p;      // Distance between the mouse and the top
qreal dty = pt.y() - bot_p;   // Distance between the mouse and the bottom

m_cornerFlags = 0;
if (dby < 7 && dby > -7)
m_cornerFlags |= Top;       // Top side
if (dty < 7 && dty > -7)
m_cornerFlags |= Bottom;    // Bottom side
if (drx < 7 && drx > -7)
m_cornerFlags |= Right;     // Right side
if (dlx < 7 && dlx > -7)
m_cornerFlags |= Left;      // Left side

QPixmap p(":/icons/arrow-up-down.png");
QPixmap pResult;
QTransform trans = transform();
if ((m_cornerFlags & Left) | (m_cornerFlags & Right))
   {
    trans.rotate(90);
    pResult = p.transformed(trans);
    setCursor(pResult.scaled(24, 24, Qt::KeepAspectRatio));
 ///   qDebug() << "Left-Right";

   }
else if ((m_cornerFlags & Top) | (m_cornerFlags & Bottom))
   {
    pResult = p.transformed(trans);
    setCursor(pResult.scaled(24, 24, Qt::KeepAspectRatio));
   }
else
   setCursor(Qt::CrossCursor);
#endif
}
///================================================

#if 0
     QPointF pt = event->pos();              // The current position of the mouse
    qreal drx = pt.x() - rect().right();    // Distance between the mouse and the right
    qreal dlx = pt.x() - rect().left();     // Distance between the mouse and the left

    qreal dby = pt.y() - rect().top();      // Distance between the mouse and the top
    qreal dty = pt.y() - rect().bottom();   // Distance between the mouse and the bottom

    // If the mouse position is within a radius of 7
    // to a certain side( top, left, bottom or right)
    // we set the Flag in the Corner Flags Register

    m_cornerFlags = 0;
    if (dby < 7 && dby > -7)
        m_cornerFlags |= Top;       // Top side
    if (dty < 7 && dty > -7)
        m_cornerFlags |= Bottom;    // Bottom side
    if (drx < 7 && drx > -7)
        m_cornerFlags |= Right;     // Right side
    if (dlx < 7 && dlx > -7)
        m_cornerFlags |= Left;      // Left side

    if (m_actionFlags == ResizeState) {
        QPixmap p(":/icons/arrow-up-down.png");
        QPixmap pResult;
        QTransform trans = transform();
        switch (m_cornerFlags) {
        case Top:
        case Bottom:
            pResult = p.transformed(trans);
            setCursor(pResult.scaled(24, 24, Qt::KeepAspectRatio));
            break;
        case Left:
        case Right:
            trans.rotate(90);
            pResult = p.transformed(trans);
            setCursor(pResult.scaled(24, 24, Qt::KeepAspectRatio));
            break;
        case TopRight:
        case BottomLeft:
            trans.rotate(45);
            pResult = p.transformed(trans);
            setCursor(pResult.scaled(24, 24, Qt::KeepAspectRatio));
            break;
        case TopLeft:
        case BottomRight:
            trans.rotate(135);
            pResult = p.transformed(trans);
            setCursor(pResult.scaled(24, 24, Qt::KeepAspectRatio));
            break;
        default:
            setCursor(Qt::CrossCursor);
            break;
        }
    }
#endif
    ///================================================
    QGraphicsItem::hoverMoveEvent(event);
}

void cust_line::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
 /*
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        QPointF point = linePath.elementAt(i);
        Dot_Signal *dot = new Dot_Signal(point, this);
        connect(dot, &Dot_Signal::signalMove, this, &cust_line::slotMove);
        connect(dot, &Dot_Signal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
        dot->setDotFlags(Dot_Signal::Movable);
        listDotes.append(dot);
    }
*/
    QGraphicsItem::hoverEnterEvent(event);
}

void cust_line::slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy)
{
/*
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        if(listDotes.at(i) == signalOwner)
        {
            QPointF pathPoint = linePath.elementAt(i);
            linePath.setElementPositionAt(i, pathPoint.x() + dx, pathPoint.y() + dy);
            m_pointForCheck = i;
        }
    }
    setPath(linePath);
    */
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
 ///       updateDots();
        m_pointForCheck = -1;
    }
}
