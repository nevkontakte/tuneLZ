#ifndef DECODER_H__
#define DECODER_H__

#include <iostream>
#include "Dictionary.h"

class Decoder
{
	Dictionary dict;
public:
	Decoder();
	virtual ~Decoder();

	void decode(std::istream& source, std::ostream& dest);

protected:
	void expandWord(CodeWord word, BitWriter& bitsOut);
};

#endif /* end of include guard: DECODER_H__ */