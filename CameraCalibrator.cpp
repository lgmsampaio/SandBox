/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <vector>

#include "CameraCalibrator.h"
#include "GenericCamera.h"
#include "PointGrey.h"
#include "ImageFiles.h"
#include "CameraUtils.h"

using namespace cv;

// Implementation of CameraCalibrator class. Returns 0 in case of success, 
// non-zero number in case of errors.
// You might find some architectural mistakes in this class, because at the 
// beginning it was planned to be handled by an external function (like "main"), 
// but I decided do everything inside the class, making public only the function
// that start the process
int CameraCalibrator::startCalibration() {

	// 1. Find the corners on the chessboard
	addChessboardPoints(boardSize);

	// 2. Calibrate the camera based on the paramenters from the chessboard
	calibrate();

	// 3. Show the image after the understortion applied
	Mat resultImage = remap();

	// 4. Save the camera parameters in a xml file
	saveCameraParams("image files", resultImage.size(), cameraMatrix, distCoeffs, rvecs, tvecs, imagePoints, boardSize);

	waitKey();
	return 0;
}

// Open chessboard images and extract corner points
int CameraCalibrator::addChessboardPoints(Size& boardSize) {

	// 2D position (image coordinate) of the corners for each image
	vector<Point2f> imageCorners;  
	// 3D position (world coordinate) of the corners for each image
	vector<Point3f> objectCorners; 
	// Copy from original image from source, to draw the corners
	Mat sample;

	int success = 0;

	// Initialize the vector with 3D points in arbitray measure unit
	// The corners are at 3D location (X,Y,Z)= (i,j,0)
	// Ex: <(0,0,0), (0,1,0), (0,2,0) ... (1,0,0), (1,1,0)...>
	for (int i=0; i<boardSize.height; i++) {
		for (int j=0; j<boardSize.width; j++) {
			objectCorners.push_back(Point3f(i, j, 0.0f));
		}
	}

	while(success < nrFrames) 
	{
		image = imageSource->getNextImage();
		image.copyTo(sample);

		cvtColor(image, grayImage, COLOR_BGR2GRAY);

		// Get the chessboard corners
		bool found = findChessboardCorners(grayImage, boardSize, imageCorners);

		if(found){
			// Get subpixel accuracy on the corners
			cornerSubPix(grayImage, imageCorners, Size(5,5), Size(-1,-1), 
				TermCriteria( TermCriteria::MAX_ITER + TermCriteria::EPS, 
				30,	//30: max number of iterations 
				0.1 //0.1: min accuracy
				));     

			cv::drawChessboardCorners(sample, boardSize, imageCorners, found);

			int key = waitKey(1);

			// if the image source are files in the disk, just add the points
			// otherwise, wait for the user's command
			// TODO: The following "if" looks stupid. I believe must have a 
			// better approach for this situation
			if(imageSource->type == SourceType::IMAGE_FILE){

				addPoints(imageCorners, objectCorners);
				success++;
			}
			else if (key == ' '){
				addPoints(imageCorners, objectCorners);
				success++;
			}
		} // if(found)

		cv::imshow("Corners on Chessboard", sample);
	}

	return success;
}

// Add scene points and corresponding image points
void CameraCalibrator::addPoints(const vector<Point2f>& imageCorners, const vector<Point3f>& objectCorners) {

	// 2D image points from one view
	imagePoints.push_back(imageCorners);          
	// corresponding 3D scene points
	objectPoints.push_back(objectCorners);
	cout << "corners stored" << endl;
}

// Calibrate the camera
// returns the re-projection error
double CameraCalibrator::calibrate()
{
	// start calibration
	return calibrateCamera(
		objectPoints, // (input) the 3D points
		imagePoints,  // (input) the image points
		image.size(), // (input) image size
		cameraMatrix, // (output) 3x3 floating-point camera matrix
		distCoeffs,   // (output) vector of distortion coefficients of 4, 5, or 8 elements
		rvecs,        // (output) vector of rotation vectors
		tvecs);		  // (output) vector of translation vectors
	//flag		  // set options
	//);        
	//,CV_CALIB_USE_INTRINSIC_GUESS);
}

// remove distortion in an image (after calibration)
Mat CameraCalibrator::remap() {

	Mat undistorted;

	initUndistortRectifyMap	(
		cameraMatrix,  // (input) computed camera matrix
		distCoeffs,    // (input) vector of distortion coefficients
		cv::Mat(),     // (input) optional rectification (none) 
		cv::Mat(),     // (input) camera matrix to generate undistorted
		image.size(),  // (input) undistorted image size
		CV_32FC1,      // (input) type of output map. See convertMaps() for details.
		map1, map2);   // the x and y mapping functions
	
	// Apply mapping functions
	cv::remap(image, undistorted, map1, map2, cv::INTER_LINEAR); // interpolation type

	imshow("Original Image", image);
	imshow("Undistorted Image", undistorted);

	return undistorted;
}

// Set the calibration options
// 8radialCoeffEnabled should be true if 8 radial coefficients are required (5 is default)
// tangentialParamEnabled should be true if tangeantial distortion is present
void CameraCalibrator::setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled) {

	// Set the flag used in cv::calibrateCamera()
	flag = 0;
	if (!tangentialParamEnabled) flag += CV_CALIB_ZERO_TANGENT_DIST;
	if (radial8CoeffEnabled) flag += CV_CALIB_RATIONAL_MODEL;
}

