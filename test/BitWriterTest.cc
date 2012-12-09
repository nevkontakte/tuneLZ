#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "BitWriter.h"

TEST(BitWriter, Regular) {
	std::ostringstream output;

	BitWriter::bit bits[] = {1, 0, 1, 1,   0, 1, 1, 1, 
	                         1, 0, 1, 1,   0, 1, 1, 1};
	std::string expected = "\xB7\xB7";
	
	BitWriter writer(output);

	for(int i = 0; i < sizeof(bits); i++) {
		writer.putBit(bits[i]);
	}

	ASSERT_EQ(expected, output.str());
}

TEST(BitWriter, Autoflush) {
	std::ostringstream output;

	BitWriter::bit bits[] = {1, 0, 1, 1,   0, 1, 1, 1,
	                         1, 0, 1, 1};
	std::string expected = "\xB7\xB0";
	
	{
		BitWriter writer(output);

		for(int i = 0; i < sizeof(bits); i++) {
			writer.putBit(bits[i]);
		}
	}

	ASSERT_EQ(expected, output.str());
}