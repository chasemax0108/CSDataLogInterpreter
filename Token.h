#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "TokenType.h"

class Token {

private:
	TokenType type;
	std::string value;
	int line;
	std::string tokenTypes[18] = {"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
	"MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT", "UNDEFINED", "ENDOFFILE"};

public:

	Token(TokenType t, std::string v, int l) {
		type = t;
		value = v;
		line = l;
	}

	void setType(TokenType t) {
		type = t;
	}

	void setValue(std::string v) {
		value = v;
	}

	void setLine(int l) {
		line = l;
	}

	TokenType getType() const {
		return type;
	}

	std::string getValue() const {
		return value;
	}

	int getLine() const {
		return line;
	}

	std::string stringedToken();
};
#endif
