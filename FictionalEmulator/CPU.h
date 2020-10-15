#pragma once
#include <array>
#include <functional>
#include "Memory.h"
#include "Bus.h"
#include "ACU.h"
#include "Clock.h"
class CPU {
public:
	CPU();
	void run();
	void linkBus(BUS * bus_);

	void setLog(std::function<void(std::uint16_t pc, std::array<std::uint8_t, 8> r, std::array<std::uint8_t, 4> rc)>);

	//set processor clock to Hertz
	void setClockSpeed(double frequency);

private:

	bool isInst(std::uint8_t code) const;

	//loads nex command into the command regsiters
	void fetch();

	//executes last fetched command
	void execute();

	//increments programm counter
	void increment();

	//optional Log data output
	void logState();

private:

	void shutdown();
	void setRamMode();
	void setRomMode();

	//loads based on static address
	void load();
	//writes based on static address
	void write();
	void set();
	void copy();

	//loads based on address saved in register
	void rload();
	//writes based on address saved in register
	void rwrite();

	void i_add();
	void i_sub();
	void i_mlt();
	void i_div();
	void i_mod();
	void i_inc();
	void i_dec();

	void u_add();
	void u_sub();
	void u_mlt();
	void u_div();
	void u_mod();
	void u_inc();
	void u_dec();

	void bit_and();
	void bit_or();
	void bit_xor();
	void bit_xnor();
	void bit_nand();
	void bit_not();

	void ifnx();
	void ifjm();
	void got0();

	void icmp_eql();
	void icmp_neq();
	void icmp_bigr();
	void icmp_smlr();
	void icmp_eqbigr();
	void icmp_eqsmlr();

	void ucmp_eql();
	void ucmp_neq();
	void ucmp_bigr();
	void ucmp_smlr();
	void ucmp_eqbigr();
	void ucmp_eqsmlr();

private:
	//Adress Generating Unit
	ACU acu;
	//System BUS
	BUS * bus;
	//Clock for processor speed
	Clock clock;
	bool running;
	bool logActive;

	//instruction / command register
	std::array<std::uint8_t, 4> rc;

	//data register
	std::array<std::uint8_t, 8> r;

	//programm counter
	std::int32_t pc;

private:
	std::function<void(
		std::uint16_t pc,
		std::array<std::uint8_t, 8> r,
		std::array<std::uint8_t, 4> rc)> log;
};

