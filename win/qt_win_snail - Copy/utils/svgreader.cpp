#include "svgreader.h"
#include <QPen>
#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QStringList>
#include <QTransform>
#include <QDebug>
#include <QtSvg>

#include "cust_circle.h"
#include "cust_rect.h"
#include "cust_line.h"

///#include "vepolyline.h"

SvgReader::SvgReader(QObject *parent) : QObject(parent)
{

}

SvgReader::~SvgReader()
{

}
QList<QGraphicsItem *> SvgReader::getElements(const QString filename)
{
    QList<QGraphicsItem *> graphicsList;
    QList<QLinearGradient> gradientList;

    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return graphicsList;

     QDomNodeList gList = doc.elementsByTagName("g");

    for (int i = 0; i < gList.size(); i++) {
        QDomNode gNode = gList.item(i);
        QDomElement circleElement = gNode.firstChildElement("circle");
        if (!circleElement.isNull()) {
            cust_circle* circle = new cust_circle();
             QDomElement pElement = gNode.toElement();
             int cx = circleElement.attribute("cx").toInt();
             int cy = circleElement.attribute("cy").toInt();
             int r = circleElement.attribute("r").toInt();

             circle->setCircle(cx-r, cy-r, r*2);

            QColor strokeColor(pElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(pElement.attribute("stroke-opacity").toFloat());
 ///===========================================================
            QString transString = pElement.attribute("transform");
            transString.replace(QString("matrix("), QString(""));
            transString.replace(QString(")"), QString(""));
            QStringList transList = transString.split(",");

            QTransform trans(circle->transform());

            qreal m11 = trans.m11();    // Horizontal scaling
            qreal m12 = trans.m12();    // Vertical shearing
            qreal m13 = trans.m13();    // Horizontal Projection
            qreal m21 = trans.m21();    // Horizontal shearing
            qreal m22 = trans.m22();    // vertical scaling
            qreal m23 = trans.m23();    // Vertical Projection
            qreal m31 = trans.m31();    // Horizontal Position (DX)
            qreal m32 = trans.m32();    // Vertical Position (DY)
            qreal m33 = trans.m33();    // Addtional Projection Factor

            m11 = transList.at(0).toFloat();
            m12 = transList.at(1).toFloat();
            m21 = transList.at(2).toFloat();
            m22 = transList.at(3).toFloat();
            m31 = transList.at(4).toFloat();
            m32 = transList.at(5).toFloat();

            trans.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);
            circle->setTransform(trans);
 ///===========================================================           
            circle->setPen(QPen(strokeColor, pElement.attribute("stroke-width", "0").toInt()));
            QColor fillColor(pElement.attribute("fill", "#ffffff"));
            fillColor.setAlphaF(pElement.attribute("fill-opacity", "0").toFloat());
            circle->setBrush(QBrush(fillColor));
            graphicsList.append(circle);
            continue;
        }
///======================================================================
#if 1
        QDomElement pathElement = gNode.firstChildElement("path");
        if (!pathElement.isNull()){
            cust_line *line = new cust_line();
            auto pElement = gNode.toElement();
            line->setBrush(QBrush(Qt::transparent));
            QColor strokeColor(pElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(pElement.attribute("stroke-opacity").toFloat());
            int thick = pElement.attribute("stroke-width", "0").toInt();
            line->setPen(QPen(strokeColor, thick));
            QPainterPath path;
            QStringList listDotes = pathElement.attribute("d").split(" ");
            QString first = listDotes.at(0);
            QStringList firstElement = first.replace(QString("M"),QString("")).split(",");
            path.moveTo(firstElement.at(0).toInt(),firstElement.at(1).toInt());
            line->setPen(QPen(strokeColor, thick));
#if 1
  ////          int num= listDotes.length();
           for (int i = 1; i < listDotes.length(); i++) {
  ///          for(int i = 1; i < num; i++){
                QString other = listDotes.at(i);
                QStringList dot = other.replace(QString("L"),QString("")).split(",");
                path.lineTo(dot.at(0).toInt(),dot.at(1).toInt());
            }
#endif
        line->setPath(path);
        graphicsList.append(line);
        continue;
        }
#endif
///===========================================================================
        QDomElement rectangle = gNode.firstChildElement("rect");
        if (!rectangle.isNull()){
            cust_rect* rect = new cust_rect();
            auto gElement = gNode.toElement();
            rect->setRect(rectangle.attribute("x").toInt(),
                          rectangle.attribute("y").toInt(),
                          rectangle.attribute("width").toInt(),
                          rectangle.attribute("height").toInt());

            QString fill = gElement.attribute("fill", "#ffffff");
            if(fill.contains("url(#gradient")){
                fill.replace(QString("url(#gradient"), QString(""));
                fill.replace(QString(")"), QString(""));
                QLinearGradient g = gradientList.at(fill.toInt() - 1);
                auto tmpRect = rect->rect();
                g.setStart(tmpRect.left() + tmpRect.width()/2,tmpRect.top());
                g.setFinalStop(tmpRect.left() + tmpRect.width()/2,tmpRect.bottom());
                rect->setBrush(QBrush(g));
            } else {
                QColor fillColor(gElement.attribute("fill", "#ffffff"));
                fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                rect->setBrush(QBrush(fillColor));
            }

            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());

            QString transString = gElement.attribute("transform");
            transString.replace(QString("matrix("),QString(""));
            transString.replace(QString(")"),QString(""));
            QStringList transList = transString.split(",");

            QTransform trans(rect->transform());

            qreal m11 = trans.m11();    // Horizontal scaling
            qreal m12 = trans.m12();    // Vertical shearing
            qreal m13 = trans.m13();    // Horizontal Projection
            qreal m21 = trans.m21();    // Horizontal shearing
            qreal m22 = trans.m22();    // vertical scaling
            qreal m23 = trans.m23();    // Vertical Projection
            qreal m31 = trans.m31();    // Horizontal Position (DX)
            qreal m32 = trans.m32();    // Vertical Position (DY)
            qreal m33 = trans.m33();    // Addtional Projection Factor

            m11 = transList.at(0).toFloat();
            m12 = transList.at(1).toFloat();
            m21 = transList.at(2).toFloat();
            m22 = transList.at(3).toFloat();
            m31 = transList.at(4).toFloat();
            m32 = transList.at(5).toFloat();

            trans.setMatrix(m11,m12,m13,m21,m22,m23,m31,m32,m33);
            rect->setTransform(trans);
            rect->setPen(QPen(strokeColor,gElement.attribute("stroke-width", "0").toInt()));

            graphicsList.append(rect);
            continue;
        }
    }
    file.close();

    return graphicsList;
}

QRectF SvgReader::getSizes(const QString filename)
{
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return QRectF(0,0,200,200);

    QDomNodeList list = doc.elementsByTagName("svg");
    if(list.length() > 0) {
        auto svgElement = list.item(0).toElement();
        auto parameters = svgElement.attribute("viewBox").split(" ");
        return QRectF(parameters.at(0).toInt(),
                      parameters.at(1).toInt(),
                      parameters.at(2).toInt(),
                      parameters.at(3).toInt());
    }
    return QRectF(0,0,200,200);
}
