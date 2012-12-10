#include "tuneLZ.h"
#include "DictionaryLimited.h"

template<Bits::bit_count bits> 
class DictionaryLimited256 : public DictionaryLimited<bits>
{
public:
	DictionaryLimited256():DictionaryLimited<bits>(256) {};
	virtual ~DictionaryLimited256() {};
};

int main(int argc, char* argv[]) {
	return mainTemplate<DictionaryLimited256>(argc, argv);
}