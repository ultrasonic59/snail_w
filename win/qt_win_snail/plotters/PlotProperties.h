#pragma once

#include <QColor>


class PlotProperties
{
public:
	QColor BGColor;
	QColor SelColor;
	QColor RuleColor;
	QColor CrossColor;
	QColor CircleColor;
	QColor GridColor;
	QColor LibGridColor;
	QColor LibBGColor;

	quint8 setka_delt_x;
	quint8 setka_delt_y;
	quint8 thick_sel;
	quint8 thick_rule;
	quint8 rad_circle;
	quint8 thick_circle;
	quint8 thick_crs;
	quint8 lib_grid_delt_x;
	quint8 lib_grid_delt_y;
///======== lib items ========================================
	QColor LibItemBGColor;
	QColor LibItemBrdColor;
	quint8 LibItemBrdThick;
	quint16 LibItemWidth;
	quint16 LibItemHeight;


	PlotProperties(void);
	virtual ~PlotProperties(void);	
///=======================================
};

