#include "tuneLZ.h"
#include "DictionaryLimited.h"

template<Bits::bit_count bits> 
class DictionaryLimited1024 : public DictionaryLimited<bits>
{
public:
	DictionaryLimited1024():DictionaryLimited<bits>(1024) {};
	virtual ~DictionaryLimited1024() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionaryLimited1024>(argc, argv);
}