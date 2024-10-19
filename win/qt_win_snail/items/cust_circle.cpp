#include "cust_circle.h"
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
/// #include <QGraphicsRectItem>
#include <math.h>
#include "dotsignal.h"
#include "params.h"


#define NUM_CORNERS 4

///static const double Pi = 3.14159265358979323846264338327950288419717;
///static double TwoPi = 2.0 * Pi;
/*
static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}
*/

cust_circle::cust_circle(QObject *parent) :
    QObject(parent),
    m_cornerFlags(0)///,
///    m_actionFlags(ResizeState)
{
    setAcceptHoverEvents(true);
    setFlags(ItemIsSelectable|ItemSendsGeometryChanges);
    for(int i = 0; i < NUM_CORNERS; i++){
        cornerGrabber[i] = new DotSignal(this);
    }
    setPositionGrabbers();
}

cust_circle::~cust_circle()
{
    for(int i = 0; i < NUM_CORNERS; i++){
        delete cornerGrabber[i];
    }
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

  ///              auto dx = event->scenePos().x() - m_previousPosition.x();
  ///              auto dy = event->scenePos().y() - m_previousPosition.y();
                auto dx = gr_pos.x() - m_previousPosition.x();
                auto dy = gr_pos.y() - m_previousPosition.y();
                moveBy(dx,dy);
                setPreviousPosition(gr_pos);
                emit signalMove(this, dx, dy);
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
     setVisibilityGrabbers();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void cust_circle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setPositionGrabbers();
    setVisibilityGrabbers();
    QGraphicsItem::hoverEnterEvent(event);
}

void cust_circle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_cornerFlags = 0;
    hideGrabbers();
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

/*
QVariant cust_circle::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case QGraphicsItem::ItemSelectedChange:
      ///  m_actionFlags = ResizeState;
        break;
    default:
        break;
    }
    return QGraphicsItem::itemChange(change, value);
}
*/
void cust_circle::resizeLeft(const QPointF &pt)
{
    QRectF tmpRect = rect();
    QPointF last_pos = pos();
    // if the mouse is on the right side we return
    if( pt.x() > tmpRect.right() )
        return;
    qreal widthOffset =  ( pt.x() - tmpRect.right() );
    qDebug() << "widthOffset=" << widthOffset;
    qDebug() << "pos=" << last_pos;

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
    // Since it's a left side , the rectange will increase in size
    // but keeps the topLeft as it was
  ///??  tmpRect.translate( rect().width() - tmpRect.width() , 0 );
  ///??  prepareGeometryChange();
    // Set the ne geometry
    setRect( tmpRect );
    setPos(last_pos.x() + widthOffset / 2, last_pos.y() + widthOffset / 2);

    // Update to see the result
    update();
    setPositionGrabbers();
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
    prepareGeometryChange();
    setRect( tmpRect );
    update();
    setPositionGrabbers();
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
    prepareGeometryChange();
    setRect( tmpRect );
    update();
    setPositionGrabbers();
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
    tmpRect.translate( 0 , rect().height() - tmpRect.height() );
    prepareGeometryChange();
    setRect( tmpRect );
    update();
    setPositionGrabbers();
}
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
