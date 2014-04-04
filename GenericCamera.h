/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#ifndef GENERICCAMERA_H
#define GENERICCAMERA_H

#include "IImageSource.h"

// Header file manage builtin generic cameras using basic OpenCV function
class GenericCamera : public IImageSource
{
private:
	VideoCapture cap;

public:
	GenericCamera(void) { GenericCamera(0, 0, 0, ""); };
	//Set horizontal and vertical resolution
	GenericCamera(int frameW, int frameH, int deviceId, char* deviceName);
	
	virtual ~GenericCamera(void);

	virtual bool isConnected();
	virtual Mat getNextImage();
};

#endif