#ifndef __SNAIL_DATA_H__
#define __SNAIL_DATA_H__

#include <QList>
#include <QColor>
#include <QRect>

#define MAX_LEN_STR 64

#define MAX_PONTS_X 5000
#define MAX_PONTS_Y 5000

struct point_data_t
{
	QPoint coord;
	quint8 point_type;
	quint8 rsv[3];
};
struct one_element_gr_t
{
quint8 type;
quint16 thick;
QColor color;
QRect rc;
};

struct lib_element_t
{
	QString PatternName;
	QList<point_data_t> points;
	QList<one_element_gr_t> gr_els;

};
struct el_pos_t
{
	float LocationX;
	float LocationY;
	float Rotation;

};
/*
struct element_data_t
{
	QString RefDes;
	QString PatternName;
	QString Value;
	QString Layer;
	el_pos_t cvs_pos;
	el_pos_t _mach_pos;
	el_pos_t _cur_pos;
};
*/
#define MAX_NAME_LEN 64
struct element_data_t
{
char RefDes[MAX_NAME_LEN];
char PatternName[MAX_NAME_LEN];
bool Layer;
bool check;
el_pos_t cvs_pos;
};


class c_snail_data
{
public:
	c_snail_data();
	~c_snail_data();
public:
	quint32 num_elem;

	qint32 offs_x;        /// in pix (0.01) mm
	qint32 offs_y;        /// in pix (0.01) mm
	float min_x;        /// in pix (0.01) mm
	float min_y;        /// in pix (0.01) mm
	float max_x;        /// in pix (0.01) mm
	float max_y;        /// in pix (0.01) mm

	QList<element_data_t> elements;
	QList<point_data_t> points;
	void insertPoint(point_data_t point_data);
	void removePoint(QPoint point);

////	element_data_t *p_elements;
////	quint8 points[MAX_PONTS_Y][MAX_PONTS_X];
};

#endif /// __SNAIL_DATA_H__
