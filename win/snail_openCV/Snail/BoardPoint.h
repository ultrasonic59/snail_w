#pragma once
#include <QString>
#include <QPoint>
class BoardPoint
{
public:
	BoardPoint();
	BoardPoint(const QPointF& pointCoord,const QString& tagPoint=0);
	~BoardPoint();

	QString getPointTag() const;
	void setPointTag(const QString &value);

	QPointF getPointCoord() const;
	void setPointCoord(const QPointF& value);
private:
	QString tagPoint;
	QPointF pointCoord;

};

