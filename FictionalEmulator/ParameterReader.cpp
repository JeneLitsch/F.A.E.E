#include "ParameterReader.h"

std::string ParameterReader::romFile(int argc, char * argv[]) {
	if (argc > 1)
		return std::string(argv[1]);
	else
		return "";
}

double ParameterReader::clockSpeed(int argc, char * argv[]) {
	if (argc > 2)
		return std::atoi(argv[2]);
	else 
		return CNST::defaultClockSpeed;
}

bool ParameterReader::logCreation(int argc, char * argv[]) {
	if (argc > 3)
		return std::atoi(argv[3]);
	else 
		return false;
}

bool ParameterReader::imgCreation(int argc, char * argv[]) {
	if (argc > 4)
		return std::atoi(argv[4]);
	else
		return false;
}

std::string ParameterReader::imgFile(int argc, char * argv[]) {
	if (argc > 5)
		return std::string(argv[5]);
	else
		return "";
}