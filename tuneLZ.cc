#include <iostream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

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
			std::cerr << "USAGE: " << argv[0] << " [-e|-d] [-1|-2|-4|-8]" << std::endl;
			return 1;
		}
	}

	if(encode) {
		switch(bits) {
			case 1:
				{
					Encoder<1> coder;
					coder.encode(std::cin, std::cout);
				}
				break;
			case 2:
				{
					Encoder<2> coder;
					coder.encode(std::cin, std::cout);
				}
				break;
			case 4:
				{
					Encoder<4> coder;
					coder.encode(std::cin, std::cout);
				}
				break;
			case 8:
			default:
				{
					Encoder<8> coder;
					coder.encode(std::cin, std::cout);
				}
				break;
		}
	} else {
		switch(bits) {
			case 1:
				{
					Decoder<1> coder;
					coder.decode(std::cin, std::cout);
				}
				break;
			case 2:
				{
					Decoder<2> coder;
					coder.decode(std::cin, std::cout);
				}
				break;
			case 4:
				{
					Decoder<4> coder;
					coder.decode(std::cin, std::cout);
				}
				break;
			case 8:
			default:
				{
					Decoder<8> coder;
					coder.decode(std::cin, std::cout);
				}
				break;
		}
	}

	return 0;
}