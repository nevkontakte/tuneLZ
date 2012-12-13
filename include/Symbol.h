#ifndef SYMBOL_H__
#define SYMBOL_H__

#include "BitReader.h"
#include "BitWriter.h"
#include "Bits.h"
#include "helper.h"
#include <ostream>

template<Bits::bit_count bits> class Symbol
{
public:
	typedef unsigned char size_type;
protected:
	char value;
public:
	Symbol():value(0) {};
	Symbol(char value):value(value) {};
	virtual ~Symbol() {};

	void read(BitReader& stream) {
		this->value = 0;
		for(size_type i = 0; i < bits; ++i) {
			BitReader::bit bit = stream.getBit();
			value = (value << 1) | bit;
		}
	};
	void write(BitWriter& stream) const {
		for(size_type i = 0; i < bits; ++i) {
			BitWriter::bit bit = (this->value & (1 << (bits - i - 1))) != 0;
			stream.putBit(bit);
		}
	};
	bool operator==(const Symbol& other) const {
		return this->value == other.value;
	};

	friend std::ostream &operator<< (std::ostream &out, const Symbol &symbol) {
		out << symbol.value << ' ' << binary(symbol.value);
		return out;
	}

	friend struct std::hash<Symbol<bits> >;
};


namespace std {
	template<Bits::bit_count bits> struct hash<Symbol<bits> > {
		size_t operator()(const Symbol<bits>& symbol) const {
			return hash<char>()(symbol.value);
		}
	};
}
#endif /* end of include guard: SYMBOL_H__ */