#pragma once
#include "IODevice.h"
class IOConsole : public IODevice {
	virtual void out(std::uint8_t reg, std::uint8_t byte) override;
	virtual std::uint8_t in(std::uint8_t reg) override;
};

