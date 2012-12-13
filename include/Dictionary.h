#ifndef DICTIONARY_H__
#define DICTIONARY_H__

#include <vector>
#include <unordered_map>
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
	typedef typename std::unordered_map< CodeWord<bits>, Index, std::hash<CodeWord<bits> > > EntriesHashMap;
	Entries entries;
	EntriesHashMap reserve_map;

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

		if(this->reserve_map.count(word) > 0) {
			return this->reserve_map.at(word)+2;
		} else {
			return NOT_FOUND;
		}
	};

	void addWord(const CodeWord<bits>& word) {
		if(word.getIndex() > this->getSize()) {
			throw std::logic_error("Code word to be added refers word out of dictionary");
		}

		this->reserve_map.insert({{word, this->entries.size()}});
		this->entries.push_back(word);
	};

	Index getSize() const {
		return this->entries.size()+2;
	};

	void expandWord(CodeWord<bits> word, BitWriter& bitsOut) {
		if(word != CodeWord<bits>::EMPTY) {
			this->expandWord(this->getWord(word.getIndex()), bitsOut);
			word.getSymbol().write(bitsOut);
		}
	};

private:
	Dictionary(const Dictionary& other);
};

template<Bits::bit_count bits>
const typename CodeWord<bits>::Index Dictionary<bits>::NOT_FOUND = CodeWord<bits>::EMPTY.getIndex();


template<Bits::bit_count bits>
const typename Dictionary<bits>::Index Dictionary<bits>::EMPTY_WORD_INDEX = 1;

#endif /* end of include guard: DICTIONARY_H__ */