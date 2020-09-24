#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
	std::vector<Parameter*> allParams;
	std::string id;
public:
	Predicate() {};
	~Predicate();
	Predicate(std::string i) {
		id = i;
	};
	void setid(std::string i) {
		id = i;
	}
	std::string getid() {
		return id;
	}
	int paramListSize() {
		return allParams.size();
	}
	Parameter* paramAt(int index) {
		return allParams[index];
	}
	std::string toString();
	void addParam(Parameter* p) {
		allParams.push_back(p);
	}
};


#endif // !PREDICATE_H

