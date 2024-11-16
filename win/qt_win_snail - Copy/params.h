#ifndef _PARAMS_H_
#define _PARAMS_H_
#include <QPoint>
#include <QColor>
#include "snail_consts.h"

#include "snail_consts.h"

class params
{
public:
    static	quint8 lib_grid_delt_x;
    static	quint8 lib_grid_delt_y;
    static	QColor LibItemBGColor;
    static	QColor LibItemBrdColor;
    static	QColor LibGridColor;
    static	QColor LibBGColor;
    static	QColor RuleColor;

    static	quint8 LibItemBrdThick;
    static	quint16 LibItemWidth;
    static	quint16 LibItemHeight;
    static	quint8 thick_rule;


    static	QPoint closest_to_grid(QPointF curr_pos);
};

#endif