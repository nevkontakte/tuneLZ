#include <gtest/gtest.h>
#include <sstream>
#include "Encoder.h"
#include "Decoder.h"
#include "Dictionary.h"
#include "DictionaryLimited.h"

const std::string sheogorath = std::string() +
	"Wonderful! Time for a celebration... Cheese for everyone! Wait, scratch that. Cheese for no one. That can be just as much of a celebration, if you don't like cheese, true? You've run a maze like a good little rat. But no cheese for you yet. Well, maybe a little.\n" +
	"I'm so happy I could just tear out your intestines and strangle you with them!\n" +
	"Jyggalag! He is the Prince of Order. Or biscuits...no, no, Order! And not in a good way. Bleak. Colorless. Dead. Boring, boring, BORING! And not a fan of my work, I can tell you. Hates it, hates me. You've seen his knights. Not the warm and cuddly sort.\n" +
	"Jyggalag's forces are gathering in the Fringe...And I HATE IT when people gather forces in my Fringe!\n" +
	"I once dug a pit and filled it with clouds....or was it clowns.... it doesn't matter, it didn't slow him down. But it really began to smell! Must have been clowns. Clouds don't smell, they taste of butter. And tears.\n" +
	"... and OUT comes the intestines! And I skip rope with them!\n" +
	"I'm a little busy here! I'm trying to decide what to have for dinner. Oh, how I love to eat. One of my favorite things to do. Go talk to Haskill, he's got more brains than a brain pie! Ooh...brain pie... perfect! ...Care to donate? ";

template<Bits::bit_count bits, template<Bits::bit_count> class D> class SheogorathCoder {
	public:
		void run(D<bits>& d1, D<bits>& d2) {
			std::ostringstream compressed;

			// Compress
			{
				std::istringstream source(sheogorath);

				Encoder<bits, D> encoder(d1);
				encoder.encode(source, compressed);
			}

			std::ostringstream uncompressed;

			// Uncompress
			{
				std::istringstream source(compressed.str());

				Decoder<bits, D> decoder(d2);
				decoder.decode(source, uncompressed);
			}

			ASSERT_EQ(sheogorath, uncompressed.str());
		}
};

TEST(Sheogorath, Dictionary) {
	Dictionary<8> d1,d2;
	SheogorathCoder<8, Dictionary> coder;
	coder.run(d1,d2);
}

TEST(Sheogorath, DictionaryLimited) {
	DictionaryLimited<8> d1(24),d2(24);
	SheogorathCoder<8, DictionaryLimited> coder;
	coder.run(d1,d2);
}
