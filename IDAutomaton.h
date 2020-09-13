#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include "Automaton.h"
#include "TokenType.h"

class IDAutomaton : public Automaton {
public:
	IDAutomaton() : Automaton(ID) {}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
