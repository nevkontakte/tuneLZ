#ifndef DICTIONARY_H__
#define DICTIONARY_H__

#include <vector>
#include "Bits.h"
#include "CodeWord.h"

template<Bits::bit_count bits> class Dictionary
{
public:
	typedef typename CodeWord<bits>::Index Index;

	static const typename CodeWord<bits>::Index NOT_FOUND;
	static const typename CodeWord<bits>::Index EMPTY_WORD_INDEX;

private:
	typedef typename std::vector<CodeWord<bits> > Entries;
	Entries entries;

public:
	Dictionary() {};
	virtual ~Dictionary() {};

	CodeWord<bits> getWord(Index index) const {
		if(index == Dictionary<bits>::NOT_FOUND) {
			throw std::logic_error("Zero index denotes not found code word, it's not allowed here.");
		}
		else if(index == Dictionary::EMPTY_WORD_INDEX) {
			return CodeWord<bits>::EMPTY;
		} else {
			return this->entries[index-2];
		}
	};
	Index getIndex(const CodeWord<bits>& word) {
		if(word == CodeWord<bits>::EMPTY) {
			return EMPTY_WORD_INDEX;
		}

		typename Entries::iterator found;
		for(found = this->entries.begin(); found != this->entries.end(); found++) {
			if(*found == word) {
				break;
			}
		}

		if(found == this->entries.end()) {
			return NOT_FOUND;
		} else {
			return found - this->entries.begin() + 2;
		}
	};

	void addWord(const CodeWord<bits>& word) {
		if(word.getIndex() > this->getSize()) {
			throw std::logic_error("Code word to be added refers word out of dictionary");
		}

		this->entries.push_back(word);
	};

	Index getSize() const {
		return this->entries.size()+2;
	};
private:
	Dictionary(const Dictionary& other);
};

template<Bits::bit_count bits>
const typename CodeWord<bits>::Index Dictionary<bits>::NOT_FOUND = CodeWord<bits>::EMPTY.getIndex();


template<Bits::bit_count bits>
const typename Dictionary<bits>::Index Dictionary<bits>::EMPTY_WORD_INDEX = 1;

#endif /* end of include guard: DICTIONARY_H__ */