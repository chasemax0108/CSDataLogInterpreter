#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Token.h"

class Parser {
private:
	void ParseParameter();
	void ParseOperator();
	void ParseExpression();
	void ParseStringList();
	void ParseIDList();
	std::vector<Token> workingTokens;
	int currentToken;
public:
	Parser() {}
	void Parse(std::vector<Token> &inputTokens);
};

#endif // !PARSER_H

