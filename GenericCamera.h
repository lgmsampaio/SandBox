#include "ICamera.h"

using namespace cv;

/// <summary>
/// Header file for builtin generic cameras using basic OpenCV function
/// </summary>
class GenericCamera : public ICamera
{
public:
	GenericCamera(void);
	virtual ~GenericCamera(void);

	virtual bool isConnected();
	virtual Mat getNextImage();

private:
	VideoCapture cap;
	
};