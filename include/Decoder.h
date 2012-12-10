#ifndef DECODER_H__
#define DECODER_H__

#include <iostream>
#include "Dictionary.h"

template<Bits::bit_count bits, template<Bits::bit_count> class D> class Decoder
{
	D<bits>& dict;
public:
	Decoder(D<bits>& dict):dict(dict) {};
	virtual ~Decoder() {};

	void decode(std::istream& source, std::ostream& dest) {
		BitReader bitsIn(source);
		BitWriter bitsOut(dest);

		unsigned char indexBits = 0;

		while(!bitsIn.eof()) {
			while((1 << indexBits) < dict.getSize()) indexBits++;

			CodeWord<bits> word;
			word.read(bitsIn, indexBits);
			this->dict.expandWord(word, bitsOut);

			if(word == CodeWord<bits>::EMPTY) {
				break;
			}

			dict.addWord(word);
		}
		dest.flush();
	};
};

#endif /* end of include guard: DECODER_H__ */