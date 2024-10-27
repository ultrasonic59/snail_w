#include "PlotProperties.h"
#include <QColor>

#include "snail_consts.h"

PlotProperties::PlotProperties(void) :
				BGColor(Qt::white),
				SelColor(0, 100, 0),//(Qt::blue),
	            RuleColor(0, 100, 100),//(Qt::blue),
	            CrossColor(Qt::black),
	            CircleColor(Qt::blue),
	            GridColor(Qt::gray),
	            LibBGColor(Qt::darkGray),
	            LibGridColor(Qt::red),
	            setka_delt_x(DEF_DELT_X),
	            setka_delt_y(DEF_DELT_Y),
	            rad_circle(DEF_RAD_CIRCLE),
                thick_circle(DEF_THICK_CIRCLE)///,
	            ///lib_grid_delt_x(DEF_DELT_X),
                ///lib_grid_delt_y(DEF_DELT_Y),
	///  Qt::darkGray
	           /// LibItemBGColor(Qt::darkGray),
              ///  LibItemBrdColor(Qt::gray),
  ///              LibItemBrdThick(1),
  ///              LibItemWidth(100),
  ///              LibItemHeight(50)

{

}


PlotProperties::~PlotProperties(void)
{
}
