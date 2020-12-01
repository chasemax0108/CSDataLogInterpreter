#include "Relation.h"

#include <iterator>
#include <vector>
#include <sstream>
#include <iostream>

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

Tuple Relation::getTuple(int index)
{
	set<Tuple>::iterator iter;
	iter = allTuples.begin();
	for (int i = 0; i < index; i++) {
		iter++;
	}
	return *iter;
}

string Relation::getHeaderAt(int index) {
	return head.getNameAt(index);
}

void Relation::updateHeader(int index, string newName) {
	head.updateName(index, newName);
}

string Relation::toString() {
	stringstream output;
	set<Tuple>::iterator iter;
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		if (iter->getSize() > 0) {
			output << "  ";
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

int Relation::headerSize() {
	return head.getSize();
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
	for (unsigned int i = 0; i < indices.size(); i++) {
		newIndices.push_back(head.getNameAt(indices.at(i)));
	}
	Header newHead(newIndices);
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		vector<string> copiedTupleValues;
		for (unsigned int i = 0; i < indices.size(); i++) {
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

Relation Relation::crossProduct(Relation cross) {
	vector<string> newHead;
	set<Tuple> newTuples;
	set<Tuple>::iterator iter;
	for (int i = 0; i < head.getSize(); i++) {
		newHead.push_back(head.getNameAt(i));
	}
	for (int i = 0; i < cross.headerSize(); i++) {
		newHead.push_back(cross.getHeaderAt(i));
	}
	for (iter = allTuples.begin(); iter != allTuples.end(); iter++) {
		for (int i = 0; i < cross.size(); i++) {
			vector<string> newTupleValues;
			for (int k = 0; k < iter->getSize(); k++) {
				newTupleValues.push_back(iter->getParamAt(k));
			}
			for (int j = 0; j < cross.getTuple(i).getSize(); j++) {
				newTupleValues.push_back(cross.getTuple(i).getParamAt(j));
			}
			Tuple newTuple(newTupleValues);
			newTuples.insert(newTuple);
		}
	}
	return Relation(newHead, newTuples);
}

Relation Relation::naturalJoin(Relation &join) {

	// NEW CODE
	vector<string> newHead;
	vector<int> equalHeads;
	vector<bool> joinHeadMap;
	int firstHeadSize;
	int secondHeadSize;
	for (int i = 0; i < head.getSize(); i++) {
		newHead.push_back(head.getNameAt(i));
	}
	for (int i = 0; i < join.headerSize(); i++) {
		bool addme = true;
		for (unsigned int j = 0; j < newHead.size(); j++) {
			if (newHead.at(j) == join.getHeaderAt(i)) {
				equalHeads.push_back(j);
				equalHeads.push_back(i);
				addme = false;
			}
		}
		if (addme) {
			newHead.push_back(join.getHeaderAt(i));
			joinHeadMap.push_back(true);
		}
		else {
			joinHeadMap.push_back(false);
		}
	}
	firstHeadSize = this->headerSize();
	secondHeadSize = join.headerSize();

	Relation finalRelation(newHead);

	set<Tuple>::iterator iter1;
	set<Tuple>::iterator iter2;
	for (iter1 = this->allTuples.begin(); iter1 != allTuples.end(); iter1++) {
		for (iter2 = join.allTuples.begin(); iter2 != join.allTuples.end(); iter2++) {
			bool addme = true;
			for (unsigned int k = 0; k < equalHeads.size(); k += 2) {
				if (iter1->getParamAt(equalHeads.at(k)) != iter2->getParamAt(equalHeads.at(k + 1))) {
					addme = false;
				}
			}
			if (addme) {
				vector<string> newTupleValues;
				for (int k = 0; k < firstHeadSize; k++) {
					newTupleValues.push_back(iter1->getParamAt(k));
				}
				for (int k = 0; k < secondHeadSize; k++) {
					if (joinHeadMap.at(k)) newTupleValues.push_back(iter2->getParamAt(k));
				}
				finalRelation.addTuple(newTupleValues);
			}
		}
	}
	
	return finalRelation;
}

Relation Relation::unionRelations(Relation &u) {
	vector<string> newHead;
	set<Tuple> newTuples;
	set<Tuple>::iterator iter1;
	set<Tuple>::iterator iter2;
	for (int i = 0; i < this->head.getSize(); i++) {
		newHead.push_back(this->head.getNameAt(i));
	}
	for (iter1 = this->allTuples.begin(); iter1 != this->allTuples.end(); iter1++) {
		newTuples.insert(*iter1);
	}
	for (iter2 = u.allTuples.begin(); iter2 != u.allTuples.end(); iter2++) {
		pair<set<Tuple>::iterator, bool> results = newTuples.insert(*iter2);
		if (results.second) {
			cout << "  ";
			cout << head.getNameAt(0) << "=" << results.first->getParamAt(0);
			for (int i = 1; i < results.first->getSize(); i++) {
				cout << ", " << head.getNameAt(i) << "=" << results.first->getParamAt(i);
			}
			cout << endl;
		}
	}
	return Relation(newHead, newTuples);
}
