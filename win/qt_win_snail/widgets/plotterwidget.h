#pragma once
#include <QWidget>
#include <opencv2/core.hpp>

class plotterwidget : public QWidget
{
public:
	plotterwidget(QWidget *parent=0);
///	plotterwidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~plotterwidget(void);
   QImage image;

public slots:
	void _setImage(QImage);
public slots:
	void updateImage(const QImage& _qimg);
	void updateImage(const cv::Mat& _cvmat);
	void updateImage(cv::Mat _cvmat, QImage::Format _format);

protected:
    void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *event);
private:
    QRect __getRectInsideWidget(const QRect& _rect);
    void __updateFPS();
    void __drawFPS(QPainter& painter, const QRect& _rect);

    QImage m_qimg;
    cv::Mat m_cvmat;

    double m_tick;
    double m_fps;

};

