#include "component.h"
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
/// #include <QGraphicsRectItem>
#include <math.h>
#include "params.h"



cust_group::cust_group(QObject *parent) :
    QObject(parent)
 {
  ///  setAcceptHoverEvents(true);
 ///   setFlags(ItemIsSelectable|ItemSendsGeometryChanges| ItemIsMovable);
    setFlags(ItemIsSelectable | ItemIsMovable);
}

cust_group::~cust_group()
{
  ///  for(int i = 0; i < NUM_CORNERS; i++){
  ///      delete cornerGrabber[i];
  ///  }
}

QPointF cust_group::previousPosition() const
{
    return m_previousPosition;
}

void cust_group::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}
void cust_group::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  QPointF gr_pos = event->scenePos();
  qreal dx = gr_pos.x() - previousPosition().x();
  qreal dy = gr_pos.y() - previousPosition().y();

 if (m_leftMouseButtonPressed) {
 ///    qDebug() << "m_previousPosition_x=" << m_previousPosition.x();
 ///    qDebug() << "m_previousPosition_y=" << m_previousPosition.y();
  ///   qDebug() << "curx=" << gr_pos.x();
  ///   qDebug() << "cury=" << gr_pos.y();
  ///   qDebug() << "dx="<< dx;
  ///   qDebug() << "dy=" << dy;
      moveBy(dx, dy);
      setPreviousPosition(gr_pos);
    }
}

#if 0
void cust_group::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
///QPointF pt = event->pos();
if (m_leftMouseButtonPressed) {
        setCursor(Qt::ClosedHandCursor);
        QPoint gr_pos = params::closest_to_grid(event->scenePos());
  ///                QPointF gr_pos = event->scenePos();
        qDebug() << "gr_pos=" << gr_pos;

        auto dx = gr_pos.x() - m_previousPosition.x();
        auto dy = gr_pos.y() - m_previousPosition.y();
        QPoint delta = params::closest_to_grid(QPoint(dx, dy));
                      qDebug() << "delta.x="<< delta.x();
                      qDebug() << "delta.y=" << delta.y();
         ///             qDebug() << "gr_pos.x=" << gr_pos.x();
          ///            qDebug() << "gr_pos.y=" << gr_pos.y();
       ///               moveBy(dx, dy);


        moveBy(delta.x(), delta.y());
        qDebug() << "m_previousPosition=" << m_previousPosition;
 ///       qDebug() << "gr_pos=" << gr_pos;
        qDebug() << "pos=" << pos();


        setPreviousPosition(gr_pos);

        ///               emit signalMove(this, dx, dy);
  ///      emit signalMove(this, delta.x(), delta.y());
    }
    QGraphicsItem::mouseMoveEvent(event);
}
#endif
#if 0
void cust_group::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));


///    scenePos();
///QPointF pt = event->pos();
     /*
QPointF pt = event->scenePos();
if (m_leftMouseButtonPressed) {
    this->setPos(mapToScene(event->pos()));
*/
#if 0
    setCursor(Qt::ClosedHandCursor);
    QPoint gr_pos = params::closest_to_grid(event->scenePos());
    ///          QPointF gr_pos = event->scenePos();
    auto dx = gr_pos.x() - m_previousPosition.x();
    auto dy = gr_pos.y() - m_previousPosition.y();
    QPoint delta = params::closest_to_grid(QPoint(dx, dy));
                  qDebug() << "dx="<< dx << "prev.x"<< m_previousPosition.x();
               qDebug() << "dy=" << dy << "prev.y" << m_previousPosition.y();
                  qDebug() << "gr_pos.x=" << gr_pos.x();
                  qDebug() << "gr_pos.y=" << gr_pos.y();
                 moveBy(dx, dy);
  ////  moveBy(delta.x(), delta.y());
    setPreviousPosition(gr_pos);
#endif
    ///               emit signalMove(this, dx, dy);
 ///   emit signalMove(this, delta.x(), delta.y());
///}
////QGraphicsItem::mouseMoveEvent(event);

#if 0
  ///  if(m_actionFlags == ResizeState)
    {
        switch (m_cornerFlags) {
        case Top:
            resizeTop(pt);
            break;
        case Bottom:
            resizeBottom(pt);
            break;
        case Left:
            resizeLeft(pt);
            break;
        case Right:
            resizeRight(pt);
            break;
        default:
           if (m_leftMouseButtonPressed) {
                setCursor(Qt::ClosedHandCursor);
                QPoint gr_pos = params::closest_to_grid(event->scenePos());
     ///          QPointF gr_pos = event->scenePos();

                auto dx = gr_pos.x() - m_previousPosition.x();
                auto dy = gr_pos.y() - m_previousPosition.y();
                QPoint delta = params::closest_to_grid(QPoint(dx,dy));
  ///              qDebug() << "dx="<< dx;
  ///              qDebug() << "dy=" << dy;
   ///             qDebug() << "gr_pos.x=" << gr_pos.x();
    ///            qDebug() << "gr_pos.y=" << gr_pos.y();
 ///               moveBy(dx, dy);
                moveBy(delta.x(), delta.y());
                setPreviousPosition(gr_pos);
 ///               emit signalMove(this, dx, dy);
                emit signalMove(this, delta.x(), delta.y());


            }
        break;
        }
    } 
    QGraphicsItem::mouseMoveEvent(event);
#endif
}
#endif
void cust_group::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = true;
 ///       QPoint gr_pos = params::closest_to_grid(event->scenePos());
        QPointF gr_pos = event->scenePos();
        setPreviousPosition(gr_pos);
 ///       setPreviousPosition(event->scenePos());
        emit clicked(this);
    }
QGraphicsItem::mousePressEvent(event);
}

void cust_group::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = false;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void cust_group::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    bool sel = isSelected();
    setSelected(!sel);

  //   setVisibilityGrabbers();
    QGraphicsItem::mouseDoubleClickEvent(event);
}
#if 1
void cust_group::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  ///  setPositionGrabbers();
 ///   setVisibilityGrabbers();
    QGraphicsItem::hoverEnterEvent(event);
}

void cust_group::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
 ///   hideGrabbers();
    setCursor(Qt::CrossCursor);
    QGraphicsItem::hoverLeaveEvent( event );
}

void cust_group::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pt = event->pos();              // The current position of the mouse
 ///   qDebug() << "hoverMoveEvent="<< pt;
#if 0
////    QPointF pt = event->pos();
    if (m_leftMouseButtonPressed) {
        setCursor(Qt::ClosedHandCursor);
        QPoint gr_pos = params::closest_to_grid(event->scenePos());
        ///          QPointF gr_pos = event->scenePos();
        auto dx = gr_pos.x() - m_previousPosition.x();
        auto dy = gr_pos.y() - m_previousPosition.y();
        QPoint delta = params::closest_to_grid(QPoint(dx, dy));
        ///              qDebug() << "dx="<< dx;
        ///              qDebug() << "dy=" << dy;
         ///             qDebug() << "gr_pos.x=" << gr_pos.x();
          ///            qDebug() << "gr_pos.y=" << gr_pos.y();
       ///               moveBy(dx, dy);
        moveBy(delta.x(), delta.y());
        setPreviousPosition(gr_pos);
        ///               emit signalMove(this, dx, dy);
        emit signalMove(this, delta.x(), delta.y());
    }
#endif
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
    if( dby < 7 && dby > -7 ) 
        m_cornerFlags |= Top;       // Top side
    if( dty < 7 && dty > -7 ) 
        m_cornerFlags |= Bottom;    // Bottom side
    if( drx < 7 && drx > -7 ) 
        m_cornerFlags |= Right;     // Right side
    if( dlx < 7 && dlx > -7 ) 
        m_cornerFlags |= Left;      // Left side

        QPixmap p(":/icons/arrow-up-down.png");
        QPixmap pResult;
        QTransform trans = transform();
        switch (m_cornerFlags) {
        case Top:
        case Bottom:
            pResult = p.transformed(trans);
            setCursor(pResult.scaled(24,24,Qt::KeepAspectRatio));
            break;
        case Left:
        case Right:
            trans.rotate(90);
            pResult = p.transformed(trans);
            setCursor(pResult.scaled(24,24,Qt::KeepAspectRatio));
            break;
        default:
            setCursor(Qt::CrossCursor);
            break;
        }
  QGraphicsItem::hoverMoveEvent( event );
#endif
}
#endif

void cust_group::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (isSelected()) {
        QPen pen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(pen);

        painter->drawRect(boundingRect());
    }
}

QPointF cust_group::GetCenter()
{
    QPointF rez;
    QRectF t_rec = boundingRect();
    qreal rtmp = t_rec.left() + (t_rec.right() - t_rec.left()) / 2;
    rez.setX(rtmp);
    rtmp = t_rec.top() + (t_rec.bottom() - t_rec.top()) / 2;
    rez.setY(rtmp);

#if 0
    QLineF t_line = line();
    qreal rtmp = t_line.p1().x() + (t_line.p2().x() - t_line.p1().x()) / 2;
    rez.setX(rtmp);
    rtmp = t_line.p1().y() + (t_line.p2().y() - t_line.p1().y()) / 2;
    rez.setY(rtmp);

    /*
    for (int i = 0; i < 8; i++) {
        cornerGrabber[i]->setVisible(false);
    }
    */
#endif
    return rez;
}
