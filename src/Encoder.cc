#include "Encoder.h"
#include <iostream>

Encoder::Encoder() {

}

Encoder::~Encoder() {

}

void Encoder::encode(std::istream& source, std::ostream& dest) {
	BitReader bitsIn(source);

	Symbol currentSymbol;
	CodeWord::Index currentIndex = Dictionary::EMPTY_WORD_INDEX;

	while(!bitsIn.eof()) {
		try {
			currentSymbol.read(bitsIn);
		} catch(std::ios_base::failure e) {
			break;
		}

		CodeWord currentWord(currentSymbol, currentIndex);

		currentIndex = this->dict.getIndex(currentWord);

		if(currentIndex == Dictionary::NOT_FOUND) {
			this->dict.addWord(currentWord);
			std::cout << currentWord << std::endl;
			currentIndex = Dictionary::EMPTY_WORD_INDEX;
		}
	}
}