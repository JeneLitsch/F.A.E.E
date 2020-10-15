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
#include <vector>
#include "Exceptions.h"
#include "Constants.h"
#include "Types.h"
class ROM {
public:
	ROM();
	ROM(const std::unique_ptr<ROMImage> & romDate);
	~ROM();



	std::uint8_t read(std::uint16_t adresse) const noexcept(false);
	std::uint32_t size() const;
	void loadRom(const std::unique_ptr<ROMImage> & romDate);

private:
	std::array<std::uint8_t, CNST::romSize> bytes;
	void write(std::uint8_t byte, std::uint16_t adresse) noexcept(false);
	void writeArr(std::array<std::uint8_t, 4> data, std::uint16_t address) noexcept(false);
};

