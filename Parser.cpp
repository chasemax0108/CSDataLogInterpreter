#include "Parser.h"
#include "TokenType.h"
#include <iostream>

using namespace std;

// IF IT HITS A TERMINAL, ADVANCE THE CURRENT TOKEN

void Parser::Parse(vector<Token> &inputTokens) {
	workingTokens = inputTokens;
	currentToken = 0;
	ParseIDList();
	return;
}

void Parser::ParseParameter() {
	TokenType current = workingTokens[currentToken].getType();
	if (current == STRING || current == ID) { // FIRST set
		currentToken++;
		return;
	}
	else if (current == LEFT_PAREN) {
		ParseExpression();
	}
	else {
		throw workingTokens[currentToken];
	}
}

void Parser::ParseOperator() {
	TokenType current = workingTokens[currentToken].getType();
	if (current == ADD || current == MULTIPLY) {
		currentToken++;
		return;
	}
	else {
		throw workingTokens[currentToken];
	}
}

void Parser::ParseExpression() {
	if (workingTokens[currentToken].getType() == LEFT_PAREN) { // FIRST Set
		currentToken++;
		ParseParameter();
		ParseOperator();
		ParseParameter();
		if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
			currentToken++;
			return;
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseStringList() {
	if (workingTokens[currentToken].getType() == COMMA) { // FIRST set
		currentToken++;
		if (workingTokens[currentToken].getType() == STRING) {
			currentToken++;
			ParseStringList();
			return;
		}
	}
	else if (workingTokens[currentToken].getType() == RIGHT_PAREN) { // FOLLOW set
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseIDList() {
	if (workingTokens[currentToken].getType() == COMMA) { // FIRST set
		currentToken++;
		if (workingTokens[currentToken].getType() == ID) {
			currentToken++;
			ParseIDList();
			return;
		}
	}
	else if (workingTokens[currentToken].getType() == RIGHT_PAREN) { // FOLLOW set
		return;
	}
	throw workingTokens[currentToken];
}