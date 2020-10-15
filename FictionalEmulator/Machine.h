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
#include "Types.h"

#include "CPU.h"
#include "RAM.h"
#include "ROM.h"
#include "IOC.h"
#include "BUS.h"
class Machine {
public:
	Machine();
	void loadRom(const std::unique_ptr<ROMImage> & romData); //load a 16kib rom cartride

	void loadRamImg(const std::unique_ptr<RAMImage> & img); //load a 32kib Array to Ram
	std::array<std::uint8_t, CNST::ramSize> createRamImg() const; //return a 32kib Array Ram Img

	void connectDevice(IODevice * device, std::uint8_t connectionID); //connects a IO device to connection 0 - 255 / 0x00 - 0xff
	void run(); //boots the machine

	void setCPUClock(double frequency);

	void setLog(bool b);

private:
	double clockSpeed = 4096;
	const static inline unsigned int versionMajor = 1;
	const static inline unsigned int versionMinor = 0;
	const static inline unsigned int versionPatch = 0;
	void printStartLine();

	CPU cpu; //processor
	RAM ram; //memory
	ROM rom; //static memory card
	BUS bus; //combined address and data bus
	IOC ioc; //i/o ontroller
};

