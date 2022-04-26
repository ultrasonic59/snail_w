#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QMargins>
#include "crosspoint.h"
#include <QPixmap>
#include <qcursor.h>
#include <QAbstractItemModel>
#include "bigcross.h"
#include "OpenCVImage.h"
#include "griditem.h"
#include "BoardPoint.h"
#include "BoardPoinsModel.h"

class GridScene : public QGraphicsScene
{
	Q_OBJECT

	static int newPointIndex;

	enum boardMargin{
		LEFT_MARGIN=100,
		TOP_MARGIN=100
	} _boardMargin;
public:
	GridScene(QObject *parent);
	~GridScene();

	bool loadBackgroundImg(const QString& fileName);
	bool loadOpenCVImg(const QString& fileName);
	QGraphicsPixmapItem* pixmapItem();
	void adjustBoardImg(const QSize& sizeBoardInMM);
	void adjustGrid();
	QRectF boardImgRect();
	void setModel(QAbstractItemModel* model);
	void clearScene();

	static int incrementPointIndex(){ return newPointIndex++;}
	static int decrementPointIndex(){ return newPointIndex--;}
private:
	CrossPoint* myPoint;
	QPixmap board_img;
	QGraphicsPixmapItem* board_PixmapItem;
	QGraphicsRectItem* img_rect_item;
	QSize pixel_in_mm;
	QSize sceneSize;
	QSize boardPhisicalSize;
	QRectF board_img_rect;
	bool mousePointerInBoardImgRect;
	QPoint cursor_position;
	QCursor cursor_target;
	OpenCVImage* openCVImage;
	GridItem* gridItem;
	BoardPointsModel* boardPointsModel;
protected:
    void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void drawForeground(QPainter * painter, const QRectF & rect) ;


private:
	void scaleBoardImg(const QSize& sizeBoard);
	QPointF translateToBoardCoordinate(const QPointF& inPoint);
	QPointF translateToPhisicalCoordinate(const QPointF& in,const QSize& pixel_in_mm);
	QPointF originScenePoint();
public:
	signals:
		void changeCursorPosition(const QString& newPos);
		void addPointInBoardPointsModel(const BoardPoint& newPoint);
		void removePointFromBoardPointsModel(int indx);

};

#endif // GRIDSCENE_H