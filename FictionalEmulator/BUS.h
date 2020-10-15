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

