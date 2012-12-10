#include "tuneLZ.h"
#include "DictionarySized.h"

template<Bits::bit_count bits> 
class DictionarySized128 : public DictionarySized<bits>
{
public:
	DictionarySized128():DictionarySized<bits>(128) {};
	virtual ~DictionarySized128() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionarySized128>(argc, argv);
}