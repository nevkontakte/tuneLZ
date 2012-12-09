#include "Symbol.h"

Symbol::Symbol():value(0) {

}

Symbol::Symbol(char value):value(value) {

}

Symbol::~Symbol() {}

void Symbol::read(BitReader& stream) {
	this->value = 0;
	for(size_type i = 0; i < bits; ++i) {
		BitReader::bit bit = stream.getBit();
		value = (value << 1) | bit;
	}
}

void Symbol::write(BitWriter& stream) {
	for(size_type i = 0; i < bits; ++i) {
		BitWriter::bit bit = (this->value & (1 << (bits - i - 1))) != 0;
		stream.putBit(bit);
	}
}

bool Symbol::operator==(const Symbol& other) const {
	return this->value == other.value;
}

std::ostream &operator<< (std::ostream &out, const Symbol &symbol) {
	out << symbol.value;
	return out;
}

const Symbol::size_type Symbol::bits = sizeof(char)*8;

