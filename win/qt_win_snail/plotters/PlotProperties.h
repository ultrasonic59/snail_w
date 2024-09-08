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
	QColor SepLineColor;
	QColor ErrorColor;

	quint8 setka_delt_x;
	quint8 setka_delt_y;
	quint8 thick_sel;
	quint8 thick_rule;
	quint8 rad_circle;
	quint8 thick_circle;
	quint8 thick_crs;


	PlotProperties(void);
	virtual ~PlotProperties(void);	
///=======================================
};

