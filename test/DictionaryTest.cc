#include <gtest/gtest.h>
#include "Dictionary.h"
#include <stdexcept>

const Bits::bit_count bits = 8;

TEST(Dictionary, Create) {
	Dictionary<bits> d;
	ASSERT_EQ(2, d.getSize());
}

TEST(Dictionary, AddAndGet) {
	Dictionary<bits> d;

	ASSERT_EQ(CodeWord<bits>::EMPTY, d.getWord(Dictionary<bits>::EMPTY_WORD_INDEX));

	
	CodeWord<bits> wordA0(Symbol<bits>('A'), Dictionary<bits>::EMPTY_WORD_INDEX);
	d.addWord(wordA0);

	ASSERT_EQ(wordA0, d.getWord(2));
	ASSERT_EQ(wordA0.getSymbol(), d.getWord(2).getSymbol());

	CodeWord<bits> wordB1(Symbol<bits>('B'), 2);
	d.addWord(wordB1);

	ASSERT_EQ(wordB1, d.getWord(3));
	ASSERT_EQ(wordB1.getSymbol(), d.getWord(3).getSymbol());

	ASSERT_EQ(wordA0, d.getWord(2));
}

TEST(Dictionary, AddException) {
	Dictionary<bits> d;
	EXPECT_THROW({
		d.addWord(CodeWord<bits>(Symbol<bits>(), d.getSize()+1));
	}, std::logic_error);
}

TEST(Dictionary, Find) {
	const Dictionary<bits>::Index count = 64;
	Dictionary<bits> d;

	ASSERT_EQ(Dictionary<bits>::EMPTY_WORD_INDEX, d.getIndex(CodeWord<bits>::EMPTY));

	CodeWord<bits> notFound(Symbol<bits>(), count+1);
	ASSERT_EQ(Dictionary<bits>::NOT_FOUND, d.getIndex(notFound));

	for(Dictionary<bits>::Index i = Dictionary<bits>::EMPTY_WORD_INDEX; i <= count; i++) {
		CodeWord<bits> word(Symbol<bits>('A'+i), i);
		d.addWord(word);
		ASSERT_EQ(i+1, d.getIndex(word));
	}

	ASSERT_EQ(Dictionary<bits>::NOT_FOUND, d.getIndex(notFound));
}