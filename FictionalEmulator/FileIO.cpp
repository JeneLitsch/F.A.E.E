#include "FileIO.h"

std::vector<std::string> FileIO::loadSource(std::string name) {
	std::vector<std::string> fileContent;
	std::string line;
	std::ifstream file;
	file.open(name);
	if (file.is_open() && file.good()) {
		while (std::getline(file, line)) {
			fileContent.push_back(line);
		}
		file.close();
	}
	return fileContent;
}

void FileIO::writeImg(const std::array<std::uint8_t, CNST::ramSize> & img) {
	std::ofstream file("ram.img", std::ios::binary);
	for (std::uint8_t chr : img) {
		file << chr;
	}
}

std::unique_ptr<RAMImage> FileIO::readImg(const std::string & file_path) {
	std::ifstream file(file_path, std::ios::in | std::ios::binary);
	std::unique_ptr<RAMImage> array = std::make_unique<RAMImage>();
	array->fill(0);
	if (file.is_open() && file.good()) {
		std::vector<std::uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		std::copy_n(data.begin(), CNST::ramSize, array->begin());
	}
	return array;
}