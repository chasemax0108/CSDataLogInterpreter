#ifndef TESTAUTOMATON_H
#define TESTAUTOMATON_H

#include <string>
#include "Automaton.h"
#include "TokenType.h"

class TestAutomaton : public Automaton{

private:
	const std::string KEYWORD = "Test";

public:
	TestAutomaton(TokenType t) : Automaton(t) {}
	virtual int Read(const std::string& input);
};

#endif

