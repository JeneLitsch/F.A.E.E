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
#pragma once
#include <cstdint>
namespace CNST {
	const static inline std::uint16_t ramSize = 0x8000;
	const static inline std::uint16_t romSize = 0x4000;
	const static inline std::uint16_t iomSize = 0x1000;
	const static inline std::uint32_t defaultClockSpeed = 4096;
}