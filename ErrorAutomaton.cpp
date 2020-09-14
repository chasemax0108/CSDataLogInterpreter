#include "ErrorAutomaton.h"

int ErrorAutomaton::Read(const std::string& input) {
	newLines = 0;
	if (!input.empty()) {
		int state = 0;
		for (unsigned int i = 0; i < input.length(); i++) {
			switch (state) {
			case 0:
				if (input[i] == '\'') state = 1;
				else if (input[i] == '#') state = 3;
				else state = 6;
				break;
			case 1: //Automaton has found opening quotation
				if (input[i] == '\'') {
					if (i == (input.length() - 1)) state = 6; //Case if the string ends with the end of the input
					state = 2;
				}
				break;
			case 2: //Automaton has found a potential closing quotation
				if (input[i] == '\'') state = 1;
				else state = 6;
				break;
			case 3:
				if (input[i] == '|') state = 4;
				else state = 6;
				break;
			case 4:
				if (input[i] == '|') state = 5;
				break;
			case 5:
				if (input[i] == '#') state = 6;
				else if (input[i] != '|') state = 4;
				break;
			}
			if (state == 6) return 0;
			if (input[i] == '\n') newLines++;
		}
	}
	// It has read through the whole input and it is faulty
	return input.length();
}

Token ErrorAutomaton::CreateToken(std::string input, int lineNumber) {
	return Token(UNDEFINED, input, lineNumber);
}
