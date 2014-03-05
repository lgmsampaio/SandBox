#pragma once

#include <opencv2/opencv.hpp>

/// <summary>
/// Interface for different camera implementations
/// </summary>
class ICamera
{
public:
	ICamera(void){}
	virtual ~ICamera(void){}

	virtual bool isConnected() = 0;
	virtual cv::Mat getNextImage() = 0;
};