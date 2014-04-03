#include "HeavyCalibration.h"
#include "CameraCalibrator.h"

#include "GenericCamera.h"
#include "PointGrey.h"
#include "ImageFiles.h"

int main()
{
	//HeavyCalibration();
	
	Size boardSize;
	int nrFrames = 25;

	// Here we can change the image source
	//GenericCamera *source = new GenericCamera(640, 480, 1);
	//PointGrey *source = new PointGrey();
	ImageFiles *source = new ImageFiles(43);

	std::unique_ptr<IImageSource> imageSource(source);
	
	boardSize = source->type == SourceType::IMAGE_FILE ? Size(6, 4) : Size(7, 5);

	CameraCalibrator calibrator(move(imageSource), nrFrames, boardSize);

	calibrator.startCalibration();
	
	return 0;
}
