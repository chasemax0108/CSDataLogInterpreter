#include "Rule.h"
#include "Token.h"

using namespace std;

std::string Rule::toString() {
	string output;
	output += headPred->toString();
	output += " ";
	output += MultiSymbolTokenValueMap.at(COLON_DASH);
	output += " ";
	output += allPreds[0]->toString();
	for (unsigned int i = 1; i < allPreds.size(); i++) {
		output += SymbolTokenValueMap.at(COMMA);
		output += allPreds[i]->toString();
	}
	output += SymbolTokenValueMap.at(PERIOD);
	return output;
}
