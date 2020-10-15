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

#include "Assembler.h"
#include <regex>
#include <bitset>
#include "InstructionFX.h"

std::unique_ptr<ROMImage> Assembler::decodeSource(const std::vector<std::string> & src) const {
	std::unique_ptr<ROMImage> binary = std::make_unique<ROMImage>();
	binary->fill(0x00);
	size_t addr = 0;
	for (const std::string & str : src) {
		if (str != "") {
			const std::array<std::uint8_t, 4> bytes = this->decodeLine(str);
			for (int i = 0; i < 4; i++) {
				(*binary)[addr + i] = bytes[i];
			}
			addr += 4;
		}
	}
	return std::move(binary);
}

std::array<std::uint8_t, 4> Assembler::decodeLine(const std::string & line) const {
	const std::array<std::string, 4> tokens = createTokens(line);
	const std::string & type = tokens[0];
	const std::uint8_t num0 = this->toInt(tokens[1]);
	const std::uint8_t num1 = this->toInt(tokens[2]);
	const std::uint8_t num2 = this->toInt(tokens[3]);

	if (type == "exit") return { 0x00, num0, num1,num2 };
	if (type == "setRam") return { 0x01, num0, num1,num2 };
	if (type == "setrom") return { 0x02, num0, num1,num2 };

	if (type == "load") return { 0x10, num0, num1, num2 };
	if (type == "write") return { 0x11, num0, num1, num2 };
	if (type == "set") return { 0x12, num0, num1, num2 };
	if (type == "copy") return { 0x13, num0, num1, num2 };
	if (type == "rload") return { 0x14, num0, num1, num2 };
	if (type == "rwrite") return { 0x15, num0, num1, num2 };

	if (type == "i_add") return { 0x20, num0, num1,num2 };
	if (type == "i_sub") return { 0x21, num0, num1,num2 };
	if (type == "i_mlt") return { 0x22, num0, num1,num2 };
	if (type == "i_div") return { 0x23, num0, num1,num2 };
	if (type == "i_mod") return { 0x24, num0, num1,num2 };
	if (type == "i_inc") return { 0x25, num0, num1,num2 };
	if (type == "i_dec") return { 0x26, num0, num1,num2 };

	if (type == "u_add") return { 0x30, num0, num1,num2 };
	if (type == "u_sub") return { 0x31, num0, num1,num2 };
	if (type == "u_mlt") return { 0x32, num0, num1,num2 };
	if (type == "u_div") return { 0x33, num0, num1,num2 };
	if (type == "u_mod") return { 0x34, num0, num1,num2 };
	if (type == "u_inc") return { 0x35, num0, num1,num2 };
	if (type == "u_dec") return { 0x36, num0, num1,num2 };

	if (type == "and") return { 0x41, num0, num1,num2 };
	if (type == "or") return { 0x42, num0, num1,num2 };
	if (type == "xor") return { 0x43, num0, num1,num2 };
	if (type == "xnor") return { 0x44, num0, num1,num2 };
	if (type == "nand") return { 0x45, num0, num1,num2 };
	if (type == "not") return { 0x46, num0, num1,num2 };

	if (type == "ifnx") return { 0x50, num0, num1,num2 };
	if (type == "ifjm") return { 0x51, num0, num1,num2 };
	if (type == "goto") return { 0x52, num0, num1,num2 };

	if (type == "ieql") return { 0x60, num0, num1,num2 };
	if (type == "ineq") return { 0x61, num0, num1,num2 };
	if (type == "ibigr") return { 0x62, num0, num1,num2 };
	if (type == "ismlr") return { 0x63, num0, num1,num2 };
	if (type == "ieqbigr") return { 0x64, num0, num1,num2 };
	if (type == "ieqsmlr") return { 0x65, num0, num1,num2 };

	if (type == "ueql") return { 0x66, num0, num1,num2 };
	if (type == "uneq") return { 0x67, num0, num1,num2 };
	if (type == "ubigr") return { 0x68, num0, num1,num2 };
	if (type == "usmlr") return { 0x69, num0, num1,num2 };
	if (type == "ueqbigr") return { 0x6a, num0, num1,num2 };
	if (type == "ueqsmlr") return { 0x6b, num0, num1,num2 };

	else return { 0, 0, 0, 0 };
}

std::uint8_t Assembler::toInt(const std::string & str) const {
	int number = 0;

	if (str.size() >= 2 && str.substr(0, 2) == "0x") {
		std::stringstream sStream;
		sStream << std::hex << str;
		sStream >> number;
		 std::uint8_t(std::int8_t(number));
	}
	else if (str.size() >= 2 && str.substr(0, 2) == "0b") {
		number = std::bitset<8>(str.substr(2)).to_ulong();
	}
	else {
		std::stringstream sStream;
		sStream << str;
		sStream >> number;
	}

	if (number >= 0) {
		return number;
	}
	else {
		return InstFX::unsign(number);
	}

}

std::array<std::string, 4> Assembler::createTokens(const std::string & string) const {
	std::array<std::string, 4> tokens = { "0x00", "0x00", "0x00", "0x00" };
	const std::regex regex("^[a-z_]+|0x[0-9a-f]+|0b[0-1]+|[0-9]+");
	unsigned int k = 0;
	std::regex_iterator regExIt(string.begin(), string.end(), regex);
	for (; regExIt != std::sregex_iterator() && (k < 4); ++regExIt, ++k) {
		tokens[k] = regExIt->str();
	}
	return tokens;
}
