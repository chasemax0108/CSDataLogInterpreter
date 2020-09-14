#include <iostream>
#include <cctype>

#include "Lexer.h"

using namespace std;

vector<Token> Lexer::Run(string input) {
	vector<Token> allTokens;
	int line = 1;
	int inputRead = 0;
	int maxRead, maxNewLines;
	Automaton* maxMachine;
	while (true) {
		//Reset Variables
		maxRead = 0;
		maxNewLines = 0;
		maxMachine = allMachines[0];

		//Eat up whitespace
 		while (input.length() != 0) {
			if (!isspace(input[0])) break;
			else if (input[0] == '\n') line++;
			input.erase(0, 1);
		}

		//Check for EOF
		if (input.empty()) {
			Token EOFToken(ENDOFFILE, "", line);
			allTokens.push_back(EOFToken);
			break;
		}

		// Cycle through all machines
		for (unsigned int i = 0; i < allMachines.size(); i++) {
			inputRead = allMachines[i]->Read(input);
			if (inputRead > maxRead) {
				maxRead = inputRead;
				maxMachine = allMachines[i];
				maxNewLines = allMachines[i]->NewLinesRead();
			}
		}

		// Create the appropriate token
		if (maxRead > 0) {
			allTokens.push_back(maxMachine->CreateToken(input, line));
		}
		else {
			maxRead = 1;
			string firstChar = string(1, input[0]);
			Token errorToken(UNDEFINED, firstChar, line);
			allTokens.push_back(errorToken);
		}

		// Erase characters off of the input and update the current line
		input.erase(0, maxRead);
		line += maxNewLines;
	}
	return allTokens;
}
