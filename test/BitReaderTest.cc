#include <gtest/gtest.h>
#include "BitReader.h"
#include <sstream>

using namespace std;

TEST(BitReader, General) {
	istringstream in("\xB7\x7B\xB4\x88", ios_base::in | ios_base::binary);

	BitReader::bit expected[] = {1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,0,0,1,0,0,0,1,0,0,0};

	BitReader bits(in);

	ASSERT_THROW({
		for (size_t i = 0; !bits.eof(); i++) {
			BitReader::bit current = bits.getBit();
			ASSERT_EQ(expected[i], current);
		}
	}, ios_base::failure);
}