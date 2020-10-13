#include "Database.h"

using namespace std;

void Database::addRelation(Relation r, string name) {
	allRelations.insert(pair<string, Relation>(name, r));
}

Relation* Database::getRelation(std::string name) {
	return &(allRelations.find(name)->second);
}
