#ifndef CROSSPOINT_H
#define CROSSPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsObject>
#pragma warning( disable : 4482 )
class CrossPoint : public QGraphicsObject
{
	Q_OBJECT
			enum bounding_rect{
			TOP=-7,
			LEFT=-7,
			WIDTH=80,
			HEIGHT=14
	} _br;

public:
	CrossPoint();
	~CrossPoint();
signals:

	void signalDblClick();
protected:

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	QPointF display_coordinate;

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 

public:
	void setDisplayCoordinate(const QPointF& coord);
	int type() const;

};

#endif // MYPOINT_H
