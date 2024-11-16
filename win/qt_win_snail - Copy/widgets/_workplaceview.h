#ifndef __WORKPLACEVIEW_H__
#define __WORKPLACEVIEW_H__

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>

class WorkplaceView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorkplaceView(QWidget *parent = 0);

protected:
    void enterEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
protected:
    void wheelEvent(QWheelEvent* event) override;

///signals:

///public slots:
};

#endif // __WORKPLACEVIEW_H__
