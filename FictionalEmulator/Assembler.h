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

