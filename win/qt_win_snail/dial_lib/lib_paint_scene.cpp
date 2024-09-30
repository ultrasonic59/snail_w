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
    , en_item_type* item_type , en_rej* _rej ) : QGraphicsScene(parent), pPlot_Prop(Plot_Prop) ,p_item_type(item_type),p_rej(_rej)
    ,cur_rect(0,0,40,40), rect_color(Qt::darkCyan),cur_frect(0, 0, 40, 40),frect_color(Qt::cyan),cur_line(0, 0, 40, 40)
    ,line_color(Qt::darkCyan), line_thick(2),circle_rad(20),circle_thick(4),circle_color(Qt::darkMagenta), sel_item(nullptr)
    ,currentItem(nullptr)
    ,m_currentAction(0)
    ,m_previousAction(0)
    ,m_leftMouseButtonPressed(false)


{
 ///   QBrush(Qt::yellow)
 ////   setBackgroundBrush(QBrush(Qt::yellow));
}

LibPaintScene::~LibPaintScene()
{

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
          VERectangle* rectangle = new VERectangle();

    if (event->button() == Qt::LeftButton)
    {
        mousePressedLeft = true;
    if (*p_rej == REJ_PLACE)
    {
        switch (*p_item_type)
        {
        case RECT_TYPE:
////            VERectangle* rectangle = new VERectangle(0, 0, cur_rect.width(), cur_rect.height(), QPen(rect_color, line_thick, Qt::SolidLine, Qt::RoundCap));
      ////      VERectangle* rectangle = new VERectangle();
            currentItem = rectangle;
            addItem(currentItem);
            connect(rectangle, &VERectangle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(rectangle, &VERectangle::signalMove, this, &LibPaintScene::slotMove);
            rectangle->setRect(0, 0, cur_rect.width(), cur_rect.height());
            rectangle-> setPos(cur_x, cur_y);
            emit signalNewSelectItem(rectangle);

            ////    addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, QPen(Qt::NoPen), QBrush(rect_color));
            ///rc_item = addRect(0, 0, cur_rect.width(), cur_rect.height(), QPen(rect_color, line_thick, Qt::SolidLine, Qt::RoundCap));
            ///rc_item->setPos(cur_x, cur_y);
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

 ///   }

#if 0
    if (event->button() & Qt::LeftButton) {
        m_leftMouseButtonPressed = true;
        setPreviousPosition(event->scenePos());
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            m_previousAction = m_currentAction;
            setCurrentAction(SelectionType);
        }
    }
    switch (m_currentAction) {
    case HLineType: {
        if (m_leftMouseButtonPressed && !(event->button() & Qt::RightButton) && !(event->button() & Qt::MiddleButton)) {
            deselectItems();
            VEPolyline* polyline = new VEPolyline();
            currentItem = polyline;
            addItem(currentItem);
            connect(polyline, &VEPolyline::clicked, this, &LibPaintScene::signalSelectItem);
            connect(polyline, &VEPolyline::signalMove, this, &LibPaintScene::slotMove);
            QPainterPath path;
            path.moveTo(m_previousPosition);
            polyline->setPath(path);
            emit signalNewSelectItem(polyline);
        }
        break;
    }
    case RectangleType: {
        if (m_leftMouseButtonPressed && !(event->button() & Qt::RightButton) && !(event->button() & Qt::MiddleButton)) {
            deselectItems();
            VERectangle* rectangle = new VERectangle();
            currentItem = rectangle;
            addItem(currentItem);
            connect(rectangle, &VERectangle::clicked, this, &LibPaintScene::signalSelectItem);
            connect(rectangle, &VERectangle::signalMove, this, &LibPaintScene::slotMove);
            emit signalNewSelectItem(rectangle);
        }
        break;
    }
    case SelectionType: {
        if (m_leftMouseButtonPressed && !(event->button() & Qt::RightButton) && !(event->button() & Qt::MiddleButton)) {
            deselectItems();
            VESelectionRect* selection = new VESelectionRect();
            currentItem = selection;
            addItem(currentItem);
        }
        break;
    }
    default: {
        QGraphicsScene::mousePressEvent(event);
        break;
    }
    }
#endif
}

void LibPaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
#if 1
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
#if 0

void LibPaintScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    switch (m_currentAction) {
    case LineType:
    case RectangleType:
    case SelectionType:
        break;
    default:
        QGraphicsScene::mouseDoubleClickEvent(event);
        break;
    }
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

///===============================================

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
}
#endif

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
