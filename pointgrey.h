/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#ifndef POINTGREY_H
#define POINTGREY_H

#include "IImageSource.h"

#include <FlyCapture2.h>

using namespace cv;
using namespace FlyCapture2;

// Header file manage PointGrey Chamemelon USB camera  
class PointGrey: public IImageSource
{

public:
	PointGrey(void); 

	virtual ~PointGrey(void);

	virtual bool isConnected();
	virtual Mat getNextImage();

private:
	Camera camera;
	Error error;
};

#endif