#include "BlockCommentAutomaton.h"

#include <string>
using namespace std;

int BlockCommentAutomaton::Read(const std::string& input) {
	newLines = 0;
	if (input.length() != 0) {
		int state = 0;
		for (unsigned int i = 0; i < input.length(); i++) {
			switch (state) {
			case 0:
				if (input[i] == '#') state = 1;
				else return 0;
				break;
			case 1:
				if (input[i] == '|') state = 2;
				else return 0;
				break;
			case 2:
				if (input[i] == '|') state = 3;
				else if (input[i] == '\n') newLines++;
				break;
			case 3:
				if (input[i] == '#') return (i + 1);
				else if (input[i] != '|') state = 2;
				if (input[i] == '\n') newLines++;
				break;
			}
		}
	}
	return 0;
}

Token BlockCommentAutomaton::CreateToken(std::string input, int lineNumber) {
	string value = "";
	int state = 0;
	for (unsigned int i = 0; i < input.length(); i++) {
		if (state == 4) break;
		value += input[i];
		switch (state) {
		case 0:
			state = 1;
			break;
		case 1:
			state = 2;
			break;
		case 2:
			if (input[i] == '|') state = 3;
			break;
		case 3:
			if (input[i] == '#') state = 4;
			else if (input[i] != '|') state = 2;
			break;
		}
	}
	return Token(type, value, lineNumber);
}
