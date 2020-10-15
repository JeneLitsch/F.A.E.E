#include "Machine.h"
#include <iostream>

Machine::Machine() : bus(cpu, ram, rom, ioc) {
	this->setCPUClock(4096);
}

void Machine::loadRom(const std::unique_ptr<ROMImage> & romData) {
	this->rom.loadRom(romData);
}

void Machine::loadRamImg(const std::unique_ptr<RAMImage> & img) {
	this->ram.loadImg(img);
}

std::array<std::uint8_t, CNST::ramSize> Machine::createRamImg() const {
	return this->ram.createImg();
}

void Machine::connectDevice(IODevice * device, std::uint8_t connectionID) {
	this->ioc.setDevice(device, connectionID);
}

void Machine::run() {
	this->printStartLine();
	try {
		cpu.run();
	}
	catch (std::exception e) {
		std::cout << "An Error has occured:" << std::endl;
		std::cout << e.what() << std::endl;
	}
	std::cout << "\n";
}

void Machine::setCPUClock(double frequency) {
	this->cpu.setClockSpeed(frequency);
	this->clockSpeed = frequency;
}

void Machine::setLog(bool b) {
	if (b) {
		cpu.setLog([](std::uint16_t pc, auto r, auto rc) {
			std::cout << std::hex
				<< "#" << int(pc) << " ||| "
				<< int(r[0]) << "|"
				<< int(r[1]) << "|"
				<< int(r[2]) << "|"
				<< int(r[3]) << "|"
				<< int(r[4]) << "|"
				<< int(r[5]) << "|"
				<< int(r[6]) << "|"
				<< int(r[7]) << " ||| "

				<< int(rc[0]) << "|"
				<< int(rc[1]) << "|"
				<< int(rc[2]) << "|"
				<< int(rc[3]) << "|" << std::dec << std::endl;
		});
	}
	else {
		cpu.setLog([](std::uint16_t pc, auto r, auto rc) {});
	}
}

void Machine::printStartLine() {
	std::cout << "F.A.E.E 8-Bit v" << this->versionMajor << "." << this->versionMinor << "." << this->versionPatch << " @ " << this->clockSpeed/1000.0 << "kHz" << std::endl;
}

