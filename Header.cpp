#include "Header.h"

using namespace std;

Header::Header(vector<string> n) {
	allNames = n;
}

int Header::getSize() {
	return allNames.size();
}

void Header::updateName(int index, string name) {
	allNames.at(index) = name;
}

string Header::getNameAt(int index) {
	return allNames.at(index);
}
