#include "Pointgrey.h"

#include <FlyCapture2.h>
#include <iostream>

using namespace cv;
using namespace FlyCapture2;
using namespace std;

PointGrey::PointGrey(void)
{
	error = camera.Connect(0);

	if(error != PGRERROR_OK)
		cout << "Failed to connect to camera" << endl;

	error = camera.StartCapture();

	if(error == PGRERROR_ISOCH_BANDWIDTH_EXCEEDED)
		cout << "Bandwith exceeded" << endl;

	else if(error != PGRERROR_OK)
		cout << "Failed to start image capture" << endl;
}

PointGrey::~PointGrey(void)
{
	error = camera.StopCapture();
	if(error != PGRERROR_OK)
		cout << "Failed to stop camera capture" << endl;

	error = camera.Disconnect();
	if(error != PGRERROR_OK)
		cout << "Failed to disconnect the camera" << endl;

	cout << "capture finished" << endl;
}

bool PointGrey::isConnected()
{
	return camera.IsConnected();
}

Mat PointGrey::getNextImage()
{
	Mat frame, clone;
	Image rawImage;

	error = camera.RetrieveBuffer(&rawImage);
	if(error != PGRERROR_OK) 
		cout << "Failed to retrieve buffer" << endl;

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
