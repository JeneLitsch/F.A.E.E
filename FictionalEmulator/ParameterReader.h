#pragma once
#include <vector>
#include <string>
#include "Constants.h"
class ParameterReader {
public:
	static std::string romFile(int argc, char * argv[]);
	//return clockspeed in hz
	static double clockSpeed(int argc, char * argv[]);
	static bool logCreation(int argc, char * argv[]);
	static bool imgCreation(int argc, char * argv[]);
	static std::string imgFile(int argc, char * argv[]);
};

