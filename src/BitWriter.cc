#include "BitWriter.h"

BitWriter::BitWriter(std::ostream& out):buffer(0),count(0),out(out) {

}

BitWriter::~BitWriter() {
	this->flush();
}

void BitWriter::putBit(bit value) {
	const char bufferBits = sizeof(bit)*8;

	value = (1 & value) << (bufferBits - this->count - 1);
	this->buffer = this->buffer | value;

	this->count++;

	if(this->count == bufferBits) {
		this->out << this->buffer;
		this->buffer = 0;
		this->count = 0;
	}
}

void BitWriter::flush() {
	if(this->count > 0) {
		this->out << this->buffer;
	}
}