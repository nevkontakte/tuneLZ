#include <iostream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

#define ENCODE(bits, Dict) case bits: {Dict<bits> d; Encoder<bits, Dict> coder(d); coder.encode(std::cin, std::cout); }; break;
#define DECODE(bits, Dict) case bits: {Dict<bits> d; Decoder<bits, Dict> coder(d); coder.decode(std::cin, std::cout); }; break;

int main(int argc, char* argv[]) {
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
		} else {
			std::cerr << "USAGE: " << argv[0] << " [-e|-d] [-1|-2|-4|-8]" << /*" [--unlim|--lim|--old]" <<*/ std::endl;
			std::cerr << "\t-e\t\t--- compression, default." << std::endl;
			std::cerr << "\t-d\t\t--- uncompression." << std::endl;
			std::cerr << "\t-[-1|-2|-4|-8]\t--- select symbol size in bits, 8 is default." << std::endl;
			// std::cerr << "\t--unlim\t\t--- unlimited dictionary size, default." << std::endl;
			// std::cerr << "\t--lim\t\t--- limited dictionary size, no new words added after limit has reached." << std::endl;
			// std::cerr << "\t--old\t\t--- limited dictionary size, new words replace olders after limit has reached." << std::endl;
			return 1;
		}
	}

	if(encode) {
		switch(bits) {
			ENCODE(1, Dictionary);
			ENCODE(2, Dictionary);
			ENCODE(4, Dictionary);
		default:
			ENCODE(8, Dictionary);
		}
	} else {
		switch(bits) {
			DECODE(1, Dictionary);
			DECODE(2, Dictionary);
			DECODE(4, Dictionary);
		default:
			DECODE(8, Dictionary);
		}
	}

	return 0;
}