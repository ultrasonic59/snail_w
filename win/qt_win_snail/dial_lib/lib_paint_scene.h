#ifndef LIBPAINTSCENE_H
#define LIBPAINTSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <QTimer>
#include <QDebug>
#include <QPainter>
#include "PlotProperties.h"
#include "snail_types.h"
#if 1
enum ActionTypes {
    _DefaultType,
    VLineType,
    HLineType,
    RectangleType,
    CircleType,
    SelectionType
};
#endif

class LibPaintScene : public QGraphicsScene
{

Q_OBJECT

///Q_PROPERTY(int currentAction READ currentAction WRITE setCurrentAction NOTIFY currentActionChanged)
///Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit LibPaintScene(QObject* parent = 0, PlotProperties* Plot_Prop = 0, en_item_tipe* item_tipe=0, en_rej* _rej=0);
    ~LibPaintScene();
///=======================================================
public:
   int currentAction() const;
   QPointF previousPosition() const;
   void setCurrentAction(const int type);
   void setPreviousPosition(const QPointF previousPosition);

signals:
   void previousPositionChanged();
   void currentActionChanged(int);
   void signalSelectItem(QGraphicsItem* item);
   void signalNewSelectItem(QGraphicsItem* item);

///=======================================================
public:
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
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void property(QGraphicsItem* _item);
     void test1();
    void test2();
///================================================
private slots:
   void deselectItems();

public slots:
    void slotMove(QGraphicsItem* signalOwner, qreal dx, qreal dy);

private:
    QGraphicsItem* currentItem;
    int m_currentAction;
    int m_previousAction;
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;

};

#endif // LIBPAINTSCENE_H
