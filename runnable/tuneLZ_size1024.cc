#include "tuneLZ.h"
#include "DictionarySized.h"

template<Bits::bit_count bits> 
class DictionarySized1024 : public DictionarySized<bits>
{
public:
	DictionarySized1024():DictionarySized<bits>(1024) {};
	virtual ~DictionarySized1024() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionarySized1024>(argc, argv);
}