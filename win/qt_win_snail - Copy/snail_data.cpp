#include "snail_data.h"

c_snail_data::c_snail_data()
{

}
c_snail_data::~c_snail_data()
{

}

void c_snail_data::insertPoint(point_data_t point_data)
{
	bool end_inst = false;
	if (points.size() == 0)
		points << point_data;
	else
	{
		point_data_t t_point_data;
	for (int ii = 0; ii < points.size(); ++ii) {
		t_point_data = points.at(ii);
		if(t_point_data.coord == point_data.coord){ 
			points.removeAt(ii);
			points << point_data;
			end_inst = true;
			break;
		   }
		}
	if(!end_inst)
		points << point_data;
	}
}
void c_snail_data::removePoint(QPoint point)
{
	if (points.size() == 0)
		return;
	point_data_t t_point_data;
	for (int ii = 0; ii < points.size(); ++ii) {
		t_point_data = points.at(ii);
		if (t_point_data.coord == point) {
			points.removeAt(ii);
			break;
		}
	}

}
