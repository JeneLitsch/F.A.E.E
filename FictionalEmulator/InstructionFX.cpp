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
#include "InstructionFX.h"

std::uint8_t InstFX::i_add(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) + sign(regIn1));
}
std::uint8_t InstFX::i_sub(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) - sign(regIn1));
}
std::uint8_t InstFX::i_mlt(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) * sign(regIn1));
}
std::uint8_t InstFX::i_div(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) / sign(regIn1));
}
std::uint8_t InstFX::i_mod(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) % sign(regIn1));
}
std::uint8_t InstFX::i_inc(std::uint8_t regIn0) {
	return unsign(sign(regIn0) + 1);
}
std::uint8_t InstFX::i_dec(std::uint8_t regIn0) {
	return unsign(sign(regIn0) - 1);
}


std::uint8_t InstFX::u_add(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 + regIn1;
}
std::uint8_t InstFX::u_sub(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 - regIn1;
}
std::uint8_t InstFX::u_mlt(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 * regIn1;
}
std::uint8_t InstFX::u_div(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 / regIn1;
}
std::uint8_t InstFX::u_mod(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 % regIn1;
}
std::uint8_t InstFX::u_inc(std::uint8_t regIn0) {
	return regIn0 + 1;
}
std::uint8_t InstFX::u_dec(std::uint8_t regIn0) {
	return regIn0 - 1;
}




std::uint8_t InstFX::bit_and(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 & regIn1;
}

std::uint8_t InstFX::bit_or(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 | regIn1;
}

std::uint8_t InstFX::bit_xor(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 ^ regIn1;
}

std::uint8_t InstFX::bit_xnor(std::uint8_t regIn0, std::uint8_t regIn1) {
	return bit_not(bit_xor(regIn0, regIn1));
}

std::uint8_t InstFX::bit_nand(std::uint8_t regIn0, std::uint8_t regIn1) {
	return bit_not(bit_and(regIn0, regIn1));
}

std::uint8_t InstFX::bit_not(std::uint8_t regIn) {
	return bit_xor(regIn, 0xff);
}



std::uint8_t InstFX::icmp_eql(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) == sign(regIn1));
}
std::uint8_t InstFX::icmp_neq(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) != sign(regIn1));
}
std::uint8_t InstFX::icmp_bigr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) > sign(regIn1));
}
std::uint8_t InstFX::icmp_smlr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) < sign(regIn1));
}
std::uint8_t InstFX::icmp_eqbigr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) >= sign(regIn1));
}
std::uint8_t InstFX::icmp_eqsmlr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return unsign(sign(regIn0) <= sign(regIn1));
}


std::uint8_t InstFX::ucmp_eql(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 == regIn1;
}
std::uint8_t InstFX::ucmp_neq(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 != regIn1;
}
std::uint8_t InstFX::ucmp_bigr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 > regIn1;
}
std::uint8_t InstFX::ucmp_smlr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 < regIn1;
}
std::uint8_t InstFX::ucmp_eqbigr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 >= regIn1;
}
std::uint8_t InstFX::ucmp_eqsmlr(std::uint8_t regIn0, std::uint8_t regIn1) {
	return regIn0 <= regIn1;
}



std::int8_t InstFX::sign(std::uint8_t val) {
	return to<std::int8_t, std::uint8_t>(val);
}
std::uint8_t InstFX::unsign(std::int8_t val){
	return to<std::uint8_t, std::int8_t>(val);

}