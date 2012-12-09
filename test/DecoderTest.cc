#include <sstream>
#include <gtest/gtest.h>
#include "Decoder.h"

TEST(Decoder, Simple) {
	std::string uncompressed;
	uncompressed = uncompressed + "a" + "ab" + "abc" + "abcd" + "abcde" + "abcdef" + "abcdefg" + "abcdefgh";

	// Array of bits expected as compressed output.
	BitReader::bit compressedData[] = {
	//	Index bin;	Symbol bin code
		1,			0,1,1,0, 0,0,0,1,	// 1 a
		1,0,		0,1,1,0, 0,0,1,0,	// 2 b
		1,1,		0,1,1,0, 0,0,1,1,	// 3 c
		1,0,0,		0,1,1,0, 0,1,0,0,	// 4 d
		1,0,1,		0,1,1,0, 0,1,0,1,	// 5 e
		1,1,0,		0,1,1,0, 0,1,1,0,	// 6 f
		1,1,1,		0,1,1,0, 0,1,1,1,	// 7 g
		1,0,0,0,	0,1,1,0, 1,0,0,0,	// 8 h
		0,0,0,0,	0,0,0,0, 0,0,0,0,	// Terminal word
	};

	std::ostringstream compressed;
	BitWriter compressedBits(compressed);

	for(unsigned int i = 0; i < (sizeof(compressedData)/sizeof(BitReader::bit)); ++i) {
		compressedBits.putBit(compressedData[i]);
	}
	compressedBits.flush();

	std::istringstream input(compressed.str());
	std::ostringstream output;

	Decoder coder;
	coder.decode(input, output);

	ASSERT_EQ(uncompressed, output.str());
}