#ifndef LIBPAINTSCENE_H
#define LIBPAINTSCENE_H
///#include <QtWidgets/QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>

class LibPaintScene : public QGraphicsScene
{

Q_OBJECT

public:
    explicit LibPaintScene(QObject* parent = 0);
    ~LibPaintScene();

private:
    QPointF     previousPoint;      // Координаты предыдущей точки
    bool mousePressedLeft;
    bool mousePressedRight;
    void drawBackground(QPainter* painter, const QRectF& rect);

private:
     void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
    void test1();
    void test2();

};

#endif // LIBPAINTSCENE_H
