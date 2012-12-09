#include "Dictionary.h"
#include <algorithm>
#include <stdexcept>

Dictionary::Dictionary() {

}

Dictionary::~Dictionary() {

}

CodeWord Dictionary::getWord(Index index) const {
	if(index == Dictionary::NOT_FOUND) {
		throw std::logic_error("Zero index denotes not found code word, it's not allowed here.");
	}
	else if(index == Dictionary::EMPTY_WORD_INDEX) {
		return CodeWord::EMPTY;
	} else {
		return this->entries[index-2];
	}
}

Dictionary::Index Dictionary::getIndex(const CodeWord& word) {
	if(word == CodeWord::EMPTY) {
		return EMPTY_WORD_INDEX;
	}

	std::vector<CodeWord>::iterator found = std::find(this->entries.begin(), this->entries.end(), word);

	if(found == this->entries.end()) {
		return NOT_FOUND;
	} else {
		return found - this->entries.begin() + 2;
	}
}

void Dictionary::addWord(const CodeWord& word) {
	if(word.getIndex() > this->getSize()) {
		throw std::logic_error("Code word to be added refers word out of dictionary");
	}

	this->entries.push_back(word);
}

Dictionary::Index Dictionary::getSize() const {
	return this->entries.size()+2;
}

const Dictionary::Index Dictionary::NOT_FOUND = CodeWord::EMPTY.getIndex();
const Dictionary::Index Dictionary::EMPTY_WORD_INDEX = 1;