#include <gtest/gtest.h>

#include "Encoder.h"

#include <sstream>
#include <string>

TEST(Encoder, Create) {
	Encoder coder;
}

TEST(Encoder, CompressSimple) {
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

	Encoder coder;
	coder.encode(input, output);

	std::istringstream compressed(output.str());
	BitReader compressedBits(compressed);

	for(unsigned int i = 0; i < (sizeof(expected)/sizeof(BitReader::bit)); ++i) {
		ASSERT_EQ(expected[i], compressedBits.getBit());
	}
}

TEST(Encoder, CompressTail) {
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

	Encoder coder;
	coder.encode(input, output);

	std::istringstream compressed(output.str());
	BitReader compressedBits(compressed);

	for(unsigned int i = 0; i < (sizeof(expected)/sizeof(BitReader::bit)); ++i) {
		ASSERT_EQ(expected[i], compressedBits.getBit());
	}
}