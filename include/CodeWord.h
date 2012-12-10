#ifndef CODEWORD_H__
#define CODEWORD_H__

#include "Symbol.h"
#include "BitWriter.h"
#include "BitReader.h"
#include "Bits.h"
#include <vector>
#include <stdexcept>

#include <iostream>
#include "helper.h"

template<Bits::bit_count bits>  class CodeWord
{
public:
	// TODO Use vector::size_type
	typedef unsigned long Index;
	static const CodeWord<bits> EMPTY;

private:
	Symbol<bits> symbol;
	Index index;

public:
	CodeWord() :index(1) {};
	CodeWord(const Symbol<bits>& symbol, Index index):symbol(symbol),index(index){
		if(index == 0) {
			throw std::logic_error("Zero index is not allowed.");
		}
	};
	virtual ~CodeWord() {};

	void read(BitReader& stream, unsigned char indexBits) {
		this->index = 0;
		for(unsigned char i = 0; i < indexBits; i++) {
			BitReader::bit bit = stream.getBit();
			this->index = (this->index << 1) | bit;
		}
		this->symbol.read(stream);
	};

	void write(BitWriter& stream, unsigned char indexBits) const {
		if((1 << indexBits)-1 < this->index) {
			throw std::logic_error("Can't encode code word index passed with required bits.");
		}

		for (unsigned char i = 0; i < indexBits; ++i) {
			BitWriter::bit bit = (this->index & (1 << (indexBits - i - 1))) != 0;
			stream.putBit(bit);
		}

		this->symbol.write(stream);
	};

	bool operator==(const CodeWord& other) const {
		return this->index == other.index && this->symbol == other.symbol;
	};
	bool operator!=(const CodeWord& other) const {
		return !(*this == other);
	};
	const Symbol<bits>& getSymbol() const {
		return this->symbol;
	};
	Index getIndex() const {
		return this->index;
	};

private:
	CodeWord(Index index) :index(index) {};
};

template<Bits::bit_count bits>
std::ostream &operator<< (std::ostream &out, const CodeWord<bits> &word) {
	out << '[' << word.getIndex() << ", " << word.getSymbol() << ']';
	return out;
};

template<Bits::bit_count bits> 
const CodeWord<bits> CodeWord<bits>::EMPTY(0);
#endif /* end of include guard: CODEWORD_H__ */