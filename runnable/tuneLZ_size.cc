#include "tuneLZ.h"
#include "DictionarySized.h"
#include <sstream>

unsigned int DictionarySizedStubLength = 256;

template<Bits::bit_count bits> 
class DictionarySizedStub : public DictionarySized<bits>
{
public:
	DictionarySizedStub():DictionarySized<bits>(DictionarySizedStubLength) {};
	virtual ~DictionarySizedStub() {};
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
				DictionarySizedStubLength = length;
			}
		}
	}
	return mainTemplate<DictionarySizedStub>(argc, argv);
}