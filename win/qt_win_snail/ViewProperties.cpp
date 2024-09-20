#include "ViewProperties.h"
#include <QColorDialog>
#include <QtGui/QPainter>
#include <QDebug>
////#include "colors.h"
////#include "qwin_otter.h"


ViewProperties::ViewProperties(QWidget *parent, QObject *reseiver, PlotProperties *plotProp) :
		QDialog(parent),
		PropInterface(),
		PlotProp(plotProp)
{
	PropInterface.setupUi(this);
/////qwin_otter *twin=(qwin_otter *)reseiver;
	PropInterface.Button_col_background->SetColor(plotProp->BGColor);
	PropInterface.Button_col_sel->SetColor(plotProp->SelColor);
	PropInterface.Button_col_rule->SetColor(plotProp->RuleColor);
    PropInterface.Button_col_crs->SetColor(plotProp->CrossColor);
	PropInterface.Button_col_circle->SetColor(plotProp->CircleColor);

	PropInterface.Button_col_grid->SetColor(plotProp->GridColor);
	PropInterface.Button_col_lib_bg->SetColor(plotProp->LibBGColor);
	PropInterface.Button_col_lib_grid->SetColor(plotProp->LibGridColor);

	setWindowFlags(Qt::Drawer);

	PropInterface.lineCellX->set_num_dig(3);
	PropInterface.lineCellX->set_data(reinterpret_cast<unsigned char*>(&PlotProp->setka_delt_x));
	PropInterface.lineCellX->set_min_max(1,100);
	PropInterface.lineCellX->show_par();
	connect(PropInterface.lineCellX, SIGNAL(param_changed()), this, SLOT(sl_change_delt_x()));

	PropInterface.lineCellY->set_num_dig(3);
	PropInterface.lineCellY->set_data(reinterpret_cast<unsigned char*>(&PlotProp->setka_delt_y));
	PropInterface.lineCellY->set_min_max(1,100);
	PropInterface.lineCellY->show_par();
	///connect(PropInterface.lineCellY, SIGNAL(param_changed()), reseiver, SLOT(ResetPlot()));
	
	PropInterface.ed_thick_sel->set_num_dig(2);
	PropInterface.ed_thick_sel->set_data(reinterpret_cast<unsigned char*>(&PlotProp->thick_sel));
	PropInterface.ed_thick_sel->set_min_max(1,10);
	PropInterface.ed_thick_sel->set_coeff(1);
	PropInterface.ed_thick_sel->show_par();
	////connect(PropInterface.ed_thick_sel, SIGNAL(param_changed()), this, SLOT(SetOscillogramWidth()));////???

	PropInterface.ed_thick_rule->set_num_dig(2);
	PropInterface.ed_thick_rule->set_data(reinterpret_cast<unsigned char*>(&PlotProp->thick_rule));
	PropInterface.ed_thick_rule->set_min_max(1,10);
	PropInterface.ed_thick_rule->show_par();

	PropInterface.ed_circle_thick->set_num_dig(2);
	PropInterface.ed_circle_thick->set_data(reinterpret_cast<unsigned char*>(&PlotProp->thick_circle));
	PropInterface.ed_circle_thick->set_min_max(1, 10);
	PropInterface.ed_circle_thick->set_coeff(1);
	PropInterface.ed_circle_thick->show_par();

	PropInterface.ed_circle_rad->set_num_dig(2);
	PropInterface.ed_circle_rad->set_data(reinterpret_cast<unsigned char*>(&PlotProp->rad_circle));
	PropInterface.ed_circle_rad->set_min_max(1, 10);
	PropInterface.ed_circle_rad->set_coeff(1);
	PropInterface.ed_circle_rad->show_par();

	PropInterface.ed_cross_thick->set_num_dig(2);
	PropInterface.ed_cross_thick->set_data(reinterpret_cast<unsigned char*>(&PlotProp->thick_crs));
	PropInterface.ed_cross_thick->set_min_max(1, 10);
	PropInterface.ed_cross_thick->set_coeff(1);
	PropInterface.ed_cross_thick->show_par();

	PropInterface.ed_lib_gr_x->set_num_dig(3);
	PropInterface.ed_lib_gr_x->set_data(reinterpret_cast<unsigned char*>(&PlotProp->lib_grid_delt_x));
	PropInterface.ed_lib_gr_x->set_min_max(1, 100);
	PropInterface.ed_lib_gr_x->show_par();
	///connect(PropInterface.lineCellX, SIGNAL(param_changed()), this, SLOT(sl_change_delt_x()));

	PropInterface.ed_lib_gr_y->set_num_dig(3);
	PropInterface.ed_lib_gr_y->set_data(reinterpret_cast<unsigned char*>(&PlotProp->lib_grid_delt_y));
	PropInterface.ed_lib_gr_y->set_min_max(1, 100);
	PropInterface.ed_lib_gr_y->show_par();


	////connect(PropInterface.ed_thick_rule, SIGNAL(param_changed()), reseiver, SLOT(ResetPlot())); ////???
	

////	connect(PropInterface.okButton, SIGNAL(clicked()), reseiver, SLOT(NewWindowParameters()));
////	connect(PropInterface.cancelButton, SIGNAL(clicked()), reseiver, SLOT(CloseWindowParameters()));

////	connect(this, SIGNAL(CloseMe()), reseiver, SLOT(CloseWindowParameters()));
/////????	connect(this, SIGNAL(PlotColorsChanged()), reseiver, SLOT(ResetPlot()));

////	connect(this, SIGNAL(BackgroundChanged()), reseiver, SLOT(apply_default_color()));

	connect(PropInterface.Button_col_background, SIGNAL(clicked()), this, SLOT(SetBackgroundColor()));
	connect(PropInterface.Button_col_sel, SIGNAL(clicked()), this, SLOT(SetSelColor()));
	connect(PropInterface.Button_col_rule, SIGNAL(clicked()), this, SLOT(SetRuleColor()));
	connect(PropInterface.Button_col_crs, SIGNAL(clicked()), this, SLOT(SetCrsColor()));
	connect(PropInterface.Button_col_circle, SIGNAL(clicked()), this, SLOT(SetCircleColor()));
	connect(PropInterface.Button_col_lib_grid, SIGNAL(clicked()), this, SLOT(SetLibGridColor()));
	connect(PropInterface.Button_col_lib_bg, SIGNAL(clicked()), this, SLOT(SetLibBGColor()));
	connect(PropInterface.okButton, SIGNAL(clicked()), this, SLOT(slOKbutton()));

#if 0
	resize(390, 677);
#endif
}

ViewProperties::~ViewProperties()
{
}
#if 0
void ViewProperties::closeEvent( QCloseEvent * event )
{
	QDialog::closeEvent(event);
////	CloseMe();
}

#endif
///ApplyNewText()
void ViewProperties::slOKbutton()
{
	PropInterface.ed_circle_rad->apply_current();
	PropInterface.ed_circle_thick->apply_current();
		PropInterface.ed_cross_thick->apply_current();
		PropInterface.ed_lib_gr_x->apply_current();
		PropInterface.ed_lib_gr_y->apply_current();
		PropInterface.ed_thick_rule->apply_current();
		PropInterface.ed_thick_sel->apply_current();
		PropInterface.lineCellX->apply_current();
		PropInterface.lineCellY->apply_current();


}
void ViewProperties::SetBackgroundColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->BGColor);

	if(tempColor.isValid())
	{
		PlotProp->BGColor = tempColor;
		PropInterface.Button_col_background->SetColor(tempColor);

	///	emit BackgroundChanged();
		emit PlotColorsChanged();
	}
}

void ViewProperties::SetSelColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->SelColor);

	if(tempColor.isValid())
	{
		PlotProp->SelColor = tempColor;
		PropInterface.Button_col_sel->SetColor(tempColor);
		emit PlotColorsChanged();
	}
}
void ViewProperties::SetLibGridColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->LibGridColor);
	if (tempColor.isValid())
	{
		PlotProp->LibGridColor = tempColor;
		PropInterface.Button_col_lib_grid->SetColor(tempColor);
		emit PlotColorsChanged();
	}
}
void ViewProperties::SetLibBGColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->LibBGColor);
	if (tempColor.isValid())
	{
		PlotProp->LibBGColor = tempColor;
		PropInterface.Button_col_lib_bg->SetColor(tempColor);
		emit PlotColorsChanged();
	}
}

void ViewProperties::SetGridColor()
{
QColor tempColor = QColorDialog::getColor(PlotProp->GridColor);
if(tempColor.isValid())
	{
	PlotProp->GridColor = tempColor;
	PropInterface.Button_col_grid->SetColor(tempColor);
	emit PlotColorsChanged();
	}
}

void ViewProperties::SetCrsColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->CrossColor);
	if(tempColor.isValid())
	{
		PlotProp->CrossColor = tempColor;
		PropInterface.Button_col_crs->SetColor(tempColor);
		emit PlotColorsChanged();
	}
}

void ViewProperties::SetRuleColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->RuleColor);

	if(tempColor.isValid())
	{
		PlotProp->RuleColor = tempColor;
		PropInterface.Button_col_rule->SetColor(tempColor);
		emit PlotColorsChanged();
	}
}

void ViewProperties::SetCircleColor()
{

	QColor tempColor = QColorDialog::getColor(PlotProp->CircleColor);

	if(tempColor.isValid())
	{
		PlotProp->CircleColor = tempColor;
		PropInterface.Button_col_circle->SetColor(tempColor);
		emit PlotColorsChanged();
	}

}
/*
void ViewProperties::sl_change_delt_x()
{
	qDebug() << "sl_change_delt_x" ;

}
*/


