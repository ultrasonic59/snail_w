#ifndef __CUST_GROUP_H__
#define __CUST_GROUP_H__

#include <QObject>
#include <QGraphicsItemGroup>

#define NUM_CORNERS 4

///class DotSignal;
class QGraphicsSceneMouseEvent;

class cust_group : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit cust_group(QObject * parent = 0);
    ~cust_group();

    enum CornerFlags {
        Top = 0x01,
        Bottom = 0x02,
        Left = 0x04,
        Right = 0x08///,
    };

    enum CornerGrabbers {
        GrabberTop = 0,
        GrabberBottom,
        GrabberLeft,
        GrabberRight///,
     };

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);

 ///   void setRect(qreal x, qreal y, qreal w, qreal h);
 ///   void setRect(const QRectF &rect);
 ///   void setCircle(qreal x, qreal y, qreal diam);

signals:
    void groupChanged(cust_group* rect);
    void previousPositionChanged();
    void clicked(cust_group* rect);
    void signalMove(QGraphicsItem *item, qreal dx, qreal dy);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
 ///   QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    unsigned int m_cornerFlags;
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    ///DotSignal *cornerGrabber[NUM_CORNERS];

 ///   void resizeLeft( const QPointF &pt);
  ///  void resizeRight( const QPointF &pt);
 ///   void resizeBottom(const QPointF &pt);
  ///  void resizeTop(const QPointF &pt);

 ///    void setPositionGrabbers();
  ///  void setVisibilityGrabbers();
  ///  void hideGrabbers();
};

#endif // __CUST_GROUP_H__
