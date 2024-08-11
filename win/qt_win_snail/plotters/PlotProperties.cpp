#include "PlotProperties.h"
#include <QColor>
////#include "colors.h"

PlotProperties::PlotProperties(void) :
				BGColor(Qt::white),
				OscColor(0, 100, 0),//(Qt::blue),
				GridColor(Qt::gray),
				TextColor(Qt::black),
				SepLineColor(Qt::darkGray),
				MarkerColor(Qt::blue),
				ErrorColor(Qt::red),
				row_number(6),
				column_number(10)
	
{

}


PlotProperties::~PlotProperties(void)
{
}
