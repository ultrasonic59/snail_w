#include "qcustomvideosurface.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QDebug>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

cv::Mat QImage2Mat(QImage const& src);
static QImage QVideoFrameToQImage(const QVideoFrame& videoFrame);
////static cv::Mat QImageToCvMat(QImage inImage, bool inCloneImageData);

QCustomVideoSurface::QCustomVideoSurface(QObject* parent): QAbstractVideoSurface(parent)
{
}

QList<QVideoFrame::PixelFormat> QCustomVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    qDebug() << handleType;
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_RGB24
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555
                << QVideoFrame::Format_ARGB8565_Premultiplied
                << QVideoFrame::Format_BGRA32
                << QVideoFrame::Format_BGRA32_Premultiplied
                << QVideoFrame::Format_BGR32
                << QVideoFrame::Format_BGR24
                << QVideoFrame::Format_BGR565
                << QVideoFrame::Format_BGR555
                << QVideoFrame::Format_BGRA5658_Premultiplied
                << QVideoFrame::Format_AYUV444
                << QVideoFrame::Format_AYUV444_Premultiplied
                << QVideoFrame::Format_YUV444
                << QVideoFrame::Format_YUV420P
                << QVideoFrame::Format_YV12
                << QVideoFrame::Format_UYVY
                << QVideoFrame::Format_YUYV
                << QVideoFrame::Format_NV12
                << QVideoFrame::Format_NV21
                << QVideoFrame::Format_IMC1
                << QVideoFrame::Format_IMC2
                << QVideoFrame::Format_IMC3
                << QVideoFrame::Format_IMC4
                << QVideoFrame::Format_Y8
                << QVideoFrame::Format_Y16
                << QVideoFrame::Format_Jpeg
                << QVideoFrame::Format_CameraRaw
                << QVideoFrame::Format_AdobeDng;
    }
    return QList<QVideoFrame::PixelFormat>();
}

cv::Mat QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
  ///  cvtColor(tmp, result, cv::COLOR_BGR2RGB);
    return result;
}

#if 0
QImage Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp; // make the same cv::Mat
    cvtColor(src, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage dest((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

cv::Mat QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cvtColor(tmp, result, CV_BGR2RGB);
    return result;
}


static cv::Mat QImageToMat(const QImage& image) {
    cv::Mat out;
    switch (image.format()) {
    case QImage::Format_Invalid:
    {
        cv::Mat empty;
        empty.copyTo(out);
        break;
    }
    case QImage::Format_RGB32:
    {
        cv::Mat view(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        view.copyTo(out);
        break;
    }
    case QImage::Format_RGB888:
    {
        cv::Mat view(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(view, out, cv::COLOR_RGB2BGR);
        break;
    }
    default:
    {
        QImage conv = image.convertToFormat(QImage::Format_ARGB32);
        cv::Mat view(conv.height(), conv.width(), CV_8UC4, (void*)conv.constBits(), conv.bytesPerLine());
        view.copyTo(out);
        break;
    }
    }
    return out;
}


#endif

static QImage QVideoFrameToQImage(const QVideoFrame& videoFrame) {
    if (videoFrame.handleType() == QAbstractVideoBuffer::NoHandle)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        QImage image = videoFrame.image();
#else
        QImage image = qt_imageFromVideoFrame(videoFrame);
#endif
        if (image.isNull()) 
            return QImage();
        if (image.format() != QImage::Format_ARGB32) 
            return image.convertToFormat(QImage::Format_ARGB32);
        return image;
    }
    if (videoFrame.handleType() == QAbstractVideoBuffer::GLTextureHandle)
    {
        QImage image(videoFrame.width(), videoFrame.height(), QImage::Format_ARGB32);
        GLuint textureId = static_cast<GLuint>(videoFrame.handle().toInt());
        QOpenGLContext* ctx = QOpenGLContext::currentContext();
        QOpenGLFunctions* f = ctx->functions();
        GLuint fbo;
        f->glGenFramebuffers(1, &fbo);
        GLint prevFbo;
        f->glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFbo);
        f->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
        f->glReadPixels(0, 0, videoFrame.width(), videoFrame.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
        f->glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(prevFbo));
        return image.rgbSwapped();
    }
    return QImage();
}
///===============================
////static 
cv::Mat QImageToCvMat(QImage inImage, bool inCloneImageData = true)
{
    switch (inImage.format())
    {
        // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat  mat(inImage.height(), inImage.width(),
            CV_8UC4,
            const_cast<uchar*>(inImage.bits()),
            static_cast<size_t>(inImage.bytesPerLine())
        );

        return (inCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB32:
    {
        if (!inCloneImageData)
        {
            qWarning() << "QImageToCvMat() - Conversion requires cloning so we don't modify the original QImage data";
        }

        cv::Mat  mat(inImage.height(), inImage.width(),
            CV_8UC4,
            const_cast<uchar*>(inImage.bits()),
            static_cast<size_t>(inImage.bytesPerLine())
        );

        cv::Mat  matNoAlpha;

        cv::cvtColor(mat, matNoAlpha, cv::COLOR_BGRA2BGR);   // drop the all-white alpha channel

        return matNoAlpha;
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB888:
    {
        if (!inCloneImageData)
        {
            qWarning() << "QImageToCvMat() - Conversion requires cloning so we don't modify the original QImage data";
        }

        QImage   swapped = inImage.rgbSwapped();

        cv::Mat mat(swapped.height(), swapped.width(),
            CV_8UC3,
            const_cast<uchar*>(swapped.bits()),
            static_cast<size_t>(swapped.bytesPerLine())
        );
        return (inCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 1 channel
    case QImage::Format_Grayscale8:
    case QImage::Format_Indexed8:
    {
        cv::Mat  mat(inImage.height(), inImage.width(),
            CV_8UC1,
            const_cast<uchar*>(inImage.bits()),
            static_cast<size_t>(inImage.bytesPerLine())
        );

        return (inCloneImageData ? mat.clone() : mat);
    }


#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    case QImage::Format_Grayscale16:
    {
        cv::Mat mat(cv::Size(inImage.width(), inImage.height()), CV_16U, const_cast<uchar*>(inImage.bits()), cv::Mat::AUTO_STEP);
        // or
        //        cv::Mat  mat( inImage.height(), inImage.width(),
        //                    CV_16U,
        //                    const_cast<uchar*>(inImage.bits()),
        //                    static_cast<size_t>(inImage.bytesPerLine())
        //                    );
        return (inCloneImageData ? mat.clone() : mat);
    }
#endif

    default:
        qWarning() << "QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }

    return cv::Mat();
}

bool QCustomVideoSurface::present(const QVideoFrame& frame)
{
    if (frame.isValid()) {
        QVideoFrame cloneFrame(frame); // makes a shallow copy (since QVideoFrame is explicitly shared), to get the access to the pixel data
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage::Format format = QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat());

      ///  int cvtype = CV_8UC1;
        QImage img = QVideoFrameToQImage(cloneFrame);
         cv::Mat mat = QImageToCvMat(img);

  /////      cv::flip(mat, mat, 0);
////        emit frameAvailable(mat, format);
        emit frame_available(img, format);

        cloneFrame.unmap();
        return true;
    }
    return false;
}
