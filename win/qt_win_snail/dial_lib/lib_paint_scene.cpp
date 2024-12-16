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
#include "cust_line.h"

#include "lib_paint_scene.h"
#include "params.h"


LibPaintScene::LibPaintScene(QObject* parent
    , en_item_type* item_type , en_rej* _rej ) : QGraphicsScene(parent)
    , p_item_type(item_type),p_rej(_rej)
     ,currentItem(nullptr)
    ,m_currentAction(0)
    ,m_previousAction(0)
    ,m_leftMouseButtonPressed(false)
    , m_altPressed(false)
    ,on_background(false)
{
}

LibPaintScene::~LibPaintScene()
{

}
///if (event->modifiers() == Qt::AltModifier)

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
        if (event->modifiers() == Qt::AltModifier)
            {
            m_altPressed = true;
            rule_beg = ev_point;
            emit signalPress(ev_point);
            cust_line* line = new cust_line(this);
            currentItem = line;
            addItem(currentItem);
            connect(line, &cust_line::signalPress, this, &LibPaintScene::signalSelectItem);
            connect(line, &cust_line::signalMove, this, &LibPaintScene::slotMove);
            line->setPen(QPen(params::RuleColor, params::thick_rule
                , Qt::DashLine, Qt::FlatCap));
             QPainterPath path;
            path.moveTo(gr_point);
////            path.lineTo(gr_point.x(), gr_point.y() + params::LibItemWidth);
            line->setPath(path);
            }
       else
          {
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
                rect->setRect(0, 0, params::LibItemWidth, params::LibItemHeight);
                rect->setPos(gr_point);
                rect->setBrush(QBrush(Qt::NoBrush));
                rect->setPen(QPen(params::LibItemBrdColor, params::LibItemBrdThick));
                ///     emit signalNewSelectItem(rc);
            }
                 break;
            case FRECT_TYPE: {
                cust_rect* frect = new cust_rect();
                currentItem = frect;
                addItem(currentItem);
                connect(frect, &cust_rect::clicked, this, &LibPaintScene::signalSelectItem);
                connect(frect, &cust_rect::signalMove, this, &LibPaintScene::slotMove);
                frect->setRect(0, 0, params::LibItemWidth, params::LibItemHeight);
                frect->setPos(gr_point);
                frect->setBrush(QBrush(QColor(params::LibItemBGColor)));
                frect->setPen(QPen(params::LibItemBrdColor, params::LibItemBrdThick));
                ///     emit signalNewSelectItem(rc);
            }
                 break;
            case VLINE_TYPE: {
                cust_line* line = new cust_line(this);
                currentItem = line;
                addItem(currentItem);
                connect(line, &cust_line::signalPress, this, &LibPaintScene::signalSelectItem);
                connect(line, &cust_line::signalMove, this, &LibPaintScene::slotMove);
                line->setPen(QPen(params::LibItemBrdColor, params::LibItemBrdThick
                    , Qt::SolidLine, Qt::FlatCap));
                ///           , Qt::SolidLine, Qt::RoundCap));
                QPainterPath path;
                path.moveTo(gr_point);
                path.lineTo(gr_point.x(), gr_point.y() + params::LibItemWidth);
                line->setPath(path);
                  }
                  break;
            case HLINE_TYPE: {
                cust_line* line = new cust_line(this);
                currentItem = line;
                addItem(currentItem);
                connect(line, &cust_line::signalPress, this, &LibPaintScene::signalSelectItem);
                connect(line, &cust_line::signalMove, this, &LibPaintScene::slotMove);
                line->setPen(QPen(params::LibItemBrdColor, params::LibItemBrdThick
                    , Qt::SolidLine, Qt::SquareCap));
                ////            , Qt::SolidLine, Qt::RoundCap));
                QPainterPath path;
                path.moveTo(gr_point);
                path.lineTo(gr_point.x() + params::LibItemWidth, gr_point.y());
                line->setPath(path);
                 }
                 break;
            case CIRCLE_TYPE: {
                cust_circle* circle = new cust_circle();
                currentItem = circle;
                addItem(currentItem);
                connect(circle, &cust_circle::clicked, this, &LibPaintScene::signalSelectItem);
                connect(circle, &cust_circle::signalMove, this, &LibPaintScene::slotMove);
                circle->setCircle(0, 0, params::LibItemWidth);
                circle->setPos(gr_point.x() - params::LibItemWidth / 2, gr_point.y() - params::LibItemWidth / 2);
                circle->setBrush(QBrush(Qt::NoBrush));
                circle->setPen(QPen(params::LibItemBrdColor, params::LibItemBrdThick));
            }
                 break;
            case POINT_TYPE: {
                cust_circle* circle = new cust_circle();
                currentItem = circle;
                addItem(currentItem);
                connect(circle, &cust_circle::clicked, this, &LibPaintScene::signalSelectItem);
                connect(circle, &cust_circle::signalMove, this, &LibPaintScene::slotMove);
                ///            cyrcle->setRect(0, 0, pPlot_Prop->LibItemWidth, pPlot_Prop->LibItemHeight);
                circle->setCircle(0, 0, params::LibItemWidth);
                circle->setPos(gr_point.x() - params::LibItemWidth / 2, gr_point.y() - params::LibItemWidth / 2);
                circle->setBrush(QBrush(Qt::NoBrush));
                circle->setBrush(QBrush(params::LibItemBrdColor));
                circle->setPen(QPen(params::LibItemBrdColor, params::LibItemBrdThick));
                 }
                 break;
            }
        }
    }
    update();
    }
}

void LibPaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
QPointF ev_point = event->scenePos();
QPointF ev_delt = QPointF(ev_point.x()- rule_beg.x(), ev_point.y() - rule_beg.y());

/// qDebug() << "LibPaintScene::mouseMoveEvent=" << ev_point<<"alt="<< m_altPressed;
/*
 if (event->modifiers() == Qt::AltModifier)
    {
     if (m_leftMouseButtonPressed)
     {
         emit signalMove(ev_point);
         cust_line* line = qgraphicsitem_cast<cust_line*>(currentItem);
         QPainterPath path;
         path.moveTo(m_previousPosition);
         path.lineTo(event->scenePos());
         line->setPath(path);
     }
    }
 else
     */
 {

 ///   if (event->modifiers() == Qt::AltModifier)
    if (m_altPressed)
        {
        ///if (m_leftMouseButtonPressed)
        {
            emit signalMove(ev_delt);
/*
            cust_line* line = qgraphicsitem_cast<cust_line*>(currentItem);
            QPainterPath path;
            path.moveTo(m_previousPosition);
            path.lineTo(event->scenePos());
            line->setPath(path);
            */
        }
    }
    else 

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
         }
         case VLINE_TYPE:
         case HLINE_TYPE:
         {
             ///   qDebug() << "LibPaintScene mouseMoveEvent " ;
             if (m_leftMouseButtonPressed) {
                 ///VEPolyline* polyline = qgraphicsitem_cast<VEPolyline*>(currentItem);
                 cust_line* line = qgraphicsitem_cast<cust_line*>(currentItem);

                 QPainterPath path;
                 path.moveTo(m_previousPosition);
                 path.lineTo(event->scenePos());
                 line->setPath(path);
             }
             break;
         }

         }
     }
     else
     {
         QGraphicsScene::mouseMoveEvent(event);
     }
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
    if (event->button() & Qt::LeftButton) 
        m_leftMouseButtonPressed = false;
    m_altPressed = false;

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
#if 0
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
#endif
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

void LibPaintScene::sl_test1() {
   sl_place_rect(300, 200, QPoint(10, 20), QBrush(Qt::NoBrush), Qt::red, 2);

    QMessageBox::information(nullptr, "test1", "test1");
}

void LibPaintScene::sl_test2(QString t_str) {
    QMessageBox::information(nullptr, t_str, "test2");
}
void LibPaintScene::sl_test3(char* t_str) {
    QMessageBox::information(nullptr, t_str, "test2");
}

///===========================================================

void LibPaintScene::drawBackground(QPainter* painter, const QRectF& rect)
{
#if 1
    if (on_background)
    {
        painter->save();

        painter->fillRect(rect, QColor(200, 220, 255));

        // Draw a grid
        QPen pen(params::LibGridColor);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        for (int x = rect.left(); x < rect.right(); x += params::lib_grid_delt_x) {
            painter->drawLine(x, rect.top(), x, rect.bottom());
        }
        for (int y = rect.top(); y < rect.bottom(); y += params::lib_grid_delt_y) {
            painter->drawLine(rect.left(), y, rect.right(), y);
        }
        painter->restore();
    }
#endif
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
        if (item != signalOwner) 
            item->moveBy(dx, dy);
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
///============================================================
void LibPaintScene::sl_place_rect(quint16 width, quint16 height, QPoint point, QBrush br, QColor color,quint8 thick)
{
cust_rect* rect = new cust_rect();
currentItem = rect;
addItem(currentItem);
rect->setRect(0, 0, width, height);
rect->setPos(point);
///rect->setBrush(QBrush(Qt::NoBrush));
rect->setBrush( br);
rect->setPen(QPen(color, thick));

}
void LibPaintScene::sl_place_line(quint16 width, quint16 height, QPoint point, QBrush br, QColor color, quint8 thick)
{
    cust_line* line = new cust_line(this);
    currentItem = line;
    addItem(currentItem);
    connect(line, &cust_line::signalPress, this, &LibPaintScene::signalSelectItem);
    connect(line, &cust_line::signalMove, this, &LibPaintScene::slotMove);
    line->setPen(QPen(color, thick, Qt::SolidLine, Qt::FlatCap));
     QPainterPath path;
    path.moveTo(point);
    path.lineTo(point.x(), point.y() + width);
    line->setPath(path);
}
void LibPaintScene::sl_place_circle(quint16 width, quint16 height, QPoint point, QBrush br, QColor color, quint8 thick)
{
    cust_circle* circle = new cust_circle();
    currentItem = circle;
    addItem(currentItem);
    connect(circle, &cust_circle::clicked, this, &LibPaintScene::signalSelectItem);
    connect(circle, &cust_circle::signalMove, this, &LibPaintScene::slotMove);
    circle->setCircle(0, 0, width);
    circle->setPos(point.x() - width/2, point.y() - width/2);
    circle->setBrush(br);
    circle->setPen(QPen(color,thick));
}

void LibPaintScene::sl_place_rect(QPoint point)
{
sl_place_rect(100, 200, point, QBrush(Qt::NoBrush), Qt::red, 3);
 
}
void LibPaintScene::sl_place_item(QString i_str)
{
 ////   sl_place_rect(100, 200, point, QBrush(Qt::NoBrush), Qt::red, 3);
    qDebug() << "sl_place_item " << i_str;

}
void LibPaintScene::sl_obr_cmd(QString i_cmd)
{
       qDebug() << "i_cmd=" << i_cmd;

QJsonDocument doc = QJsonDocument::fromJson(i_cmd.toUtf8());
QJsonObject json = doc.object();
QString type_cmd = json["cmd"].toString();
quint16 width= json["width"].toInt();
quint16 height = json["height"].toInt();
QJsonValue point = json.value("point");
int x;
int y;
if (point.isObject())
   {
    x = point["x"].toInt();
    y = point["y"].toInt();
   }
int br= json["brush"].toInt();
int t_col= json["color"].toInt();
int thick= json["thick"].toInt();
if (type_cmd == "Rect")
   {
    sl_place_rect(width, height, QPoint(x, y), QBrush(br), QColor(t_col), thick);
   }
else if(type_cmd == "Circle")
   {
    sl_place_circle(width, height, QPoint(x, y), QBrush(br), QColor(t_col), thick);
   }
else if (type_cmd == "Line")
  {
    sl_place_line(width, height, QPoint(x, y), QBrush(br), QColor(t_col), thick);
  }
}
