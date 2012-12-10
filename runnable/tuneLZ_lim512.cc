#include "tuneLZ.h"
#include "DictionaryLimited.h"

template<Bits::bit_count bits> 
class DictionaryLimited512 : public DictionaryLimited<bits>
{
public:
	DictionaryLimited512():DictionaryLimited<bits>(512) {};
	virtual ~DictionaryLimited512() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionaryLimited512>(argc, argv);
}