#pragma once
#include "asm_opencv.h"
#include "CameraCalibrator.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include "Transformer.h"

#ifdef _MSC_VER
# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 3 && CV_SUBMINOR_VERSION == 1
// OpenCV 2.3.1
#  if defined(_DEBUG)
#  pragma comment(lib, "opencv_core231d.lib")
#  pragma comment(lib, "opencv_highgui231d.lib")
#  pragma comment(lib, "opencv_imgproc231d.lib")
#  pragma comment(lib, "opencv_video231d.lib")
#  pragma comment(lib, "opencv_ml231d.lib")

#  pragma comment(lib, "opencv_calib3d231d.lib")
#  pragma comment(lib, "opencv_objdetect231d.lib")
#  pragma comment(lib, "opencv_features2d231d.lib")
#  pragma comment(lib, "opencv_contrib231d.lib")
#  pragma comment(lib, "opencv_ts231d.lib")
#  pragma comment(lib, "opencv_legacy231d.lib")
#  pragma comment(lib, "opencv_flann231d.lib")
#  pragma comment(lib, "opencv_gpu231d.lib")
# else
#  pragma comment(lib, "opencv_core231.lib")
#  pragma comment(lib, "opencv_highgui231.lib")
#  pragma comment(lib, "opencv_imgproc231.lib")
#  pragma comment(lib, "opencv_video231.lib")
#  pragma comment(lib, "opencv_ml231.lib")

#  pragma comment(lib, "opencv_calib3d231.lib")
#  pragma comment(lib, "opencv_objdetect231.lib")
#  pragma comment(lib, "opencv_features2d231.lib")
#  pragma comment(lib, "opencv_contrib231.lib")
#  pragma comment(lib, "opencv_ts231.lib")
#  pragma comment(lib, "opencv_legacy231.lib")
#  pragma comment(lib, "opencv_flann231.lib")
#  pragma comment(lib, "opencv_gpu231.lib")
# endif //#  if defined(_DEBUG)

//# endif //# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 3

# else if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION ==4  && CV_SUBMINOR_VERSION == 2
// OpenCV 2.4.2
#  if defined(_DEBUG)
#  pragma comment(lib, "opencv_core2411d.lib")
#  pragma comment(lib, "opencv_highgui2411d.lib")
#  pragma comment(lib, "opencv_imgproc2411d.lib")
#  pragma comment(lib, "opencv_video2411d.lib")
#  pragma comment(lib, "opencv_ml2411d.lib")

#  pragma comment(lib, "opencv_calib3d2411d.lib")
#  pragma comment(lib, "opencv_objdetect2411d.lib")
#  pragma comment(lib, "opencv_features2d2411d.lib")
#  pragma comment(lib, "opencv_contrib2411d.lib")
#  pragma comment(lib, "opencv_ts2411d.lib")
#  pragma comment(lib, "opencv_legacy2411d.lib")
#  pragma comment(lib, "opencv_flann2411d.lib")
#  pragma comment(lib, "opencv_gpu2411d.lib")
# else
#  pragma comment(lib, "opencv_core2411.lib")
#  pragma comment(lib, "opencv_highgui2411.lib")
#  pragma comment(lib, "opencv_imgproc2411.lib")
#  pragma comment(lib, "opencv_video2411.lib")
#  pragma comment(lib, "opencv_ml2411.lib")

#  pragma comment(lib, "opencv_calib3d2411.lib")
#  pragma comment(lib, "opencv_objdetect2411.lib")
#  pragma comment(lib, "opencv_features2d2411.lib")
#  pragma comment(lib, "opencv_contrib2411.lib")
#  pragma comment(lib, "opencv_ts2411.lib")
#  pragma comment(lib, "opencv_legacy2411.lib")
#  pragma comment(lib, "opencv_flann2411.lib")
#  pragma comment(lib, "opencv_gpu2411.lib")
# endif //#  if defined(_DEBUG)

# endif //# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 4
#endif //#ifdef _MSC_VER

class OpenCVImage
{
public:
	OpenCVImage(void);
	virtual ~OpenCVImage(void);
	bool loadImage(const QString& imgFileName);
	void resizeImage(float factorWidth,float factorHeight);
	void loadUndistortFile(const QString& undistortFileName);
	void undistortImage();
	QPixmap curPixmap();

private:
	cv::Mat debugImg;
	cv::Mat currImage;
	cv::Mat map1;
	cv::Mat map2;
private:

	void loadDistortCameraMatrix(const QString& filename,cv::Mat& mat1,cv::Mat& mat2);
	cv::Mat undistortCameraImage(const QString& filename,const cv::Mat& mat1,const cv::Mat& mat2);

public:
	void adjustImgToBoundingRect(void);
	void setCurrImg(const cv::Mat& img);
};

