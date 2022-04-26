#include "griditem.h"
#include "gridscene.h"

GridItem::GridItem(QGraphicsObject *parent)
	: QGraphicsObject(parent)
{
	pen_fat=QPen(QBrush(Qt::yellow), RulerTraits::PEN_FAT, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		pen_fat.setCosmetic(true);
		pen_thin=QPen(QBrush(Qt::yellow), RulerTraits::PEN_THIN, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		pen_thin.setCosmetic(true);
}

GridItem::~GridItem()
{

}
void GridItem::setBoardPhisicalSize(const QSize& size)
{
phisicalSize=size;

}
void GridItem::calculatePixelInMm()
{
	pixel_in_mm.setWidth(boundingRect().width()/phisicalSize.width());
	pixel_in_mm.setHeight(boundingRect().height()/phisicalSize.height());

}
QRectF GridItem::boundingRect() const
{
  
	GridScene* scene=reinterpret_cast<GridScene*>(this->scene());
	
	return scene->boardImgRect();
}
 
void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	calculatePixelInMm();
	painter->setPen(pen_fat);
	painter->drawRect(boundingRect());
	drawHorizRuler(painter,boundingRect().topLeft(),boundingRect().width(),pixel_in_mm.width());
	drawVertRuler(painter,boundingRect().topLeft(),boundingRect().height(),pixel_in_mm.height());
	drawGridLegend(painter);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
void GridItem::drawHorizRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash)
{

	int ruler_origin=RulerTraits::RULER_ORIGIN;

	int step_cm=0;
	int step_mm=0;

	for(int i=ruler_origin;i<length;i++)
	{
		if(!(i%step))
		{
			step_mm+=step;
			if (!(i%step)&&((i%(step*RulerTraits::STEP_HALF_CM))&&(i%(step*RulerTraits::STEP_CM)))) {
				
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x()+step_mm,origin.y()),QPoint(origin.x()+step_mm,origin.y()+step));
				painter->drawLine(dash_mm);
			}
		 if(!(i%(step*RulerTraits::STEP_HALF_CM))&&(i%(step*RulerTraits::STEP_CM))) {
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x()+step_mm,origin.y()),QPoint(origin.x()+step_mm,origin.y()+step*mult_length_dash));
				painter->drawLine(dash_mm);
			}
		}
		if(!(i%(step*RulerTraits::STEP_CM)))
		{
				
			
			step_cm+=step*RulerTraits::STEP_CM;
			painter->setPen(pen_fat);
			QLine dash_cm(QPoint(origin.x()+step_cm,origin.y()),QPoint(origin.x()+step_cm,origin.y()+step*mult_length_dash));
		
			painter->drawLine(dash_cm);
		}

	}
}
void GridItem::drawVertRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash)
{

	int ruler_origin=RulerTraits::RULER_ORIGIN;

	int step_cm=0,step_mm=0;
	int counter=1;
	for(int i=ruler_origin;i<length;i++)
	{
		if(!(i%step))
		{

		
			step_mm+=step;
		    if (!(i%step)&&((i%(step*RulerTraits::STEP_HALF_CM))&&(i%(step*RulerTraits::STEP_CM))))  { 
				
		
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x(),origin.y()+step_mm),QPoint(origin.x()+step,origin.y()+step_mm));
				painter->drawLine(dash_mm);
				
			}
			
				 if(!(i%(step*RulerTraits::STEP_HALF_CM))&&(i%(step*RulerTraits::STEP_CM))) {
				
			
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x(),origin.y()+step_mm),QPoint(origin.x()+step*mult_length_dash,origin.y()+step_mm));
				painter->drawLine(dash_mm);
				}
				//continue;
			
					if(!(i%(step*RulerTraits::STEP_CM))) {
							
	
			painter->setPen(pen_fat);
		step_cm+=step*RulerTraits::STEP_CM;
			QLine dash_cm(QPoint(origin.x(),origin.y()+step_cm),QPoint(origin.x()+step*mult_length_dash,origin.y()+step_cm));
			painter->drawLine(dash_cm);
						
		}
		
		}
	

	}
}
void GridItem::drawGridLegend(QPainter *painter)
{
	QFont legend_font("Arial", 36);
	painter->setPen(pen_thin);
	painter->setFont(legend_font);
	QString origin_txt=QString("%1").arg(0);
	QString right_top_txt=QString("%1").arg(phisicalSize.width());
	QString left_bottom_txt=QString("%1").arg(phisicalSize.height());
	painter->drawText((boundingRect().topLeft()+QPoint(10,50)),origin_txt);
	painter->drawText((boundingRect().topRight()+QPoint(-85,50)),right_top_txt);
	painter->drawText((boundingRect().bottomLeft()+QPoint(10,-10)),left_bottom_txt);


}


QSize GridItem::pixelInMM() 
{
	this->calculatePixelInMm();
	return pixel_in_mm;
}
int GridItem::type() const
{
    return UserType + 2;
}