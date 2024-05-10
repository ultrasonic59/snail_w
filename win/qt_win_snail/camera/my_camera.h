#pragma once

#include <QObject>
#include <QCamera>

class MyCamera : public QObject
{
    Q_OBJECT
public:
    enum FrameTransform { NoTransform, RotateClockWise90Degree, RotateClockOpposite90Degree, FlipVertically, FlipHorizontally };
    explicit MyCamera(QObject* parent = 0);
public slots:
    void selectDevice();

private:
    QCamera* pt_qcam;
    FrameTransform m_transform;

};