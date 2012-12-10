#include "tuneLZ.h"
#include "DictionarySized.h"

template<Bits::bit_count bits> 
class DictionarySized64 : public DictionarySized<bits>
{
public:
	DictionarySized64():DictionarySized<bits>(64) {};
	virtual ~DictionarySized64() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionarySized64>(argc, argv);
}