#ifndef BIGCROSS_H
#define BIGCROSS_H
#pragma warning( disable : 4482 )
#include <QGraphicsObject>
#include <QPainter>
struct CrossDimention{
	int dX1;
	int dX2;
	int dY1;
	int dY2;
};

class BigCross : public QGraphicsObject
{
	Q_OBJECT
		enum BigCrossBoundingRect{
			LEFT=-1500,
			TOP=-1500,
			WIDTH=3000,
			HEIGHT=3000
	}_BigCrossBoundingRect;
public:
	BigCross();
	BigCross(QGraphicsItem *parent,const QRectF& boardImgRect);
	BigCross(const QRectF& boardImgRect);
	~BigCross();
	void	setCrossDimention(const CrossDimention& cross_dimention);
private:
	QRectF bounding_rect;


	CrossDimention cross_dimention;
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 

};

#endif // BIGCROSS_H
