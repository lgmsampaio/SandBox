/* ============================================================================
Name        : webcam.cpp
Author      : Luiz Sampaio
Version     : 0.1
Copyright   : Public use
Description : Functions to work with generic cameras
============================================================================ */

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

VideoCapture cap(CV_CAP_ANY);

int startWebCam()
{
	return cap.isOpened() ? 0 : -1;
}

void stopWebCam()
{
	cap.release();
}

Mat getWebCamCapture()
{
	Mat frame;
	cap >> frame;

	return frame;
}


