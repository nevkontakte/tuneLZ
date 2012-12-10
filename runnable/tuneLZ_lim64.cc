#include "tuneLZ.h"
#include "DictionaryLimited.h"

template<Bits::bit_count bits> 
class DictionaryLimited64 : public DictionaryLimited<bits>
{
public:
	DictionaryLimited64():DictionaryLimited<bits>(64) {};
	virtual ~DictionaryLimited64() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionaryLimited64>(argc, argv);
}