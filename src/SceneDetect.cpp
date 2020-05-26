#include "Detector.h"
#include "SceneDetect.h"
#include  "ContentDetector.h"
#include <string>

SceneDetect::SceneDetect(bool useCuda, std::string inputFileName, std::string outputFileName, int duration, Detector* d) {
	this->useCuda = useCuda;
	this->input = inputFileName;
	this->output = outputFileName;
	this->duration = duration;
	this->detector = d;
}

void SceneDetect::detectSceneChanges() {

}