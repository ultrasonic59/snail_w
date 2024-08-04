#include "my_camera.h"
#include <QDialog>
#include <QCameraViewfinderSettings>
#include <QCameraInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QVariant>
#include <QByteArray>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes

MyCamera::MyCamera(QObject* parent, c_snail_data* _snail_data) : QObject(parent),
    pt_qcam(nullptr), p_snail_data(_snail_data),
    m_transform(MyCamera::NoTransform)
{
    connect(&m_qvideosurface, SIGNAL(frameAvailable(cv::Mat, QImage::Format)), this, SLOT(__transformFrame(cv::Mat, QImage::Format)));
}

void MyCamera::selectDevice()
{
    QDialog dialog;
    int pS = dialog.font().pointSize();
    dialog.resize(40 * pS, 10 * pS);

    QVBoxLayout dialogL;

    QComboBox devicesCB;
    QList<QCameraInfo> devlist = QCameraInfo::availableCameras();
    for (int i = 0; i < devlist.length(); i++)
        devicesCB.addItem(devlist.at(i).description());

    QHBoxLayout buttonsL;
   
    QPushButton cancelB(tr("Cancel"));
    
    connect(&cancelB, SIGNAL(clicked()), &dialog, SLOT(reject()));
    QPushButton acceptB(tr("Accept"));
    connect(&acceptB, SIGNAL(clicked()), &dialog, SLOT(accept()));
    buttonsL.addWidget(&cancelB);
    buttonsL.addWidget(&acceptB);

    dialogL.addWidget(&devicesCB);
    dialogL.addLayout(&buttonsL);

    dialog.setLayout(&dialogL);

    if (dialog.exec() == QDialog::Accepted) {
        delete pt_qcam;
        pt_qcam = nullptr;
        pt_qcam = new QCamera(devlist.at(devicesCB.currentIndex()));
    }

}
///================================================================
bool MyCamera::open()
{
    if (pt_qcam != nullptr) {
        connect(pt_qcam, SIGNAL(error(QCamera::Error)), this, SLOT(__onError(QCamera::Error)));
        pt_qcam->setViewfinder(&m_qvideosurface);
        pt_qcam->start();
        return true;
    }
    else {
        return false;
    }
}

void MyCamera::__onError(QCamera::Error _error)
{
    switch (_error) {
    case QCamera::NoError:
        qWarning("QCamera: no errors have occurred");
        break;
    case QCamera::CameraError:
        qWarning("QCamera: an error has occurred");
        break;
    case QCamera::InvalidRequestError:
        qWarning("QCamera: system resource doesn't support requested functionality");
        break;
    case QCamera::ServiceMissingError:
        qWarning("QCamera: no camera service available");
        break;
    case QCamera::NotSupportedFeatureError:
        qWarning("QCamera: the feature is not supported");
        break;
    }
}


void MyCamera::close()
{
    if (pt_qcam != nullptr) {
        pt_qcam->stop();
    }
}

void MyCamera::pause()
{
    if (pt_qcam != nullptr) {
        pt_qcam->stop();
    }
}

void MyCamera::resume()
{
    if (pt_qcam != nullptr) {
        pt_qcam->start();
    }
}
int t_cols;
int t_rows;

void MyCamera::__transformFrame(const cv::Mat& _mat, QImage::Format format)
{
    cv::Mat tmpmat;
    switch (m_transform) {
    case NoTransform:
        tmpmat = _mat;
        break;
    case FlipVertically:
        cv::flip(_mat, tmpmat, 0);
        break;
    case FlipHorizontally:
        cv::flip(_mat, tmpmat, 1);
        break;
    case RotateClockWise90Degree:
        cv::flip(_mat, tmpmat, 0);
        cv::transpose(tmpmat, tmpmat);
        break;
    case RotateClockOpposite90Degree:
        cv::flip(_mat, tmpmat, 1);
        cv::transpose(tmpmat, tmpmat);
        break;
    }
 ////    cv::circle(tmpmat, (900, 500), 100, (0, 0, 255), 5, cv::LINE_AA);
    //####################(  Draw Circle  )#########################
    // unfilled circle
  ///  cv::Point centerCircle1(1200, 250);
    int radiusCircle = 4;
    cv::Scalar colorCircle1(0, 0, 255);
    int thicknessCircle1 = 2;
#if 1
  ///  p_snail_data
    t_cols= _mat.cols;
    t_rows= _mat.rows;
    /*
    float coef_x;
    float coef_y;
    int cur_x;
    int cur_y;
    coef_x = t_cols;
    coef_y = t_rows;
*/
        point_data_t t_point_data;
    for (int ii = 0; ii < p_snail_data->points.size(); ++ii) {
        t_point_data = p_snail_data->points.at(ii);
        cv::Point centerCircle1(t_point_data.coord.x(), t_point_data.coord.y());
        cv::circle(tmpmat, centerCircle1, radiusCircle, colorCircle1, thicknessCircle1);
   ////     qDebug() << "mousePressEvent" << curX1 << curY1;


      }
#endif


    ///cv::circle(tmpmat, centerCircle1, radiusCircle, colorCircle1, thicknessCircle1);


    emit frameUpdated(tmpmat, format);
}

void MyCamera::nextTransform()
{
    m_transform = static_cast<FrameTransform>((static_cast<int>(m_transform) + 1) % 5); // 5 is a number of FrameTransform instances
    qWarning("Transform selected %d", m_transform);
}

void MyCamera::setTransform(FrameTransform _transform)
{
    m_transform = _transform;
}

void MyCamera::setViewfinderSettings()
{
    if (pt_qcam) {

        QDialog dialog;
        int pS = dialog.font().pointSize();
        dialog.resize(40 * pS, 10 * pS);

        QVBoxLayout dialogL;

        QComboBox settingsCB;
        QList<QCameraViewfinderSettings> settingsList = pt_qcam->supportedViewfinderSettings();
        for (int i = 0; i < settingsList.length(); i++) {
            QString description = QString("%1x%2 - %3 fps").arg(QString::number(settingsList[i].resolution().width()),
                QString::number(settingsList[i].resolution().height()),
                QString::number(settingsList[i].minimumFrameRate(), 'f', 1));
            settingsCB.addItem(description);
        }

        QHBoxLayout buttonsL;
        QPushButton cancelB(tr("Cancel"));
        connect(&cancelB, SIGNAL(clicked()), &dialog, SLOT(reject()));
        QPushButton acceptB(tr("Accept"));
        connect(&acceptB, SIGNAL(clicked()), &dialog, SLOT(accept()));
        buttonsL.addWidget(&cancelB);
        buttonsL.addWidget(&acceptB);

        dialogL.addWidget(&settingsCB);
        dialogL.addLayout(&buttonsL);

        dialog.setLayout(&dialogL);

        if (dialog.exec() == QDialog::Accepted)
            pt_qcam->setViewfinderSettings(settingsList[settingsCB.currentIndex()]);
    }
}
