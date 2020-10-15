// Copyright(C) 2012, 2013 Jene Maracel Litsch
// This file is part of FAEE.
//
// FAEE is free software : you can redistribute it and /or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FAEE is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
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