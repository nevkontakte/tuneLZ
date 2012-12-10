#include <gtest/gtest.h>

#include "Encoder.h"

#include <sstream>
#include <string>

const Bits::bit_count bits8 = 8;
const Bits::bit_count bits4 = 4;

TEST(Encoder, Create) {
	Encoder<bits8> coder;
}

TEST(Encoder, CompressSimple8) {
	std::string uncompressed;
	uncompressed = uncompressed + "a" + "ab" + "abc" + "abcd" + "abcde" + "abcdef" + "abcdefg" + "abcdefgh";

	// Array of bits expected as compressed output.
	BitReader::bit expected[] = {
	//	Index bin;	Symbol bin code
		1,			0,1,1,0, 0,0,0,1,	// 1 a
		1,0,		0,1,1,0, 0,0,1,0,	// 2 b
		1,1,		0,1,1,0, 0,0,1,1,	// 3 c
		1,0,0,		0,1,1,0, 0,1,0,0,	// 4 d
		1,0,1,		0,1,1,0, 0,1,0,1,	// 5 e
		1,1,0,		0,1,1,0, 0,1,1,0,	// 6 f
		1,1,1,		0,1,1,0, 0,1,1,1,	// 7 g
		1,0,0,0,	0,1,1,0, 1,0,0,0,	// 8 h
		0,0,0,0,	0,0,0,0, 0,0,0,0,	// Treminal word
	};

	std::istringstream input(uncompressed, std::istringstream::binary | std::istringstream::in);
	std::ostringstream output;

	Encoder<bits8> coder;
	coder.encode(input, output);

	std::istringstream compressed(output.str());
	BitReader compressedBits(compressed);

	for(unsigned int i = 0; i < (sizeof(expected)/sizeof(BitReader::bit)); ++i) {
		ASSERT_EQ(expected[i], compressedBits.getBit());
	}
}

TEST(Encoder, CompressTail8) {
	std::string uncompressed;
	uncompressed = uncompressed + "a" + "ab" + "abc" + "abcd" + "abcde" + "abcdef" + "abcdefg" + "abcdefg";

	// Array of bits expected as compressed output.
	BitReader::bit expected[] = {
	//	Index bin;	Symbol bin code
		1,			0,1,1,0, 0,0,0,1,	// 1 a
		1,0,		0,1,1,0, 0,0,1,0,	// 2 b
		1,1,		0,1,1,0, 0,0,1,1,	// 3 c
		1,0,0,		0,1,1,0, 0,1,0,0,	// 4 d
		1,0,1,		0,1,1,0, 0,1,0,1,	// 5 e
		1,1,0,		0,1,1,0, 0,1,1,0,	// 6 f
		1,1,1,		0,1,1,0, 0,1,1,1,	// 7 g
		0,1,1,1,	0,1,1,0, 0,1,1,1,	// 7 g
		0,0,0,0,	0,0,0,0, 0,0,0,0,	// Treminal word
	};

	std::istringstream input(uncompressed, std::istringstream::binary | std::istringstream::in);
	std::ostringstream output;

	Encoder<bits8> coder;
	coder.encode(input, output);

	std::istringstream compressed(output.str());
	BitReader compressedBits(compressed);

	for(unsigned int i = 0; i < (sizeof(expected)/sizeof(BitReader::bit)); ++i) {
		ASSERT_EQ(expected[i], compressedBits.getBit());
	}
}

TEST(Encoder, SimpleTest4) {
	std::string uncompressed;
	uncompressed = uncompressed + "a" + "ab" + "abc" + "abcd";

	// Array of bits expected as compressed output.
	BitReader::bit expected[] = {
	//	Index bin;	Symbol bin code
		1,			0,1,1,0, 	// 1 _*			2
		0,1,		0,0,0,1, 	// 1 _a 		3
		1,0,		0,0,0,1,	// 2 _*a 		4
		0,1,0,		0,0,1,0, 	// 2 _*b 		5
		1,0,0,		0,1,1,0,	// 4 _*a* 		6
		0,0,1,		0,0,1,0,	// 1 _b 		7
		0,1,0,		0,0,1,1,	// 2 _*c 		8
		0,1,1,0,	0,0,1,0,	// 6 _*a*b		9
		1,0,0,0,	0,1,1,0,	// 8 _*c* 		10
		0,0,0,1,	0,1,0,0,	// 2 _d 		11
		0,0,0,0,	0,0,0,0,	// Terminal word
	};

	std::istringstream input(uncompressed, std::istringstream::binary | std::istringstream::in);
	std::ostringstream output;

	Encoder<bits4> coder;
	coder.encode(input, output);

	std::istringstream compressed(output.str());
	BitReader compressedBits(compressed);

	for(unsigned int i = 0; i < (sizeof(expected)/sizeof(BitReader::bit)); ++i) {
		ASSERT_EQ(expected[i], compressedBits.getBit());
	}
}