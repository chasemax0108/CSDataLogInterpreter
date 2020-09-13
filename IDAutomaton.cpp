#include "IDAutomaton.h"

#include <string>
#include <cctype>
#include <map>

using namespace std;

int IDAutomaton::Read(const std::string& input) {
	if (input.length() != 0) {
		
		// First, we need to test for a keyword
		// We need to see if it is in the MultiSymbolTokenValueMap map
		// Might not need this code but it's here if you need it
		/*
		string testKeyword = "";
		string keyWord = "";
		char peek;
		map<TokenType, string>::const_iterator it = MultiSymbolTokenValueMap.begin();
		for (it = MultiSymbolTokenValueMap.begin(); it != MultiSymbolTokenValueMap.end(); it++) {
			keyWord = it->second;
			testKeyword = input.substr(0, keyWord.length());
			peek = input[keyWord.length()];
			if (testKeyword.compare(it->second) == 0) {
				if (isspace(peek) || peek == '/n') return 0;
			}
		}
		*/

		// Now we can run our state machine

		int state = 0;
		for (int i = 0; i < input.length(); i++) {
			switch (state) {
			case 0:
				if (isalpha(input[i])) state = 1;
				else return 0;
				break;
			case 1:
				if (isspace(input[i]) || input[i] == '\n') return i;
				else if (!isalnum(input[i])) return 0;
				break;
			}
		}
	}
	return 0;
}

Token IDAutomaton::CreateToken(std::string input, int lineNumber) {
	string value = "";
	int state = 0;
	for (int i = 0; i < input.length(); i++) {
		if (isspace(input[i]) || input[i] == '\n') break;
		value += input[i];
	}
	return Token(type, value, lineNumber);
}
