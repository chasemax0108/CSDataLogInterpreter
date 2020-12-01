#include "Database.h"

using namespace std;

void Database::addRelation(Relation r, string name) {
	allRelations.insert(pair<string, Relation>(name, r));
}

Relation* Database::getRelation(std::string name) {
	return &(allRelations.find(name)->second);
}

Relation* Database::getRelationByIndex(int index) {
	map<string, Relation>::iterator iter = allRelations.begin();
	for (int i = 0; i < index; i++) {
		iter++;
	}
	return &(iter->second);
}
