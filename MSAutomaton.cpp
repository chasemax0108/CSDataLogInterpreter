#include "MSAutomaton.h"

using namespace std;

int MSAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		bool isMatch = true;
		for (unsigned int i = 0; i < keyString.length(); i++) {
			if (input[i] != keyString[i]) {
				isMatch = false;
				break;
			}
		}
		if (isMatch) return keyString.length();
	}
	return 0;
}

Token MSAutomaton::CreateToken(std::string input, int lineNumber) {
	return Token(type, keyString, lineNumber);
}
