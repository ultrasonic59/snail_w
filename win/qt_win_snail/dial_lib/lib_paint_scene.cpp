#include <Qdebug>
#include <QFont>
#include <QMenu>
#include <QMessageBox>
#include <QPoint>

#include "lib_paint_scene.h"

LibPaintScene::LibPaintScene(QObject* parent) : QGraphicsScene(parent)
{
 ///   QBrush(Qt::yellow)
 ////   setBackgroundBrush(QBrush(Qt::yellow));
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
        update();


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

 ///       QPoint t_QPoint = event->screenPos().toPoint();
  ///      qDebug() << "t_QPoint" << pos;/// t_QPoint;
  ///      qDebug() << "sel_rc" << sel_rect;

        QMenu menu;
        QAction* pact;

        QAction* a1 = menu.addAction(QString("Clear"));
        QAction* a2 = menu.addAction(QString("Move"));
        ////       QPointF t_QPointF = event->screenPos();

         ////      const QPoint t_QPoint = t_QPointF.toPoint();
        pact = menu.exec(event->screenPos());
#if 1
 ///       if (a2 == menu.exec(event->screenPos())) {
        if (a1 == pact) {
            test1();
            //// _selected = true;
            update();
        }
        else if (a2 == pact) {
            test2();
            //// _selected = true;
            update();
        }

#endif
    }

///===============================================

  }
void LibPaintScene::test1() {
    QMessageBox::information(nullptr, "test1", "test1");
}

void LibPaintScene::test2() {
    QMessageBox::information(nullptr, "test2", "test2");
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
        update();

    }
}
///===========================================================
#if 0
QPolygonF myPolygon1;
myPolygon1 << QPointF(0, 10) << QPointF(20, 10);
QPolygonF myPolygon2;
myPolygon2 << QPointF(10, 0) << QPointF(10, 20);
QPixmap pixmap(20, 20);
pixmap.fill(Qt::transparent);
QPainter painter(&pixmap);

QVector<qreal> dashes;//Line style - dashed line  
qreal space = 2;
dashes << 2 << space << 2 << space;
QPen pen(Qt::lightGray, 1);
pen.setDashPattern(dashes);
pen.setWidth(1);

painter.setPen(pen);
painter.translate(0, 0);
painter.drawPolyline(myPolygon1);
painter.drawPolyline(myPolygon2);
this->setBackgroundBrush(pixmap); */

QPolygonF mypolygon1, mypolygon2;
mypolygon1 << QPointF(0, 5) << QPointF(10, 5);
mypolygon2 << QPointF(5, 0) << QPointF(5, 10);
QPixmap pix(10, 10);
pix.fill(Qt::transparent);
QPainter painter(&pix);
QVector <qreal> dashes;
dashes << 2 << 2 << 2 << 2;
QPen pen(Qt::darkCyan, 0.2);
pen.setDashPattern(dashes);
painter.setPen(pen);
painter.translate(0, 0);
painter.drawPolyline(mypolygon1);
painter.drawPolyline(mypolygon2);
this->setBackgroundBrush(pix);

void CustomQGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    int step = GRID_STEP;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    // draw horizontal grid
    qreal start = round(rect.top(), step);
    if (start > rect.top()) {
        start -= step;
    }
    for (qreal y = start - step; y < rect.bottom(); ) {
        y += step;
        painter->drawLine(rect.left(), y, rect.right(), y);
    }
    // now draw vertical grid
    start = round(rect.left(), step);
    if (start > rect.left()) {
        start -= step;
    }
    for (qreal x = start - step; x < rect.right(); ) {
        x += step;
        painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}

#endif
///===========================================================

void LibPaintScene::drawBackground(QPainter* painter, const QRectF& rect)
{
////    Q_UNUSED(rect);
    QVector <qreal> dashes;
    dashes << 2 << 2 << 2 << 2;

    QPen pen;
    pen.setColor(QColor(60, 60, 60));
    pen.setWidth(1);
    pen.setDashPattern(dashes);

    painter->setPen(pen);
    qreal left = rect.left();
    qreal right = rect.right();
    painter->fillRect(rect, Qt::darkGray);

    for (int i = left; i < right; i += 20)
    {
        painter->drawLine(left, i, right, i);
    }
    for (int i = left; i < right; i += 20)
    {
        painter->drawLine(i, left, i, right);
    }
/*
    for (int i = left; i < 2068; i += 20)
    {
        painter->drawLine(left, i, 2068, i);
    }
    for (int i = left; i < 2068; i += 20)
    {
        painter->drawLine(i, left, i, 2068);
    }
    */
}