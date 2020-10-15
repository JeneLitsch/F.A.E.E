#pragma once
#include <cstdint>
#include <array>
#include "Exceptions.h"
#include "IODevice.h"
class IOController {
public:
	IOController();

	//read a byte from device and port
	std::uint8_t read(std::uint16_t adresse) const noexcept(false);

	//writes a byte to a specified device and port
	void write(std::uint8_t byte, std::uint16_t adresse) noexcept(false);

	//connects a device to the specified connection
	//use nullptr to remove the current device from a connection
	void setDevice(IODevice * device, std::uint8_t id);
private:
	std::uint8_t deviceAddr(std::uint16_t addr) const;
	std::uint8_t deviceRegisterAddr(std::uint16_t addr) const;
	std::array<IODevice *, 256> ioDevices;
};

typedef IOController IOC;