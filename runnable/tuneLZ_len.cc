#include "tuneLZ.h"
#include "DictionaryLimited.h"
#include <sstream>

unsigned int DictionaryLimitedStubLength = 8;

template<Bits::bit_count bits> 
class DictionaryLimitedStub : public DictionaryLimited<bits>
{
public:
	DictionaryLimitedStub():DictionaryLimited<bits>(DictionaryLimitedStubLength) {};
	virtual ~DictionaryLimitedStub() {};
};

int main(int argc, char* argv[]) {
	// Try to find max length
	for(int i = 1; i < argc; i++) {
		std::string arg1(argv[i]);

		if((arg1.size() > 2) && (arg1[0] == '-') && (arg1[1] == '-')) {
			std::istringstream num(arg1.substr(2));
			unsigned int length;
			num >> length;
			if(length > 0) {
				DictionaryLimitedStubLength = length;
			}
		}
	}
	return mainTemplate<DictionaryLimitedStub>(argc, argv);
}