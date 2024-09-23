#ifndef LIBPAINTSCENE_H
#define LIBPAINTSCENE_H
///#include <QtWidgets/QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
///#include <QGraphicsView>
///#include <QGraphicsScene>
///#include <QGraphicsItemGroup>
#include <QGraphicsItem>

#include <QTimer>
#include <QDebug>
#include <QPainter>
#include "PlotProperties.h"
#include "snail_types.h"

class LibPaintScene : public QGraphicsScene
{

Q_OBJECT

public:
    explicit LibPaintScene(QObject* parent = 0, PlotProperties* Plot_Prop = 0, en_item_tipe* item_tipe=0, en_rej* _rej=0);
    ~LibPaintScene();


    en_item_tipe* p_item_tipe;
    en_rej* p_rej;
private:
    QPointF     previousPoint;      //
    QPointF     currPoint;      //
    bool mousePressedLeft;
    bool mousePressedRight;
    void drawBackground(QPainter* painter, const QRectF& rect);
    PlotProperties* pPlot_Prop;
private:
    QGraphicsItem* sel_item;
    QGraphicsRectItem* rc_item;
    QRect cur_rect;
    QColor rect_color;
    QRect cur_frect;
    QColor frect_color;
    QGraphicsLineItem* line_item;
    QLine cur_line;
    QColor line_color;
    quint16 line_thick;

    quint16 circle_rad;
    quint16 circle_thick;
    QColor circle_color;

private:
     void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
    void property(QGraphicsItem* _item);
        ///void addRect();
    void test1();
    void test2();

};

#endif // LIBPAINTSCENE_H
