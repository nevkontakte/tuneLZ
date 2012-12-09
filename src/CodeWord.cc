#include "CodeWord.h"
#include <stdexcept>

CodeWord::CodeWord():index(1) {

}

CodeWord::CodeWord(Index index):index(index) {

}

CodeWord::CodeWord(const Symbol& symbol, Index index): symbol(symbol),index(index) {
	if(index == 0) {
		throw std::logic_error("Zero index is not allowed.");
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

std::ostream &operator<< (std::ostream &out, const CodeWord &word) {
	out << '[' << word.getIndex() << ", " << word.getSymbol() << ']';
	return out;
}

const CodeWord CodeWord::EMPTY(0);