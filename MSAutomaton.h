#ifndef MSAUTOMATON_H
#define MSAUTOMATON_H

// MS stands for "multi-symbol". This Automaton takes a string in its constructor and uses
// that in order to produce a recognition state.

#include "Automaton.h"
#include <string>

class MSAutomaton : public Automaton {
private:
	std::string keyString;

public:
	MSAutomaton(TokenType t) : Automaton(t) {
		keyString = MultiSymbolTokenValueMap.at(t);
	}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif