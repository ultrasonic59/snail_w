#ifndef __SNAIL_DATA_H__
#define __SNAIL_DATA_H__

#include <QList>

#define MAX_LEN_STR 64

#define MAX_PONTS_X 5000
#define MAX_PONTS_Y 5000

struct element_data_t
{
	char RefDes[MAX_LEN_STR];
	char PatternName[MAX_LEN_STR];
	char Value[MAX_LEN_STR];
	char Layer[MAX_LEN_STR];
    float LocationX;
    float LocationY;
	float Rotation;
};
struct point_data_t
{
QPoint coord;
quint8 point_type;
quint8 rsv[3];
};

class c_snail_data
{
public:
	c_snail_data();
	~c_snail_data();
public:
	quint32 offs_x;
	quint32 offs_y;
	QList<element_data_t> elements;
	QList<point_data_t> points;
	void insertPoint(point_data_t point_data);
	void removePoint(QPoint point);

////	element_data_t *p_elements;
////	quint8 points[MAX_PONTS_Y][MAX_PONTS_X];
};

#endif /// __SNAIL_DATA_H__
