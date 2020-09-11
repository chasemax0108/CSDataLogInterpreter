#ifndef SSAUTOMATON_H
#define SSAUTOMATON_H

#include "Automaton.h"
#include "TokenType.h"

class SSAutomaton : public Automaton {
private:
	char keySymbol;

public:
	SSAutomaton(TokenType t) : Automaton(t) {
		keySymbol = SymbolTokenValueMap.at(t);
	}
	virtual int Read(const std::string& input);
	virtual Token CreateToken(std::string input, int lineNumber);
};

#endif
