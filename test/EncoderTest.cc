#include <gtest/gtest.h>

#include "Encoder.h"

#include <sstream>
#include <string>

TEST(Encoder, Create) {
	Encoder coder;
}

TEST(Encoder, CompressSimple) {
	std::istringstream input(std::string("aababcabcd", 10), std::istringstream::binary | std::istringstream::in);
	std::ostringstream output;

	Encoder coder;
	coder.encode(input, output);
}