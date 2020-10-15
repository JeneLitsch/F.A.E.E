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
#include <iostream>
#include <fstream>
#include "Assembler.h"
#include "Machine.h"
#include "IOConsole.h"
#include "FileIO.h"
#include "ParameterReader.h"

int main(int argc, char * argv[]) {

	const std::string fileSource = ParameterReader::romFile(argc, argv);
	const double clockSpeed = ParameterReader::clockSpeed(argc, argv);
	const double log = ParameterReader::logCreation(argc, argv);
	const double wImg = ParameterReader::imgCreation(argc, argv);
	const std::string fileImg = ParameterReader::imgFile(argc, argv);

	Assembler assembler;
	IOConsole console;

	std::unique_ptr<Machine> machine = std::make_unique<Machine>();
	machine->loadRamImg(FileIO::readImg(fileImg));
	machine->setCPUClock(clockSpeed);
	machine->loadRom(assembler.decodeSource(FileIO::loadSource(fileSource)));
	machine->connectDevice(&console, 0);
	machine->setLog(log);
	machine->run();

	if (wImg) FileIO::writeImg(machine->createRamImg());
	return 0;
}