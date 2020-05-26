#include "Detector.h"
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef ContentDetector_H
#define ContentDetector_H

class ContentDetector : public Detector {
	int threshold;
	int minSceneLen;
	int totalFrames;
	int numPixelsPerFrame;
public:
	ContentDetector(int , int , int , int );
	bool processFrame(cv::cuda::GpuMat, cv::cuda::GpuMat, int);
	bool processFrame(cv::Mat, cv::Mat, int);
};

#endif