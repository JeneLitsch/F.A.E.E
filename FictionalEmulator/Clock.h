#pragma once
#include <chrono>
class Clock {
public:
	void setFrequency(double hertz);

	//waits unteil end of processor cycly
	void wait() const;

	//restart clock and processor cycle
	void start();

private:
	std::chrono::high_resolution_clock clock;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	double frequency = 4096; //HZ
};

