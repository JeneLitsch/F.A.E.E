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
#include <cstddef>
namespace InstFX {
	//signed interger arithmetic
	std::uint8_t i_add(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t i_sub(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t i_mlt(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t i_div(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t i_mod(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t i_inc(std::uint8_t regIn0);
	std::uint8_t i_dec(std::uint8_t regIn0);

	//unsigned interger arithmetic
	std::uint8_t u_add(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t u_sub(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t u_mlt(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t u_div(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t u_mod(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t u_inc(std::uint8_t regIn0);
	std::uint8_t u_dec(std::uint8_t regIn0);

	//bitwise operation
	std::uint8_t bit_and(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t bit_or(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t bit_xor(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t bit_xnor(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t bit_nand(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t bit_not(std::uint8_t regIn0);

	std::uint8_t icmp_eql(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t icmp_neq(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t icmp_bigr(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t icmp_smlr(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t icmp_eqbigr(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t icmp_eqsmlr(std::uint8_t regIn0, std::uint8_t regIn1);

	std::uint8_t ucmp_eql(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t ucmp_neq(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t ucmp_bigr(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t ucmp_smlr(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t ucmp_eqbigr(std::uint8_t regIn0, std::uint8_t regIn1);
	std::uint8_t ucmp_eqsmlr(std::uint8_t regIn0, std::uint8_t regIn1);

	template <class T_OUT, class T_IN>
	T_OUT to(T_IN val) {
		union {
			T_IN in;
			T_OUT out;
		} converter = { val };
		return converter.out;
	}
	//bit pattern cast unsigned -> signed
	std::int8_t sign(std::uint8_t val);
	//bit pattern cast signed -> unsigned
	std::uint8_t unsign(std::int8_t val);
};


