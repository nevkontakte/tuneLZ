#ifndef DICTIONARY_H__
#define DICTIONARY_H__

#include <vector>
#include "CodeWord.h"

class Dictionary
{
public:
	typedef CodeWord::Index Index;

	static const CodeWord::Index NOT_FOUND;
	static const CodeWord::Index EMPTY_WORD_INDEX;

private:
	std::vector<CodeWord> entries;

public:
	Dictionary();
	virtual ~Dictionary();

	CodeWord getWord(Index index);
	Index getIndex(const CodeWord& word);
	void addWord(const CodeWord& word);

	Index getSize();
private:
	Dictionary(const Dictionary& other);
};

#endif /* end of include guard: DICTIONARY_H__ */