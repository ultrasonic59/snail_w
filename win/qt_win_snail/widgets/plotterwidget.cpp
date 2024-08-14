#include "PlotterWidget.h"
#include "qpainter.h"
#include <QPainterPath>
#include <QPaintEvent>
#include <Qdebug>
#include <QFont>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

plotterwidget::plotterwidget(QWidget *parent) :
								QWidget(parent),
                                m_fps(0)
{

}
plotterwidget::~plotterwidget(void)
{
////	pPlotter = nullptr;
}

void plotterwidget::_updateImage(const QImage& _qimg)
{
    m_qimg = _qimg.copy();
    __updateFPS();
    update();
}

void plotterwidget::_updateImage(const cv::Mat& _cvmat)
{
    switch (_cvmat.type()) {
    case CV_8UC1: {
        m_cvmat = _cvmat.clone();
        m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, m_cvmat.cols, QImage::Format_Grayscale8);
    } break;
    case CV_8UC3: {
        cv::cvtColor(_cvmat, m_cvmat, cv::COLOR_BGR2RGB);
        m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, 3 * m_cvmat.cols, QImage::Format_RGB888);
    } break;
    case CV_8UC4: {
        m_cvmat = _cvmat.clone();
        m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, 4 * m_cvmat.cols, QImage::Format_RGB32);
    } break;
    }
    __updateFPS();
    update();
}
void plotterwidget::_update_image(const QImage& img)
{
    m_qimg = img.copy();
    __updateFPS();
    update();
}

void plotterwidget::updateImage(cv::Mat& _cvmat, QImage::Format _format)
{
    ////   m_cvmat = _cvmat.clone();
    ////   m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, m_cvmat.channels()*m_cvmat.cols, _format);
    ////   __updateFPS();
    ////   update();
    _updateImage(_cvmat);
}
void plotterwidget::update_image(QImage& img, QImage::Format _format)
{
 ////   m_qimg = img.copy();

    ////   m_cvmat = _cvmat.clone();
    ////   m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, m_cvmat.channels()*m_cvmat.cols, _format);
    ////   __updateFPS();
    ////   update();
    _update_image(img);
}

#if 0
void plotterwidget::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
	QRect cr = contentsRect();
painter.drawPixmap(cr, QPixmap::fromImage(image));
painter.end();

}
#endif

void plotterwidget::_setImage(QImage ipm)
{
image=ipm;
////	 qDebug() << " _setImage " ;
//// UpdatePlot();
//qDebug() << "updating plotter widget image..";
update();
}

#if 1
void plotterwidget::resizeEvent(QResizeEvent *event)
{
QWidget::resizeEvent(event);  // 
}
#endif
///QRect t_viewR;

void plotterwidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (!m_qimg.isNull()) {
        QRect viewR = __getRectInsideWidget(m_qimg.rect());
  ///      t_viewR = viewR;
        painter.drawImage(viewR, m_qimg);
        painter.setRenderHint(QPainter::Antialiasing);
        __drawFPS(painter, viewR);
    }
}

QRect plotterwidget::__getRectInsideWidget(const QRect& _rect)
{
    QRect outrect = rect();
    float w2h = static_cast<float>(_rect.width()) / static_cast<float>(_rect.height());
    if (w2h > static_cast<float>(rect().width()) / static_cast<float>(rect().height())) {
        outrect.setWidth(rect().width());
        outrect.setHeight(static_cast<int>(rect().width() / w2h));
        outrect.moveTop(static_cast<int>((rect().height() - outrect.height()) / 2.0f));
    }
    else {
        outrect.setHeight(rect().height());
        outrect.setWidth(static_cast<int>(rect().height() * w2h));
        outrect.moveLeft(static_cast<int>((rect().width() - outrect.width()) / 2.0f));
    }
    return outrect;
}

void plotterwidget::__updateFPS()
{
    double tick = static_cast<double>(cv::getTickCount());
    m_fps = (m_fps + cv::getTickFrequency() / (tick - m_tick)) / 2.0;
    m_tick = tick;
}

void plotterwidget::__drawFPS(QPainter& painter, const QRect& _rect)
{
    QPainterPath path;
    QFont _font = font();
    double pS = 0.020 * std::sqrt(_rect.width() * _rect.width() + _rect.height() * _rect.height()) + 10.0;
    _font.setPointSizeF(pS);
    path.addText(_rect.x() + pS, _rect.y() + 2 * pS, _font, QString::number(m_fps, 'f', 1));
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawPath(path);
    path.clear();
    path.addText(_rect.x() + 0.95f * pS, _rect.y() + 1.85f * pS, _font, QString::number(m_fps, 'f', 1));
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    painter.drawPath(path);
}
extern int t_cols;
extern int t_rows;
////QRect t_viewR;
///==========================================================
QPoint plotterwidget::getMouseInsideCoord(QPoint inPos)
{
    QPoint rez;
  QRect viewR = QRect();
  if (!m_qimg.isNull()) {
        viewR = __getRectInsideWidget(m_qimg.rect());
  }
  float coef_x = t_cols;
  coef_x /= viewR.width();
  float coef_y = t_rows;
  coef_y /= viewR.height();
  float xx = (inPos.x() - viewR.x()) * coef_x;
  float yy = (inPos.y() - viewR.y()) * coef_y;
 /// xx = (inPos.x() - viewR.x())* coef_x;
 /// yy = (inPos.y() - viewR.y())* coef_y;
 /// xx *= coef_x;
 /// yy *= coef_y;
  rez.setX( (int)xx);
  rez.setY( (int)yy);

  return rez;
}

void plotterwidget::mousePressEvent(QMouseEvent* event)
{
point_data_t t_point_data;
QPoint pos = getMouseInsideCoord(event->pos());
 ////t_point_data.coord.setX(cur_x);
if (event->button() == Qt::LeftButton)
    {
    if (event->modifiers() == Qt::ShiftModifier)
    {
        t_point_data.coord = pos;
        emit sSetPoint(&t_point_data);
    }
 else if (event->modifiers() == Qt::ControlModifier)
        {
   ///     t_point_data.coord = pos;
   ///     emit sSetPoint(&t_point_data);
        emit sClrPoint(&pos);
    }
    }
}
void plotterwidget::mouseMoveEvent(QMouseEvent* event)
{
    point_data_t t_point_data;
    QPoint pos = getMouseInsideCoord(event->pos());

////    if (event->button() == Qt::LeftButton)
    {
        if (event->modifiers() == Qt::ShiftModifier)
        {
            t_point_data.coord = pos;
            emit sMovePoint(&t_point_data);
        }
    }

}
void plotterwidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pos = getMouseInsideCoord(event->pos());

 ///   qDebug() << "mouseDoubleClickEvent";
    if (event->button() == Qt::LeftButton)
    {
        ;
  ///      t_point_data.coord = pos;
  ////      emit sClrPoint(&pos);
  ///   qDebug() << "mouseDoubleClickEvent left" ;
    }

}

#if 0
int curX1 = event->pos().x();
int curY1 = event->pos().y();
point_data_t t_point_data;
QRect viewR = QRect();
if (!m_qimg.isNull()) {
    viewR = __getRectInsideWidget(m_qimg.rect());
}
 
qDebug() << "t_viewR=" << viewR;
int offs_x;
int offs_y;

offs_x = viewR.x();
offs_y = viewR.y();

qDebug() << "t_cols=" << t_cols;
qDebug() << "t_rows=" << t_rows;

qDebug() << "mousePressEvent"<< curX1 << curY1;

float xx;
float yy;

float coef_x;
    float coef_y;
  ///  int cr_w=cr.width();
 ///   int cr_h =cr.height();
    int cr_w = viewR.width();
    int cr_h = viewR.height();

    int cur_x;
    int cur_y;
    coef_x = t_cols;
    coef_x /= cr_w;

    coef_y = t_rows;
    coef_y /= cr_h;

    qDebug() << "coef_x=" << coef_x;
    qDebug() << "coef_y=" << coef_y;

    xx = curX1- offs_x;
    yy = curY1- offs_y;
    xx *= coef_x;
    yy *= coef_y;
    cur_x = (int)xx;
    cur_y= (int)yy;

    qDebug() << "cur_x=" << cur_x;
    qDebug() << "cur_y=" << cur_y;
 ///   cur_x -= offs_x;
 ///   cur_y -= offs_y;
 ///   qDebug() << "cur_x1=" << cur_x;
 ///   qDebug() << "cur_y1=" << cur_y;

#if 1
    ////PlotterWidget::mousePressEvent(event);
    ////qDebug() << "P"<<"curX1 " << curX1 <<"curX2 "<< curX2<<"curY1 " << curY1 <<"curY2 "<< curY2;
    if (event->button() == Qt::LeftButton)
    {
        ////mousePressed = true;
 ///       curX1 = event->pos().x();
 ///       curY1 = event->pos().y();
        t_point_data.coord.setX(cur_x);
        t_point_data.coord.setY(cur_y);
        emit sSetPoint(&t_point_data);
    }
    ////if (event->button() == Qt::RightButton)
    ////{
        ///emit show_tips(event->pos());
    ////}
#endif
 ///   point_data_t t_point_data;
  ///  t_point_data.coord.setX(curX1);
 ///   t_point_data.coord.setY(curY1);

 ///  emit sSetPoint(&t_point_data);

}
#endif