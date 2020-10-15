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

