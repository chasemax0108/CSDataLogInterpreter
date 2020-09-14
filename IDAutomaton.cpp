#include "IDAutomaton.h"

#include <string>
#include <cctype>

using namespace std;

int IDAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		int state = 0;
		for (unsigned int i = 0; i < input.length(); i++) {
			switch (state) {
			case 0:
				if (isalpha(input[i])) state = 1;
				else return 0;
				break;
			case 1:
				if (!isalnum(input[i])) return i;
				else if (i == (input.length() - 1)) return i + 1; //This ID is at the end of the file, return it
				break;
			}
		}
	}
	return 0;
}

Token IDAutomaton::CreateToken(std::string input, int lineNumber) {
	string value = "";
	for (unsigned int i = 0; i < input.length(); i++) {
		if (!isalnum(input[i])) break;
		value += input[i];
	}
	return Token(type, value, lineNumber);
}
