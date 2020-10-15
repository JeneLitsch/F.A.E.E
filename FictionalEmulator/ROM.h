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

