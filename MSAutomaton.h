#ifndef MSAUTOMATON_H
#define MSAUTOMATON_H

// MS stands for "multi-symbol"

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