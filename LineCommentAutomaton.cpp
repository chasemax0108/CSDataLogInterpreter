#include "LineCommentAutomaton.h"

#include <string>
using namespace std;

int LineCommentAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		int state = 0;
		for (unsigned int i = 0; i < input.length(); i++) {
			switch (state) {
			case 0:
				if (input[i] != '#') return 0;
				state = 1;
				break;
			case 1:
				if (input[i] == '\n') return i;
				break;
			}
		}
	}
	return 0;
}

Token LineCommentAutomaton::CreateToken(std::string input, int lineNumber) {
	string value = "";
	for (unsigned int i = 0; i < input.length(); i++) {
		if (input[i] == '\n') break;
		value += input[i];
	}
	return Token(type, value, lineNumber);
}
