#include "Detector.h"
#include <string.h>
#ifndef SceneDetect_H
#define SceneDetect_H

class SceneDetect
{
	bool useCuda;
	std::string input;
	std::string output;
	int duration; 
	Detector *detector;

public:
	SceneDetect(bool, std::string, std::string, int, Detector*);
	void detectSceneChanges();
};

#endif