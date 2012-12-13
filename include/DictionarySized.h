#ifndef DICTIONARY_SIZED_H__
#define DICTIONARY_SIZED_H__

#include <vector>
#include <unordered_map>
#include "Bits.h"
#include "CodeWord.h"

template<Bits::bit_count bits> class DictionarySized
{
	struct Entry;
	struct EntryHash;

public:
	typedef typename CodeWord<bits>::Index Index;

	static const typename CodeWord<bits>::Index NOT_FOUND;
	static const typename CodeWord<bits>::Index EMPTY_WORD_INDEX;

private:
	typedef typename std::vector<Entry> Entries;
	typedef typename std::unordered_map< CodeWord<bits>, Index, std::hash<CodeWord<bits> > > EntriesHashMap;

	Entries entries;
	Index limit;
	EntriesHashMap reserve_map;

public:
	DictionarySized(Index limit):limit(limit) {};
	virtual ~DictionarySized() {};

	CodeWord<bits> getWord(Index index) const {
		if(index == DictionarySized<bits>::NOT_FOUND) {
			throw std::logic_error("Zero index denotes not found code word, it's not allowed here.");
		}
		else if(index == DictionarySized::EMPTY_WORD_INDEX || index >= this->getSize()) {
			return CodeWord<bits>::EMPTY;
		} else {
			return this->getEntry(index).word;
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

		if(this->getSize() >= this->limit) {
			return;
		}

		this->reserve_map.insert({{word, this->entries.size()}});
		Entry entry(word, *this);
		this->entries.push_back(entry);
	};

	Index getSize() const {
		return this->entries.size()+2;
	};

	void expandWord(CodeWord<bits> word, BitWriter& stream) const {
		if(word != CodeWord<bits>::EMPTY) {
			if(word.getIndex() != EMPTY_WORD_INDEX) {
				this->getEntry(word.getIndex()).expand(stream);
			}
			word.getSymbol().write(stream);
		}
	};

private:
	DictionarySized(const DictionarySized& other);

	const Entry& getEntry(Index index) const {
		return this->entries.at(index-2);
	}

	/**
	 * Internal dictionary entry.
	 */
	struct Entry {
		CodeWord<bits> word;
		std::vector<Symbol<bits> > symbols;

		Entry(const CodeWord<bits>& word, DictionarySized& d):word(word) {
			if(word.getIndex() > EMPTY_WORD_INDEX) {
				const std::vector<Symbol<bits> >& syms = d.getEntry(word.getIndex()).symbols;
				this->symbols.assign(syms.begin(), syms.end());
			}
			this->symbols.push_back(word.getSymbol());
		}

		void expand(BitWriter stream) const {
			for(typename std::vector<Symbol<bits> >::const_iterator i = this->symbols.begin(); i != this->symbols.end(); i++) {
				i->write(stream);
			}
		}
	};
};

template<Bits::bit_count bits>
const typename CodeWord<bits>::Index DictionarySized<bits>::NOT_FOUND = CodeWord<bits>::EMPTY.getIndex();


template<Bits::bit_count bits>
const typename DictionarySized<bits>::Index DictionarySized<bits>::EMPTY_WORD_INDEX = 1;

#endif /* end of include guard: DICTIONARY_SIZED_H__ */