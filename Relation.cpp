#include "Relation.h"

#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

Relation::Relation(Header h, set<Tuple> t) {
	head = h;
	allTuples = t;
}

Relation::Relation(Header h) {
	head = h;
}

void Relation::addTuple(Tuple t) {
	allTuples.insert(t);
}

string Relation::getHeaderAt(int index) {
	return head.getNameAt(index);
}

string Relation::toString() {
	stringstream output;
	set<Tuple>::iterator iter;
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		output << "  ";
		if (iter->getSize() > 0) {
			output << head.getNameAt(0) << "=" << iter->getParamAt(0);
			for (int i = 1; i < iter->getSize(); i++) {
				output << ", " << head.getNameAt(i) << "=" << iter->getParamAt(i);
			}
			output << endl;
		}
	}
	return output.str();
}

int Relation::size() {
	return allTuples.size();
}

Relation Relation::select(int index, string value) {
	set<Tuple>::iterator iter;
	set<Tuple> returnTuples;
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		if (iter->getParamAt(index) == value) {
			returnTuples.insert(*iter);
		}
	}
	return Relation(head, returnTuples);
}

Relation Relation::select(int index1, int index2) {
	set<Tuple>::iterator iter;
	set<Tuple> returnTuples;
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		if (iter->getParamAt(index1) == iter->getParamAt(index2)) {
			returnTuples.insert(*iter);
		}
	}
	return Relation(head, returnTuples);
}


Relation Relation::project(std::vector<int> indices) {
	vector<string> newIndices;
	set<Tuple>::iterator iter;
	set<Tuple> newTuples;
	for (int i = 0; i < indices.size(); i++) {
		newIndices.push_back(head.getNameAt(indices.at(i)));
	}
	Header newHead(newIndices);
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		vector<string> copiedTupleValues;
		for (int i = 0; i < indices.size(); i++) {
			copiedTupleValues.push_back(iter->getParamAt(indices.at(i)));
		}
		Tuple copiedTuple(copiedTupleValues);
		newTuples.insert(copiedTuple);
	}
	return Relation(newHead, newTuples);
}

Relation Relation::rename(std::vector<std::string> names) {
	Header newHeader(names);
	return Relation(newHeader, allTuples);
}