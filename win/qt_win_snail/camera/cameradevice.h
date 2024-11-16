#ifndef __CAMERADEVICE_H__
#define __CAMERADEVICE_H__

#include <QObject>
#include <opencv2/opencv.hpp>
/*
QT_BEGIN_NAMESPACE
class QTimer;
class QImage;
QT_END_NAMESPACE
*/
struct camera_info {
    int id; // This can be used to open the device in OpenCV
    QString devicePath;
    QString deviceName; // This can be used to show the devices to the user
};
/*
namespace cv{
    class VideoCapture;
    class Mat;
}
*/
////using namespace cv;
///using namespace cv;

class CameraDevice : public QObject
{
    Q_OBJECT
public:
    explicit CameraDevice(QObject *parent = 0);
    ~CameraDevice();
public:

    QList<camera_info>  enumerator();

signals:
    void imageReady(const QImage& image);

public slots:
    bool start(int id);
    bool stop();

private slots:
    void onTimeout();

private:
    cv::VideoCapture cap;
   cv::VideoCapture *m_capture;
  ///  VideoCapture* m_capture;
    QTimer * m_timer;
};

#endif // CAMERADEVICE_H
