#ifndef BITREADER_H__
#define BITREADER_H__

#include "Bits.h"
#include <istream>

class BitReader
{
public:
	typedef Bits::bit bit;

private:
	std::istream &stream;
	bit buffer;
	char count;

	static const unsigned int pattern;

public:
	BitReader(std::istream &stream);
	virtual ~BitReader();

	bit getBit();
	bool eof() const;

private:
	bool isBufferEmpty() const;
	void fillBuffer();

	BitReader(const BitReader &stream);
};

#endif /* end of include guard: BITREADER_H__ */