#ifndef TUNELZ_LIM_H__
#define TUNELZ_LIM_H__

#include <iostream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

#define ENCODE(bits, Dict) case bits: {Dict<bits> d; Encoder<bits, Dict> coder(d); coder.encode(std::cin, std::cout); }; break;
#define DECODE(bits, Dict) case bits: {Dict<bits> d; Decoder<bits, Dict> coder(d); coder.decode(std::cin, std::cout); }; break;

template<template<Bits::bit_count> class D> int mainTemplate(int argc, char* argv[]) {
	bool encode = true;
	Bits::bit_count bits = 8;

	for(int i = 1; i < argc; i++) {
		std::string arg1(argv[i]);

		if(arg1 == "-e" || arg1 == "e") {
			encode = true;
		} else if(arg1 == "-d" || arg1 == "d") {
			encode = false;
		} else if(arg1 == "-1" || arg1 == "-2" || arg1 == "-4" || arg1 == "-8") {
			bits = arg1[1] - '0';
		} else if ((arg1.size() > 2) && (arg1[0] == '-') && (arg1[1] == '-')) {
		} else {
			std::cerr << "USAGE: " << argv[0] << " [-e|-d] [-1|-2|-4|-8]" << std::endl;
			std::cerr << "\t-e\t\t--- compression, default." << std::endl;
			std::cerr << "\t-d\t\t--- uncompression." << std::endl;
			std::cerr << "\t-[-1|-2|-4|-8]\t--- select symbol size in bits, 8 is default." << std::endl;
			return 1;
		}
	}

	if(encode) {
		switch(bits) {
			ENCODE(1, D);
			ENCODE(2, D);
			ENCODE(4, D);
		default:
			ENCODE(8, D);
		}
	} else {
		switch(bits) {
			DECODE(1, D);
			DECODE(2, D);
			DECODE(4, D);
		default:
			DECODE(8, D);
		}
	}

	return 0;
}

#undef ENCODE
#undef DECODE

#endif /* end of include guard: TUNELZ_LIM_H__ */