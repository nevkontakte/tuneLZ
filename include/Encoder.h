#ifndef ENCODER_H__
#define ENCODER_H__

#include "Dictionary.h"
#include "Bits.h"

template<Bits::bit_count bits> class Encoder
{
	Dictionary<bits> dict;
public:
	Encoder() {};
	~Encoder() {};

	void encode(std::istream& source, std::ostream& dest) {
		BitReader bitsIn(source);
		BitWriter bitsOut(dest);

		Symbol<bits> currentSymbol;
		typename CodeWord<bits>::Index currentIndex = Dictionary<bits>::EMPTY_WORD_INDEX;

		unsigned char indexBits = 0;

		while(!bitsIn.eof()) {
			while((1 << indexBits) < dict.getSize()) indexBits++;

			try {
				currentSymbol.read(bitsIn);
			} catch(std::ios_base::failure e) {
				if (currentIndex != Dictionary<bits>::EMPTY_WORD_INDEX) {
					this->dict.getWord(currentIndex).write(bitsOut, indexBits);
				}
				break;
			}

			CodeWord<bits> currentWord(currentSymbol, currentIndex);

			currentIndex = this->dict.getIndex(currentWord);

			if(currentIndex == Dictionary<bits>::NOT_FOUND) {
				this->dict.addWord(currentWord);
				currentWord.write(bitsOut, indexBits);
				currentIndex = Dictionary<bits>::EMPTY_WORD_INDEX;
			}
		}

		while((1 << indexBits) < dict.getSize()) indexBits++;

		CodeWord<bits>::EMPTY.write(bitsOut, indexBits);
		bitsOut.flush();
	};
};

#endif /* end of include guard: ENCODER_H__ */