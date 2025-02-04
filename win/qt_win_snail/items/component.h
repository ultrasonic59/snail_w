#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <QObject>
#include <QGraphicsItemGroup>

#define NUM_CORNERS 4

///class DotSignal;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneEvent;

class component : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit component(QObject * parent = 0);
    ~component();
 
    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);
  ///  QString Name;
    QPointF GetCenter();

signals:
    void groupChanged(component* rect);
    void previousPositionChanged();
    void clicked(component* rect);
    void signalMove(QGraphicsItem *item, qreal dx, qreal dy);

protected:
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  ///  QGraphicsSceneEvent
 ///       void mouseMoveEvent(QGraphicsSceneEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
 ///   QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

public:
  ///  QList<QPointF> red_points;
  ///  QPointF  green_point;

 };

#endif // __CUST_GROUP_H__
