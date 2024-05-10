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

MyCamera::MyCamera(QObject* parent) : QObject(parent),
    pt_qcam(nullptr),
    m_transform(MyCamera::NoTransform)
{
 ///   connect(&m_qvideosurface, SIGNAL(frameAvailable(cv::Mat, QImage::Format)), this, SLOT(__transformFrame(cv::Mat, QImage::Format)));
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
