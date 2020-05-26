#include "ContentDetector.h"
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/cudaarithm.hpp>
#include <iostream>

ContentDetector::ContentDetector(int threshold, int minSceneLen, int numPixelsPerFrame, int totalFrames) {
	this->threshold = threshold;
	this->minSceneLen = minSceneLen;
	this->numPixelsPerFrame = numPixelsPerFrame;
	this->totalFrames = totalFrames;
}

bool ContentDetector::processFrame(cv::cuda::GpuMat frame, cv::cuda::GpuMat prevFrame, int lastFrameNum) {
	try {
		cv::cuda::GpuMat difference;
		cv::Scalar sum;
		double avg = 0;
		cv::cuda::subtract(frame, prevFrame, difference);

		sum = cv::cuda::absSum(difference);
		avg = (sum[0] + sum[1] + sum[2])/3.0;
		avg /= double(this->numPixelsPerFrame);

		if (avg >= this->threshold &&  ((this->totalFrames - lastFrameNum) > this->minSceneLen))
			return true;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return false;
}

bool ContentDetector::processFrame(cv::Mat frame, cv::Mat prevFrame, int lastFrameNum) {
	try {
		cv::Mat difference;
		cv::Scalar sum;
		double avg = 0;
		cv::absdiff(frame, prevFrame, difference);

		sum = cv::sum(difference);
		avg = (sum[0] + sum[1] + sum[2])/3.0;

		avg /= (double(this->numPixelsPerFrame));
		if (avg >= this->threshold &&  ((this->totalFrames - lastFrameNum) > this->minSceneLen))
			return true;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return false;
	
}