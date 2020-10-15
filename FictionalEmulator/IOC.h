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