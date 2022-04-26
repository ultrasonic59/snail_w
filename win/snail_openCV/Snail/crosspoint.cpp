#include "crosspoint.h"
#include "qdebug.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
CrossPoint::CrossPoint()
	: QGraphicsObject()
{
setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsScenePositionChanges);
setDisplayCoordinate(QPoint(0,0));

}

CrossPoint::~CrossPoint()
{

}

void CrossPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
      
            setSelected(true);
        } else if (event->modifiers() == Qt::AltModifier) {

        } else {
		
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
  
        event->ignore();
    }
}

QRectF CrossPoint::boundingRect() const
{
	return QRectF(bounding_rect::TOP,bounding_rect::LEFT,bounding_rect::WIDTH,bounding_rect::HEIGHT);
}

void CrossPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	double width_pen=3;
	QPointF pos=data(1).toPointF();
			if(isSelected()){


				painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::green, 3, Qt::SolidLine));
	painter->drawEllipse(QPoint(0,0),5,5);
	
	painter->setPen(QPen(Qt::green, 1, Qt::SolidLine));

	painter->drawLine(0,-7,0,7);
	painter->drawLine(-7,0,7,0);
	QString coordinate=QString("(%1,%2)").arg(pos.x(),0,'f',1).arg(pos.y(),0,'f',1);
	painter->drawText(5,5, coordinate);

	}
	else
	{
	painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
	painter->drawEllipse(QPoint(0,0),5,5);
	
	painter->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));

	painter->drawLine(0,-7,0,7);
	painter->drawLine(-7,0,7,0);
	QString coordinate=QString("(%1,%2)").arg(pos.x(),0,'f',1).arg(pos.y(),0,'f',1);
	painter->drawText(5,5, coordinate);

	}
	


}

void CrossPoint::setDisplayCoordinate(const QPointF& coord)
{
	display_coordinate=coord;
}

QVariant CrossPoint::itemChange(GraphicsItemChange change, const QVariant &value)
 {
     if (change == ItemSelectedChange) {
	

         
     }
	 else if(change==ItemScenePositionHasChanged)
	 {
	
		 setData(1,value);
	 }
     return QGraphicsItem::itemChange(change, value);
 }
int CrossPoint::type() const
{
    return UserType + 1;
}