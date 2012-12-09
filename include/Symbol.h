#ifndef SYMBOL_H__
#define SYMBOL_H__

#include "BitReader.h"
#include "BitWriter.h"
#include <ostream>

class Symbol
{
public:
	typedef unsigned char size_type;
protected:
	char value;
	static const size_type bits;
public:
	Symbol();
	Symbol(char value);
	virtual ~Symbol();

	void read(BitReader& stream);
	void write(BitWriter& stream);
	bool operator==(const Symbol& other) const;

	friend std::ostream &operator<< (std::ostream &out, const Symbol &symbol);
};

#endif /* end of include guard: SYMBOL_H__ */