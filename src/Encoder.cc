#include "Encoder.h"

Encoder::Encoder() {

}

Encoder::~Encoder() {

}

void Encoder::encode(std::istream& source, std::ostream& dest) {
	BitReader bitsIn(source);
	BitWriter bitsOut(dest);

	Symbol currentSymbol;
	CodeWord::Index currentIndex = Dictionary::EMPTY_WORD_INDEX;

	unsigned char indexBits = 0;

	while(!bitsIn.eof()) {
		try {
			currentSymbol.read(bitsIn);
		} catch(std::ios_base::failure e) {
			break;
		}

		while((1 << indexBits) < dict.getSize()) indexBits++;

		CodeWord currentWord(currentSymbol, currentIndex);

		currentIndex = this->dict.getIndex(currentWord);

		if(currentIndex == Dictionary::NOT_FOUND) {
			this->dict.addWord(currentWord);
			currentWord.write(bitsOut, indexBits);
			currentIndex = Dictionary::EMPTY_WORD_INDEX;
		}
	}

	while((1 << indexBits) < dict.getSize()) indexBits++;

	CodeWord::EMPTY.write(bitsOut, indexBits);
	bitsOut.flush();
}