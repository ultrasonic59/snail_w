////#pragma once
#ifndef __MYITEM_H__
#define __MYITEM_H__

#include <QPainter>
#include <QGraphicsItem>

// class for customization
class MyItem :public QGraphicsItem
{
public:
    MyItem();

    QRectF boundingRect() const;

    // overriding paint()
    void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget);

    // item state
    bool Pressed;
protected:
    // overriding mouse events
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

#endif // __MYITEM_H__