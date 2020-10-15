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

