#include "ACU.h"
#include "Constants.h"
#include <array>
ACU::ACU() {
	this->setRAMMode();
}
std::uint16_t ACU::resolveAddr(std::uint16_t pc) const {
	const std::uint32_t sectorAddr = (pc * 4) % this->sectorSize;
	return std::uint16_t(sectorAddr + this->cmdOffset);
}
void ACU::setRAMMode() {
	this->cmdOffset = 0;
	this->sectorSize = CNST::ramSize;
}
void ACU::setROMMode() {
	this->cmdOffset = CNST::ramSize;
	this->sectorSize = CNST::romSize;
}

bool ACU::endian() const {
	std::uint16_t num = 0x0001;
	std::array<std::uint8_t, 2> arr = *reinterpret_cast<std::array<std::uint8_t, 2> *>(&num);
	return bool(arr[0]);
}

std::uint16_t ACU::merge(std::uint8_t u8_0, std::uint8_t u8_1) const {
	if (endian()) {
		return std::uint16_t(u8_0) << 8 | std::uint16_t(u8_1);
	}
	else {
		return std::uint16_t(u8_0) | std::uint16_t(u8_1) << 8;
	}
}