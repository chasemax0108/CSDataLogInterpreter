#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Token.h"
#include "ParserDataStructures.h"

class Parser {
private:
	void ParseParameter(Predicate* parentPred, Parameter* p, Expression* e);
	void ParseOperator(Expression* e);
	void ParseExpression(Expression* parentExp);
	void ParseStringList(Predicate* p);
	void ParseIDList(Predicate* p);
	void ParseParameterList(Predicate* p);
	void ParsePredicate(Rule* r, Predicate* p);
	void ParsePredicateList(Rule* r);
	void ParseHeadPredicate(Rule* r);
	void ParseScheme(DataLogProgram* p);
	void ParseFact(DataLogProgram* p);
	void ParseRule(DataLogProgram* p);
	void ParseQuery(DataLogProgram* p);
	void ParseSchemeList(DataLogProgram* p);
	void ParseFactList(DataLogProgram* p);
	void ParseRuleList(DataLogProgram* p);
	void ParseQueryList(DataLogProgram* p);
	void ParseDataLogProgram(DataLogProgram* p);
	std::vector<Token> workingTokens;
	int currentToken;
public:
	Parser() {}
	void Parse(std::vector<Token> &inputTokens, DataLogProgram* program);
};

#endif // !PARSER_H

