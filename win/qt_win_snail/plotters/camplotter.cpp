#include "CamPlotter.h"
#include <QtGui/QPainter>
#include <QColor>
#include <QPointF>
#include <QDebug>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes
///=================================================
Scalar qcolor2scalar(QColor color)
{
	int r, g, b;
	color.getRgb(&r, &g, &b);
	return Scalar(b, g, r); // swap RGB-->BGR
}
QColor scalar2qcolor(Scalar color)
{
	return QColor(color[2], color[1], color[0]); // swap RGB-->BGR
}
///=================================================
CamPlotter::CamPlotter(PlotProperties *Plot_Prop, quint32* flags,c_snail_data* _snail_data) :
								image(1000, 1000, QImage::Format_ARGB32),
								pPlot_Prop(Plot_Prop), p_snail_data(_snail_data)
	                           /// , setka_delt_x(DEF_DELT_X)
	                           /// , setka_delt_y(DEF_DELT_Y)
	                           //// , m_flags(FLG_ON_RULE| FLG_ON_SEL)
							    , p_flags(flags)
	                            , redraw_sel_rc(false)
	                           ///// ,m_flags(FLG_ON_KRS)

{
}
CamPlotter::~CamPlotter(void)
{

}
void CamPlotter::ConnectToWidget(QWidget* _PlotWidgetNew)
{
	pPlotWidget = _PlotWidgetNew;
}

extern cv::Mat QImageToCvMat(QImage inImage, bool inCloneImageData=true);
extern cv::Mat QImage2Mat(QImage const& src);

void CamPlotter::sl_update_image(QImage& img, QImage::Format _format)
{
QImage _qimg = img.copy();

mat_img = QImageToCvMat(_qimg);

///cv::flip(mat_img, mat_img, 0);

///cv::flip(mat, mat, 0);

if (*p_flags & FLG_ON_CRS)
{
	drawCrs(mat_img);
}
if (*p_flags & FLG_ON_SEL)
{
	///if (redraw_sel_rc)
	   {
		drawSelRect(mat_img);
		////redraw_sel_rc = false;
	    }
}
////else 
if (*p_flags & FLG_ON_RULE)
    {
	drawRuleLine(mat_img);
    }
if (*p_flags & FLG_ON_PNT)
   {
	drawPoints(mat_img);
   }
////   m_cvmat = _cvmat.clone();
QImage  t_qimg = QImage(mat_img.data, mat_img.cols, mat_img.rows, mat_img.channels()*mat_img.cols, QImage::Format_RGB32);

emit s_update_image(t_qimg, _format);
///emit s_update_image(img, _format);
}
///
void CamPlotter::drawSelRect(const Mat& _mat)
{
Scalar colorRect(255, 0, 0);
QColor tcolor = pPlot_Prop->SelColor;
int thickness = pPlot_Prop->thick_sel;
QPoint pnt_tl = getMouseInsideCoord(sel_rect.topLeft());
QPoint pnt_br = getMouseInsideCoord(sel_rect.bottomRight());
///	QPoint t_pnt = getMouseInsideCoord(*pn);
// Top Left Corner 
Point p1(pnt_tl.x(), pnt_tl.y());
colorRect = qcolor2scalar(tcolor);
// Bottom Right Corner 
Point p2(pnt_br.x(), pnt_br.y());
rectangle(_mat, p1, p2,
	colorRect,
	thickness, LINE_AA/*LINE_4*/);
}

void CamPlotter::drawRuleLine(const Mat& _mat)
{
	Scalar colorLine(255, 0, 255);
	QColor tcolor = pPlot_Prop->RuleColor;

	int thickness = pPlot_Prop->thick_rule;
///	if(sel_rect.topLeft().x()>)
	QPoint pnt_tl = getMouseInsideCoord(sel_rect.topLeft());
	QPoint pnt_br = getMouseInsideCoord(sel_rect.bottomRight());
	///	QPoint t_pnt = getMouseInsideCoord(*pn);
	// Top Left Corner 
	Point p1(pnt_tl.x(), pnt_tl.y());
////	colorLine = pPlot_Prop->RuleColor.rgb();
	colorLine = qcolor2scalar(tcolor);

	// Bottom Right Corner 
	Point p2(pnt_br.x(), pnt_br.y());
	line(_mat, p1, p2,
		colorLine,
		thickness, LINE_AA/*LINE_4*/);
}

void CamPlotter::drawCrs(const Mat& _mat)
{
Scalar colorLine(0, 255, 0);
int thickness = pPlot_Prop->thick_crs;
colorLine = qcolor2scalar(pPlot_Prop->CrossColor);

Point p1(0, _mat.rows/2);
Point p2(_mat.cols, _mat.rows/2);

line(_mat, p1, p2, colorLine,
	thickness, LINE_AA);
p1.x = _mat.cols / 2;
p1.y = 0;
p2.x = _mat.cols / 2;
p2.y = _mat.rows;

line(_mat, p1, p2, colorLine,
	thickness, LINE_AA);

}
void CamPlotter::drawPoints(const Mat& _mat)
{
///===================(  Draw Circle  )======================
	int radiusCircle = pPlot_Prop->rad_circle;
	Scalar colorCircle = qcolor2scalar(pPlot_Prop->CircleColor);
	int thicknessCircle = pPlot_Prop->thick_circle;
	point_data_t t_point_data;
	for (int ii = 0; ii < p_snail_data->points.size(); ++ii) {
		t_point_data = p_snail_data->points.at(ii);
		Point centerCircle(t_point_data.coord.x(), t_point_data.coord.y());
		circle(_mat, centerCircle, radiusCircle, colorCircle, thicknessCircle);
		////     qDebug() << "mousePressEvent" << curX1 << curY1;
	}
}
QPoint CamPlotter::getMouseInsideCoord(QPoint inPos)
{
	QPoint rez = QPoint();
	QRect t_viewR = ((plotterwidget*)pPlotWidget)->getViewR();
	float coef_x = mat_img.cols;
	coef_x /= t_viewR.width();
	float coef_y = mat_img.rows;
	coef_y /= t_viewR.height();
	float xx = (inPos.x() - t_viewR.x()) * coef_x;
	float yy = (inPos.y() - t_viewR.y()) * coef_y;
	rez.setX((int)xx);
	rez.setY((int)yy);
	return rez;
}

void CamPlotter::slSetPoint(QPoint* pn)
{
///	qDebug() << "slSetPoint" << *pn;
	int tmp;
	QPoint t_pnt = getMouseInsideCoord(*pn);
#if 1
	if (pPlot_Prop->setka_delt_x)
	{
		tmp = (t_pnt.x() / pPlot_Prop->setka_delt_x) * pPlot_Prop->setka_delt_x;
		t_pnt.setX(tmp);
	}
	if (pPlot_Prop->setka_delt_y)
	{
		tmp = (t_pnt.y() / pPlot_Prop->setka_delt_y) * pPlot_Prop->setka_delt_y;
		t_pnt.setY(tmp);
	}
	point_data_t t_point_data;
	t_point_data.coord = t_pnt;
	p_snail_data->insertPoint(t_point_data);
///	qDebug() << "slSetPoint1" << t_point_data.coord;
///	last_pn = t_pnt;
	last_pn = *pn;
#endif
}
void CamPlotter::slMovePoint(QPoint* pn)
{
///	qDebug() << "slMovePoint";
	slClrPoint(&last_pn);
///	QPoint t_pnt = getMouseInsideCoord(*pn);
///	slSetPoint(&t_pnt);

	slSetPoint(pn);
	////   snail_data.insertPoint(*pd);
}

void CamPlotter::slClrPoint(QPoint* pn)
{
///	qDebug() << "slClrPoint";
	int tmp;
	QPoint t_pnt = getMouseInsideCoord(*pn);

	if (pPlot_Prop->setka_delt_x)
	{
		tmp = (t_pnt.x() / pPlot_Prop->setka_delt_x) * pPlot_Prop->setka_delt_x;
		t_pnt.setX(tmp);
	}
	if (pPlot_Prop->setka_delt_y)
	{
		tmp = (t_pnt.y() / pPlot_Prop->setka_delt_y) * pPlot_Prop->setka_delt_y;
		t_pnt.setY(tmp);
	}

	p_snail_data->removePoint(t_pnt);
}
void CamPlotter::sl_set_sel_rect(QRect t_rect)
{
	QRect rule_rect= QRect();
	sel_rect = t_rect;
///	rule_rect.setBottomRight(getMouseInsideCoord(sel_rect.bottomRight()));
///	rule_rect.setTopLeft(getMouseInsideCoord(sel_rect.topLeft()));

	if (*p_flags & FLG_ON_RULE)
	{
		rule_rect.setBottomRight(getMouseInsideCoord(sel_rect.bottomRight()));
		rule_rect.setTopLeft(getMouseInsideCoord(sel_rect.topLeft()));
		emit s_show_rule_coord(rule_rect);
	}
////	redraw_sel_rc = true;
}
