#pragma once

#include <QtWidgets/QMainWindow>
#include "PlotterWidget.h"

#include "ui_win_snail.h"
///======================================================================
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class win_snail; };
QT_END_NAMESPACE

using namespace cv;

class win_snail : public QMainWindow
{
    Q_OBJECT

public:
    win_snail(QWidget *parent = nullptr);
    ~win_snail();
public:
    plotterwidget* p_CamView;
private:
    QLabel* _label;
    QPen pen;

    VideoCapture _cap;
    Mat _frame;
    QImage    _image;
public slots:
    void setCamImage(QImage ipm);

protected:
    void timerEvent(QTimerEvent* e);

private:
    Ui::win_snail *ui;
signals:
    void updateCamView(QImage);

};
