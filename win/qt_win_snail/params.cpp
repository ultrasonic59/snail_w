#include "params.h"
#if 0
QPoint closest_to_grid(QPointF curr_pos, QPoint grid)
{
    ///QPoint rez;
    int rez_x = 0;
    int rez_y = 0;
    if ((grid.x() != 0) && (grid.y() != 0))
    {
        quint32 num_x = curr_pos.x() / grid.x();
        if ((int)curr_pos.x() % grid.x() > grid.x() / 2)
            num_x++;
        quint32 num_y = curr_pos.y() / grid.y();
        if ((int)curr_pos.y() % grid.y() > grid.y() / 2)
            num_y++;

        rez_x = grid.x() * num_x;
        rez_y = grid.y() * num_y;
    }
    return QPoint(rez_x, rez_y);
}
#endif
QPoint params::closest_to_grid(QPointF curr_pos)
{
    ///QPoint rez;
    int rez_x = 0;
    int rez_y = 0;
    if ((lib_grid_delt_x != 0) && (lib_grid_delt_y != 0))
    {
        quint32 num_x = curr_pos.x() / lib_grid_delt_x;
        if ((int)curr_pos.x() % lib_grid_delt_x > lib_grid_delt_x / 2)
            num_x++;
        quint32 num_y = curr_pos.y() / lib_grid_delt_y;
        if ((int)curr_pos.y() % lib_grid_delt_y > lib_grid_delt_y / 2)
            num_y++;

        rez_x = lib_grid_delt_x * num_x;
        rez_y = lib_grid_delt_y * num_y;
    }
    return QPoint(rez_x, rez_y);
}
/// LibItemBGColor(Qt::darkGray),
///  LibItemBrdColor(Qt::gray),
///              LibItemBrdThick(1),
///              LibItemWidth(100),
///              LibItemHeight(50)

/// round(newPos.x() / gridSize)* gridSize;

quint8 params::lib_grid_delt_x = DEF_DELT_X;
quint8 params::lib_grid_delt_y = DEF_DELT_Y;
QColor params::LibItemBGColor= Qt::darkGray;
QColor params::LibItemBrdColor= Qt::gray;
QColor params::LibBGColor = Qt::darkGray;
QColor params::LibGridColor = Qt::red;
QColor params::RuleColor = (Qt::blue);


quint8 params::LibItemBrdThick=1;
quint16 params::LibItemWidth=100;
quint16 params::LibItemHeight=50;
quint8 params::thick_rule = 1;