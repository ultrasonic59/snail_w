#ifndef LIBPAINTSCENE_H
#define LIBPAINTSCENE_H
///#include <QtWidgets/QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include "PlotProperties.h"

class LibPaintScene : public QGraphicsScene
{

Q_OBJECT

public:
    explicit LibPaintScene(QObject* parent = 0, PlotProperties* Plot_Prop = 0);
    ~LibPaintScene();

private:
    QPointF     previousPoint;      //
    QPointF     currPoint;      //
    bool mousePressedLeft;
    bool mousePressedRight;
    void drawBackground(QPainter* painter, const QRectF& rect);
    PlotProperties* pPlot_Prop;

private:
     void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
    void addRect();
        void test1();
    void test2();

};

#endif // LIBPAINTSCENE_H
