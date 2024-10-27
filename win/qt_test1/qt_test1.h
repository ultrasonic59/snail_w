#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qt_test1.h"
#include <opencv2/opencv.hpp>
using namespace cv;
class qt_test1 : public QMainWindow
{
    Q_OBJECT

public:
    qt_test1(QWidget *parent = nullptr);
    ~qt_test1();
     VideoCapture _cap;
protected:
    void timerEvent(QTimerEvent* e);
    Mat cvFrame;

private:
    ///QTimer* timer;

    Ui::qt_test1Class ui;
};
