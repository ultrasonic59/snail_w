#include "lib_paint_scene.h"

LibPaintScene::LibPaintScene(QObject* parent) : QGraphicsScene(parent)
{

}

LibPaintScene::~LibPaintScene()
{

}
void LibPaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    ////   plotterwidget::mouseReleaseEvent(event);
    mousePressedLeft = false;
}

void LibPaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    ///   point_data_t t_point_data;
 ////   QPoint pos = event->pos();
    ////t_point_data.coord.setX(cur_x);
    if (event->button() == Qt::LeftButton)
    {
        mousePressedLeft = true;

        // При нажатии кнопки мыши отрисовываем эллипс
        addEllipse(event->scenePos().x() - 5,
            event->scenePos().y() - 5,
            10,
            10,
            QPen(Qt::NoPen),
            QBrush(Qt::red));
        // Сохраняем координаты точки нажатия
        previousPoint = event->scenePos();

#if 0
        mousePressed = true;
        curX1 = event->pos().x();
        curY1 = event->pos().y();

        if (event->modifiers() == Qt::ShiftModifier)
        {
            ///           t_point_data.coord = pos;
            emit sSetPoint(&pos);
        }
        else if (event->modifiers() == Qt::ControlModifier)
        {
            ///     t_point_data.coord = pos;
            ///     emit sSetPoint(&t_point_data);
            emit sClrPoint(&pos);
        }
#endif
    }
    if (event->button() == Qt::RightButton)
    {
#if 0
        QPoint t_QPoint = event->screenPos().toPoint();
        qDebug() << "t_QPoint" << pos;/// t_QPoint;
        qDebug() << "sel_rc" << sel_rect;

        QMenu menu;
        QAction* a1 = menu.addAction(QString("Clear"));
        QAction* a2 = menu.addAction(QString("Move"));
        ////       QPointF t_QPointF = event->screenPos();

         ////      const QPoint t_QPoint = t_QPointF.toPoint();

        if (a2 == menu.exec(event->screenPos().toPoint())) {
            test2();
            //// _selected = true;
            update();
        }
#endif
    }

///===============================================

  }

void LibPaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (mousePressedLeft)
    {

        addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
        // Обновляем данные о предыдущей координате
        previousPoint = event->scenePos();
    }
}
