#pragma once
#include <cstdint>
#include "Exceptions.h"
#include "IOC.h"
class CPU;
class RAM;
class ROM;
class BUS {
public:
	BUS(CPU & cpu_, RAM & ram_, const ROM & rom_, IOC & ioc);

	std::uint8_t fetchData(std::uint16_t addr) const noexcept(false);
	void pushData(std::uint16_t addr, std::uint8_t byte) noexcept(false);

private:
	CPU & cpu;
	RAM & ram;
	const ROM & rom;
	IOC & ioc;
};

