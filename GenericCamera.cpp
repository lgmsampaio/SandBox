#include "GenericCamera.h"

using namespace std;

GenericCamera::GenericCamera(void)
{
	cap = cv::VideoCapture(CV_CAP_ANY);
}

GenericCamera::~GenericCamera(void)
{
	cap.release();

	cout << "capture finished" << endl;
}

bool GenericCamera::isConnected()
{
	return cap.isOpened();
}

cv::Mat GenericCamera::getNextImage()
{
	cv::Mat frame;
	cap >> frame;

	return frame;
}




