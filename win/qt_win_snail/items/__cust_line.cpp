#include "cust_line.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QGraphicsScene>
///#include <QGraphicsPathItem>
#include <QDebug>
#include "dotsignal.h"
#include "params.h"

///extern QPoint closest_to_grid(QPointF curr_pos, QPoint grid);

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
  ///  QGraphicsPathItem::setPath(path);
}

void cust_line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_leftMouseButtonPressed) {
       QPoint gr_pos = params::closest_to_grid(event->scenePos());
  ///      QPoint gr_pos = closest_to_grid(event->scenePos(), QPoint(*p_grid_x, *p_grid_y));

        auto dx = gr_pos.x() - m_previousPosition.x();
        auto dy = gr_pos.y() - m_previousPosition.y();

        qDebug() << "dx="<< dx<<"dy="<<dy ;
        qDebug() << "curx=" << gr_pos.x() << "cury=" << gr_pos.y();
        qDebug() << "prevx=" << m_previousPosition.x() << "prevy=" << m_previousPosition.y();

        moveBy(dx,dy);
  ////      setPreviousPosition(event->scenePos());
        setPreviousPosition(gr_pos);
        emit signalMove(this, dx, dy);
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void cust_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
///QPoint gr_pos=closest_to_grid(event->scenePos(), QPoint(*p_grid_x, *p_grid_y));
QPoint gr_pos = params::closest_to_grid(event->scenePos());
if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = true;

        setPreviousPosition(gr_pos);
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

void cust_line::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    ///  setPositionGrabbers();
    ///  setVisibilityGrabbers();
   ////   QLineF line() const;
   ///   Q_DECL_CONSTEXPR inline QPointF p1() const;
   ///   Q_DECL_CONSTEXPR inline QPointF p2() const;
    QPointF n_point[2];
    n_point[0] = line().p1();
    n_point[1] = line().p2();
    for (int ii = 0; ii < 2; ii++)
    {
        QPointF point = n_point[ii];
        DotSignal* dot = new DotSignal(point, this);
        connect(dot, &DotSignal::signalMove, this, &cust_line::slotMove);
        connect(dot, &DotSignal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
        dot->setDotFlags(DotSignal::Movable);
        listDotes.append(dot);
    }
/*
    QPointF point2 = line().p2();
    DotSignal* dot1 = new DotSignal(point2, this);
    connect(dot1, &DotSignal::signalMove, this, &cust_line::slotMove);
    connect(dot1, &DotSignal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
    dot1->setDotFlags(DotSignal::Movable);
    listDotes.append(dot1);
*/
    /*
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        QPointF point = linePath.elementAt(i);
        DotSignal *dot = new DotSignal(point, this);
        connect(dot, &DotSignal::signalMove, this, &cust_line::slotMove);
        connect(dot, &DotSignal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
        dot->setDotFlags(DotSignal::Movable);
        listDotes.append(dot);
    }
*/
    QGraphicsItem::hoverEnterEvent(event);
}

void cust_line::slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy)
{
    QPointF n_point[2];
    n_point[0] = line().p1();
    n_point[1] = line().p2();
    if (listDotes.at(0) == signalOwner)
        {
        setLine(line().p1().x() + dx, line().p1().y() + dy, line().p2().x() , line().p2().y() );
    ///    m_pointForCheck = 0;
        }
    else
        {
        setLine(line().p1().x() , line().p1().y() , line().p2().x() + dx, line().p2().y() + dy);
    ///    m_pointForCheck = 1;
        }

#if 0
    for (int ii = 0; ii < 2; ii++){
        if (listDotes.at(ii) == signalOwner) {
            QPointF pathPoint = n_point[ii];
            setLine(n_point[ii].x() , n_point[ii].y(), n_point[ii].x()+dx, n_point[ii].y() + dy);
   ///         linePath.setElementPositionAt(i, pathPoint.x() + dx, pathPoint.y() + dy);
            m_pointForCheck = ii;
        }
    }
#endif
/*
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        if(listDotes.at(i) == signalOwner){
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
/*
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
    */
}

void cust_line::updateDots()
{
    if(!listDotes.isEmpty()){
        foreach (DotSignal *dot, listDotes) {
            dot->deleteLater();
        }
        listDotes.clear();
    }
/*
    QPainterPath linePath = path();
    for(int i = 0; i < linePath.elementCount(); i++){
        QPointF point = linePath.elementAt(i);
        DotSignal *dot = new DotSignal(point, this);
        connect(dot, &DotSignal::signalMove, this, &cust_line::slotMove);
        connect(dot, &DotSignal::signalMouseRelease, this, &cust_line::checkForDeletePoints);
        dot->setDotFlags(DotSignal::Movable);
        listDotes.append(dot);
    }
    */
}
#if 0
void cust_line::setPositionGrabbers()
{
    /*
    QRectF tmpRect = rect();
    cornerGrabber[GrabberTop]->setPos(tmpRect.left() + tmpRect.width() / 2, tmpRect.top());
    cornerGrabber[GrabberBottom]->setPos(tmpRect.left() + tmpRect.width() / 2, tmpRect.bottom());
    cornerGrabber[GrabberLeft]->setPos(tmpRect.left(), tmpRect.top() + tmpRect.height() / 2);
    cornerGrabber[GrabberRight]->setPos(tmpRect.right(), tmpRect.top() + tmpRect.height() / 2);
    cornerGrabber[GrabberTopLeft]->setPos(tmpRect.topLeft().x(), tmpRect.topLeft().y());
    cornerGrabber[GrabberTopRight]->setPos(tmpRect.topRight().x(), tmpRect.topRight().y());
    cornerGrabber[GrabberBottomLeft]->setPos(tmpRect.bottomLeft().x(), tmpRect.bottomLeft().y());
    cornerGrabber[GrabberBottomRight]->setPos(tmpRect.bottomRight().x(), tmpRect.bottomRight().y());
    */
}

void cust_line::setVisibilityGrabbers()
{
   /// cornerGrabber
    /*
    cornerGrabber[GrabberTopLeft]->setVisible(true);
    cornerGrabber[GrabberTopRight]->setVisible(true);
    cornerGrabber[GrabberBottomLeft]->setVisible(true);
    cornerGrabber[GrabberBottomRight]->setVisible(true);

    if (m_actionFlags == ResizeState) {
        cornerGrabber[GrabberTop]->setVisible(true);
        cornerGrabber[GrabberBottom]->setVisible(true);
        cornerGrabber[GrabberLeft]->setVisible(true);
        cornerGrabber[GrabberRight]->setVisible(true);
    }
    else {
        cornerGrabber[GrabberTop]->setVisible(false);
        cornerGrabber[GrabberBottom]->setVisible(false);
        cornerGrabber[GrabberLeft]->setVisible(false);
        cornerGrabber[GrabberRight]->setVisible(false);
    }
    */
}

void cust_line::hideGrabbers()
{
    /*
    for (int i = 0; i < 8; i++) {
        cornerGrabber[i]->setVisible(false);
    }
    */
}
#endif