#include <gtest/gtest.h>
#include <sstream>
#include "CodeWord.h"

TEST(CodeWord, Read) {
	{
		std::istringstream in(std::string("\x01") + "a");
		BitReader stream(in);
		CodeWord word;
		word.read(stream, 8);
		ASSERT_EQ(1, word.getIndex());
		ASSERT_EQ(Symbol('a'), word.getSymbol());
	}
	
	{
		std::istringstream in(std::string("\x00\x01", 2) + "a");
		BitReader stream(in);
		CodeWord word;
		word.read(stream, 16);
		ASSERT_EQ(1, word.getIndex());
		ASSERT_EQ(Symbol('a'), word.getSymbol());
	}
	
	{
		std::istringstream in(std::string("\x16\x10"));
		BitReader stream(in);
		CodeWord word;
		word.read(stream, 4);
		ASSERT_EQ(1, word.getIndex());
		ASSERT_EQ(Symbol('a'), word.getSymbol());
	}
	
}

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