#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H



#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "qdebug.h"


class CameraCalibrator{
private:
   std::vector<std::vector<cv::Point3f>> objectPoints;
   std::vector<std::vector<cv::Point2f>> imagePoints;
   //Square Lenght
   float squareLenght;
   //output Matrices
   cv::Mat cameraMatrix; //intrinsic
   cv::Mat distCoeffs;
   cv::Size boardSize_;
   //flag to specify how calibration is done
   int flag;
   //used in image undistortion
   cv::Mat map1,map2;
   bool mustInitUndistort;
public:
    CameraCalibrator(): flag(0), squareLenght(24.0), mustInitUndistort(true){};
    int addChessboardPoints(const std::vector<std::string>& filelist,cv::Size& boardSize){
        std::vector<std::string>::const_iterator itImg;
        std::vector<cv::Point2f> imageCorners;
        std::vector<cv::Point3f> objectCorners;
		boardSize_=boardSize;

        for(int i = 0; i<boardSize.height; i++){
            for(int j=0;j<boardSize.width;j++){
                objectCorners.push_back(cv::Point3f(float(i)*squareLenght,float(j)*squareLenght,0.0f));
            }
        }
    
        cv::Mat image; //to contain chessboard image
        int successes = 0;
    
        for(itImg=filelist.begin(); itImg!=filelist.end(); itImg++){
            image = cv::imread(*itImg,0);

            bool found = cv::findChessboardCorners(image, boardSize, imageCorners);

            cv::cornerSubPix(image, imageCorners, cv::Size(5,5),cv::Size(-1,-1),
                cv::TermCriteria(cv::TermCriteria::MAX_ITER+cv::TermCriteria::EPS,30,0.1));
            //if we have a good board, add it to our data
            if(imageCorners.size() == boardSize.area()){
                addPoints(imageCorners,objectCorners);
                successes++;
            }
        }
        return successes;
    }
    void addPoints(const std::vector<cv::Point2f>& imageCorners,const std::vector<cv::Point3f>& objectCorners){
     
        imagePoints.push_back(imageCorners);

        objectPoints.push_back(objectCorners);
    }
    double calibrate(cv::Size &imageSize){
        mustInitUndistort = true;
        std::vector<cv::Mat> rvecs,tvecs;
	

        return
            cv::calibrateCamera(objectPoints, //the 3D points
                imagePoints,
                imageSize, 
                cameraMatrix, //output camera matrix
                distCoeffs,
                rvecs,tvecs,
                flag);
    }
    void remap(const cv::Mat &image, cv::Mat &undistorted){

		std::cout<<cameraMatrix;
        if(mustInitUndistort){ //called once per calibration
            cv::initUndistortRectifyMap(
                cameraMatrix,
                distCoeffs,
                cv::Mat(),
                cameraMatrix,
                image.size(),
                CV_32FC1,
                map1,map2);
            mustInitUndistort = false;
        }
        //apply mapping functions
        cv::remap(image,undistorted,map1,map2,cv::INTER_LINEAR);
    }
	void SaveToFile(const QString& strFile,cv::Size& imageSize)
	{
		cv::FileStorage fs(strFile.toStdString(), cv::FileStorage::WRITE);
  fs << "camera_matrix" << cameraMatrix;
  fs << "distortion_coefficients" << distCoeffs;
  fs << "img_width" <<imageSize.width;
  fs << "img_height" << imageSize.height;
  fs << "square_size" << squareLenght;
	}
};
#endif