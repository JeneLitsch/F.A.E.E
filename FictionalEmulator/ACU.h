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
#include <cstdint>
class ACU {
public:
	ACU();

	//returns memory address based in pc and readmode Offset 
	std::uint16_t resolveAddr(std::uint16_t programmCounter) const;

	//merges two 8 bit number
	std::uint16_t merge(std::uint8_t u8_0, std::uint8_t u8_1) const;

	void setRAMMode();
	//adds offset to begin of ROM memory
	void setROMMode();
private:
	//returns endianess
	bool endian() const;
	std::uint16_t cmdOffset;
	std::uint16_t sectorSize;
};

