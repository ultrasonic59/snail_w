#include <Qdebug>
#include <QFont>
#include <QMenu>
#include <QMessageBox>
#include <QPoint>

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "verectangle.h"
#include "veselectionrect.h"
#include "vepolyline.h"

#include "lib_paint_scene.h"


LibPaintScene::LibPaintScene(QObject* parent, PlotProperties* Plot_Prop
    , en_item_type* item_type , en_rej* _rej ) : QGraphicsScene(parent)
    , pPlot_Prop(Plot_Prop) ,p_item_type(item_type),p_rej(_rej)
    ,cur_rect(0,0,40,40), rect_color(Qt::darkCyan),cur_frect(0, 0, 40, 40)
    ,frect_color(Qt::cyan),cur_line(0, 0, 40, 40)
    ,line_color(Qt::darkCyan), line_thick(2),circle_rad(20),circle_thick(4)
    ,circle_color(Qt::darkMagenta), sel_item(nullptr)
    ,currentItem(nullptr)
    ,m_currentAction(0)
    ,m_previousAction(0)
    ,m_leftMouseButtonPressed(false)
{
 rc = new VERectangle();
 frc = new VERectangle();

 ///   QBrush(Qt::yellow)
 ////   setBackgroundBrush(QBrush(Qt::yellow));
}

LibPaintScene::~LibPaintScene()
{
    delete rc;
    delete frc;

}
///===================================================================
void LibPaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    qreal cur_x = event->scenePos().x();
    qreal cur_y = event->scenePos().y();
    quint32 num_x = cur_x / pPlot_Prop->lib_grid_delt_x;
    quint32 num_y = cur_y / pPlot_Prop->lib_grid_delt_y;
    cur_x = pPlot_Prop->lib_grid_delt_x * num_x;
    cur_y = pPlot_Prop->lib_grid_delt_y * num_y;

  ///        VERectangle* rectangle = new VERectangle();
   /// VERectangle* rect = new VERectangle();
  ///  VERectangle* frect = new VERectangle();

    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtonPressed = true;
        setPreviousPosition(event->scenePos());
        mousePressedLeft = true;
    if (*p_rej == REJ_PLACE)
    {
        switch (*p_item_type)
        {
        case RECT_TYPE: {
            VERectangle* rect = new VERectangle();
            currentItem = rect;
            addItem(currentItem);
            connect(rect, &VERectangle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(rect, &VERectangle::signalMove, this, &LibPaintScene::slotMove);
            rect->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
            rect->setPos(cur_x, cur_y);
            rect->setBrush(QBrush(Qt::NoBrush));
            rect->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));
            ///     emit signalNewSelectItem(rc);
        }
            break;
        case FRECT_TYPE: {
            VERectangle* frect = new VERectangle();
            currentItem = frect;
            addItem(currentItem);
            connect(frect, &VERectangle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(frect, &VERectangle::signalMove, this, &LibPaintScene::slotMove);
            frect->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
            frect->setPos(cur_x, cur_y);
            frect->setBrush(QBrush(QColor(pPlot_Prop->LibItemBGColor)));
            frect->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));
            ///     emit signalNewSelectItem(rc);
        }
            break;
        case VLINE_TYPE: {
            VEPolyline* polyline = new VEPolyline();
            currentItem = polyline;
            addItem(currentItem);
            connect(polyline, &VEPolyline::clicked, this, &LibPaintScene::signalSelectItem);
            connect(polyline, &VEPolyline::signalMove, this, &LibPaintScene::slotMove);
          ///  polyline->setPos(cur_x, cur_y);

            QPainterPath path;
            path.moveTo(m_previousPosition);
            polyline->setPath(path);
            polyline->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick
                , Qt::SolidLine, Qt::RoundCap));
           ///  emit signalNewSelectItem(polyline);
            }
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
        case CIRCLE_TYPE: {
            cust_circle* circle = new cust_circle();
            currentItem = circle;
            addItem(currentItem);
            connect(circle, &cust_circle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(circle, &cust_circle::signalMove, this, &LibPaintScene::slotMove);
///            cyrcle->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
            circle->setCircle(0, 0, pPlot_Prop->LibItemWidth);
            circle->setPos(cur_x- pPlot_Prop->LibItemWidth/2, cur_y- pPlot_Prop->LibItemWidth/2);
            circle->setBrush(QBrush(Qt::NoBrush));
            circle->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));
            ///     emit signalNewSelectItem(rc);

/*
            addEllipse(event->scenePos().x(),
                event->scenePos().y(),
                circle_rad,
                circle_rad,
                QPen(Qt::NoPen),
                QBrush(rect_color));
*/
        }
            break;
        case POINT_TYPE: {
            cust_point* point = new cust_point();
            currentItem = point;
            addItem(currentItem);
            connect(point, &cust_point::clicked, this, &LibPaintScene::signalSelectItem);
            connect(point, &cust_point::signalMove, this, &LibPaintScene::slotMove);
            point->setCircle(0, 0, pPlot_Prop->LibItemWidth);
            point->setPos(cur_x - pPlot_Prop->LibItemWidth / 2, cur_y - pPlot_Prop->LibItemWidth / 2);
            point->setBrush(QBrush(Qt::NoBrush));
            point->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemWidth ));
        }
            break;
        }
    }
    update();
    }

 ///   }

}

void LibPaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (*p_rej == REJ_PLACE)
    {
        switch (*p_item_type)
        {
        case FRECT_TYPE:
        case RECT_TYPE: {
            if (m_leftMouseButtonPressed) {
                auto dx = event->scenePos().x() - m_previousPosition.x();
                auto dy = event->scenePos().y() - m_previousPosition.y();
                VERectangle* rectangle = qgraphicsitem_cast<VERectangle*>(currentItem);
                rectangle->setRect((dx > 0) ? m_previousPosition.x() : event->scenePos().x(),
                    (dy > 0) ? m_previousPosition.y() : event->scenePos().y(),
                    qAbs(dx), qAbs(dy));
            }
            break;
        case VLINE_TYPE: {
            if (m_leftMouseButtonPressed) {
                VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(currentItem);
                QPainterPath path;
                path.moveTo(m_previousPosition);
                path.lineTo(event->scenePos());
                polyline->setPath(path);

             }
             break;
        }
        }
    }
}
    else
       {
        QGraphicsScene::mouseMoveEvent(event);
       }
#if 0
    switch (m_currentAction) {
    case HLineType: {
        if (m_leftMouseButtonPressed) {
            VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(currentItem);
            QPainterPath path;
            path.moveTo(m_previousPosition);
            path.lineTo(event->scenePos());
            polyline->setPath(path);
        }
        break;
    }
    case RectangleType: {
        if (m_leftMouseButtonPressed) {
            auto dx = event->scenePos().x() - m_previousPosition.x();
            auto dy = event->scenePos().y() - m_previousPosition.y();
            VERectangle* rectangle = qgraphicsitem_cast<VERectangle*>(currentItem);
            rectangle->setRect((dx > 0) ? m_previousPosition.x() : event->scenePos().x(),
                (dy > 0) ? m_previousPosition.y() : event->scenePos().y(),
                qAbs(dx), qAbs(dy));
        }
        break;
    }
    case SelectionType: {
        if (m_leftMouseButtonPressed) {
            auto dx = event->scenePos().x() - m_previousPosition.x();
            auto dy = event->scenePos().y() - m_previousPosition.y();
            VESelectionRect* selection = qgraphicsitem_cast<VESelectionRect*>(currentItem);
            selection->setRect((dx > 0) ? m_previousPosition.x() : event->scenePos().x(),
                (dy > 0) ? m_previousPosition.y() : event->scenePos().y(),
                qAbs(dx), qAbs(dy));
        }
        break;
    }
    default: {
        QGraphicsScene::mouseMoveEvent(event);
        break;
    }
    }
#endif
}

void LibPaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
#if 1
    if (event->button() & Qt::LeftButton) m_leftMouseButtonPressed = false;
    switch (m_currentAction) {
    case HLineType:
    case RectangleType: {
        if (!m_leftMouseButtonPressed &&
            !(event->button() & Qt::RightButton) &&
            !(event->button() & Qt::MiddleButton)) {
            currentItem = nullptr;
        }
        break;
    }
    case SelectionType: {
        if (!m_leftMouseButtonPressed &&
            !(event->button() & Qt::RightButton) &&
            !(event->button() & Qt::MiddleButton)) {
            VESelectionRect* selection = qgraphicsitem_cast<VESelectionRect*>(currentItem);
            if (!selection->collidingItems().isEmpty()) {
                foreach(QGraphicsItem * item, selection->collidingItems()) {
                    item->setSelected(true);
                }
            }
            selection->deleteLater();
            if (selectedItems().length() == 1) {
                signalSelectItem(selectedItems().at(0));
            }
            setCurrentAction(m_previousAction);
            currentItem = nullptr;
        }
        break;
    }
    default: {
        QGraphicsScene::mouseReleaseEvent(event);
        break;
    }
    }
#endif
}
///===================================================================

void LibPaintScene::property(QGraphicsItem* _item) {
    ///   _item->sceneBoundingRect();
    qDebug() << "sceneBoundingRect" << _item->sceneBoundingRect();
    ///    QMessageBox::information(nullptr, "test1", "test1");
}

void LibPaintScene::test1() {
    QMessageBox::information(nullptr, "test1", "test1");
}

void LibPaintScene::test2() {
    QMessageBox::information(nullptr, "test2", "test2");
}

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

///======================================================================
int LibPaintScene::currentAction() const
{
    return m_currentAction;
}

QPointF LibPaintScene::previousPosition() const
{
    return m_previousPosition;
}

void LibPaintScene::setCurrentAction(const int type)
{
    m_currentAction = type;
   emit currentActionChanged(m_currentAction);
}
void LibPaintScene::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}
void LibPaintScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
#if 1
    switch (m_currentAction) {
    case HLineType:
    case RectangleType:
    case SelectionType:
        break;
    default:
        QGraphicsScene::mouseDoubleClickEvent(event);
        break;
    }
#endif
}
void LibPaintScene::deselectItems()
{
    foreach(QGraphicsItem * item, selectedItems()) {
        item->setSelected(false);
    }
    selectedItems().clear();
}
void LibPaintScene::slotMove(QGraphicsItem* signalOwner, qreal dx, qreal dy)
{
    foreach(QGraphicsItem * item, selectedItems()) {
        if (item != signalOwner) item->moveBy(dx, dy);
    }
}
void LibPaintScene::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Delete: {
        foreach(QGraphicsItem * item, selectedItems()) {
            removeItem(item);
            delete item;
        }
        deselectItems();
        break;
    }
    case Qt::Key_A: {
        if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
            foreach(QGraphicsItem * item, items()) {
                item->setSelected(true);
            }
           if (selectedItems().length() == 1) signalSelectItem(selectedItems().at(0));
        }
        break;
    }
    default:
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}
