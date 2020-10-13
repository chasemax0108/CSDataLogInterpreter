#ifndef DATABASE_H
#define DATABASE_H	

#include <map>
#include "Relation.h"

class Database {

private:
	std::map<std::string, Relation> allRelations;
public:
	Database() {};
	void addRelation(Relation r, std::string name);
	Relation* getRelation(std::string name);
};

#endif // !DATABASE_H
