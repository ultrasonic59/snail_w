#include "qt_test1.h"
using namespace std;

qt_test1::qt_test1(QWidget *parent)
    : QMainWindow(parent), _cap(0)
{
   ui.setupUi(this);
///	VideoCapture _cap(0);
	QObject::startTimer(10);
#if 0
	if (_cap.isOpened() == false)
	{
		return ;
	}
	double dWidth = _cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = _cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	///string window_name = "My Camera Feed";
	///namedWindow(window_name); //create a window called "My Camera Feed"
	while (true)
	{
		Mat frame;
		bool bSuccess = _cap.read(frame); // read a new frame from video 

		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
	///		cout << "Video camera is disconnected" << endl;
	///		cin.get(); //Wait for any key press
			break;
		}

		//show the frame in the created window
	///	imshow(window_name, frame);

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop 
		/*
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
		*/
	}
#endif
}

qt_test1::~qt_test1()
{}


void qt_test1::timerEvent(QTimerEvent* e)
{
	   bool rez;
#if 1
	if (_cap.isOpened())
	{
		////  _frame = cv::Mat::zeros(640, 480, 3); // fill zeros for debug purpose
		rez = _cap.read(cvFrame);
	///	qDebug() << "rez" << rez;
		if (rez == false)
			return;
		QImage qtFrame(cvFrame.data, cvFrame.size().width, cvFrame.size().height, cvFrame.step, QImage::Format_RGB888);

		qtFrame = qtFrame.rgbSwapped();
		////  _cap >> _frame;
			 /// <param name="e"></param>
///		_image = Mat2QImage(_frame);
///
///
ui.cam_label->setPixmap(QPixmap::fromImage(qtFrame));
#if 0
		QPainter painter(&qtFrame);    ////???   _label->setPixmap(QPixmap::fromImage(_image));
		painter.setPen(QPen(Qt::red, 40, Qt::SolidLine));
		painter.setFont(QFont("Arial", 20));
		////  QRect text_rc = QRect(15, 25, 200,100);
		QRect text_rc = _image.rect();

		painter.drawText(text_rc, Qt::AlignVCenter | Qt::AlignCenter, "TEST");

		painter.end();
		emit updateCamView(_image);
#endif
	}
#endif
}
