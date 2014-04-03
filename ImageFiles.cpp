/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#include "ImageFiles.h"

#include <iomanip>  

using namespace cv;
using namespace std;

// Implementation of ImageFiles class, loading chessboard images from disk
ImageFiles::ImageFiles(int totalImages) 
	: nrImages(totalImages), currentImage(0)
{
	type = SourceType::IMAGE_FILE;
	
	// Load all images into a vector
	for (int i = 0; i < nrImages; i++) 
	{
		stringstream str;
		// TODO: Make this input more generic in order to load different files
		// from different places
		str << "chessboards/chessboard" << std::setw(2) << std::setfill('0') 
			<< i << ".jpg";

		// Simple output just to know what's happenning 
		//cout << str.str() << std::endl;
		filelist.push_back(str.str());
	}
}

ImageFiles::~ImageFiles(void) {}

bool ImageFiles::isConnected()
{
	return true;
}

// In case of cameras, we can deliver infinite images while the camera is
// working. Here we have a limit of loaded images
Mat ImageFiles::getNextImage()
{
	if(currentImage < nrImages)
		return imread(filelist[++currentImage]);

	return Mat();
}




