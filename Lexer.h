#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

#include "Automaton.h"
#include "Token.h"

class Lexer {
private:
	std::vector<Automaton*> allMachines;
public:
	Lexer(std::vector<Automaton*> aM) {
		allMachines = aM;
	};
	std::vector<Token> Run(std::string);
};

#endif
