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

#include "Clock.h"
#include <thread>
void Clock::setFrequency(double hertz) {
	if (hertz >= 0) {
		this->frequency = std::max(hertz, 1.0);
	}
	else {
		this->frequency = 4096;
	}
}

void Clock::wait() const {
	const auto total = std::chrono::duration<double>(1.0 / this->frequency);
	const auto elapsed = std::chrono::duration<double>(this->clock.now() - this->startTime);
	const auto remaining = total - elapsed;
	std::this_thread::sleep_for(remaining);
}
void Clock::start() {
	this->startTime = this->clock.now();
}