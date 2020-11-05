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

Relation Relation::naturalJoin(Relation join) {
	// Rename the relations to prepare for the cross product and store similar relations in pairs
	vector<int> equalHeaders;
	vector<int> newHeaders;
	for (int i = 0; i < head.getSize(); i++) {
		for (int j = 0; j < join.headerSize(); j++) {
			if (head.getNameAt(i) == join.getHeaderAt(j)) {
				join.updateHeader(j, join.getHeaderAt(j) + "'");
				equalHeaders.push_back(i);
				equalHeaders.push_back(j + head.getSize());
				break;
			}
		}
	}

	// Run the cross product
	Relation joinedRelation = this->crossProduct(join);
	// Select out the equal columns
	for (int i = 0; i < equalHeaders.size(); i += 2) {
		joinedRelation = joinedRelation.select(equalHeaders.at(i), equalHeaders.at(i + 1));
	}
	// Project the new relation without duplicate columns
	for (int i = 0; i < joinedRelation.headerSize(); i++) {
		for (int j = 0; j < equalHeaders.size(); j += 2) {
			if (equalHeaders.at(j + 1) != i) {
				newHeaders.push_back(i);
			}
		}
	}
	joinedRelation = joinedRelation.project(newHeaders);

	return joinedRelation;
}
