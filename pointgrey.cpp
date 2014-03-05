/* ============================================================================
Name        : pointgrey.cpp
Author      : Luiz Sampaio
Version     : 0.1
Copyright   : Public use
Description : Functions to work with PointGrey Chameleon digital camera
============================================================================ */

#include "pointgrey.h"

#include <FlyCapture2.h>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace cv;
using namespace FlyCapture2;
using namespace std;

Camera camera;
Error camError;

/// <summary>
/// Starts the camera.
/// </summary>
/// <returns></returns>
int startCamera()
{
	camError = camera.Connect(0);
	if(camError != PGRERROR_OK)
	{
		cout << "Failed to connect to camera" << endl;
		return -1;
	}

	camError = camera.StartCapture();
	if(camError == PGRERROR_ISOCH_BANDWIDTH_EXCEEDED)
	{
		cout << "Bandwith exceeded" << endl;
		return -1;
	}
	else if(camError != PGRERROR_OK)
	{
		cout << "Failed to start image capture" << endl;
		return -1;
	}

	return 0;
}

/// <summary>
/// Stops the camera.
/// </summary>
void stopCamera()
{
	camError = camera.StopCapture();
	camError = camera.Disconnect();
}

/// <summary>
/// Gets the point grey capture.
/// </summary>
/// <returns></returns>
Mat getPointGreyCapture()
{
	Mat frame, clone;
	Image rawImage;

	camError = camera.RetrieveBuffer(&rawImage);
	//if(camError != PGRERROR_OK) throw exception("Capture error");

	//convert to RGB
	Image rgbImage;
	rawImage.Convert(PIXEL_FORMAT_BGR, &rgbImage);

	//Convert to OpenCV Mat
	unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize()/(double)rgbImage.GetRows();
	frame = Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);

	//if we don't make this clone, we lose the data to return to next method
	clone = frame.clone();

	return clone;
}