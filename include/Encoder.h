#ifndef ENCODER_H__
#define ENCODER_H__

#include <iostream>
#include "Dictionary.h"

class Encoder
{
	Dictionary dict;
public:
	Encoder();
	~Encoder();

	void encode(std::istream& source, std::ostream& dest);
};

#endif /* end of include guard: ENCODER_H__ */