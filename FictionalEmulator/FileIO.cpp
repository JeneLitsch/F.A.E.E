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