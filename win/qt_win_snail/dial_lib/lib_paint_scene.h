#ifndef LIBPAINTSCENE_H
#define LIBPAINTSCENE_H
///#include <QtWidgets/QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

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

private:
     void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

};

#endif // LIBPAINTSCENE_H
