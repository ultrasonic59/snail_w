#include "OpenCVImage.h"


OpenCVImage::OpenCVImage(void)
{
}


OpenCVImage::~OpenCVImage(void)
{
	currImage.release();
	debugImg.release();
}



bool OpenCVImage::loadImage(const QString& imgFileName)
{
	currImage=cv::imread(imgFileName.toStdString());
	if(currImage.empty()) return false;
	return true;
}
void OpenCVImage::resizeImage(float factorWidth,float factorHeight)
{
	cv::resize(currImage, currImage, cv::Size(0,0),factorWidth,factorHeight);//картинка будет 50% от изначальной
}
void OpenCVImage::loadUndistortFile(const QString& undistortFileName)
{

	loadDistortCameraMatrix("calibration_matrix.yaml",map1,map2);
}
void OpenCVImage::undistortImage()
{
	
	cv::Mat undistort_img;

	cv::remap(currImage,undistort_img,map1,map2,cv::INTER_LINEAR,cv::BORDER_CONSTANT,cv::Scalar());
	currImage= undistort_img.clone();
}
QPixmap OpenCVImage::curPixmap()
{
	return ASM::cvMatToQPixmap(currImage);

}



void OpenCVImage::loadDistortCameraMatrix(const QString& fileName,cv::Mat& map1,cv::Mat& map2)
{
	cv::FileStorage fs(fileName.toStdString(), cv::FileStorage::READ);

	int img_width,img_height;
	fs["img_width"]>>img_width;
	fs["img_height"]>>img_height;
	cv::Mat camera_matrix,distortion_coeffs;
	fs["camera_matrix"]>>camera_matrix;
	fs["distortion_coefficients"]>>distortion_coeffs;
	cv::Size image_size(img_width,img_height);
	//cv::Mat map1,map2;
	cv::initUndistortRectifyMap(
		camera_matrix,
		distortion_coeffs,
		cv::Mat(),
		camera_matrix,
		image_size,
		CV_16SC2,
		map1,
		map2
		);
}


cv::Mat  OpenCVImage::undistortCameraImage(const QString& fileName,const cv::Mat& map1,const cv::Mat& map2)
{
	cv::Mat originalimage;
	cv::Mat undistort_img;
	originalimage = cv::imread(fileName.toStdString());
	cv::remap(originalimage,undistort_img,map1,map2,cv::INTER_LINEAR,cv::BORDER_CONSTANT,cv::Scalar());
	return undistort_img.clone();
}



void OpenCVImage::adjustImgToBoundingRect(void)
{
	Transformer boardTransformer(currImage);
	boardTransformer.findContoursThreshold(100,255,CV_BGR2GRAY,cv::THRESH_BINARY);

	cv::Rect boundRect;
	boardTransformer.findBoardBoundRect(boundRect);

//	//cv::rectangle(undistort_img, boundRect, CV_RGB(0,255,0), 2);
//
	cv::Point2f centerRect;
	boardTransformer.findCenterRect(boundRect,centerRect);
//
//	/*cv::circle(undistort_img, centerRect,5, cv::Scalar(0, 0, 255), 3);
//	cv::line(undistort_img, boundRect.tl(), boundRect.br(), cv::Scalar(0, 255, 0), 1);
//	cv::line(undistort_img,cv::Point(boundRect.tl().x,boundRect.tl().y+boundRect.height), cv::Point(boundRect.br().x,boundRect.br().y-boundRect.height), cv::Scalar(0, 255, 0), 1);*/
	QVector<cv::Point2f> furthestPoints;
	boardTransformer.find4FurthestPoints(centerRect,furthestPoints);

	QVector<cv::Point2f> destRect;
	boardTransformer.settingDestQuadrant(boundRect,destRect);

	QVector<cv::Point2f> orderedSrcRect;
	boardTransformer.settingSourceQuadrant(destRect,furthestPoints,orderedSrcRect);

	cv::Mat dst;
	dst=boardTransformer.applyPerspectiveTransform(orderedSrcRect,destRect);
	boardTransformer.setTransformImg(dst);
	boardTransformer.findContoursThreshold(100,255,CV_BGR2GRAY,cv::THRESH_BINARY);
	boardTransformer.findBoardBoundRect(boundRect);
	cv::Mat roi=boardTransformer.ROI(boundRect);
	setCurrImg(roi);
//
//	v.clear();
//	findContours(dst,v);
//
//	cv::Rect boundRect1;
//	findBoardBoundRect(v,boundRect1);
//
//	cv::rectangle(dst, boundRect1, CV_RGB(0,255,255), 2);
//	cv::line(dst, boundRect1.tl(), boundRect1.br(), cv::Scalar(0, 255, 255), 1);
//	cv::line(dst,cv::Point(boundRect1.tl().x,boundRect1.tl().y+boundRect1.height), cv::Point(boundRect1.br().x,boundRect1.br().y-boundRect1.height), cv::Scalar(0, 255, 255), 1);
//
//	//TODO обрезать картинку 
//	cv::Mat roi;
//	roi=dst(boundRect1);cv::Rect boundRect;
//	findBoardBoundRect(v,boundRect);
//	//cv::rectangle(undistort_img, boundRect, CV_RGB(0,255,0), 2);
//
//	cv::Point2f centerRect;
//	findCenterRect(boundRect,centerRect);
//
//	/*cv::circle(undistort_img, centerRect,5, cv::Scalar(0, 0, 255), 3);
//	cv::line(undistort_img, boundRect.tl(), boundRect.br(), cv::Scalar(0, 255, 0), 1);
//	cv::line(undistort_img,cv::Point(boundRect.tl().x,boundRect.tl().y+boundRect.height), cv::Point(boundRect.br().x,boundRect.br().y-boundRect.height), cv::Scalar(0, 255, 0), 1);*/
//	QVector<cv::Point2f> furthestPoints;
//	find4FurthestPoints(v,centerRect,furthestPoints);
//
//	QVector<cv::Point2f> destRect;
//	settingDestQuadrant(boundRect,destRect);
//
//	QVector<cv::Point2f> orderedSrcRect;
//	settingSourceQuadrant(destRect,furthestPoints,orderedSrcRect);
//
//	cv::Mat dst;
//	dst=applyPerspectiveTransform(undistort_img,orderedSrcRect,destRect);
//
//	v.clear();
//	findContours(dst,v);
//
//	cv::Rect boundRect1;
//	findBoardBoundRect(v,boundRect1);
//
//	cv::rectangle(dst, boundRect1, CV_RGB(0,255,255), 2);
//	cv::line(dst, boundRect1.tl(), boundRect1.br(), cv::Scalar(0, 255, 255), 1);
//	cv::line(dst,cv::Point(boundRect1.tl().x,boundRect1.tl().y+boundRect1.height), cv::Point(boundRect1.br().x,boundRect1.br().y-boundRect1.height), cv::Scalar(0, 255, 255), 1);
//
//	//TODO обрезать картинку 
//	cv::Mat roi;
//	roi=dst(boundRect1);
}


void OpenCVImage::setCurrImg(const cv::Mat& img)
{
	currImage.release();
	
	currImage=img.clone();
}
