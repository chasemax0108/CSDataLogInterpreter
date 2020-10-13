#include "Header.h"

using namespace std;

Header::Header(vector<string> n) {
	allNames = n;
}

int Header::getSize() {
	return allNames.size();
}

string Header::getNameAt(int index) {
	return allNames.at(index);
}
