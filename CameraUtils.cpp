#include "CameraUtils.h"
#include <time.h>

using namespace std;

void saveCameraParams(char* cameraName, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, const vector<Mat>& rvecs, const vector<Mat>& tvecs, const vector<vector<Point2f>>& imagePoints, Size& boardSize)
{
	//char* name = strcat(cameraName, ".xml");
	//printf(name);
	
	FileStorage fs("teste.xml", FileStorage::WRITE );

	time_t tm;
	time(&tm);
	struct tm *t2 = localtime( &tm );
	char buf[1024];
	strftime( buf, sizeof(buf)-1, "%c", t2 );

	fs << "calibration_Time" << buf;

	fs << "image_Width" << imageSize.width;
	fs << "image_Height" << imageSize.height;
	fs << "board_Width" << boardSize.width;
	fs << "board_Height" << boardSize.height;
	
	fs << "Camera_Matrix" << cameraMatrix;
	fs << "Distortion_Coefficients" << distCoeffs;

	if( !rvecs.empty() && !tvecs.empty() )
	{
		CV_Assert(rvecs[0].type() == tvecs[0].type());
		Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
		for( int i = 0; i < (int)rvecs.size(); i++ )
		{
			Mat r = bigmat(Range(i, i+1), Range(0,3));
			Mat t = bigmat(Range(i, i+1), Range(3,6));

			CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
			CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
			//*.t() is MatExpr (not Mat) so we can use assignment operator
			r = rvecs[i].t();
			t = tvecs[i].t();
		}
		cvWriteComment( *fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0 );
		fs << "Extrinsic_Parameters" << bigmat;
	}

	if( !imagePoints.empty() )
	{
		Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
		for( int i = 0; i < (int)imagePoints.size(); i++ )
		{
			Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
			Mat imgpti(imagePoints[i]);
			imgpti.copyTo(r);
		}
		fs << "imagePoints" << imagePtMat;
	}
}
