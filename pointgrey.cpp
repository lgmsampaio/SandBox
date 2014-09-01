/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

/*
#include "Pointgrey.h"

#include <FlyCapture2.h>
#include <iostream>

using namespace std;
using namespace cv;
using namespace FlyCapture2;

// Implementation of PointGrey class to connect Chameleon USB camera
PointGrey::PointGrey(void)
{
	type = SourceType::CAM_CHAMELEON;
	deviceName = "Point Grey Chameleon USB";

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

	// Convert to RGB
	Image rgbImage;
	rawImage.Convert(PIXEL_FORMAT_BGR, &rgbImage);

	// Convert to OpenCV Mat
	// TODO: Try to solve the warning about possible loss of data when casting 
	// from double to int
	unsigned int rowBytes = (double) rgbImage.GetReceivedDataSize() 
							/ (double)rgbImage.GetRows();

	frame = Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, 
		rgbImage.GetData(), rowBytes);

	// If we don't make this clone, we lose the data to return to next method
	// TODO: Try to investigate the real reason for this issue
	clone = frame.clone();

	return clone;
}

*/