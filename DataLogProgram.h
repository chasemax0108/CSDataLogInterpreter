#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <set>
#include <string>
#include "Rule.h"
#include "Predicate.h"

class DataLogProgram {
private:
	std::vector<Predicate*> schemes;
	std::vector<Predicate*> facts;
	std::vector<Rule*> rules;
	std::vector<Predicate*> queries;
	std::set<std::string> domain;
public:
	DataLogProgram() {};
	~DataLogProgram() {
		for (unsigned int i = 0; i < schemes.size(); i++) {
			delete schemes[i];
		}
		for (unsigned int i = 0; i < facts.size(); i++) {
			delete facts[i];
		}
		for (unsigned int i = 0; i < rules.size(); i++) {
			delete rules[i];
		}
		for (unsigned int i = 0; i < queries.size(); i++) {
			delete queries[i];
		}
	}

	void updateDomain();
	std::string toString();

	std::set<std::string> getDomain() {
		return domain;
	}

	void addScheme(Predicate* s) {
		schemes.push_back(s);
	}
	void addFact(Predicate* f) {
		facts.push_back(f);
	}
	void addRule(Rule* r) {
		rules.push_back(r);
	}
	void addQuery(Predicate* q) {
		queries.push_back(q);
	}

	int schemeListSize() {
		return schemes.size();
	}
	int factListSize() {
		return facts.size();
	}
	int ruleListSize() {
		return rules.size();
	}
	int queryListSize() {
		return queries.size();
	}

	Predicate* schemeAt(int i) {
		return schemes[i];
	}
	Predicate* factAt(int i) {
		return facts[i];
	}
	Rule* ruleAt(int i) {
		return rules[i];
	}
	Predicate* queryAt(int i) {
		return queries[i];
	}
};

#endif // !DATALOGPROGRAM_H
