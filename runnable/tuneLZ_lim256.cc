#include "tuneLZ.h"
#include "DictionarySized.h"

template<Bits::bit_count bits> 
class DictionarySized256 : public DictionarySized<bits>
{
public:
	DictionarySized256():DictionarySized<bits>(256) {};
	virtual ~DictionarySized256() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionarySized256>(argc, argv);
}