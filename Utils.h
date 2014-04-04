/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#ifndef UTILS
#define UTILS

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void saveCameraParams(char* cameraName, 
					  Size& imageSize, 
					  Mat& cameraMatrix, 
					  Mat& distCoeffs, 
					  const vector<Mat>& rvecs,
					  const vector<Mat>& tvecs, 
					  const vector<vector<Point2f>>& imagePoints, 
					  Size& boardSize);

#endif