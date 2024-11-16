#pragma once
#include <QWidget>
#include <QtWidgets/QtWidgets>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QWheelEvent>

#include <QTimer>

class LibGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LibGraphicView(QWidget* parent = 0);
    ~LibGraphicView();

signals:
    void zoom_chnged(double);
protected:
    void enterEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent* event) override;

private slots:
 ///   void slotAlarmTimer();  
 private:
    QGraphicsScene* scene;     // 
 ///   QGraphicsItemGroup* group_1;   //
 ///   QGraphicsItemGroup* group_2;   // 

     QTimer* timer;

private:
     void resizeEvent(QResizeEvent* event);
///    void deleteItemsFromGroup(QGraphicsItemGroup* group_1);
};
