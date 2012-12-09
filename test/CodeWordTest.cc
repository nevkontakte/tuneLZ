#include <gtest/gtest.h>
#include <sstream>
#include "CodeWord.h"

TEST(CodeWord, Write) {
	{
		std::ostringstream out;
		CodeWord word(Symbol('a'), 1);
		BitWriter stream(out);
		word.write(stream, 8);
		stream.flush();
		ASSERT_EQ(std::string("\x01") + "a", out.str());
	}

	{
		std::ostringstream out;
		CodeWord word(Symbol('a'), 1);
		BitWriter stream(out);
		word.write(stream, 16);
		stream.flush();
		ASSERT_EQ(std::string("\x00\x01", 2) + "a", out.str());
	}

	{
		std::ostringstream out;
		CodeWord word(Symbol('a'), 1);
		BitWriter stream(out);
		word.write(stream, 4);
		stream.flush();
		ASSERT_EQ(std::string("\x16\x10"), out.str()); // 'a' = 0x61
	}
}