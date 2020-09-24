#include "DataLogProgram.h"
#include "TokenType.h"

#include <sstream>
#include <set>

using namespace std;

void DataLogProgram::updateDomain() {
	domain.clear();
	for (int i = 0; i < facts.size(); i++) {
		for (int j = 0; j < facts[i]->paramListSize(); j++) {
			domain.insert(facts[i]->paramAt(j)->toString());
		}
	}
}

string DataLogProgram::toString() {
	stringstream output;
	output << "Schemes(" << schemes.size() << "):" << endl;
	for (int i = 0; i < schemes.size(); i++) {
		output << "  " << schemeAt(i)->toString() << endl;
	}
	output << "Facts(" << facts.size() << "):" << endl;
	for (int i = 0; i < facts.size(); i++) {
		output << "  " << factAt(i)->toString() << SymbolTokenValueMap.at(PERIOD) << endl;
	}
	output << "Rules(" << rules.size() << "):" << endl;
	for (int i = 0; i < rules.size(); i++) {
		output << "  " << ruleAt(i)->toString() << endl;
	}
	output << "Queries(" << queries.size() << "):" << endl;
	for (int i = 0; i < queries.size(); i++) {
		output << "  " << queryAt(i)->toString() << SymbolTokenValueMap.at(Q_MARK) << endl;
	}
	output << "Domain(" << domain.size() << "):" << endl;
	set<string>::iterator iter;
    for (iter = domain.begin(); iter != domain.end(); ++iter) {
		output << "  " << *iter << endl;
	}
	return output.str();
}