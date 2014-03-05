#include "GenericCamera.h"
#include "PointGrey.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	const char ESC_KEY = 27;
	char exitKey = 0;
	char* windowName = "video test";
	bool useSecondScreen = false;

	int windowWidth = 1366;
	int windowHeight = 768;
	int windowX = -1366;
	int windowY = 0;
	int result = 0;

	GenericCamera cam = GenericCamera();
	//PointGrey cam = PointGrey();
	ICamera& camera = cam;
	
	Mat frame;

	if(useSecondScreen)
	{
		namedWindow(windowName, 0);
		setWindowProperty(windowName, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
		resizeWindow(windowName, windowWidth, windowHeight);
		moveWindow(windowName, windowX, windowY);
	}
	else
		namedWindow(windowName, CV_WINDOW_AUTOSIZE);

	while(exitKey != ESC_KEY)
	{
		frame = camera.getNextImage();
		if (!frame.empty())	imshow(windowName, frame);

		exitKey = (char)waitKey(30);
	}

	destroyWindow(windowName);
	
	return 0;
}



