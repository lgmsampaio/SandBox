/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#ifndef IMAGEGILES_H
#define IMAGEGILES_H

#include "IImageSource.h"

// Class to get image files stored in the disk
class ImageFiles : public IImageSource
{
private:
	vector<string> filelist;
	int nrImages;
	int currentImage;

public:
	ImageFiles(void) { ImageFiles(0); };
	ImageFiles(int totalImages);

	virtual ~ImageFiles(void);

	virtual bool isConnected();
	virtual Mat getNextImage();
};

#endif