#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>

#ifndef Detector_H
#define Detector_H

class Detector
{
	public:
		Detector() {};
		virtual bool process_frame(cv::cuda::GpuMat, cv::cuda::GpuMat, int, int) = 0;
		virtual bool process_frame(cv::Mat, cv::Mat, int, int) = 0;
};

#endif