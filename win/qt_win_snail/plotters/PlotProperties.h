#pragma once

#include <QColor>


class PlotProperties
{
public:
	QColor BGColor;
	QColor OscColor;
	QColor GridColor;
	QColor TextColor;
	QColor SepLineColor;
	QColor MarkerColor;
	QColor ErrorColor;

	int row_number;
	int column_number;

	PlotProperties(void);
	virtual ~PlotProperties(void);	
///=======================================
};

