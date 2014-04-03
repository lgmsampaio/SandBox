/*---------------------------------------------------------------------------*\
This program is free software. It comes without any warranty, to the extent 
permitted by applicable law. You can redistribute it and/or modify it under 
the terms of the Do What The Fuck You Want To Public License, Version 2, as 
published by Sam Hocevar. See http://www.wtfpl.net/ for more details. 

Copyright © 2014 Luiz Gustavo M. Sampaio www.lgmsampaio.com
\*---------------------------------------------------------------------------*/

#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include <vector>
#include <iostream>
#include <memory>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "IImageSource.h"

using namespace std;
using namespace cv;

// Class to make camera calibration based in OpenCV functions. It was deeply 
// modified by me, but still based in the example found on the book "OpenCV 2 
// Computer Vision Application Programming Cookbook" by Robert Laganiere.
class CameraCalibrator 
{
private:
	// list of vectors with 2D points from the chessboard
	vector<vector<Point2f>> imagePoints;
	// list of vectors with 3D points from the chessboard
	vector<vector<Point3f>> objectPoints;

	// Output Matrices
	Mat cameraMatrix; // Intrinsic parameters
	Mat distCoeffs;	  // Distortion coefficienst
	Mat map1,map2;    // used for remaping the image

	// Holds the image from image source
	Mat image, grayImage;

	//Output rotations and translations matrices
	vector<Mat> rvecs, tvecs;

	// Flag to specify how calibration is done
	// TODO: Understand better how these options have influence on calibration
	int flag;
	
	// Number of images necessary for calibration
	int nrFrames;

	// Number of inner corners in the chessboard
	Size boardSize;

	// Smart point to image source (files or camera)
	unique_ptr<IImageSource> imageSource;

	// Open the chessboard images and extract corner points
	int addChessboardPoints(Size& boardSize);
	
	// Calibrate the camera
	double calibrate();
	
	// Add scene points and corresponding image points
	void addPoints(const vector<Point2f>& imageCorners, const vector<Point3f>& objectCorners);
	
	// Set the calibration flag
	void setCalibrationFlag(bool radial8CoeffEnabled = false, bool tangentialParamEnabled = false);
	
	// Remove distortion in an image (after calibration)
	Mat CameraCalibrator::remap();

public:
	// Smart pointer to set the image source, number of frames to complete
	// the calibration and number of inner corners in the chessboard
	CameraCalibrator(unique_ptr<IImageSource> src, int frames, Size boardSize) 
		: nrFrames(frames), boardSize(boardSize) 
	{	
		imageSource = move(src); 
	};

	// Start the calibration process
	int startCalibration();
};

#endif 
