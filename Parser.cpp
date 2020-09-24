#include "Parser.h"
#include "TokenType.h"
#include <iostream>

using namespace std;

// IF IT HITS A TERMINAL, ADVANCE THE CURRENT TOKEN

void Parser::Parse(vector<Token> &inputTokens) {
	workingTokens = inputTokens;
	currentToken = 0;
	ParseDataLogProgram();
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

void Parser::ParseParameterList() {
	if (workingTokens[currentToken].getType() == COMMA) { // FIRST
		currentToken++;
		ParseParameter();
		ParseParameterList();
		return;
	}
	else if (workingTokens[currentToken].getType() == RIGHT_PAREN) { // FOLLOW set
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParsePredicate() {
	if (workingTokens[currentToken].getType() == ID) {
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			ParseParameter();
			ParseParameterList();
			if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
				currentToken++;
				return;
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParsePredicateList() {
	if (workingTokens[currentToken].getType() == COMMA) { // First
		currentToken++;
		ParsePredicate();
		ParsePredicateList();
		return;
	}
	else if (workingTokens[currentToken].getType() == PERIOD) { // Follow
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseHeadPredicate() {
	if (workingTokens[currentToken].getType() == ID) {
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			if (workingTokens[currentToken].getType() == ID) {
				currentToken++;
				ParseIDList();
				if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
					currentToken++;
					return;
				}
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseScheme() {
	if (workingTokens[currentToken].getType() == ID) {
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			if (workingTokens[currentToken].getType() == ID) {
				currentToken++;
				ParseIDList();
				if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
					currentToken++;
					return;
				}
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseFact() {
	if (workingTokens[currentToken].getType() == ID) {
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			if (workingTokens[currentToken].getType() == STRING) {
				currentToken++;
				ParseStringList();
				if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
					currentToken++;
					if (workingTokens[currentToken].getType() == PERIOD) {
						currentToken++;
						return;
					}
				}
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseRule() {
	if (workingTokens[currentToken].getType() == ID) {
		ParseHeadPredicate();
		if (workingTokens[currentToken].getType() == COLON_DASH) {
			currentToken++;
			ParsePredicate();
			ParsePredicateList();
			if (workingTokens[currentToken].getType() == PERIOD) {
				currentToken++;
				return;
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseQuery() {
	if (workingTokens[currentToken].getType() == ID) {
		ParsePredicate();
		if (workingTokens[currentToken].getType() == Q_MARK) {
			currentToken++;
			return;
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseSchemeList() {
	if (workingTokens[currentToken].getType() == ID) {
		ParseScheme();
		ParseSchemeList();
		return;
	}
	else if (workingTokens[currentToken].getType() == FACTS) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseFactList() {
	if (workingTokens[currentToken].getType() == ID) {
		ParseFact();
		ParseFactList();
		return;
	}
	else if (workingTokens[currentToken].getType() == RULES) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseRuleList() {
	if (workingTokens[currentToken].getType() == ID) {
		ParseRule();
		ParseRuleList();
		return;
	}
	else if (workingTokens[currentToken].getType() == QUERIES) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseQueryList() {
	if (workingTokens[currentToken].getType() == ID) {
		ParseQuery();
		ParseQueryList();
		return;
	}
	else if (workingTokens[currentToken].getType() == ENDOFFILE) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseDataLogProgram() {
	if (workingTokens[currentToken].getType() == SCHEMES) {
		currentToken++;
		if (workingTokens[currentToken].getType() == COLON) {
			currentToken++;
			ParseScheme();
			ParseSchemeList();
			if (workingTokens[currentToken].getType() == FACTS) {
				currentToken++;
				if (workingTokens[currentToken].getType() == COLON) {
					currentToken++;
					ParseFactList();
					if (workingTokens[currentToken].getType() == RULES) {
						currentToken++;
						if (workingTokens[currentToken].getType() == COLON) {
							currentToken++;
							ParseRuleList();
							if (workingTokens[currentToken].getType() == QUERIES) {
								currentToken++;
								if (workingTokens[currentToken].getType() == COLON) {
									currentToken++;
									ParseQuery();
									ParseQueryList();
									if (workingTokens[currentToken].getType() == ENDOFFILE) {
										return;
									}
								}
							}
						}

					}
				}
			}
		}
	}
	throw workingTokens[currentToken];
}