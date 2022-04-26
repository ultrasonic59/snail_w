#ifndef QSCALEDGRAPHVIEW_H
#define QSCALEDGRAPHVIEW_H

#include <QGraphicsView>
#include<qpoint.h>
#include "gridscene.h"
class QScaledGraphView : public QGraphicsView
{
	 Q_OBJECT

private:
    qreal _numScheduledScalings;
    QPoint wheelEventMousePos;


public:
	QScaledGraphView(QWidget *parent=0);
	~QScaledGraphView();
	void ScaleView(qreal qFactor);
public:
		GridScene *gridScene;
protected:
	void resizeEvent(QResizeEvent *event);
	void wheelEvent(QWheelEvent* event);
signals:
	void SetZoomText(qreal factor);
public slots:
   
    void scalingTime(qreal x);
    void animFinished();
};

#endif // QSCALEDGRAPHVIEW_H
