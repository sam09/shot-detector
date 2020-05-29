#include "Detector.h"
#include "SceneDetect.h"
#include "ContentDetector.h"
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/cudacodec.hpp>
#include <fstream>

#include <string>

SceneDetect::SceneDetect(bool use_cuda, std::string input, std::string output, int duration, Detector* d) {
	this->use_cuda = use_cuda;
	this->input = input;
	this->output = output;
	this->duration = duration;
	this->detector = d;
	this->output_fs.open(this->output);
	this->total_frames = 0;
}

void SceneDetect::detect_cuts_gpu(ContentDetector *content_detector, std::vector<int> &cuts, int last_frame, cv::Size sz) {
	cv::cuda::GpuMat frame, hsv_frame, prev_hsv_frame;
	try {
		cv::Ptr<cv::cudacodec::VideoReader> reader = cv::cudacodec::createVideoReader(this->input);
		while(1) {
			if (!reader->nextFrame(frame)) {
				break;
			}
			cv::cuda::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

			if(total_frames == 0) {
				sz = hsv_frame.size();
				content_detector->set_num_pixels_per_frame(sz.width * sz.height);
			} else {
				if (detector->process_frame(std::ref(hsv_frame), std::ref(prev_hsv_frame), last_frame, total_frames)) {
					last_frame = total_frames;
					cuts.push_back(last_frame);
				}
			}
			prev_hsv_frame = hsv_frame.clone();
			this->total_frames++;
			if (total_frames % 100 == 0)
				std::cout<<total_frames<<" processed"<<std::endl;
		}
		for(int i=0; i<cuts.size(); i++) {
			write_output(cuts[i]);
		}
	} catch(cv::Exception e) {
		std::cerr<<e.what()<<std::endl;
	}
}

void SceneDetect::detect_cuts_cpu(ContentDetector *content_detector, std::vector<int> &cuts, int last_frame, cv::Size sz) {
	cv::VideoCapture cap(this->input);
	cv::Mat frame, hsv_frame, prev_hsv_frame;

	if (!cap.isOpened()) {
		std::cerr<<"Error opening video file"<<std::endl;
		return;
	}
		
	while(1) {
		cap >> frame;
		if (frame.empty())
			break;
		cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);
		if (total_frames == 0) {
			sz = hsv_frame.size();
			content_detector->set_num_pixels_per_frame(sz.width * sz.height);	
		} else {
			if (detector->process_frame(std::ref(hsv_frame), std::ref(prev_hsv_frame), last_frame, total_frames)) {
				last_frame = total_frames;
				cuts.push_back(last_frame);
			}
		}
		if (total_frames % 100 == 0)
			std::cout<<total_frames<<" processed"<<std::endl;
		prev_hsv_frame = hsv_frame.clone();
		this->total_frames++;
	}
}

void SceneDetect::detect_cuts() {
	cv::TickMeter tm;
	tm.reset();
	tm.start();
	ContentDetector *content_detector = (ContentDetector *) &detector;
	cv::Size sz;
	std::vector<int> cuts;
	int last_frame = -1;

	if (use_cuda) {
		detect_cuts_gpu(content_detector, cuts, last_frame, sz);
	} else {
		detect_cuts_cpu(content_detector, cuts, last_frame, sz);
	}
	std::cout<<"Writing Output"<<std::endl;
	for(int i=0; i<cuts.size(); i++) {
		write_output(cuts[i]);
	}
	tm.stop();
	std::cout << "Total Time : " << tm.getTimeMilli() << " ms Frames : " << this->total_frames << std::endl;
}

SceneDetect::~SceneDetect() {
	this->output_fs.close();
}


void SceneDetect::write_output(int frame_number) {
	int milliseconds, seconds;
	get_time(&seconds, &milliseconds, frame_number);
	this->output_fs << "00:00:";
	if(seconds > 10)
		this->output_fs << seconds;
	else
		this->output_fs << "0" << seconds;

	this->output_fs << ":";

	if(milliseconds > 100)
		this->output_fs << milliseconds;
	else if (milliseconds > 10)
		this->output_fs << "0" << milliseconds;
	else
		this->output_fs << "00" << milliseconds;

	if(frame_number == this->total_frames - 1)
		this->output_fs << ", ";
	else
		this->output_fs << "\n";
}

void SceneDetect::get_time(int *seconds, int *milliseconds, int frame_num) {
	double length_in_secs = (double)duration/1000.0;
	double frame_rate = total_frames/length_in_secs;

	*seconds = frame_num/ frame_rate;
	int extra_frames = frame_num - int( (*seconds) * frame_rate);
	*milliseconds = (extra_frames * 1000)/frame_rate;
}