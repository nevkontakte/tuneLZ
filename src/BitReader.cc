#include "BitReader.h"

BitReader::BitReader(std::istream &stream):stream(stream),buffer(0),count(0) {
	stream.exceptions(std::istream::eofbit | std::istream::badbit |std::istream::failbit);
}

BitReader::~BitReader() {}

bool BitReader::isBufferEmpty() const {
	return this->count == 0;
}

void BitReader::fillBuffer() {
	this->stream.get(this->buffer);
	this->count = sizeof(this->buffer)*8;
}

BitReader::bit BitReader::getBit() {
	if (this->isBufferEmpty()) {
		this->fillBuffer();
	}

	--this->count;
	bit current = (this->buffer & pattern) != 0;
	this->buffer = this->buffer << 1;
	return current;
}

bool BitReader::eof() const {
	return this->stream.eof();
}

const unsigned int BitReader::pattern = ((bit) 1) << sizeof(bit)*8;