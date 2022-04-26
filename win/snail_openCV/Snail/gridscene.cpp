#include "snail.h"
#include "gridscene.h"
#include <qmath.h>
class QGraphicsTextItem;
class QGraphicsRectItem;

int GridScene::newPointIndex=1;

GridScene::GridScene(QObject *parent)
	: QGraphicsScene(parent),
	mousePointerInBoardImgRect(false)
{
	
	setBackgroundBrush(QColor("#393939"));
	openCVImage=new OpenCVImage();


}

GridScene::~GridScene()
{

}
/*Bring into line phisical and logical size board
logical size must been multiplies phisical size
Приводит в соответствие физические и логические размеры платы.
Для правильного позиционирования логические размеры платы должны быть кратны физическим размерам*/

void GridScene::scaleBoardImg(const QSize& sizeBoard)
{
	int width_scale_factor=(sceneRect().width()/sizeBoard.width())-1;
	int height_scale_factor=(sceneRect().height()/sizeBoard.height())-1;
	int scale_factor=qMin(width_scale_factor,height_scale_factor);
	int predict_width=sizeBoard.width()*scale_factor;
	int predict_height=sizeBoard.height()*scale_factor;
	board_img= board_img.scaled(QSize(predict_width,predict_height));
	boardPhisicalSize=sizeBoard;

}





void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

	bool gridOnScene=false;
		foreach (QGraphicsItem *item, items()) {
			if (item->type() == QGraphicsItem::UserType+2)
				gridOnScene=true;
			}
		if(!gridOnScene)return;
	cursor_position.setX(mouseEvent->scenePos().x());
	cursor_position.setY(mouseEvent->scenePos().y());
	update();

	QPointF topLeft(gridItem->mapToScene(board_PixmapItem->boundingRect().topLeft()));
	QSizeF sizeRect(board_PixmapItem->boundingRect().size());
	QRectF matchRect(topLeft,sizeRect);

	if(matchRect.contains(cursor_position)){

		QApplication::setOverrideCursor(Qt::BlankCursor/*Qt::CrossCursor*/);
	
		mousePointerInBoardImgRect=true;
		QPointF boardCoordinate=translateToBoardCoordinate(cursor_position);
		QPointF phisCoordinate=translateToPhisicalCoordinate(boardCoordinate,pixel_in_mm);
		 QString txtNewPos = QString("X=%1, Y=%2")
               .arg(phisCoordinate.x(),0,'f',1)
              .arg(phisCoordinate.y(),0,'f',1); 
		 emit changeCursorPosition(txtNewPos);

	}
	else
	{
		QApplication::setOverrideCursor(Qt::ArrowCursor);
		emit changeCursorPosition("Out of board");

		mousePointerInBoardImgRect=false;

	}

}
void GridScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsScene::mousePressEvent(event);
	if(!mousePointerInBoardImgRect) return /*QGraphicsScene::mousePressEvent(event)*/;
	if (!event->isAccepted()) {
		if (event->button() == Qt::LeftButton) {

			QPointF point = event->scenePos();
			CrossPoint *item = new CrossPoint();
			item->setPos(point);
			int newPointIndex=incrementPointIndex();
			item->setData(0,QVariant(newPointIndex));
			item->setData(1,QVariant(
				translateToPhisicalCoordinate(translateToBoardCoordinate(point),pixel_in_mm)
				));
			addItem(item);
			QString pointTag = QString("Point (%1)").arg(newPointIndex); 
			BoardPoint boardPoint(translateToPhisicalCoordinate(translateToBoardCoordinate(point),pixel_in_mm),pointTag);
			boardPointsModel->append(boardPoint);
		

		} else if (event->button() == Qt::RightButton) {
	
			QGraphicsItem *itemToRemove = NULL;
			foreach (QGraphicsItem *item, items(event->scenePos())) {
				if (item->type() == QGraphicsItem::UserType+1) {
					itemToRemove = item;
				
					break;
				}
			}
		
			if (itemToRemove != NULL)
			{
				int indx=itemToRemove->data(0).toInt();
				qDebug() << "Point #" <<indx;
				removeItem(itemToRemove);
				boardPointsModel->deleteRow(indx);
		
			}
		}
	}




}

QPointF GridScene::translateToBoardCoordinate(const QPointF& in)
{
	QPointF boardCoordinate=gridItem->mapFromScene(in);//offset from corner board_img_rect
	return boardCoordinate;
}


QPointF GridScene::translateToPhisicalCoordinate(const QPointF& in,const QSize& pixel_in_mm)
{
	QPointF phisical_coordinate(in.x()/pixel_in_mm.width(),in.y()/pixel_in_mm.height());
	return phisical_coordinate;
}


void GridScene::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Delete) {
		while (!selectedItems().isEmpty()) {
			QGraphicsItem *item=selectedItems().front();
			removeItem(item);
			boardPointsModel->deleteRow(item->data(0).toInt());
		}
	} else if(event->key()==Qt::Key_Up)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x(),item->y()-1);      
	}
	else if(event->key()==Qt::Key_Down)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x(),item->y()+1);      
	}
	else if(event->key()==Qt::Key_Left)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x()-1,item->y());      
	}
	else if(event->key()==Qt::Key_Right)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x()+1,item->y());      
	}
	else {
		QGraphicsScene::keyPressEvent(event);
	}
}
bool GridScene::loadOpenCVImg(const QString& fileName)
{
	openCVImage->loadUndistortFile("calibration_matrix.yaml");
	openCVImage->loadImage(fileName);
	openCVImage->undistortImage();
	openCVImage->resizeImage(0.5,0.5);
	QPixmap pixmap=openCVImage->curPixmap();
	clear();
	board_PixmapItem=addPixmap(pixmap);

	return true;
}
QGraphicsPixmapItem* GridScene::pixmapItem()
{
	return board_PixmapItem;
}

void GridScene::adjustBoardImg(const QSize& sizeBoardInMM)
{
	openCVImage->adjustImgToBoundingRect();
	board_img=openCVImage->curPixmap();
	scaleBoardImg(sizeBoardInMM);
	clear();
	board_PixmapItem=addPixmap(board_img);
	board_PixmapItem->setPos(originScenePoint());
	board_img_rect=board_PixmapItem->boundingRect();



}
void GridScene::adjustGrid()
{


	QPen pen(Qt::red, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
	addRect(sceneRect(),pen,QBrush(Qt::NoBrush));
	gridItem=new GridItem();
	gridItem->setBoardPhisicalSize(boardPhisicalSize);
	gridItem->setPos(board_PixmapItem->pos());
	
	addItem(gridItem);
	update();
	pixel_in_mm = gridItem->pixelInMM();

}

QPointF GridScene::originScenePoint(void)
{
	return QPointF(sceneRect().left()+boardMargin::LEFT_MARGIN,sceneRect().top()+boardMargin::TOP_MARGIN);
}


QRectF GridScene::boardImgRect()
{
	return board_img_rect;
}
void GridScene::drawForeground(QPainter * painter, const QRectF & rect) 
{
	if(mousePointerInBoardImgRect){
		painter->setCompositionMode(QPainter::RasterOp_SourceXorDestination);

		QPen ROP_pen(Qt::white, 1, Qt::SolidLine);
		ROP_pen.setCosmetic(true);
		painter->setPen(ROP_pen);

		painter->drawLine(QPoint(cursor_position.x(),0),QPoint(cursor_position.x(),sceneRect().height()));
		painter->drawLine(QPoint(0,cursor_position.y()),QPoint(sceneRect().width(),cursor_position.y()));
	}

}

void GridScene::setModel(QAbstractItemModel* model)
{
	boardPointsModel=static_cast<BoardPointsModel*>(model);
}
void GridScene::clearScene()
{

			foreach (QGraphicsItem *item, items()) {
				//removeItem(item);
				if (item->type() == QGraphicsItem::UserType+1) {
					
					boardPointsModel->deleteRow(item->data(0).toInt());
					}
			}
			this->clear();
			mousePointerInBoardImgRect=false;
}
