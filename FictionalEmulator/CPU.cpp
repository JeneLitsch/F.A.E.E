#include "CPU.h"
#include "InstructionFX.h"
#include <iostream>

CPU::CPU() {
	this->pc = 0;
	this->r.fill(0x00);
	this->rc.fill(0x00);
	this->running = true;
	this->bus = nullptr;
	this->logActive = false;
	this->acu.setROMMode();
}

void CPU::run() {
	while (this->running) {
		this->clock.start();
		this->fetch();
		this->execute();
		this->increment();
		this->logState();
		this->clock.wait();
	}				   
}

void CPU::linkBus(BUS * bus_) {
	this->bus = bus_;
}

void CPU::fetch() {
	std::uint16_t addr = this->acu.resolveAddr(pc);
	this->rc[0] = this->bus->fetchData(addr + 0);
	this->rc[1] = this->bus->fetchData(addr + 1);
	this->rc[2] = this->bus->fetchData(addr + 2);
	this->rc[3] = this->bus->fetchData(addr + 3);
}
void CPU::execute() {
	if (this->isInst(0x00)) return this->shutdown();
	if (this->isInst(0x01)) return this->setRamMode();
	if (this->isInst(0x02)) return this->setRomMode();

	if (this->isInst(0x10)) return this->load();
	if (this->isInst(0x11)) return this->write();
	if (this->isInst(0x12)) return this->set();
	if (this->isInst(0x13)) return this->copy();
	if (this->isInst(0x14)) return this->rload();
	if (this->isInst(0x15)) return this->rwrite();

	if (this->isInst(0x20)) return this->i_add();
	if (this->isInst(0x21)) return this->i_sub();
	if (this->isInst(0x22)) return this->i_mlt();
	if (this->isInst(0x23)) return this->i_div();
	if (this->isInst(0x24)) return this->i_mod();
	if (this->isInst(0x25)) return this->i_inc();
	if (this->isInst(0x26)) return this->i_dec();

	if (this->isInst(0x30)) return this->u_add();
	if (this->isInst(0x31)) return this->u_sub();
	if (this->isInst(0x32)) return this->u_mlt();
	if (this->isInst(0x33)) return this->u_div();
	if (this->isInst(0x34)) return this->u_mod();
	if (this->isInst(0x35)) return this->u_inc();
	if (this->isInst(0x36)) return this->u_dec();

	if (this->isInst(0x41)) return this->bit_and();
	if (this->isInst(0x42)) return this->bit_or();
	if (this->isInst(0x43)) return this->bit_xor();
	if (this->isInst(0x44)) return this->bit_xnor();
	if (this->isInst(0x45)) return this->bit_nand();
	if (this->isInst(0x46)) return this->bit_not();

	if (this->isInst(0x50)) return this->ifnx();
	if (this->isInst(0x51)) return this->ifjm();
	if (this->isInst(0x52)) return this->got0();

	if (this->isInst(0x60)) return this->icmp_eql();
	if (this->isInst(0x61)) return this->icmp_neq();
	if (this->isInst(0x62)) return this->icmp_bigr();
	if (this->isInst(0x63)) return this->icmp_smlr();
	if (this->isInst(0x64)) return this->icmp_eqbigr();
	if (this->isInst(0x65)) return this->icmp_eqsmlr();

	if (this->isInst(0x66)) return this->ucmp_eql();
	if (this->isInst(0x67)) return this->ucmp_neq();
	if (this->isInst(0x68)) return this->ucmp_bigr();
	if (this->isInst(0x69)) return this->ucmp_smlr();
	if (this->isInst(0x6a)) return this->ucmp_eqbigr();
	if (this->isInst(0x6b)) return this->ucmp_eqsmlr();

	return this->shutdown();
}
void CPU::increment() {
	this->pc++;
}

void CPU::logState() {
	if (this->logActive) {
		if (this->log) {
			log(pc, r, rc);
		}
	}
}

void CPU::setClockSpeed(double frequency) {
	this->clock.setFrequency(frequency);
}

void CPU::shutdown() {
	this->running = false;
}
void CPU::setRamMode() {
	this->acu.setRAMMode();
	this->pc--;
}
void CPU::setRomMode() {
	this->acu.setROMMode();
	this->pc--;
}

bool CPU::isInst(std::uint8_t code) const {
	return this->rc[0] == std::uint8_t(code);
}

void CPU::load() {
	const std::uint16_t adr = this->acu.merge(this->rc[2], this->rc[3]);
	const std::uint8_t reg = this->rc[1];
	this->r[reg] = this->bus->fetchData(adr);
}
void CPU::write() {
	const std::uint16_t adr = this->acu.merge(this->rc[1], this->rc[2]);
	const std::uint8_t reg = this->rc[3];
	this->bus->pushData(adr, this->r[reg]);
}
void CPU::set() {
	const std::uint8_t reg = this->rc[1];
	const std::uint8_t val = this->rc[2];
	this->r[reg] = val;
}
void CPU::copy() {
	const std::uint8_t reg_from = this->rc[2];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = this->r[reg_from];
}

void CPU::rload() {
	const std::uint16_t adr = this->acu.merge(this->r[this->rc[2]], this->r[this->rc[3]]);
	const std::uint8_t reg = this->rc[1];
	this->r[reg] = this->bus->fetchData(adr);
}
void CPU::rwrite() {
	const std::uint16_t adr = this->acu.merge(this->r[this->rc[1]], this->r[this->rc[2]]);
	const std::uint8_t reg = this->rc[3];
	this->bus->pushData(adr, this->r[reg]);
}

void CPU::i_add() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::i_add(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::i_sub() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::i_sub(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::i_mlt() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::i_mlt(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::i_div() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::i_div(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::i_mod() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::i_mod(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::i_inc() {
	const std::uint8_t reg = this->rc[1];
	this->r[reg] = InstFX::i_inc(this->r[reg]);
}
void CPU::i_dec() {
	const std::uint8_t reg = this->rc[1];
	this->r[reg] = InstFX::i_dec(this->r[reg]);
}

void CPU::u_add() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::u_add(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::u_sub() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::u_sub(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::u_mlt() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::u_mlt(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::u_div() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::u_div(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::u_mod() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::u_mod(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::u_inc() {
	const std::uint8_t reg = this->rc[1];
	this->r[reg] = InstFX::u_inc(this->r[reg]);
}
void CPU::u_dec() {
	const std::uint8_t reg = this->rc[1];
	this->r[reg] = InstFX::u_dec(this->r[reg]);
}


void CPU::bit_and() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::bit_and(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::bit_or() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::bit_or(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::bit_xor() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::bit_xor(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::bit_xnor() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::bit_xnor(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::bit_nand() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::bit_nand(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::bit_not() {
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::bit_not(this->r[reg_from0]);
}

void CPU::icmp_eql(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::icmp_eql(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::icmp_neq(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::icmp_neq(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::icmp_bigr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::icmp_bigr(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::icmp_smlr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::icmp_smlr(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::icmp_eqbigr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::icmp_eqbigr(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::icmp_eqsmlr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::icmp_eqsmlr(this->r[reg_from0], this->r[reg_from1]);
}

void CPU::ucmp_eql(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::ucmp_eql(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::ucmp_neq(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::ucmp_neq(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::ucmp_bigr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::ucmp_bigr(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::ucmp_smlr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::ucmp_smlr(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::ucmp_eqbigr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::ucmp_eqbigr(this->r[reg_from0], this->r[reg_from1]);
}
void CPU::ucmp_eqsmlr(){
	const std::uint8_t reg_from0 = this->rc[2];
	const std::uint8_t reg_from1 = this->rc[3];
	const std::uint8_t reg_to = this->rc[1];
	this->r[reg_to] = InstFX::ucmp_eqsmlr(this->r[reg_from0], this->r[reg_from1]);
}

void CPU::ifnx() {
	if (!this->r[this->rc[1]]) {
		this->pc++;
	}
}
void CPU::ifjm() {
	if (this->r[this->rc[1]]) {
		this->pc = this->rc[2];
		this->pc--;
	}
	else {
		this->pc = this->rc[3];
		this->pc--;
	}
}
void CPU::got0() {
	this->pc = this->rc[1];
	this->pc--;
}

void CPU::setLog(std::function<void(std::uint16_t pc, std::array<std::uint8_t, 8> r, std::array<std::uint8_t, 4> rc)> output) {
	this->logActive = true;
	this->log = output;
}