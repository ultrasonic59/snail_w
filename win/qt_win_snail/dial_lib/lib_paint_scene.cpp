#include <Qdebug>
#include <QFont>
#include <QMenu>
#include <QMessageBox>
#include <QPoint>

///#include <QGraphicsItem>

#include "lib_paint_scene.h"


LibPaintScene::LibPaintScene(QObject* parent, PlotProperties* Plot_Prop
    , en_item_tipe* item_tipe , en_rej* _rej ) : QGraphicsScene(parent), pPlot_Prop(Plot_Prop) ,p_item_tipe(item_tipe),p_rej(_rej)
    ,cur_rect(0,0,40,40), rect_color(Qt::darkCyan),cur_frect(0, 0, 40, 40),frect_color(Qt::cyan),cur_line(0, 0, 40, 40)
    ,line_color(Qt::darkCyan), line_thick(2),circle_rad(20),circle_thick(4),circle_color(Qt::darkMagenta), sel_item(nullptr)

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
    sel_item = nullptr;
}

void LibPaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    qreal cur_x= event->scenePos().x();
    qreal cur_y= event->scenePos().y();
    quint32 num_x= cur_x/ pPlot_Prop->lib_grid_delt_x;
    quint32 num_y = cur_y / pPlot_Prop->lib_grid_delt_y;
    cur_x = pPlot_Prop->lib_grid_delt_x* num_x;
    cur_y = pPlot_Prop->lib_grid_delt_y * num_y;

    sel_item = this->itemAt(event->scenePos(), QTransform());

    if (event->button() == Qt::LeftButton)
    {
        mousePressedLeft = true;

        if (*p_rej == REJ_SELECT)
           {
  ///         QGraphicsItem* item = scene.itemAt(mapToScene(event->pos()), QTransform());
          ////  sel_item = this->itemAt(event->scenePos(), QTransform());
        ////    this->setCursor(QCursor(Qt::ClosedHandCursor));
        ///    this->setCursor(QCursor(Qt::ArrowCursor));

           /// qDebug() << "item" << item;
           }
        else if (*p_rej == REJ_PLACE)
        {
            switch (*p_item_tipe)
            {
            case RECT_TYPE:
            ////    addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, QPen(Qt::NoPen), QBrush(rect_color));
                rc_item = addRect(0, 0, cur_rect.width(), cur_rect.height(), QPen(rect_color, line_thick, Qt::SolidLine, Qt::RoundCap));
                rc_item->setPos(cur_x, cur_y);
                break;
            case FRECT_TYPE:
                rc_item = addRect(0, 0, cur_rect.width(), cur_rect.height(), QPen(Qt::black, line_thick, Qt::SolidLine, Qt::RoundCap), QBrush(rect_color));
                rc_item->setPos(cur_x, cur_y);
                break;
            case VLINE_TYPE:
                addLine(event->scenePos().x(),
                    event->scenePos().y(),
                    event->scenePos().x(),
                    cur_line.y2(),
                    QPen(line_color, line_thick, Qt::SolidLine, Qt::RoundCap));
                break;
            case HLINE_TYPE:
                /*
                addLine(event->scenePos().x(),
                    event->scenePos().y(),
                    cur_line.x2(),
                    event->scenePos().y(),
                    QPen(line_color, line_thick, Qt::SolidLine, Qt::RoundCap));
                */
                line_item = addLine(0,
                    0,
                    cur_line.x2(),
                    0,
                    QPen(line_color, line_thick, Qt::SolidLine, Qt::RoundCap));
                line_item->setPos(cur_x, cur_y);

                break;
            case CIRCLE_TYPE:
                addEllipse(event->scenePos().x(),
                    event->scenePos().y(),
                    circle_rad,
                    circle_rad,
                    QPen(Qt::NoPen),
                    QBrush(rect_color));
                break;
            }
        }
      update();
    }
   if (event->button() == Qt::RightButton)
    {
        currPoint = event->screenPos();
        qDebug() << "currPoint:" << currPoint;

 ///       QPoint t_QPoint = event->screenPos().toPoint();
  ///      qDebug() << "t_QPoint" << pos;/// t_QPoint;
  ///      qDebug() << "sel_rc" << sel_rect;

        QMenu menu;
        QAction* pact;
        QAction* prop = menu.addAction(QString("Property"));
    ////    menu.addSection("Add");
        menu.addSeparator();
        QAction* remove = menu.addAction(QString("Remove"));
        QAction* copy = menu.addAction(QString("Copy"));
        QAction* paste = menu.addAction(QString("Paste"));
        ////       QPointF t_QPointF = event->screenPos();

         ////      const QPoint t_QPoint = t_QPointF.toPoint();
        pact = menu.exec(event->screenPos());
#if 1
 ///       if (a2 == menu.exec(event->screenPos())) {
        if (prop == pact) {
            property(sel_item);
           //// test1();
            //// _selected = true;
            update();
        }
        else if (remove == pact) {
            if (sel_item) {
                removeItem(sel_item);
                update();
            }
        }

#endif
    }

/*
   void removeItem(QGraphicsItem * item);

   QGraphicsItem* focusItem() const;
   void setFocusItem(QGraphicsItem * item, Qt::FocusReason focusReason = Qt::OtherFocusReason);
*/
 ///  QGraphicsItem* sel_item
///===============================================

  }
void LibPaintScene::property(QGraphicsItem* _item) {
 ///   _item->sceneBoundingRect();
qDebug()<<"sceneBoundingRect"<< _item->sceneBoundingRect();
  ///    QMessageBox::information(nullptr, "test1", "test1");
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
    qreal cur_x = event->scenePos().x();
    qreal cur_y = event->scenePos().y();
    quint32 num_x = cur_x / pPlot_Prop->lib_grid_delt_x;
    quint32 num_y = cur_y / pPlot_Prop->lib_grid_delt_y;
    cur_x = pPlot_Prop->lib_grid_delt_x * num_x;
    cur_y = pPlot_Prop->lib_grid_delt_y * num_y;

    if (*p_rej == REJ_SELECT)
    {

        if (mousePressedLeft)
        {
            if (sel_item)
            {
                sel_item->setPos(cur_x, cur_y);
                update();

            }
        }
    }
#if 0
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
#endif
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
  ////dashes << 4 << 4 << 4 << 4;

    QPen pen;
 ////   pen.setColor(QColor(60, 60, 60));
    pen.setColor( pPlot_Prop->LibGridColor );
    pen.setWidth(1);
    pen.setDashPattern(dashes);

    painter->setPen(pen);
    qreal left = rect.left();
    qreal right = rect.right();
  ///  painter->fillRect(rect, Qt::darkGray);
    painter->fillRect(rect, pPlot_Prop->LibBGColor);

    for (int i = left; i < right; i += pPlot_Prop->lib_grid_delt_x)
    {
        painter->drawLine(left, i, right, i);
    }
    for (int i = left; i < right; i += pPlot_Prop->lib_grid_delt_y)
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