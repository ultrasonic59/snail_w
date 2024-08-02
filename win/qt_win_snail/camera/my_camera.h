#pragma once

#include <QObject>
#include <QCamera>

#include <qcustomvideosurface.h>
#include <opencv2/core.hpp>
#include "snail_data.h"

class MyCamera : public QObject
{
    Q_OBJECT
public:
    enum FrameTransform { NoTransform, RotateClockWise90Degree, RotateClockOpposite90Degree, FlipVertically, FlipHorizontally };
    explicit MyCamera(QObject* parent = 0, c_snail_data* _snail_data=0);
public:
    c_snail_data *p_snail_data;

public slots:
    void selectDevice();
    bool open();
    void pause();
    void resume();
    void close();
    void nextTransform();
    void setTransform(FrameTransform transform);
    void setViewfinderSettings(); // works only after QCamera::start() call

private slots:
    void __transformFrame(const cv::Mat& _mat, QImage::Format format);
    void __onError(QCamera::Error  _error);

private:
    QCamera* pt_qcam;
    QCustomVideoSurface m_qvideosurface;
    FrameTransform m_transform;
signals:
    void frameUpdated(cv::Mat& _cvmat, QImage::Format format);

};