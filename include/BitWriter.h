#ifndef BITWRITER_H__
#define BITWRITER_H__

#include "Bits.h"
#include <ostream>

class BitWriter
{
public:
	typedef Bits::bit bit;

private:
	bit buffer;
	char count;
	std::ostream& out;

public:
	BitWriter(std::ostream& out);
	virtual ~BitWriter();

	void putBit(bit value);
	void flush();
	/* data */
};

#endif /* end of include guard: BITWRITER_H__ */