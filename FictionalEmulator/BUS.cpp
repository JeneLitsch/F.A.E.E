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
#include "Bus.h"
#include "RAM.h"
#include "ROM.h"
#include "CPU.h"
#include "IOC.h"
BUS::BUS(CPU & cpu_, RAM & ram_, const ROM & rom_, IOC & ioc) : cpu(cpu_), ram(ram_), rom(rom_), ioc(ioc) {
	this->cpu.linkBus(this);
}

std::uint8_t BUS::fetchData(std::uint16_t addr) const {
	std::uint16_t sectorAddr = (addr & 0xf000) >> 12;
	if (sectorAddr >= 0x0 && sectorAddr < 0x8) {
		return this->ram.read(addr);
	}
	else if (sectorAddr >= 0x8 && sectorAddr < 0xC) {
		return this->rom.read(addr - 0x8000);
	}
	else if (sectorAddr >= 0xD) {
		return this->ioc.read(addr);
	}
	else 
		throw MemoryOutOfRange();
}


void BUS::pushData(std::uint16_t addr, std::uint8_t byte) {
	std::uint16_t sectorAddr = (addr & 0xf000) >> 12;
	if (sectorAddr >= 0x0 && sectorAddr < 0x8) {
		this->ram.write(byte, addr);
	}
	else if (sectorAddr >= 0x8 && sectorAddr < 0xC) {
		//this->rom.write(byte, addr);
	}
	else if (sectorAddr >= 0xD) {
		this->ioc.write(byte, addr);
	}
	else
		throw MemoryOutOfRange(addr);
}
