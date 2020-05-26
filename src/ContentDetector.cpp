#include "ContentDetector.h"
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/cudaarithm.hpp>
#include <iostream>
#include <fstream>

ContentDetector::ContentDetector(int threshold, int min_scene_len, int num_pixels_per_frame) {
	this->threshold = threshold;
	this->min_scene_len = min_scene_len;
	this->num_pixels_per_frame = num_pixels_per_frame;
}

void ContentDetector::set_num_pixels_per_frame(int numPixelsPerFrame) {
	this->num_pixels_per_frame = num_pixels_per_frame;
}

int ContentDetector::get_num_pixels_per_frame() {
	return this->num_pixels_per_frame;
}

bool ContentDetector::process_frame(cv::cuda::GpuMat frame, cv::cuda::GpuMat prev_frame, int last_frame_num, int cur_frame_num) {
	try {
		cv::cuda::GpuMat difference;
		cv::Scalar sum;
		double avg = 0;
		cv::cuda::subtract(frame, prev_frame, difference);

		sum = cv::cuda::absSum(difference);
		avg = (sum[0] + sum[1] + sum[2])/3.0;
		avg /= double(this->num_pixels_per_frame);

		if (avg >= this->threshold &&  ((cur_frame_num - last_frame_num) > this->min_scene_len))
			return true;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return false;
}

bool ContentDetector::process_frame(cv::Mat frame, cv::Mat prev_frame, int last_frame_num, int cur_frame_num) {
	try {
		cv::Mat difference;
		cv::Scalar sum;
		double avg = 0;
		cv::absdiff(frame, prev_frame, difference);

		sum = cv::sum(difference);
		avg = (sum[0] + sum[1] + sum[2])/3.0;

		avg /= (double(this->num_pixels_per_frame));
		if (avg >= this->threshold &&  ((cur_frame_num - last_frame_num) > this->min_scene_len))
			return true;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return false;
	
}