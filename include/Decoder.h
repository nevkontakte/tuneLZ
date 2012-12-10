#ifndef DECODER_H__
#define DECODER_H__

#include <iostream>
#include "Dictionary.h"

template<Bits::bit_count bits> class Decoder
{
	Dictionary<bits> dict;
public:
	Decoder() {};
	virtual ~Decoder() {};

	void decode(std::istream& source, std::ostream& dest) {
		BitReader bitsIn(source);
		BitWriter bitsOut(dest);

		unsigned char indexBits = 0;

		while(!bitsIn.eof()) {
			while((1 << indexBits) < dict.getSize()) indexBits++;

			CodeWord<bits> word;
			word.read(bitsIn, indexBits);
			this->expandWord(word, bitsOut);

			if(word == CodeWord<bits>::EMPTY) {
				break;
			}

			dict.addWord(word);
		}
		dest.flush();
	};

protected:
	void expandWord(CodeWord<bits> word, BitWriter& bitsOut) {
		if(word != CodeWord<bits>::EMPTY) {
			this->expandWord(this->dict.getWord(word.getIndex()), bitsOut);
			word.getSymbol().write(bitsOut);
		}
	};
};

#endif /* end of include guard: DECODER_H__ */