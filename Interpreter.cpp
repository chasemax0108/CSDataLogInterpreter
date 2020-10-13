#include "Interpreter.h"

#include <iostream>
#include <sstream>

using namespace std;

Interpreter::Interpreter(DataLogProgram &log, Database &base) {
	datalog = &log;
	database = &base;
}

void Interpreter::Run() {

	// Interpret the Schemes
	for (int i = 0; i < datalog->schemeListSize(); i++) {
		string name = datalog->schemeAt(i)->getid();
		vector<string> columns;
		for (int j = 0; j < datalog->schemeAt(i)->paramListSize(); j++) {
			columns.push_back(datalog->schemeAt(i)->paramAt(j)->toString());
		}
		Header schemeHead(columns);
		Relation newRelation(schemeHead);
		database->addRelation(newRelation, name);
	}

	// Interpret the Facts
	for (int i = 0; i < datalog->factListSize(); i++) {
		vector<string> newTupleValues;
		for (int j = 0; j < datalog->factAt(i)->paramListSize(); j++) {
			newTupleValues.push_back(datalog->factAt(i)->paramAt(j)->toString());
		}
		Tuple newTuple(newTupleValues);
		(database->getRelation(datalog->factAt(i)->getid()))->addTuple(newTuple);
	}

	// Interpret the Queries
	for (int i = 0; i < datalog->queryListSize(); i++) {
		stringstream output;
		Relation processedRelation = evaluatePredicate(datalog->queryAt(i));
		output << datalog->queryAt(i)->toString() << "? ";
		if (processedRelation.size() > 0) {
			output << "Yes(" << processedRelation.size() << ")" << endl;
			output << processedRelation.toString();
		}
		else {
			output << "No" << endl;
		}
		cout << output.str();
	}

}

Relation Interpreter::evaluatePredicate(Predicate* p) {
	Relation* originalRelation;
	originalRelation = database->getRelation(p->getid());
	Relation workingRelation = *originalRelation;
	for (int i = 0; i < p->paramListSize(); i++) {
		string currentColumn = p->paramAt(i)->toString();
		if (currentColumn[0] == '\'') { // This select is looking for values
			workingRelation = workingRelation.select(i, currentColumn);
		}
	}
	return workingRelation;
}
