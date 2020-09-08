#ifndef TESTAUTOMATON_H
#define TESTAUTOMATON_H

#include <string>
#include "Automaton.h"

class TestAutomaton : public Automaton{

private:
	const std::string KEYWORD = "Test";

public:
	virtual int Read(const std::string& input);
};

#endif

