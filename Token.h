#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "TokenType.h"

class Token {

private:
	TokenType type;
	std::string value;
	int line;

public:
	Token() {
		type = COMMA;
		value = "";
		line = 0;
	}

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
