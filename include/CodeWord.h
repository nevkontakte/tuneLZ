#ifndef CODEWORD_H__
#define CODEWORD_H__

#include "Symbol.h"
#include <vector>


class CodeWord
{
public:
	typedef std::vector<CodeWord>::difference_type Index;
	static const CodeWord EMPTY;

private:
	Symbol symbol;
	Index index;

public:
	CodeWord();
	CodeWord(const Symbol& symbol, Index index);
	virtual ~CodeWord();

	bool operator==(const CodeWord& other) const;
	const Symbol& getSymbol() const;
	Index getIndex() const;

private:
	CodeWord(Index index);
};

#endif /* end of include guard: CODEWORD_H__ */