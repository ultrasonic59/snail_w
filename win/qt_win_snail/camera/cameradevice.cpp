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
    QObject(parent)
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

bool CameraDevice::start(int id)
{
if (m_capture->isOpened())
    return true;

m_capture->open(id);
if (m_capture->isOpened())
     m_timer->start(40);
return m_capture->isOpened();
}

bool CameraDevice::stop()
{
    if (m_capture->isOpened())
        m_capture->release();

    return true;
}

void CameraDevice::onTimeout()
{
    if (!m_capture->isOpened())
        return;

    static cv::Mat frame;
    *m_capture >> frame;
 ///   if (frame.cols)
 ///       emit imageReady(QtOcv::mat2Image(frame));
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