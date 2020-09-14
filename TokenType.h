#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <map>
#include <string>

enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
		MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOFFILE};

const std::map<TokenType, char> SymbolTokenValueMap = { {COMMA, ','}, {PERIOD, '.'}, {Q_MARK, '?'}, {LEFT_PAREN, '('},
	{RIGHT_PAREN, ')'}, {COLON, ':'}, {MULTIPLY, '*'}, {ADD, '+'} };

const std::map<TokenType, std::string> MultiSymbolTokenValueMap = { {COLON_DASH, ":-"}, {SCHEMES, "Schemes"},
	{FACTS, "Facts"}, {RULES, "Rules"}, {QUERIES, "Queries"} };

const std::string TokenStrings[18] = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
	"MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT", "UNDEFINED", "EOF" };

#endif