#include "Detector.h"
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef ContentDetector_H
#define ContentDetector_H

class ContentDetector : public Detector {
	int threshold;
	int min_scene_len;
	int num_pixels_per_frame;
public:
	ContentDetector(int , int , int);
	bool process_frame(cv::cuda::GpuMat, cv::cuda::GpuMat, int, int);
	bool process_frame(cv::Mat, cv::Mat, int, int);
	void set_num_pixels_per_frame(int);
	int get_num_pixels_per_frame();
};

#endif