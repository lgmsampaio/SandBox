/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#include "CameraCalibrator.h"
#include "GenericCamera.h"
//#include "PointGrey.h"
#include "ImageFiles.h"

int main()
{
	// Number of inner corners on the chessboard
	Size boardSize;
	// Number of "shots" do make the calibration
	int nrFrames = 20;

	// Here we can change the image source
	GenericCamera *source = new GenericCamera(640, 480, 0, "Lenovo Camera");
	//PointGrey *source = new PointGrey();
	//ImageFiles *source = new ImageFiles(43);

	// Set the smart pointer for image source
	std::unique_ptr<IImageSource> imageSource(source);
	
	// My chessboard has different size than the one in the images I'm using
	boardSize = source->type == SourceType::IMAGE_FILE ? Size(6, 4) : Size(7, 5);

	CameraCalibrator calibrator(move(imageSource), nrFrames, boardSize);

	calibrator.startCalibration();
	
	return 0;
}
