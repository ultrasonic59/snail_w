#include "BoardPoint.h"


BoardPoint::BoardPoint()
{
}

BoardPoint::BoardPoint(const QPointF& pointCoord,const QString& pointTag)
{
	this->pointCoord=pointCoord;
	this->tagPoint=pointTag;

}
BoardPoint::~BoardPoint(void)
{
}


QString BoardPoint::getPointTag() const
{
	return tagPoint;
}

void BoardPoint::setPointTag(const QString &value)
{
	this->tagPoint=value;
}

QPointF BoardPoint::getPointCoord() const
{
	return pointCoord;
}

void BoardPoint::setPointCoord(const QPointF& value)
{
	this->pointCoord=value;
}
