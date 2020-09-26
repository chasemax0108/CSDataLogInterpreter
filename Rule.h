#ifndef RULE_H
#define RULE_H

#include <vector>
#include <string>

#include "Predicate.h"

class Rule {
private:
	std::vector<Predicate*> allPreds;
	Predicate* headPred;
public:
	Rule() {};
	~Rule() {
		delete headPred;
		for (int i = 0; i < allPreds.size(); i++) {
			delete allPreds[i];
		}
	}
	Rule(Predicate* h) {
		headPred = h;
	}
	std::string toString();
	int predListSize() {
		return allPreds.size();
	}
	void addPred(Predicate* p) {
		allPreds.push_back(p);
	}
	void addHeadPred(Predicate* p) {
		headPred = p;
	}
	Predicate* predAt(int i) {
		return allPreds[i];
	}
};

#endif // !RULE_H
