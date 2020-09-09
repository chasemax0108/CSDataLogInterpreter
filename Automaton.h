#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>

#include "Token.h"

class Automaton {
protected:
	int newLines = 0;
	TokenType type;

public:
	Automaton(TokenType type) { this->type = type; }

	virtual int Read(const std::string& input) = 0;

	virtual Token CreateToken(std::string input, int lineNumber) {
		return Token(type, input, lineNumber);
	}

	virtual int NewLinesRead() const {
		return newLines;
	}

};

#endif
