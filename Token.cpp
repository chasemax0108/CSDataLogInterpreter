#include <string>

#include "Token.h"
#include "TokenType.h"

using namespace std;

string Token::stringedToken()
{
	string output = "";
	string stringedType = "";
	stringedType = TokenStrings[type];
	output = "(" + stringedType + ",\"" + value + "\"," + to_string(line) + ")";
	return output;
}
