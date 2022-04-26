#include"snail.h"
#include "qscaledgraphview.h"

#include <QWheelEvent>
#include <QTimeLine>
#include <QResizeEvent>
QScaledGraphView::QScaledGraphView(QWidget *parent)
	: QGraphicsView(parent)
{
	setTransformationAnchor(QGraphicsView::NoAnchor);
	setResizeAnchor(QGraphicsView::NoAnchor);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	_numScheduledScalings=0;
	gridScene=new GridScene(this);
	setScene(gridScene);
}

QScaledGraphView::~QScaledGraphView()
{

}
void QScaledGraphView::wheelEvent(QWheelEvent* event)
{
	if (!(event->modifiers() & Qt::ControlModifier)) return;
	wheelEventMousePos = event->pos();

	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15; // see QWheelEvent documentation
	_numScheduledScalings += numSteps;
	if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
		_numScheduledScalings = numSteps;

	QTimeLine *anim = new QTimeLine(350, this);
	anim->setUpdateInterval(20);

	connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
	connect(anim, SIGNAL (finished()), SLOT (animFinished()));
	anim->start();
}

void QScaledGraphView::scalingTime(qreal x)
{
	QPointF oldPos = mapToScene(wheelEventMousePos);

	qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
	scale(factor, factor);

	QPointF newPos = mapToScene(wheelEventMousePos);
	QPointF delta = newPos - oldPos;
	this->translate(delta.x(), delta.y());
}

void QScaledGraphView::animFinished()
{
	if (_numScheduledScalings > 0)
		_numScheduledScalings--;
	else
		_numScheduledScalings++;

	sender()->~QObject();
}
void QScaledGraphView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);


}
void QScaledGraphView::ScaleView(qreal factor)
{
    QMatrix matrix = this->matrix();
    qreal currTx = 0.0, currTy = 0.0;
    matrix.map(1.0, 1.0, &currTx, &currTy); 
    double currentFactor = (currTx + currTy) * 0.5;

    qreal newTx = 0.0, newTy = 0.0;
    matrix.scale(factor, factor).map(1.0, 1.0, &newTx, &newTy);
    double newFactor = (newTx + newTy) * 0.5;


	if  (((newFactor >= 0.07) && (newFactor <= 100.0))||
        ((currentFactor < 0.07) && (newFactor > currentFactor)) ||
        ((currentFactor > 100.0) && (newFactor < currentFactor))) 
    {
        scale(factor, factor);
        emit SetZoomText(factor);
    }
}
