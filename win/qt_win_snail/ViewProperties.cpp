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
   //// PropInterface.Button_col_text->SetColor(plotProp->TextColor);

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
	////connect(PropInterface.ed_thick_rule, SIGNAL(param_changed()), reseiver, SLOT(ResetPlot())); ////???
	

////	connect(PropInterface.okButton, SIGNAL(clicked()), reseiver, SLOT(NewWindowParameters()));
////	connect(PropInterface.cancelButton, SIGNAL(clicked()), reseiver, SLOT(CloseWindowParameters()));

////	connect(this, SIGNAL(CloseMe()), reseiver, SLOT(CloseWindowParameters()));
/////????	connect(this, SIGNAL(PlotColorsChanged()), reseiver, SLOT(ResetPlot()));

////	connect(this, SIGNAL(BackgroundChanged()), reseiver, SLOT(apply_default_color()));

	connect(PropInterface.Button_col_background, SIGNAL(clicked()), this, SLOT(SetBackgroundColor()));
	connect(PropInterface.Button_col_sel, SIGNAL(clicked()), this, SLOT(SetSelColor()));
	connect(PropInterface.Button_col_rule, SIGNAL(clicked()), this, SLOT(SetRuleColor()));
#if 0
	connect(PropInterface.Button_col_no_ak, SIGNAL(clicked()), this, SLOT(SetNoAKColor()));

	/////connect(PropInterface.Button_col_norma, SIGNAL(clicked()), this, SLOT(SetNoDefColor()));

	////connect(PropInterface.Button_col_RL, SIGNAL(clicked()), this, SLOT(SetRLColor()));
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

void ViewProperties::SetBackgroundColor()
{
	QColor tempColor = QColorDialog::getColor(PlotProp->BGColor);

	if(tempColor.isValid())
	{
		PlotProp->BGColor = tempColor;
		PropInterface.Button_col_background->SetColor(tempColor);

		emit BackgroundChanged();
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

void ViewProperties::SetGridColor()
{
	/*
QColor tempColor = QColorDialog::getColor(PlotProp->GridColor);
if(tempColor.isValid())
	{
	PlotProp->GridColor = tempColor;
	PropInterface.Button_col_cell->SetColor(tempColor);
	emit PlotColorsChanged();
	}
	*/
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

void ViewProperties::sl_change_delt_x()
{
	qDebug() << "sl_change_delt_x" ;

}



