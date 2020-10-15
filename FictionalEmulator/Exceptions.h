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
#pragma once
#include <exception>
#include <string>
#include <sstream>

class EmulatorERROR : public std::exception {
public:
	EmulatorERROR(const std::string & str) : std::exception(str.c_str()) {}
protected:
	static std::string toHexString(unsigned int num) {
		std::stringstream sstream;
		sstream << std::hex << num;
		return sstream.str();
	}
};

class MemoryOutOfRange : public EmulatorERROR {
public:
	MemoryOutOfRange() : EmulatorERROR("Invalid Memory Address") {}
	MemoryOutOfRange(std::uint16_t addr) : EmulatorERROR("Invalid Memory Address: " + toHexString(addr)) {}
};

class WritingToROM : public EmulatorERROR {
public:
	WritingToROM() : EmulatorERROR("Attempt to write in read only memory") {}
};
