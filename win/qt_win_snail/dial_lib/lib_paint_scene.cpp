#include <Qdebug>
#include <QFont>
#include <QMenu>
#include <QMessageBox>
#include <QPoint>

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "cust_rect.h"
#include "veselectionrect.h"
///#include "vepolyline.h"
#include "cust_line.h"

#include "lib_paint_scene.h"
#include "params.h"


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
 ///rc = new VERectangle();
 ////frc = new VERectangle();

 ///   QBrush(Qt::yellow)
 ////   setBackgroundBrush(QBrush(Qt::yellow));
}

LibPaintScene::~LibPaintScene()
{
  ///  delete rc;
  ///  delete frc;

}
///===================================================================
void LibPaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
     QPoint gr_point;
    QPointF ev_point= event->scenePos();

    gr_point = params::closest_to_grid(ev_point);

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
            cust_rect* rect = new cust_rect();
            currentItem = rect;
            addItem(currentItem);
            connect(rect, &cust_rect::clicked, this, &LibPaintScene::signalSelectItem);
            connect(rect, &cust_rect::signalMove, this, &LibPaintScene::slotMove);
            rect->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
            rect->setPos(gr_point);
            rect->setBrush(QBrush(Qt::NoBrush));
            rect->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));
            ///     emit signalNewSelectItem(rc);
        }
            break;
        case FRECT_TYPE: {
            cust_rect* frect = new cust_rect();
            currentItem = frect;
            addItem(currentItem);
            connect(frect, &cust_rect::clicked, this, &LibPaintScene::signalSelectItem);
            connect(frect, &cust_rect::signalMove, this, &LibPaintScene::slotMove);
            frect->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
            frect->setPos(gr_point);
            frect->setBrush(QBrush(QColor(pPlot_Prop->LibItemBGColor)));
            frect->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));
            ///     emit signalNewSelectItem(rc);
        }
            break;
        case VLINE_TYPE: {
            cust_line* line = new cust_line(this);
            currentItem = line;
            addItem(currentItem);
            connect(line, &cust_line::clicked, this, &LibPaintScene::signalSelectItem);
            connect(line, &cust_line::signalMove, this, &LibPaintScene::slotMove);
            line->setLine(0, 0, 0,pPlot_Prop->LibItemWidth);
            line->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick
                , Qt::SolidLine, Qt::RoundCap));
            line->setPos(gr_point);

            /*
            VEPolyline* polyline = new VEPolyline();
            currentItem = polyline;
            addItem(currentItem);
            connect(polyline, &VEPolyline::clicked, this, &LibPaintScene::signalSelectItem);
            connect(polyline, &VEPolyline::signalMove, this, &LibPaintScene::slotMove);
 
            QPainterPath path;
            path.moveTo(m_previousPosition);
            polyline->setPath(path);
            polyline->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick
                , Qt::SolidLine, Qt::RoundCap));
                */
             }
            break;
        case HLINE_TYPE: {
            cust_line* line = new cust_line(this);
            currentItem = line;
            addItem(currentItem);
            connect(line, &cust_line::clicked, this, &LibPaintScene::signalSelectItem);
            connect(line, &cust_line::signalMove, this, &LibPaintScene::slotMove);
            line->setLine(0, 0, pPlot_Prop->LibItemWidth, 0);
            line->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick
                , Qt::SolidLine, Qt::RoundCap));
            line->setPos(gr_point);
        }
            break;
        case CIRCLE_TYPE: {
            cust_circle* circle = new cust_circle();
            currentItem = circle;
            addItem(currentItem);
            connect(circle, &cust_circle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(circle, &cust_circle::signalMove, this, &LibPaintScene::slotMove);
            circle->setCircle(0, 0, pPlot_Prop->LibItemWidth);
            circle->setPos(gr_point.x()- pPlot_Prop->LibItemWidth/2, gr_point.y()- pPlot_Prop->LibItemWidth/2);
            circle->setBrush(QBrush(Qt::NoBrush));
            circle->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));
         }
            break;
        case POINT_TYPE: {
            cust_circle* circle = new cust_circle();
            currentItem = circle;
            addItem(currentItem);
            connect(circle, &cust_circle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(circle, &cust_circle::signalMove, this, &LibPaintScene::slotMove);
            ///            cyrcle->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
            circle->setCircle(0, 0, pPlot_Prop->LibItemWidth);
            circle->setPos(gr_point.x() - pPlot_Prop->LibItemWidth / 2, gr_point.y() - pPlot_Prop->LibItemWidth / 2);
            circle->setBrush(QBrush(Qt::NoBrush));
            circle->setBrush(QBrush(pPlot_Prop->LibItemBrdColor));

            circle->setPen(QPen(pPlot_Prop->LibItemBrdColor, pPlot_Prop->LibItemBrdThick));

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
                cust_rect* rectangle = qgraphicsitem_cast<cust_rect*>(currentItem);
                rectangle->setRect((dx > 0) ? m_previousPosition.x() : event->scenePos().x(),
                    (dy > 0) ? m_previousPosition.y() : event->scenePos().y(),
                    qAbs(dx), qAbs(dy));
            }
            break;
        case VLINE_TYPE: {
            /*
            if (m_leftMouseButtonPressed) {
                VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(currentItem);
                QPainterPath path;
                path.moveTo(m_previousPosition);
                path.lineTo(event->scenePos());
                polyline->setPath(path);

             }
             */
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
#if 0
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

 ///   for (int i = left; i < right; i += pPlot_Prop->lib_grid_delt_x)
   for (int i = left; i < right; i += params::lib_grid_delt_x)
        {
        painter->drawLine(left, i, right, i);
    }
///    for (int i = left; i < right; i += pPlot_Prop->lib_grid_delt_y)
    for (int i = left; i < right; i += params::lib_grid_delt_y)
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
#endif
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
