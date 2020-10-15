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
#include "IOConsole.h"
#include <iostream>
#include <bitset>
void IOConsole::out(std::uint8_t reg, std::uint8_t byte) {
	if (reg == 0) {
		std::cout << byte;
	}
	else if (reg == 1) {
		std::cout << int(std::int16_t(byte));
	}
	else if (reg == 2) {
		std::cout << unsigned int(byte);
	}
	else if (reg == 3) {
		std::cout << "0x" << std::hex << unsigned int(byte) << std::dec;
	}
	else if (reg == 3) {
		std::cout << "0b" << std::bitset<8>(byte);
	}

	else if (reg == 0x8) {
		std::cout << byte << "\n";
	}
	else if (reg == 0x9) {
		std::cout << int(std::int16_t(byte)) << "\n";
	}
	else if (reg == 0xa) {
		std::cout << unsigned int(byte) << "\n";
	}
	else if (reg == 0xb) {
		std::cout << "0x" << std::hex << unsigned int(byte) << std::dec << "\n";
	}
	else if (reg == 0xc) {
		std::cout << "0b" << std::bitset<8>(byte) << "\n";
	}
}
std::uint8_t IOConsole::in(std::uint8_t reg) {
	return 0;
}