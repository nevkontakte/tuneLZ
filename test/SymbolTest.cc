#include <gtest/gtest.h>
#include <sstream>

#include "Symbol.h"

using namespace std;

const Bits::bit_count bits = 8;

TEST(Symbol, Read) {
	Symbol<bits> actual;
	char c = 0;
	for(unsigned int i = 0; i < 256; ++i) {
		Symbol<bits> expected(c);

		istringstream in(string(1, c));
		BitReader stream(in);
		actual.read(stream);

		ASSERT_EQ(expected, actual);
		++c;
	}
}

TEST(Symbol, Write) {
	char c = 0;
	for(unsigned int i = 0; i < 256; ++i) {
		string expected(&c, 1);

		ostringstream out;
		BitWriter stream(out);
		Symbol<bits> symbol(c);
		symbol.write(stream);

		ASSERT_EQ(expected, out.str());
		++c;
	}
}