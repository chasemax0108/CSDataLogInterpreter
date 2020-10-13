#include "Tuple.h"

using namespace std;

Tuple::Tuple(vector<string> p) {
	allValues = p;
}

string Tuple::getParamAt(int index) const {
	return allValues[index];
}

int Tuple::getSize() const {
	return allValues.size();
}

bool Tuple::operator<(const Tuple& other) const {
	for (unsigned int i = 0; i < allValues.size(); i++) {
		if (allValues.at(i) > other.getParamAt(i)) {
			return false;
		}
		else if (allValues.at(i) < other.getParamAt(i)) {
			return true;
		}
	}
	return false;
}
