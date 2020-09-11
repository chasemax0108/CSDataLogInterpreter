#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"
#include "TokenType.h"

class StringAutomaton : public Automaton {

public:
	StringAutomaton() : Automaton(STRING) {}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
