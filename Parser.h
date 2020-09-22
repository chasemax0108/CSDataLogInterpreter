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
	void ParseParameterList();
	void ParsePredicate();
	void ParsePredicateList();
	void ParseHeadPredicate();
	void ParseScheme();
	void ParseFact();
	void ParseRule();
	void ParseQuery();
	void ParseSchemeList();
	void ParseFactList();
	void ParseRuleList();
	void ParseQueryList();
	void ParseDataLogProgram();
	std::vector<Token> workingTokens;
	int currentToken;
public:
	Parser() {}
	void Parse(std::vector<Token> &inputTokens);
};

#endif // !PARSER_H

