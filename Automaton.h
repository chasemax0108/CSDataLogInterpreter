#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>

class Automaton {

public:
	Automaton() {}

	virtual int Read(const std::string& input) = 0;

};

#endif
