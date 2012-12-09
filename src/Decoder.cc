#include "Decoder.h"

Decoder::Decoder() {

}

Decoder::~Decoder() {
	
}

void Decoder::decode(std::istream& source, std::ostream& dest) {
	BitReader bitsIn(source);
	BitWriter bitsOut(dest);

	unsigned char indexBits = 0;

	while(!bitsIn.eof()) {
		while((1 << indexBits) < dict.getSize()) indexBits++;

		CodeWord word;
		word.read(bitsIn, indexBits);
		this->expandWord(word, bitsOut);

		if(word == CodeWord::EMPTY) {
			break;
		}

		dict.addWord(word);
	}
	dest.flush();
}

void Decoder::expandWord(CodeWord word, BitWriter& bitsOut) {
	if(word != CodeWord::EMPTY) {
		this->expandWord(this->dict.getWord(word.getIndex()), bitsOut);
		word.getSymbol().write(bitsOut);
	}
}