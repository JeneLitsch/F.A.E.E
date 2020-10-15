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