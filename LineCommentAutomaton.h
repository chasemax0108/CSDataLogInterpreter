#ifndef LINECOMMENTAUTOMATON_H
#define LINECOMMENTAUTOMATON_H

#include "Automaton.h"
#include "TokenType.h"

class LineCommentAutomaton : public Automaton {
public:
	LineCommentAutomaton() : Automaton(COMMENT) {}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
