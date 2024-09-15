#pragma once
#include <QWidget>
#include <QtWidgets/QtWidgets>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

class LibGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LibGraphicView(QWidget* parent = 0);
    ~LibGraphicView();

////signals:

private slots:
    void slotAlarmTimer();  
 private:
    QGraphicsScene* scene;     // 
    QGraphicsItemGroup* group_1;   //
    QGraphicsItemGroup* group_2;   // 

     QTimer* timer;

private:
     void resizeEvent(QResizeEvent* event);
    void deleteItemsFromGroup(QGraphicsItemGroup* group_1);
};
