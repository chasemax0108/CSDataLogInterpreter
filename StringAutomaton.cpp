#include "StringAutomaton.h"

using namespace std;

int StringAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		int state = 0;
		for (int i = 0; i < input.length(); i++) {
			switch (state) {
			case 0: //Automaton init
				if (input[i] == '\'') state = 1;
				else return 0;
				break;
			case 1: //Automaton has found opening quotation
				if (input[i] == '\'') {
					if (i == (input.length() - 1)) return (i + 1); //Case if the string ends with the end of the input
					state = 2;
				}
				break;
			case 2: //Automaton has found a potential closing quotation
				if (input[i] == '\'') state = 1;
				else return (i);
				break;
			}
		}
	}
	return 0;
}

Token StringAutomaton::CreateToken(std::string input, int lineNumber) {
	int state = 0;
	string value = "";
	bool finished = false;
	for (int i = 0; i < input.length(); i++) {
		if (finished) break;
		switch (state) {
		case 0:
			value += input[i];
			state = 1;
			break;
		case 1:
			value += input[i];
			if (input[i] == '\'') {
				if (i == (input.length() - 1)) finished = true; //Case if the string ends with the end of the input
				state = 2;
			}
			break;
		case 2: //Automaton has found a potential closing quotation
			if (input[i] == '\'') {
				value += input[i];
				state = 1;
			}
			else finished = true;
			break;
		}
	}
	return Token(type, value, lineNumber);
}
