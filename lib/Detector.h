#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>

#ifndef Detector_H
#define Detector_H

class Detector
{
	public:
		Detector() {};
		virtual bool processFrame(cv::cuda::GpuMat frame, cv::cuda::GpuMat prevframe, int lastFrameNum) = 0;
		virtual bool processFrame(cv::Mat frame, cv::Mat prevframe, int lastFrameNum) = 0;
};

#endif