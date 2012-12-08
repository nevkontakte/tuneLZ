#include <gtest/gtest.h>
#include "Dictionary.h"
#include <stdexcept>

TEST(Dictionary, Create) {
	Dictionary d;
	ASSERT_EQ(0, d.getSize());
}

TEST(Dictionary, AddAndGet) {
	Dictionary d;

	ASSERT_EQ(CodeWord::EMPTY, d.getWord(0));

	
	CodeWord wordA0(Symbol('A'), 0);
	d.addWord(wordA0);

	ASSERT_EQ(wordA0, d.getWord(1));
	ASSERT_EQ(wordA0.getSymbol(), d.getWord(1).getSymbol());

	CodeWord wordB1(Symbol('B'), 1);
	d.addWord(wordB1);

	ASSERT_EQ(wordB1, d.getWord(2));
	ASSERT_EQ(wordB1.getSymbol(), d.getWord(2).getSymbol());

	ASSERT_EQ(wordA0, d.getWord(1));
}

TEST(Dictionary, AddException) {
	Dictionary d;
	EXPECT_THROW({
		d.addWord(CodeWord(Symbol(), d.getSize()+1));
	}, std::logic_error);
}

TEST(Dictionary, Find) {
	const Dictionary::Index count = 64;
	Dictionary d;

	ASSERT_EQ(0, d.getIndex(CodeWord::EMPTY));

	CodeWord notFound(Symbol(), count+1);
	ASSERT_EQ(Dictionary::NOT_FOUND, d.getIndex(notFound));

	for(Dictionary::Index i = 1; i <= count; i++) {
		CodeWord word(Symbol('A'+i), i-1);
		d.addWord(word);
		ASSERT_EQ(i, d.getIndex(word));
	}

	ASSERT_EQ(Dictionary::NOT_FOUND, d.getIndex(notFound));
}