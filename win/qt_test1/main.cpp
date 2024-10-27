#include "qt_test1.h"
#include <QtWidgets/QApplication>

#if 1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_test1 w;
    w.show();
    return a.exec();
}
#else
using namespace std;

int main(int argc, char* argv[])
{
	VideoCapture _cap(0);
	if (_cap.isOpened() == false)
	{
		return -1;
	}
	double dWidth = _cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = _cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"
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
		imshow(window_name, frame);

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

}
#endif