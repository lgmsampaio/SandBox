/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#include "GenericCamera.h"

using namespace std;
using namespace cv;

// Implementation of Generic Camera class, connecting usually builtin cameras
GenericCamera::GenericCamera(int frameW, int frameH, int deviceId, 
							 char* deviceName) 
{
	type = SourceType::CAM_GENERIC;
	this->deviceName = deviceName;

	// Will get the first camera available (if any)
	//cap = VideoCapture(CV_CAP_ANY);
	cap = VideoCapture(deviceId);

	if(frameW > 0 && frameH > 0){
		cap.set(CV_CAP_PROP_FRAME_WIDTH, frameW);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, frameH);
	}
}

GenericCamera::~GenericCamera(void)
{
	cap.release();

	cout << "capture finished" << endl;
}

bool GenericCamera::isConnected()
{
	return cap.isOpened();
}

Mat GenericCamera::getNextImage()
{
	Mat frame;

	cap >> frame;

	// Some cameras take more time to start to deliver images, so we need to 
	// wait until we get some data before return it to "outside"
	while(frame.empty()) cap >> frame;

	return frame;
}




