#ifndef _PARAMS_H_
#define _PARAMS_H_
#include <QPoint>
#include "snail_consts.h"

#include "snail_consts.h"

class params
{
public:
    static	quint8 lib_grid_delt_x;
    static	quint8 lib_grid_delt_y;
    static	QPoint closest_to_grid(QPointF curr_pos);
};

#endif