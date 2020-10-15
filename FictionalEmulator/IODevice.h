#pragma once
#include <cstdint>
class IODevice {
public:
	virtual void out(std::uint8_t reg, std::uint8_t byte) = 0;
	virtual std::uint8_t in(std::uint8_t reg) = 0;
};

