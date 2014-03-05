/* ============================================================================
Name        : main.cpp
Author      : Luiz Sampaio
Version     : 0.1
Copyright   : Public use
Description : Initial file
============================================================================ */

#include "pointgrey.h"
#include "webcam.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

bool usePointGrey = true;
bool useSecondScreen = false;

Mat getImageFromCamera();

int main(int argc, char** argv)
{
	const char ESC_KEY = 27;
	char exitKey = 0;
	char* windowName = "video test";

	int windowWidth = 1366;
	int windowHeight = 768;
	int windowX = -1366;
	int windowY = 0;
	int result = 0;

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

	if(usePointGrey) 
		startCamera();
	else
		startWebCam();
		
	while(exitKey != ESC_KEY)
	{
		frame = getImageFromCamera();
		if (!frame.empty())	imshow(windowName, frame);

		exitKey = (char)waitKey(30);
	}

	destroyWindow(windowName);

	if(usePointGrey) stopCamera();
	
	return 0;
}

Mat getImageFromCamera()
{
	return usePointGrey ? getPointGreyCapture() : getWebCamCapture();
}

