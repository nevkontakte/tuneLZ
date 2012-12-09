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

void CodeWord::write(BitWriter& stream, unsigned char indexBits) {
	if((1 << (indexBits-1)) <= this->index) {
		throw std::logic_error("Can't encode code word index passed with required bits.");
	}

	for (unsigned char i = 0; i < indexBits; ++i) {
		BitWriter::bit bit = (this->index & (1 << (indexBits - i - 1))) != 0;
		stream.putBit(bit);
	}

	this->symbol.write(stream);
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