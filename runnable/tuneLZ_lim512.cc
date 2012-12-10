#include "tuneLZ.h"
#include "DictionarySized.h"

template<Bits::bit_count bits> 
class DictionarySized512 : public DictionarySized<bits>
{
public:
	DictionarySized512():DictionarySized<bits>(512) {};
	virtual ~DictionarySized512() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionarySized512>(argc, argv);
}