#ifndef __CAMERADEVICE_H__
#define __CAMERADEVICE_H__

/// #include <QObject>
#include <QThread>
#include <QImage>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

///#include <opencv2/opencv.hpp>
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
#define CAMERA_TICK 40

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
    void s_is_open(bool is_open);

public slots:
    void sl_start(int id);
    void sl_stop();
    void sl_is_open();

private slots:
    void onTimeout();

private:
    bool stop;
    bool is_open;
    cv::Mat frame;
    cv::Mat RGBframe;
    QImage img;
    int frameRate;

    cv::VideoCapture *m_capture;
  ///  VideoCapture* m_capture;
    QTimer * m_timer;
};

#endif // CAMERADEVICE_H
