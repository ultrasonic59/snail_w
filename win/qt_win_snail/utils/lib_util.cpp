#include "lib_util.h"

LibUtil::LibUtil() 
 {
    ///  setAcceptHoverEvents(true);
   ///   setFlags(ItemIsSelectable|ItemSendsGeometryChanges| ItemIsMovable);
  ///  setFlags(ItemIsSelectable | ItemIsMovable);
}

LibUtil::~LibUtil()
{
    ///  for(int i = 0; i < NUM_CORNERS; i++){
    ///      delete cornerGrabber[i];
    ///  }
}


QGraphicsItem* LibUtil::getItem(QJsonObject& itemObj)
{
    QString t_type = itemObj.value("type").toString();
    qDebug() << "type=" << t_type;

    if (t_type == "Rect")
    {
        cust_rect* rect = new cust_rect();
        bool err = false;

        int Width = itemObj.value("width").toInt();
        int Height = itemObj.value("height").toInt();
        rect->setRect(0, 0, Width, Height);
        QJsonObject pointObj = itemObj.value("pos").toObject();
        int xx = pointObj.value("x").toInt();
        int yy = pointObj.value("y").toInt();
        rect->setPos(QPoint(xx, yy));
        QJsonObject brushObj = itemObj.value("brush").toObject();
        QString   str_col = brushObj.value("color").toString();

        quint32 br_color = str_col.toUInt(&err, 16); ////brushObj.value("color").toInt();
        Qt::BrushStyle br_style = (Qt::BrushStyle)brushObj.value("style").toInt();
        rect->setBrush(QBrush(QColor(br_color), br_style));
        QJsonObject penObj = itemObj.value("pen").toObject();
        str_col = penObj.value("color").toString();
        ///bool err = false;
        quint32 pen_color = str_col.toUInt(&err, 16);

        int penWidth = penObj.value("width").toInt();
        rect->setPen(QPen(QColor(pen_color), penWidth));
        return qgraphicsitem_cast<cust_rect*>(rect);
    }
    else if (t_type == "Line")
    {
        cust_line* line = new cust_line();
        bool err = false;
        QJsonObject penObj = itemObj.value("pen").toObject();
        QString   str_col = penObj.value("color").toString();
        quint32 pen_color = str_col.toUInt(&err, 16);

        int penWidth = penObj.value("width").toInt();
        line->setPen(QPen(QColor(pen_color), penWidth));
        QJsonObject p1Obj = itemObj.value("p1").toObject();
        int xx1 = p1Obj.value("x").toInt();
        int yy1 = p1Obj.value("y").toInt();
        QJsonObject p2Obj = itemObj.value("p2").toObject();
        int xx2 = p2Obj.value("x").toInt();
        int yy2 = p2Obj.value("y").toInt();
        line->setLine(xx1, yy1, xx2, yy2);

        return qgraphicsitem_cast<cust_line*>(line);
    }
    else if (t_type == "Circle")
    {
        cust_circle* circle = new cust_circle();
        bool err = false;
        int Width = itemObj.value("width").toInt();
        circle->setCircle(0, 0, Width);
        QJsonObject pointObj = itemObj.value("pos").toObject();
        int xx = pointObj.value("x").toInt();
        int yy = pointObj.value("y").toInt();
        circle->setPos(xx, yy);
        QJsonObject brushObj = itemObj.value("brush").toObject();
        QString   str_col = brushObj.value("color").toString();

        quint32 br_color = str_col.toUInt(&err, 16);
        Qt::BrushStyle br_style = (Qt::BrushStyle)brushObj.value("style").toInt();
        circle->setBrush(QBrush(QColor(br_color), br_style));
        QJsonObject penObj = itemObj.value("pen").toObject();
        str_col = penObj.value("color").toString();
        quint32 pen_color = str_col.toUInt(&err, 16);

        int penWidth = penObj.value("width").toInt();
        circle->setPen(QPen(QColor(pen_color), penWidth));
        return qgraphicsitem_cast<cust_circle*>(circle);
    }
    else
    {
        return nullptr;
        ///    rez = false;
    }
    ///return rez;
}
void LibUtil::insertItem(QGraphicsItem* item, QJsonObject& itemObj)
{
    QJsonObject objObject;

    switch (item->type()) {
    case QGraphicsRectItem::Type: {
        cust_rect* rect = qgraphicsitem_cast<cust_rect*>(item);
        QRectF t_rect = rect->rect();
        qDebug() << "rect=" << t_rect;
        objObject.insert("type", "Rect");
        objObject.insert("width", QJsonValue::fromVariant(t_rect.width()));
        objObject.insert("height", QJsonValue::fromVariant(t_rect.height()));
        QBrush t_br = rect->brush();

        quint32 br_color = t_br.color().rgb();
        int br_style = t_br.style();
        QJsonObject obj2Object;
        obj2Object.insert("color", QString::number(br_color, 16));
        obj2Object.insert("style", QJsonValue::fromVariant(br_style));
        objObject.insert("brush", obj2Object);
        QPen t_pen = rect->pen();
        QJsonObject obj3Object;
        quint32 pen_color = t_pen.color().rgb();
        obj3Object.insert("color", QString::number(pen_color, 16));
        obj3Object.insert("width", QJsonValue::fromVariant(t_pen.width()));
        objObject.insert("pen", obj3Object);
        QJsonObject obj4Object;

        qDebug() << "rect pos" << rect->pos()<< rect->rect();
 ///       qDebug() << "tr=" << rect->transform()<< rect->transform().dx() << rect->transform().dy();

        qreal xx = rect->pos().x() + rect->transform().m31();
        qreal yy = rect->pos().y() + rect->transform().m32();

        obj4Object.insert("x", QJsonValue::fromVariant(xx));
        obj4Object.insert("y", QJsonValue::fromVariant(yy));
        objObject.insert("pos", obj4Object);
        ///   itemObj.insert("rect", objObject);
    }
       break;
    case QGraphicsLineItem::Type: {
        cust_line* line = qgraphicsitem_cast<cust_line*>(item);

        objObject.insert("type", "Line");

        QJsonObject objPen;
        QPen t_pen = line->pen();
        quint32 pen_color = t_pen.color().rgb();

        objPen.insert("color", QString::number(pen_color, 16));

        objPen.insert("width", QJsonValue::fromVariant(t_pen.width()));
        objObject.insert("pen", objPen);

        QJsonObject objP1;
        qreal xx = line->line().p1().x() + line->transform().dx();
        qreal yy = line->line().p1().y() + line->transform().dy();

        objP1.insert("x", QJsonValue::fromVariant(xx));
        objP1.insert("y", QJsonValue::fromVariant(yy));
        objObject.insert("p1", objP1);
        QJsonObject objP2;
        xx = line->line().p2().x() + line->transform().dx();
        yy = line->line().p2().y() + line->transform().dy();

        objP2.insert("x", QJsonValue::fromVariant(xx));
        objP2.insert("y", QJsonValue::fromVariant(yy));
        ///      obj3Object.insert("x", QJsonValue::fromVariant(xx2));
        ///      obj3Object.insert("y", QJsonValue::fromVariant(yy2));

        objObject.insert("p2", objP2);

        ///           itemObj.insert("obj", objObject);
    }
    break;
    case QGraphicsEllipseItem::Type: {
        cust_circle* circle = qgraphicsitem_cast<cust_circle*>(item);
        QRectF t_rect = circle->rect();

        objObject.insert("type", "Circle");
        objObject.insert("width", QJsonValue::fromVariant(t_rect.width()));
        objObject.insert("height", QJsonValue::fromVariant(t_rect.height()));
        QBrush t_br = circle->brush();

        quint32 br_color = t_br.color().rgb();
        int br_style = t_br.style();
        QJsonObject obj2Object;
        obj2Object.insert("color", QString::number(br_color, 16));
        obj2Object.insert("style", QJsonValue::fromVariant(br_style));
        objObject.insert("brush", obj2Object);
        QJsonObject obj3Object;

        QPen t_pen = circle->pen();
        obj3Object.insert("color", QString::number(t_pen.color().rgb(), 16));
        obj3Object.insert("width", QJsonValue::fromVariant(t_pen.width()));
        objObject.insert("pen", obj3Object);
        QJsonObject obj4Object;
        qreal xx = circle->pos().x() + circle->transform().dx();
        qreal yy = circle->pos().y() + circle->transform().dy();

        qDebug() << "circle pos" << circle->pos();
        qDebug() << "tr=" << circle->transform() << circle->transform().dx() << circle->transform().dy();

        obj4Object.insert("x", QJsonValue::fromVariant(xx));
        obj4Object.insert("y", QJsonValue::fromVariant(yy));
        objObject.insert("pos", obj4Object);
        itemObj.insert("obj", objObject);
    }
     break;
    }
    itemObj.insert("obj", objObject);
}
