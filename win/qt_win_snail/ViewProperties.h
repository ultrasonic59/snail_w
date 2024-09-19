#ifndef VIEWPROPERTIES_H
#define VIEWPROPERTIES_H

#include <QDialog>
#include "ui_ViewProperies.h"
#include "PlotProperties.h"
#include "QPushButtonColored.h"


class ViewProperties : public QDialog
{
	Q_OBJECT

private slots:

	void SetBackgroundColor();
	void SetSelColor();
	void SetRuleColor();
	void SetCrsColor();
	void SetCircleColor();

	void SetGridColor();
	void SetLibGridColor();
	void SetLibBGColor();

	void sl_change_delt_x();

signals:
	void PlotColorsChanged();
	void BackgroundChanged();
	///void CloseMe();
public:
	ViewProperties(QWidget *parent, QObject *reseiver, PlotProperties *plotProp);
	virtual ~ViewProperties();
////protected:
///	virtual void closeEvent( QCloseEvent * event );
private:
	Ui::propertiesDialog PropInterface;
	PlotProperties *PlotProp;
	////int curr_osc_width;
///public:
///	PlotProperties PlotPropTemp;
};

#endif // VIEWPROPERTIES_H
