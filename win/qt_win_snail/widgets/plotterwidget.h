#pragma once
#include <QWidget>
#include <QPen>
#include <QMenu>
#include <opencv2/core.hpp>
#include "snail_data.h"

class plotterwidget : public QWidget
{
    Q_OBJECT
public:
	plotterwidget(QWidget *parent=0);
///	plotterwidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~plotterwidget(void);
 ////  QImage _image;
public:
    QRect getViewR(void);
    QRect get_sel_rect();
    QRect sel_rect;
protected:
    QPen pen_select;
protected:
    quint16 curX1;
    quint16 curX2;
    quint16 curY1;
    quint16 curY2;

    quint16 prevX1;
    quint16 prevX2;
    quint16 prevY1;
    quint16 prevY2;
    QRect CurMouseRect;
    ////	QRect PrevMouseCoord;
    bool mousePressed;
    void test2();
public slots:
////	void _setImage(QImage);

public slots:
    void update_image(QImage& img, QImage::Format _format);


protected:
    void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *event);
    QRect viewR;
private:
    QRect __getRectInsideWidget(const QRect& _rect);
    void __updateFPS();
    void __drawFPS(QPainter& painter, const QRect& _rect);
    ///QPoint getMouseInsideCoord(QPoint inPoint);

    QImage m_qimg;
////    cv::Mat _m_cvmat;

    double m_tick;
    double m_fps;
protected:

	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

///	virtual void wheelEvent(QWheelEvent* event) override;

signals:
 ///   void sSetPoint(point_data_t* pd);
 ///   void sMovePoint(point_data_t* pd);
    void sSetPoint(QPoint* pn);
    void sMovePoint(QPoint* pn);
    void sClrPoint(QPoint* pn);
    void sel_rect_changet(QRect rc);


};

