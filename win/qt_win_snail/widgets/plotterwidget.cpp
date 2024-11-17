#include "PlotterWidget.h"
#include "qpainter.h"
#include <QPainterPath>
#include <QPaintEvent>
#include <Qdebug>
#include <QFont>
#include <QMenu>
#include <QMessageBox>

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
#if 0
void plotterwidget::_updateImage(const QImage& _qimg)
{
    _m_qimg = _qimg.copy();
    __updateFPS();
    update();
}
#endif
#if 0
void plotterwidget::_updateImage(const cv::Mat& _cvmat)
{
#if 0
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
#endif
}
#endif
#if 0
void plotterwidget::_update_image(const QImage& img)
{
    _m_qimg = img.copy();
    __updateFPS();
    update();
}
#else
void plotterwidget::update_image1(QImage& img, QImage::Format _format)
{
    m_qimg = img.copy();
    __updateFPS();
    update();
}
void plotterwidget::update_image(QImage img, QImage::Format _format)
{
    m_qimg = img.copy();
    __updateFPS();
    update();
}
#endif
#if 0
void plotterwidget::updateImage(cv::Mat& _cvmat, QImage::Format _format)
{
    ////   m_cvmat = _cvmat.clone();
    ////   m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, m_cvmat.channels()*m_cvmat.cols, _format);
    ////   __updateFPS();
    ////   update();
    _updateImage(_cvmat);
}
#endif
#if 0
void plotterwidget::update_image(QImage& img, QImage::Format _format)
{
 ////   m_qimg = img.copy();

    ////   m_cvmat = _cvmat.clone();
    ////   m_qimg = QImage(m_cvmat.data, m_cvmat.cols, m_cvmat.rows, m_cvmat.channels()*m_cvmat.cols, _format);
    ////   __updateFPS();
    ////   update();
    _update_image(img);
}
#endif
#if 0
void plotterwidget::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
	QRect cr = contentsRect();
painter.drawPixmap(cr, QPixmap::fromImage(image));
painter.end();

}
#endif
#if 0
void plotterwidget::_setImage(QImage ipm)
{
_image=ipm;
////	 qDebug() << " _setImage " ;
//// UpdatePlot();
//qDebug() << "updating plotter widget image..";
update();
}
#endif
#if 1
void plotterwidget::resizeEvent(QResizeEvent *event)
{
QWidget::resizeEvent(event);  // 
}
#endif
///QRect t_viewR;
QRect plotterwidget::getViewR(void)
{
    return viewR;
}
void plotterwidget::update_image(const QImage& img)
{
    m_qimg = img.copy();
    __updateFPS();
    update();
}


void plotterwidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
#if 1
    QPainter painter(this);
    if (!m_qimg.isNull()) {
        viewR = __getRectInsideWidget(m_qimg.rect());
        painter.drawImage(viewR, m_qimg);
        ////       painter.setRenderHint(QPainter::Antialiasing);
        __drawFPS(painter, viewR);
    }
    else
        viewR = QRect();
#endif
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
///==========================================================
#if 0
PlotterWidget::mousePressEvent(event);
////qDebug() << "P"<<"curX1 " << curX1 <<"curX2 "<< curX2<<"curY1 " << curY1 <<"curY2 "<< curY2;
if (event->button() == Qt::LeftButton)
{
    mousePressed = true;
    curX1 = event->pos().x();
    curY1 = event->pos().y();
}
#endif
#if 0
void mousePressEvent(QGraphicsSceneMouseEvent* e) override {
    QGraphicsItem::mousePressEvent(e);
    if (e->button() & Qt::RightButton) {
        QMenu menu;
        QAction* a1 = menu.addAction(QString("test1"));
        QAction* a2 = menu.addAction(QString("test2"));
        if (a2 == menu.exec(e->screenPos())) {
            test2();
            _selected = true;
            update();
        }
    }
}
void test2() {
    QMessageBox::information(nullptr, "test2", "test2");
}
#endif

void plotterwidget::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    ///   point_data_t t_point_data;
    QPoint pos =event->pos();
    ////t_point_data.coord.setX(cur_x);
    if (event->button() == Qt::LeftButton)
    {
        mousePressed = true;
        curX1 = event->pos().x();
        curY1 = event->pos().y();

        if (event->modifiers() == Qt::ShiftModifier)
        {
 ///           t_point_data.coord = pos;
            emit sSetPoint(&pos);
        }
        else if (event->modifiers() == Qt::ControlModifier)
        {
            ///     t_point_data.coord = pos;
            ///     emit sSetPoint(&t_point_data);
            emit sClrPoint(&pos);
        }
    }
    if (event->button() == Qt::RightButton)
    {
      QPoint t_QPoint = event->screenPos().toPoint();
      qDebug() << "t_QPoint" << pos;/// t_QPoint;
     qDebug() << "sel_rc" << sel_rect;

        QMenu menu;
        QAction* a1 = menu.addAction(QString("Clear"));
        QAction* a2 = menu.addAction(QString("Move"));
 ////       QPointF t_QPointF = event->screenPos();

  ////      const QPoint t_QPoint = t_QPointF.toPoint();
#if 1
         if (a2 == menu.exec(event->screenPos().toPoint())) {
                test2();
           //// _selected = true;
 ////           update();
        }
#endif
    }
}
void plotterwidget::test2() {
    QMessageBox::information(nullptr, "test2", "test2");
}

void plotterwidget::mouseReleaseEvent(QMouseEvent* event)
{
 ////   plotterwidget::mouseReleaseEvent(event);
    mousePressed = false;
}
#if 0
void AdtView::mouseMoveEvent(QMouseEvent* event)
{
    PlotterWidget::mouseMoveEvent(event);
    QRect prev_rc;
    ////QRect sel_rect;
    QRect cr = contentsRect();
    emit show_tips(event->pos());

    if (mousePressed)
    {
        curX2 = event->pos().x();
        curY2 = event->pos().y();
        if (curX2 > curX1)
        {
            CurMouseRect.setLeft(curX1);
            CurMouseRect.setWidth(curX2 - curX1);
        }
        else
        {
            CurMouseRect.setLeft(curX2);
            CurMouseRect.setWidth(curX1 - curX2);
        }
        if (curY2 > curY1)
        {
            CurMouseRect.setY(curY1);
            CurMouseRect.setHeight(curY2 - curY1);
        }
        else
        {
            CurMouseRect.setY(curY2);
            CurMouseRect.setHeight(curY1 - curY2);
        }
        ////pen.setStyle( SolidLine);
    ////	qDebug() << "M"<<"curX1 " << curX1 <<"curX2 "<< curX2<<"curY1 " << curY1 <<"curY2 "<< curY2;

        ////qDebug() << "K"<< CurMouseRect;

        if (prev_rc != CurMouseRect)
        {
            prev_rc = CurMouseRect;
            sel_rect = CurMouseRect;
            ////	qDebug() << "sel_rect"<<"curX1 " << curX1 <<"curX2 "<< curX2<<"curY1 " << curY1 <<"curY2 "<< curY2;
            /////	qDebug() << "sel_rect" << sel_rect <<"contentsRect" << cr;

            emit sel_rect_changet(sel_rect);
        }

        update();
    }

}
#endif
void plotterwidget::mouseMoveEvent(QMouseEvent* event)
{
 ////   plotterwidget::mouseMoveEvent(event);
    QRect prev_rc;
    ///  point_data_t t_point_data;
    QPoint pos = event->pos();
    if (mousePressed)
    {
        curX2 = event->pos().x();
        curY2 = event->pos().y();
   ////     if (curX2 > curX1)
        {
            CurMouseRect.setLeft(curX1);
            CurMouseRect.setWidth(curX2 - curX1);
        }
  ////      else
  ////      {
   ////         CurMouseRect.setLeft(curX2);
   ////         CurMouseRect.setWidth(curX1 - curX2);
  ////  }
    ////    if (curY2 > curY1)
        {
            CurMouseRect.setY(curY1);
            CurMouseRect.setHeight(curY2 - curY1);
        }
   ////     else
   ////     {
   ////         CurMouseRect.setY(curY2);
  ////          CurMouseRect.setHeight(curY1 - curY2);
   ////     }
   
        ////qDebug() << "K"<< CurMouseRect;

        if (prev_rc != CurMouseRect)
        {
            prev_rc = CurMouseRect;
            sel_rect = CurMouseRect;
            ////	qDebug() << "sel_rect"<<"curX1 " << curX1 <<"curX2 "<< curX2<<"curY1 " << curY1 <<"curY2 "<< curY2;
            /////	qDebug() << "sel_rect" << sel_rect <<"contentsRect" << cr;

            emit sel_rect_changet(sel_rect);
        }

        update();

    }
#if 0
    ////    if (event->button() == Qt::LeftButton)
    {
        if (event->modifiers() == Qt::ShiftModifier)
        {
  ///          t_point_data.coord = pos;
            emit sMovePoint(&pos);
        }
    }
#endif
}
void plotterwidget::mouseDoubleClickEvent(QMouseEvent* event)
{
 ////   QPoint pos = getMouseInsideCoord(event->pos());
    QPoint pos = event->pos();

 ///   qDebug() << "mouseDoubleClickEvent";
    if (event->button() == Qt::LeftButton)
    {
        ;
  ///      t_point_data.coord = pos;
  ////      emit sClrPoint(&pos);
  ///   qDebug() << "mouseDoubleClickEvent left" ;
    }

}

QRect plotterwidget::get_sel_rect()
{
    return CurMouseRect;
}
#if 0
void AdtView::mousePressEvent(QMouseEvent* event)
{
    PlotterWidget::mousePressEvent(event);
    ////qDebug() << "P"<<"curX1 " << curX1 <<"curX2 "<< curX2<<"curY1 " << curY1 <<"curY2 "<< curY2;
    if (event->button() == Qt::LeftButton)
    {
        mousePressed = true;
        curX1 = event->pos().x();
        curY1 = event->pos().y();
    }
#endif