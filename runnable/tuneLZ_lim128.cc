#include "tuneLZ.h"
#include "DictionaryLimited.h"

template<Bits::bit_count bits> 
class DictionaryLimited128 : public DictionaryLimited<bits>
{
public:
	DictionaryLimited128():DictionaryLimited<bits>(128) {};
	virtual ~DictionaryLimited128() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionaryLimited128>(argc, argv);
}