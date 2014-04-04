/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#ifndef IIMAGESOURCE_H
#define IIMAGESOURCE_H

#include <opencv2/opencv.hpp>

using namespace cv;

// Enum to define what kind of resource we are using. Probably in the future 
// this type will need to be more 'dynamic'in order to accept other sources.
enum class SourceType {CAM_GENERIC, CAM_CHAMELEON, IMAGE_FILE};

// Abstract class to standardize different image sources, as collection of 
// files in your disk or cameras. Following this contract, you can handle
// different image sources without needding to change your code. 
class IImageSource
{

public:
	IImageSource(void){}
	virtual ~IImageSource(void){}

	// Especially required when connecting cameras, we need to know if they are
	// connected before request frames
	virtual bool isConnected() = 0;

	// Get the next image file or next frame from camera
	virtual Mat getNextImage() = 0;

	SourceType type;

	char* deviceName;
};

#endif