#include "Predicate.h"

using namespace std;

string Predicate::toString() {
	string output;
	output += id;
	output += "(";
	output += this->paramAt(0)->toString();
	for (int i = 1; i < this->paramListSize(); i++) {
		output += ",";
		output += this->paramAt(i)->toString();
	}
	output += ")";
	return output;
}

Predicate::~Predicate() {
	for (unsigned int i = 0; i < allParams.size(); i++) {
		delete allParams[i];
	}
}