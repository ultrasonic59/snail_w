#include "cust_circle.h"
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
/// #include <QGraphicsRectItem>
#include <math.h>
///#include "dotsignal.h"
#include "params.h"


///#define NUM_CORNERS 4


cust_circle::cust_circle(QObject *parent) :
    QObject(parent),
    m_cornerFlags(0)
{
    setAcceptHoverEvents(true);
    setFlags(ItemIsSelectable|ItemSendsGeometryChanges);
   /// for(int i = 0; i < NUM_CORNERS; i++){
   ///    cornerGrabber[i] = new DotSignal(0,this);
  ///     cornerGrabber[i] = new DotSignal(QPointF(0, 0), 0, this);
 ///   }
 ////   setPositionGrabbers();
}

cust_circle::~cust_circle()
{
  ///  for(int i = 0; i < NUM_CORNERS; i++){
  ///      delete cornerGrabber[i];
  ///  }
}

QPointF cust_circle::previousPosition() const
{
    return m_previousPosition;
}

void cust_circle::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void cust_circle::setRect(qreal x, qreal y, qreal w, qreal h)
{
   setRect(QRectF(x,y,w,h));
}
void cust_circle::setCircle(qreal x, qreal y, qreal d)
{
    setRect(QRectF(x, y, d, d));
}

void cust_circle::setRect(const QRectF &rect)
{
 QGraphicsEllipseItem::setRect(rect);
}

void cust_circle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->pos();
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
}

void cust_circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = true;
        setPreviousPosition(event->scenePos());
        emit clicked(this);
    }
    QGraphicsItem::mousePressEvent(event);
}

void cust_circle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = false;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void cust_circle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  //   setVisibilityGrabbers();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void cust_circle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  ///  setPositionGrabbers();
 ///   setVisibilityGrabbers();
    QGraphicsItem::hoverEnterEvent(event);
}

void cust_circle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_cornerFlags = 0;
 ///   hideGrabbers();
    setCursor(Qt::CrossCursor);
    QGraphicsItem::hoverLeaveEvent( event );
}

void cust_circle::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
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
}

void cust_circle::resizeLeft(const QPointF &pt)
{
    QRectF tmpRect = rect();
    if( pt.x() > tmpRect.right() )
        return;
    qreal widthOffset =  ( pt.x() - tmpRect.right() );

    // limit the minimum width
    if( widthOffset > -10 )
        return;
    // if it's negative we set it to a positive width value
    if (widthOffset < 0)
    {
        tmpRect.setWidth(-widthOffset);
        tmpRect.setHeight(-widthOffset);
    }
    else
    {
        tmpRect.setWidth(widthOffset);
        tmpRect.setHeight(widthOffset);
    }
     tmpRect.translate( (rect().width() - tmpRect.width())/2 , (rect().width() - tmpRect.width()) / 2);
    prepareGeometryChange();
    // Set the ne geometry
    setRect( tmpRect );
     // Update to see the result
    update();
  ///  setPositionGrabbers();
}

void cust_circle::resizeRight(const QPointF &pt)
{
    QRectF tmpRect = rect();
    if( pt.x() < tmpRect.left() )
        return;
    qreal widthOffset =  ( pt.x() - tmpRect.left() );
    if( widthOffset < 10 ) /// limit
        return;
    if (widthOffset < 10)
        {
        tmpRect.setWidth(-widthOffset);
        tmpRect.setHeight(-widthOffset);
    }
    else
        {
        tmpRect.setWidth(widthOffset);
        tmpRect.setHeight(widthOffset);
        }
    tmpRect.translate((rect().width() - tmpRect.width()) / 2, (rect().width() - tmpRect.width()) / 2);
    prepareGeometryChange();
    setRect( tmpRect );
    update();
 ///   setPositionGrabbers();
}

void cust_circle::resizeBottom(const QPointF &pt)
{
    QRectF tmpRect = rect();
    if( pt.y() < tmpRect.top() )
        return;
    qreal heightOffset =  ( pt.y() - tmpRect.top() );
    if( heightOffset < 11 ) /// limit
        return;
    if (heightOffset < 0)
    {
        tmpRect.setHeight(-heightOffset);
        tmpRect.setWidth(-heightOffset);
    }
    else
    {
        tmpRect.setHeight(heightOffset);
        tmpRect.setWidth(heightOffset);
    }
    tmpRect.translate((rect().width() - tmpRect.width()) / 2, (rect().width() - tmpRect.width()) / 2);
    prepareGeometryChange();
    setRect( tmpRect );
    update();
 ///   setPositionGrabbers();
}

void cust_circle::resizeTop(const QPointF &pt)
{
    QRectF tmpRect = rect();
    if( pt.y() > tmpRect.bottom() )
        return;
    qreal heightOffset =  ( pt.y() - tmpRect.bottom() );
    if( heightOffset > -11 ) /// limit
        return;
    if (heightOffset < 0)
       {
        tmpRect.setHeight(-heightOffset);
        tmpRect.setWidth(-heightOffset);
    }
    else
       {
        tmpRect.setHeight(heightOffset);
        tmpRect.setWidth(heightOffset);
    }
     tmpRect.translate((rect().width() - tmpRect.width()) / 2, (rect().width() - tmpRect.width()) / 2);

    prepareGeometryChange();
    setRect( tmpRect );
    update();
 ///   setPositionGrabbers();
}
#if 0
void cust_circle::setPositionGrabbers()
{
    QRectF tmpRect = rect();
  ///  cornerGrabber[GrabberTop]->setPos(tmpRect.left() + tmpRect.width()/2, tmpRect.top() + tmpRect.width() / 2);
    cornerGrabber[GrabberTop]->setPos(tmpRect.left() + tmpRect.width() / 2, tmpRect.top() );
    cornerGrabber[GrabberBottom]->setPos(tmpRect.left() + tmpRect.width()/2, tmpRect.bottom());
    cornerGrabber[GrabberLeft]->setPos(tmpRect.left(), tmpRect.top() + tmpRect.height()/2);
    cornerGrabber[GrabberRight]->setPos(tmpRect.right(), tmpRect.top() + tmpRect.height()/2);
}

void cust_circle::setVisibilityGrabbers()
{

cornerGrabber[GrabberTop]->setVisible(true);
cornerGrabber[GrabberBottom]->setVisible(true);
cornerGrabber[GrabberLeft]->setVisible(true);
 cornerGrabber[GrabberRight]->setVisible(true);
 
}

void cust_circle::hideGrabbers()
{
    for(int i = 0; i < NUM_CORNERS; i++){
        cornerGrabber[i]->setVisible(false);
    }
}
#endif