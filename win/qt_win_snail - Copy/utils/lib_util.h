#ifndef __LIB_UTIL_H___
#define __LIB_UTIL_H___

#include <QObject>
///#include <QGraphicsLineItem>
///#include <QGraphicsRectItem>
///#include <QGraphicsEllipseItem>
#include <QtScript/QScriptEngine>
#include <QJSEngine>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPen>
#include "cust_line.h"
#include "cust_circle.h"
#include "cust_rect.h"
#include "cust_group.h"

class LibUtil : public QObject
{
	Q_OBJECT

public:
	LibUtil();
	virtual ~LibUtil();
public:
	QGraphicsItem* getItem(QJsonObject& itemObj);
	void insertItem(QGraphicsItem* item, QJsonObject& itemObj);

};

#endif
