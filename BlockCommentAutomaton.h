#ifndef BLOCKCOMMENTAUTOMATON_H
#define BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"
#include "TokenType.h"

class BlockCommentAutomaton : public Automaton {
public:
	BlockCommentAutomaton() : Automaton(COMMENT) {}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
