#include "SSAutomaton.h"

using namespace std;

int SSAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		if (keySymbol == input[0]) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

Token SSAutomaton::CreateToken(std::string input, int lineNumber) {
	string value(1, keySymbol);
	return Token(type, value, lineNumber);
}
