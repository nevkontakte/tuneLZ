#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

#include "Symbol.h"

using namespace std;

TEST(Symbol, Read){
	Symbol actual;
	char c = 0;
	for(unsigned int i = 0; i < 256; ++i) {
		Symbol expected(c);

		istringstream in(string(1, c));
		BitReader stream(in);
		actual.read(stream);

		ASSERT_EQ(expected, actual);
		++c;
	}
}