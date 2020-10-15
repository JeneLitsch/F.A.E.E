#pragma once
#include <array>
#include <vector>
#include "Memory.h"
#include "Constants.h"
#include "Exceptions.h"
#include <memory>
#include "Types.h"
class RAM {
public:
	RAM();
	~RAM();
	void write(std::uint8_t byte, std::uint16_t adresse) noexcept(false);
	void writeVec(std::vector<std::uint8_t> data, std::uint16_t address) noexcept(false);
	void writeArr(std::array<std::uint8_t, 4> data, std::uint16_t address) noexcept(false);
	std::uint8_t read(std::uint16_t adresse) const noexcept(false);

	void loadImg(const std::unique_ptr<RAMImage> & data);
	std::array<std::uint8_t, CNST::ramSize> createImg() const;


	std::uint32_t size() const;

private:
	std::array<std::uint8_t, CNST::ramSize> bytes;
};

