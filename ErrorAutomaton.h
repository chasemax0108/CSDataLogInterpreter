#ifndef ERRORAUTOMATON_H
#define ERRORAUTOMATON_H

#include "Automaton.h"
#include "TokenType.h"

class ErrorAutomaton : public Automaton {

public:
	ErrorAutomaton() : Automaton(STRING) {}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
