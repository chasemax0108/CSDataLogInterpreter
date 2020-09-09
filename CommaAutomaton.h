#ifndef COMMAAUTOMATON_H
#define COMMAAUTOMATON_H

#include "Automaton.h"
class CommaAutomaton : public Automaton {
private:
	const char KEYWORD = ':';

public:
	CommaAutomaton() : Automaton(COMMA) {}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
