
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
	if (argc < 5) {
		std::cout<<"Wrong number of arguments"<<std::endl;
		return 1;
	}
	std::string input = std::string(argv[1]);
	std::string output = std::string(argv[2]);
	int duration = atoi(argv[3]);
	int use_cuda = atoi(argv[4]);
	
	// Default values for video.
	int threshold = 30;
	int min_scene_len = 15;
	int num_pixels_per_frame = 0;

	ContentDetector *c = new ContentDetector(threshold, min_scene_len, num_pixels_per_frame);
    SceneDetect s (use_cuda == 1, input, output, duration, c);
    std::cout<<"Starting video cut detection"<<std::endl;
    s.detect_cuts();
}