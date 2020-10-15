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
#include "ROM.h"

ROM::ROM() {
	this->bytes.fill(static_cast<std::uint8_t>(0x00));
}

ROM::ROM(const std::unique_ptr<ROMImage> & img) {
	this->bytes = *img;
}

ROM::~ROM() {

}

void ROM::write(std::uint8_t byte, std::uint16_t adresse) {
	if (adresse >= this->bytes.size()) {
		throw MemoryOutOfRange();
	}
	else {
		this->bytes[adresse] = byte;
	}
}

void ROM::writeArr(std::array<std::uint8_t, 4> data, std::uint16_t address) noexcept(false) {
	for (std::uint16_t i = 0; i < data.size(); i++) {
		this->write(data[i], address + i);
	}
}

std::uint32_t ROM::size() const {
	return static_cast<std::uint32_t>(this->bytes.size());
}


std::uint8_t ROM::read(std::uint16_t adresse) const {
	if (adresse >= this->bytes.size()) {
		throw MemoryOutOfRange();
		return std::uint8_t(0x00);
	}
	else {
		return this->bytes[adresse];
	}
}

void ROM::loadRom(const std::unique_ptr<ROMImage> & romDate) {
	this->bytes = *romDate;
}
