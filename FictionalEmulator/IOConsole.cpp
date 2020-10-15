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