#include "Dictionary.h"
#include <algorithm>
#include <stdexcept>

Dictionary::Dictionary() {

}

Dictionary::~Dictionary() {

}

CodeWord Dictionary::getWord(Index index) {
	if(index == 0) {
		return CodeWord::EMPTY;
	} else {
		return this->entries[index-1];
	}
}

Dictionary::Index Dictionary::getIndex(const CodeWord& word) {
	if(word == CodeWord::EMPTY) {
		return 0;
	}

	std::vector<CodeWord>::iterator found = std::find(this->entries.begin(), this->entries.end(), word);

	if(found == this->entries.end()) {
		return NOT_FOUND;
	} else {
		return found - this->entries.begin() + 1;
	}
}

void Dictionary::addWord(const CodeWord& word) {
	if(word.getIndex() > this->getSize()) {
		throw std::logic_error("Code word to be added refers word out of dictionary");
	}

	this->entries.push_back(word);
}

Dictionary::Index Dictionary::getSize() {
	return this->entries.size();
}

const Dictionary::Index Dictionary::NOT_FOUND = -1;