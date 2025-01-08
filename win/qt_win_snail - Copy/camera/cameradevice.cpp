#include "cameradevice.h"
#include <QTimer>
#include <QImage>
#include <map>
#include <QDebug>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
/// #include "cvmatandqimage.h"
#include "DeviceEnumerator.h"

using namespace cv;

CameraDevice::CameraDevice(QObject *parent) :
    QObject(parent), is_open(false), stop(false)
{
 ////   m_capture = new VideoCapture;
    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

CameraDevice::~CameraDevice()
{
    delete m_capture;
    m_capture = NULL;
}

void CameraDevice::sl_start(int id)
{
m_capture = new VideoCapture(id);
if (m_capture->isOpened())
   {
    frameRate = (int)m_capture->get(CAP_PROP_FPS);
    m_timer->start(CAMERA_TICK);
    is_open = true;
   }
else
   is_open = false;
emit s_is_open(is_open);
////return m_capture->isOpened();
}

void CameraDevice::sl_stop()
{
if (m_capture->isOpened())
    m_capture->release();
m_timer->stop();

 ////   return true;
}
void CameraDevice::sl_is_open()
{
emit s_is_open(is_open);
}


void CameraDevice::onTimeout()
{
if (!m_capture->isOpened())
        return;
///=========================================
if (!m_capture->read(frame))
   {
    stop = true;
   }
else {
    if (frame.channels() == 3) {
        cv::cvtColor(frame, RGBframe, COLOR_BGR2RGB);
        img = QImage((const unsigned char*)(RGBframe.data),
            RGBframe.cols, RGBframe.rows, QImage::Format_RGB888);
    }
    else {
        img = QImage((const unsigned char*)(frame.data),
            frame.cols, frame.rows, QImage::Format_Indexed8);
    }
    emit imageReady(img);
}
///=========================================
 ////static cv::Mat frame;
///*m_capture >> frame;
 ///   if (frame.cols)
 ///       emit imageReady(QtOcv::mat2Image(frame));
///emit imageReady(img);
}

QList<camera_info> CameraDevice::enumerator()
{
DeviceEnumerator de;
QList<camera_info> rez;
camera_info t_info;
std::map<int, Device> devices = de.getVideoDevicesMap();
// Print information about the devices

for (auto const& device : devices) {
    t_info.id = device.first;
    t_info.devicePath = QString::fromUtf8(device.second.devicePath.data(),int(device.second.devicePath.size()));
   /// t_info.deviceName = QString::fromUtf8(device.second.deviceName.data(), int(device.second.deviceName.size()));
    t_info.deviceName = QString::fromStdString(device.second.deviceName);
    rez << t_info;

    ///   std::cout << "== VIDEO DEVICE (id:" << device.first << ") ==" << std::endl;
 ///   std::cout << "Name: " << device.second.deviceName << std::endl;
 ///   std::cout << "Path: " << device.second.devicePath << std::endl;
}


return rez;
}
////fromUtf8(s.data(), int(s.size()));