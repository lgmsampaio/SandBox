#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void saveCameraParams(char* cameraName, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, const vector<Mat>& rvecs, const vector<Mat>& tvecs, const vector<vector<Point2f>>& imagePoints, Size& boardSize);