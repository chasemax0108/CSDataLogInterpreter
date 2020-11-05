#ifndef RELATION_H
#define RELATION_H

#include <set>

#include "Tuple.h"
#include "Header.h"

class Relation {
private:
	std::set<Tuple> allTuples;
	Header head;
public:
	Relation(Header h, std::set<Tuple> t);
	Relation(Header h);
	void addTuple(Tuple t);
	Tuple getTuple(int index);
	std::string getHeaderAt(int index);
	void updateHeader(int index, std::string newName);
	std::string toString();
	int size();
	int headerSize();
	Relation select(int index, std::string value);
	Relation select(int index1, int index2);
	Relation project(std::vector<int> indices);
	Relation rename(std::vector<std::string> names);
	Relation crossProduct(Relation cross);
	Relation naturalJoin(Relation join);
};

#endif // !RELATION_H
