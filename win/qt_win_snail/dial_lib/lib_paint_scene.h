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
#include "cust_rect.h"
#include "cust_circle.h"
///#include "cust_point.h"

class LibPaintScene : public QGraphicsScene
{

Q_OBJECT

///Q_PROPERTY(int currentAction READ currentAction WRITE setCurrentAction NOTIFY currentActionChanged)
///Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit LibPaintScene(QObject* parent = 0, en_item_type* item_tipe=0, en_rej* _rej=0);
    ~LibPaintScene();
///=======================================================
public:
    bool on_background;
   int currentAction() const;
   QPointF previousPosition() const;
   void setCurrentAction(const int type);
   void setPreviousPosition(const QPointF previousPosition);

signals:
   void previousPositionChanged();
   void currentActionChanged(int);
   void signalSelectItem(QGraphicsItem* item);
   void signalNewSelectItem(QGraphicsItem* item);
   void signalPress(QPointF pnt);
   void signalMove(QPointF pnt);
   ///=======================================================
public:
    en_item_type* p_item_type;
    en_rej*       p_rej;
    QPointF      rule_beg;
    QPointF      rule_end;

private:
    bool _mousePressedLeft;
    bool _mousePressedRight;
    void drawBackground(QPainter* painter, const QRectF& rect);
    PlotProperties* pPlot_Prop;
private:
 ///   QGraphicsItem* sel_item;

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
    void sl_place_rect(quint16 width, quint16 height, QPoint point, QBrush br, QColor color, quint8 thick);

private:
    QGraphicsItem* currentItem;
    int m_currentAction;
    int m_previousAction;
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    bool m_altPressed;

};

#endif // LIBPAINTSCENE_H
