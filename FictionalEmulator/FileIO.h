#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <array>
#include "Constants.h"
#include "Types.h"
class FileIO {
public:
	static std::vector<std::string> loadSource(std::string name);

	static void writeImg(const std::array<std::uint8_t, CNST::ramSize> & img);
	static std::unique_ptr<RAMImage> readImg(const std::string & file_path);
};

