#include "Transformer.h"


Transformer::Transformer(const cv::Mat& img)
{
	currImg=img.clone();
}


Transformer::~Transformer(void)
{
	currImg.release();
}

void  Transformer::findBoardBoundRect(cv::Rect& boundRect)
{



	// Finds the contour with the largest area

	QVector<cv::RotatedRect> boxes;//create vector RotatedRect for sorting later

	for(int i=0; i<vertexContours.size();i++) {

		cv::RotatedRect box = cv::minAreaRect(vertexContours[i]);
		boxes<<box;


	}
	qSort(boxes.begin(),boxes.end(),Transformer::CompareRotateRect);//sorting RotatedRect



	cv::Point2f vertex[4];
	cv::RotatedRect boardRect=boxes.at(1);//less then largest
	boardRect.points(vertex);
	//упорядочить точки (левый_верхний,правый_верхний,правый_нижний,левый_нижний)
	std::swap(vertex[0],vertex[1]);
	std::swap(vertex[2],vertex[3]);

	cv::Point pt1, pt2;
	pt1=vertex[0];
	pt2=vertex[2];
	cv::Rect rect(vertex[0],vertex[2]);
	boundRect=rect;

}


void Transformer::findContoursThreshold(double thresh,double maxval,int colorScheme,int typeThresh)
{
	cv::Mat grayImage;
	cv::Mat imageEdge;

	cv::cvtColor(currImg, grayImage, colorScheme);// Converts original image to an 8UC1 image
	cv::threshold(grayImage,imageEdge,thresh,maxval,typeThresh);



	// Finds contours
	cv::findContours(imageEdge,vertexContours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

}


void Transformer::findCenterRect(const cv::Rect& rect,cv::Point2f& centerPoint)
{
	centerPoint.x = rect.tl().x + rect.width/2;
	centerPoint.y = rect.tl().y + rect.height/2;
}


void Transformer::find4FurthestPoints(const cv::Point2f& centerPoint,QVector<cv::Point2f>& furthestPoints)
{
	QVector<MinEnclosingCircle> circles;
	for(int i=0; i<vertexContours.size();i++) {
		cv::Point2f center;
		float radius = 0;
		cv::minEnclosingCircle(vertexContours[i], center, radius);
		//TODO Найти критерии для отсечения ненужных окружностей
		if((radius<5)||(radius>8)) continue;
		MinEnclosingCircle circle;
		circle.center=center;
		circle.radius=radius;
		circles<<circle;
	}
	QVector<QPair<MinEnclosingCircle,double>> circleWithDistantion;
	for(int i=1;i<circles.size();i++)
	{
		cv::Point2f center=circles[i].center;
		double distantion=cv::norm(centerPoint-center);//euclid distance beetwin points
		circleWithDistantion.append(qMakePair(circles[i],distantion));
	}

	qSort(circleWithDistantion.begin(),circleWithDistantion.end(),Transformer::CompareDistantionEnclosingCircle);

	for(int i=0;i<4;i++)
	{
		furthestPoints.append(circleWithDistantion[i].first.center);
		//srcRect[i]=circleWithDistantion[i].first.center;
		//cv::circle(undistort_img, circleWithDistantion[i].first.center, cvRound(circleWithDistantion[i].first.radius), cv::Scalar(255, 0, 255), 3);
	}


}


void Transformer::settingDestQuadrant(const cv::Rect& rect,QVector<cv::Point2f>& destQuadr)
{
	cv::Point2f topRight(rect.br().x,rect.br().y-rect.height);
	cv::Point2f bottomLeft(rect.tl().x,rect.tl().y+rect.height);

	destQuadr.append(bottomLeft);
	destQuadr.append(rect.br());
	destQuadr.append(topRight);
	destQuadr.append(rect.tl());
}


void Transformer::settingSourceQuadrant(const QVector<cv::Point2f>& destQuadr,const QVector<cv::Point2f>& sourceQuadr,QVector<cv::Point2f>& orderedQuadr)
{
	for(int i=0;i<destQuadr.size();i++)
	{
		cv::Point2f curPoint=destQuadr[i];
		int  index=0;
		double dist=cv::norm(curPoint-sourceQuadr[index]);
		for(int j=index;j<sourceQuadr.size();j++)
		{
			double curDist=cv::norm(curPoint-sourceQuadr[j]);
			if(curDist<dist) 
			{
				dist=curDist;
				index=j;
			}
		}
		orderedQuadr.push_back(sourceQuadr[index]);
	}
}


cv::Mat Transformer::applyPerspectiveTransform(const QVector<cv::Point2f>& srcQuadr,const QVector<cv::Point2f>& destQuadr )
{
	cv::Mat warpMat=cv::getPerspectiveTransform(srcQuadr.data(),destQuadr.data());
	cv::Mat dst;
	cv::warpPerspective(currImg,dst,warpMat,currImg.size(),cv::INTER_LINEAR,cv::BORDER_CONSTANT,cv::Scalar());
	return dst.clone();
}

void Transformer::setTransformImg(const cv::Mat& img)
{
	currImg.release();
	vertexContours.clear();
	currImg=img.clone();
}


cv::Mat Transformer::ROI(const cv::Rect& boundRect)
{
	return currImg(boundRect);
//	roi=dst(boundRect1);
}
