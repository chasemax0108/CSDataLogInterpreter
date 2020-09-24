#include "PlainParameter.h"

using namespace std;

PlainParameter::PlainParameter(string v) {
	value = v;
}

string PlainParameter::toString() {
	return value;
}