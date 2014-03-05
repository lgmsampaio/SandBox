#include "ICamera.h"
#include <FlyCapture2.h>

/// <summary>
/// Header file for PointGrey Chameleon USB Camera
/// </summary>
class PointGrey: public ICamera
{
public:
	PointGrey(void);
	virtual ~PointGrey(void);

	virtual bool isConnected();
	virtual cv::Mat getNextImage();

private:
	FlyCapture2::Camera camera;
	FlyCapture2::Error error;
};

