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
#include "IOC.h"
#include <iostream>

IOController::IOController() {
	this->ioDevices.fill(nullptr);
}


std::uint8_t IOController::read(std::uint16_t addr) const noexcept(false) {
	const std::uint8_t dAddr = this->deviceAddr(addr);
	const std::uint8_t rAddr = this->deviceRegisterAddr(addr);
	if (this->ioDevices[dAddr]) {
		return this->ioDevices[dAddr]->in(rAddr);
	}
	else return 0;
}
void IOController::write(std::uint8_t byte, std::uint16_t addr) noexcept(false) {
	const std::uint8_t dAddr = this->deviceAddr(addr);
	const std::uint8_t rAddr = this->deviceRegisterAddr(addr);
	if (this->ioDevices[dAddr]) {
		this->ioDevices[dAddr]->out(rAddr, byte);
	}
}

std::uint8_t IOController::deviceAddr(std::uint16_t addr) const {
	return static_cast<std::uint8_t>((addr & 0x0ff0) >> 4);
}
std::uint8_t IOController::deviceRegisterAddr(std::uint16_t addr) const {
	return static_cast<std::uint8_t>((addr & 0x000f));
}

void IOController::setDevice(IODevice * device, std::uint8_t id) {
	this->ioDevices[id % 256] = device;
}