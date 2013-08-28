
/**
 * Automatic perspective correction for quadrilateral objects. See the tutorial at
 * http://opencv-code.com/tutorials/automatic-perspective-correction-for-quadrilateral-objects/
 */
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "PlateFinder.h"
using namespace cv;

int main( int argc, char** argv )
{
	PlateFinder plateFinder = PlateFinder(argv[1]);
	plateFinder.find_plates();

	return 0;
}
