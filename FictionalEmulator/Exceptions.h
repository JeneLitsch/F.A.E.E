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
