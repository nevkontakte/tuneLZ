#include <gtest/gtest.h>
#include <sstream>
#include "DictionarySized.h"

const Bits::bit_count bits8 = 8;

TEST(DictionarySized, Create) {
	const DictionarySized<bits8>::Index limit = 4;
	DictionarySized<bits8> d(limit);
	ASSERT_EQ(2, d.getSize());
}

TEST(DictionarySized, Fill) {
	const DictionarySized<bits8>::Index limit = 6;
	DictionarySized<bits8> d(limit);
	
	for(char i = 2; i <= limit; i++) {
		CodeWord<bits8> word(Symbol<bits8>('a'+i), i-1);
		d.addWord(word);
	}

	for(char i = 2; i < limit; i++) {
		CodeWord<bits8> word(Symbol<bits8>('a'+i), i-1);
		ASSERT_EQ(word, d.getWord(i));
	}

	ASSERT_EQ(CodeWord<bits8>::EMPTY, d.getWord(limit));
}

TEST(DictionarySized, Expand) {
	const DictionarySized<bits8>::Index limit = 6;
	DictionarySized<bits8> d(limit);
	
	for(char i = 2; i <= limit; i++) {
		CodeWord<bits8> word(Symbol<bits8>('a'+i), i-1);
		d.addWord(word);
	}

	std::string expected;
	for(char i = 2; i <= limit; i++) {
		expected += ('a'+i);
		CodeWord<bits8> word(Symbol<bits8>('a'+i), i-1);
		std::ostringstream out;
		BitWriter stream(out);
		d.expandWord(word, stream);
		stream.flush();
		ASSERT_EQ(expected, out.str());
	}
}