#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsObject>
#include <qpainter.h>
#include <qpen.h>
#include <qdebug.h>
class GridItem : public QGraphicsObject
{
	Q_OBJECT
    enum RulerTraits{
			RULER_ORIGIN=1,
			STEP_HALF_CM=5,
			STEP_CM=10,
			PEN_THIN=1,
			PEN_FAT=3
	} _RulerTraits;



public:
	GridItem(QGraphicsObject *parent=0);
	~GridItem();
	void setBoardPhisicalSize(const QSize& size);
private:
	QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void drawHorizRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash=3);
	void drawVertRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash=3);
	void drawGridLegend(QPainter *painter);
	void calculatePixelInMm();
private:
	QPen pen_thin;
	QPen pen_fat;
	QSize pixel_in_mm;
	QSize phisicalSize;
public:
	QSize pixelInMM();
	int type() const;
};

#endif // GRIDITEM_H
