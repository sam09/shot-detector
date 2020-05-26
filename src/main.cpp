
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/cudaarithm.hpp"
#include <string>
#include "SceneDetect.h"
#include  "ContentDetector.h"

int main (int argc, char* argv[])
{
	if (argc < 4) {
		std::cout<<"Wrong number of arguments"<<std::endl;
	}
	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	int duration = atoi(argv[3]);

	// Default values for video.
	int threshold = 30;
	int minSceneLen = 15;
	int totalFrames = 0;
	int numPixelsPerFrame = 0;

	ContentDetector *c = new ContentDetector(threshold, minSceneLen, numPixelsPerFrame, totalFrames);
    SceneDetect s (false, inputFileName, outputFileName, duration, c);
    s.detectSceneChanges();
}