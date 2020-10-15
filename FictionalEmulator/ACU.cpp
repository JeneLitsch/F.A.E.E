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
#include "ACU.h"
#include "Constants.h"
#include <array>
ACU::ACU() {
	this->setRAMMode();
}
std::uint16_t ACU::resolveAddr(std::uint16_t pc) const {
	const std::uint32_t sectorAddr = (pc * 4) % this->sectorSize;
	return std::uint16_t(sectorAddr + this->cmdOffset);
}
void ACU::setRAMMode() {
	this->cmdOffset = 0;
	this->sectorSize = CNST::ramSize;
}
void ACU::setROMMode() {
	this->cmdOffset = CNST::ramSize;
	this->sectorSize = CNST::romSize;
}

bool ACU::endian() const {
	std::uint16_t num = 0x0001;
	std::array<std::uint8_t, 2> arr = *reinterpret_cast<std::array<std::uint8_t, 2> *>(&num);
	return bool(arr[0]);
}

std::uint16_t ACU::merge(std::uint8_t u8_0, std::uint8_t u8_1) const {
	if (endian()) {
		return std::uint16_t(u8_0) << 8 | std::uint16_t(u8_1);
	}
	else {
		return std::uint16_t(u8_0) | std::uint16_t(u8_1) << 8;
	}
}