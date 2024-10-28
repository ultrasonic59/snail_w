#ifndef __CUST_LINE_H_
#define __CUST_LINE_H_

#include <QObject>
#include <QGraphicsPathItem>

class DotSignal;
class QGraphicsSceneMouseEvent;

class cust_line : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
  ///  Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit cust_line(QObject *parent = 0);
    ~cust_line();

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);
    void setPath(const QPainterPath &path);

signals:
    void previousPositionChanged();
    void clicked(cust_line *rect);
    void signalMove(QGraphicsItem *item, qreal dx, qreal dy);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

public slots:

private slots:
    void slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy);
    void checkForDeletePoints();

private:
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
  ///  QList<DotSignal *> listDotes;
    int m_pointForCheck;

 ////   void updateDots();
};

#endif // VEPOLYLINE_H
