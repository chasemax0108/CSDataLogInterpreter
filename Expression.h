#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "Parameter.h"
#include "TokenType.h"

class Expression : public Parameter {
private:
	Parameter* param1;
	Parameter* param2;
	TokenType oper;
public:
	Expression() {}
	~Expression() {
		delete param1;
		delete param2;
	}
	Expression(Parameter* p1, Parameter* p2, TokenType o);
	virtual std::string toString();
	
	void setParam1(Parameter* p) {
		param1 = p;
	}
	Parameter* getParam1() {
		return param1;
	}
	void setParam2(Parameter* p) {
		param2 = p;
	}
	Parameter* getParam2() {
		return param2;
	}
	void setOperator(TokenType o) {
		oper = o;
	}
	TokenType getOperator() {
		return oper;
	}

};

#endif