#include "win_snail.h"

QImage Mat2QImage(cv::Mat cvImg);

win_snail::win_snail(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win_snail())
{
    ui->setupUi(this);
    int camid = 0; // video device id

    if (!_cap.open(camid))
    {
        qDebug() << "camera open failed.";
        return;
    }

    p_CamView = ui->CamWidget;
    connect(this, SIGNAL(updateCamView(QImage)), this, SLOT(setCamImage(QImage)));
    startTimer(100);

}

win_snail::~win_snail()
{
    delete ui;
}
void win_snail::setCamImage(QImage ipm)
{
    p_CamView->_setImage(ipm);
}
void win_snail::timerEvent(QTimerEvent* e)
{

    _cap >> _frame;
    _image = Mat2QImage(_frame);
    QPainter painter(&_image);    ////???   _label->setPixmap(QPixmap::fromImage(_image));
    painter.setPen(QPen(Qt::red, 40, Qt::SolidLine));
    painter.setFont(QFont("Arial", 20));
  ////  QRect text_rc = QRect(15, 25, 200,100);
    QRect text_rc = _image.rect();

    painter.drawText(text_rc, Qt::AlignVCenter | Qt::AlignCenter,"TEST");

    painter.end();
    emit updateCamView(_image);
}

///=================================================================
QImage Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;

    ////   cv::cvtColor(cvImg, cvImg, CV_BGR2RGB); // color format conversion
    cv::cvtColor(cvImg, cvImg, COLOR_BGR2RGB); // color format conversion
  ////  cv::cvtColor(cvImg, cvImg, COLOR_BGR2GRAY); // color format conversion
    qImg = QImage((const unsigned char*)(cvImg.data),
        cvImg.cols, cvImg.rows,
        cvImg.cols * cvImg.channels(),
        QImage::Format_RGB888);

    return qImg;
}
///======================================================================