#include "Detector.h"
#include "ContentDetector.h"
#include <string.h>
#include <fstream>
#ifndef SceneDetect_H
#define SceneDetect_H

class SceneDetect
{
	bool use_cuda;
	std::string input;
	std::string output;
	int duration;
	int total_frames;
	std::ofstream output_fs; 
	Detector *detector;

public:
	SceneDetect(bool, std::string, std::string, int, Detector*);
	void detect_cuts();
	void detect_cuts_cpu(ContentDetector*, std::vector<int> &, int, cv::Size);
	void detect_cuts_gpu(ContentDetector*, std::vector<int> &, int, cv::Size);
	~SceneDetect();
	void write_output(int);
	void get_time(int *, int *, int );
};

#endif