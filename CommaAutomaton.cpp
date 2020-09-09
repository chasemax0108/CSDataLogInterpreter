#include "CommaAutomaton.h"

using namespace std;

int CommaAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		if (KEYWORD == input[0]) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

Token CommaAutomaton::CreateToken(std::string input, int lineNumber) {
	string value(1, KEYWORD);
	return Token(type, value, lineNumber);
}
