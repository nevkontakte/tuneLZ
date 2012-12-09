#include <iostream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

int main(int argc, char* argv[]) {
	bool encode = true;

	if(argc > 1) {
		std::string arg1(argv[1]);

		if(arg1 == "-e" || arg1 == "e") {
			encode = true;
		} else if(arg1 == "-d" || arg1 == "d") {
			encode = false;
		} else {
			std::cerr << "USAGE: " << argv[0] << " [-e|e|-d|d]" << std::endl;
			return 1;
		}
	}

	if(encode) {
		Encoder coder;
		coder.encode(std::cin, std::cout);
	} else {
		Decoder coder;
		coder.decode(std::cin, std::cout);
	}

	return 0;
}