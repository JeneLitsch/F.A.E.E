#pragma once
#include <array>
#include <vector>
#include <cstdint>
#include <string>
#include <sstream>

#include "Types.h"
class Assembler {
public:
	Assembler(){}
	std::unique_ptr<ROMImage> decodeSource(const std::vector<std::string> & text) const;
	std::array<std::uint8_t, 4> decodeLine(const std::string & line) const;

private:
	std::array<std::string, 4> createTokens(const std::string & string) const;
	std::uint8_t toInt(const std::string & str) const;
};

