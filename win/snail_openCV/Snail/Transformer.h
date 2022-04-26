#pragma once
#include "OpenCVImage.h"
#include <vector>
struct MinEnclosingCircle{
	cv::Point2f center;
	float radius;
};
class Transformer
{
public:
	Transformer(const cv::Mat& img);
	virtual ~Transformer(void);
	void findBoardBoundRect(cv::Rect& boundRect);
	void findContoursThreshold(double hresh,double maxval,int typeThresh,int colorScheme);
	void findCenterRect(const cv::Rect& rect,cv::Point2f& centerPoint);
	void find4FurthestPoints(const cv::Point2f& centerPoint,QVector<cv::Point2f>& furthestPoint);
	void settingDestQuadrant(const cv::Rect& rect,QVector<cv::Point2f>& destQuadr);
	void settingSourceQuadrant(const QVector<cv::Point2f>& destQuadr,const QVector<cv::Point2f>& sourceQuadr,QVector<cv::Point2f>& orderedQuadr);
	cv::Mat applyPerspectiveTransform(const QVector<cv::Point2f>& srcQuadr,const QVector<cv::Point2f>& destQuadr );
private:
	cv::Mat currImg;
	cv::vector<cv::vector<cv::Point> >  vertexContours;

private:

	inline static bool CompareRotateRect(const cv::RotatedRect& rc1,const cv::RotatedRect& rc2)
		{
			return (rc1.size.area()>rc2.size.area());
		}
	inline static bool CompareDistantionEnclosingCircle(const QPair<MinEnclosingCircle,double>& circle1,const QPair<MinEnclosingCircle,double>& circle2)
		{
			return (circle1.second>circle2.second);
		}

public:
	void setTransformImg(const cv::Mat& img);
	cv::Mat ROI(const cv::Rect& boundRect);
};

