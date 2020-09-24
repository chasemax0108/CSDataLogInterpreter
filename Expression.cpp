#include "Expression.h"

using namespace std;

Expression::Expression(Parameter* p1, Parameter* p2, TokenType o) {
	param1 = p1;
	param2 = p2;
	oper = o;
}

string Expression::toString() {
	string output;
	string stringedOper(1, SymbolTokenValueMap.at(oper));
	output += "(";
	output += param1->toString();
	output += stringedOper;
	output += param2->toString();
	output += ")";
	return output;
}