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
#include "Ram.h"


RAM::RAM() {
	this->bytes.fill(static_cast<std::uint8_t>(0x00));
}

RAM::~RAM() {

}

void RAM::write(std::uint8_t byte, std::uint16_t adresse) {
	if (adresse >= this->bytes.size()) {
		throw MemoryOutOfRange();
	}
	else {
		this->bytes[adresse] = byte;
	}
}

void RAM::writeVec(std::vector<std::uint8_t> data, std::uint16_t address) {
	for (std::uint16_t i = 0; i < data.size(); i++) {
		this->write(data[i], address + i);
	}
}

void RAM::writeArr(std::array<std::uint8_t, 4> data, std::uint16_t address) noexcept(false) {
	for (std::uint16_t i = 0; i < data.size(); i++) {
		this->write(data[i], address + i);
	}
}

std::uint32_t RAM::size() const {
	return static_cast<std::uint32_t>(this->bytes.size());
}


std::uint8_t RAM::read(std::uint16_t adresse) const {
	if (adresse >= this->bytes.size()) {
		throw MemoryOutOfRange();
		return std::uint8_t(0x00);
	}
	else {
		return this->bytes[adresse];
	}
}

void RAM::loadImg(const std::unique_ptr<RAMImage> & img) {
	this->bytes = *img;
}
std::array<std::uint8_t, CNST::ramSize> RAM::createImg()const {
	return this->bytes;
}