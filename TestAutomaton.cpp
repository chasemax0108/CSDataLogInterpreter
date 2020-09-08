#include "TestAutomaton.h"

#include <string>

using namespace std;

int TestAutomaton::Read(const std::string& input) {
	if (input.compare(KEYWORD) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}