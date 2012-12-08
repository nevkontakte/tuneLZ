#include "CodeWord.h"
#include <stdexcept>

CodeWord::CodeWord():index(0) {

}

CodeWord::CodeWord(Index index):index(index) {

}

CodeWord::CodeWord(const Symbol& symbol, Index index): symbol(symbol),index(index) {
	if(index < 0) {
		throw std::logic_error("Index lesser than 0 is not allowed.");
	}
}

CodeWord::~CodeWord() {

}

bool CodeWord::operator==(const CodeWord& other) const {
	return this->index == other.index && this->symbol == other.symbol;
}

const Symbol& CodeWord::getSymbol() const {
	return this->symbol;
}

CodeWord::Index CodeWord::getIndex() const {
	return this->index;
}

const CodeWord CodeWord::EMPTY(-1);