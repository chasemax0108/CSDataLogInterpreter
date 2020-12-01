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

	// Interpret the Rules (IMPLEMENT)
	cout << "Rule Evaluation" << endl;
	// Step 3: create the fixed-point algorithm
	bool tuplesAdded = true;
	int totalTuplesBefore = 0;
	int totalTuplesAfter = 0;
	int passCount = 0;
	while (tuplesAdded) {
		passCount++;
		tuplesAdded = false;
		// INSERT EVALUATION CODE HERE
		for (int i = 0; i < datalog->ruleListSize(); i++) {
			Rule* workingRule = datalog->ruleAt(i);
			cout << workingRule->toString() << endl;

			// STEP 1: evaluate all Predicates
			vector<Relation> processedRelations;
			for (int j = 0; j < workingRule->predListSize(); j++) {
				processedRelations.push_back(evaluatePredicate(workingRule->predAt(j)));
			}

			// STEP 2: natural join all Predicates
			while (processedRelations.size() > 1) {
				Relation temp = processedRelations.at(processedRelations.size() - 1);
				processedRelations.pop_back();
				Relation temp2 = processedRelations.at(processedRelations.size() - 1);
				processedRelations.pop_back();
				processedRelations.push_back(temp2.naturalJoin(temp));
			}
			Relation joinedRelation = processedRelations.at(0);

			// STEP 3: project columns from Head Predicate
			vector<int> newColumns;
			for (int j = 0; j < workingRule->getHeadPred()->paramListSize(); j++) {
				for (int k = 0; k < joinedRelation.headerSize(); k++) {
					if (workingRule->getHeadPred()->paramAt(j)->toString() == joinedRelation.getHeaderAt(k)) {
						newColumns.push_back(k);
					}
				}
			}
			Relation projectedRelation = joinedRelation.project(newColumns);

			// STEP 4: rename the columns to match Relation in database
			vector<string> newNames;
			Relation* databaseRelation = database->getRelation(workingRule->getHeadPred()->getid());
			for (int j = 0; j < databaseRelation->headerSize(); j++) {
				newNames.push_back(databaseRelation->getHeaderAt(j));
			}
			Relation renamedRelation = projectedRelation.rename(newNames);

			// STEP 5: union the new relation with the old relation
			*databaseRelation = databaseRelation->unionRelations(renamedRelation);
		}

		// Check to see if the database has changed
		for (int i = 0; i < database->relationCount(); i++) {
			totalTuplesAfter += database->getRelationByIndex(i)->size();
		}
		if (totalTuplesAfter > totalTuplesBefore) tuplesAdded = true;
		totalTuplesBefore = totalTuplesAfter;
		totalTuplesAfter = 0;
	}
	cout << endl;
	cout << "Schemes populated after " << passCount << " passes through the Rules." << endl;
	cout << endl;

	// Interpret the Queries
	cout << "Query Evaluation" << endl;
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

	// First we select
	for (int i = 0; i < p->paramListSize(); i++) { // select all of the values first
		string currentColumn = p->paramAt(i)->toString();
		if (currentColumn[0] == '\'') { // This select is looking for values
			workingRelation = workingRelation.select(i, currentColumn);
		}
	}
	for (int i = 0; i < p->paramListSize(); i++) { // Then select all of the similar columns
		string currentColumn = p->paramAt(i)->toString();
		if (currentColumn[0] != '\'') {
			for (int j = 0; j < p->paramListSize(); j++) {
				string compareColumn = p->paramAt(j)->toString();
				if (currentColumn == compareColumn && j != i) { // This is an equivalence test
					workingRelation = workingRelation.select(i, j);
				}
			}
		}
	}

	// Now we project and get names for rename
	vector<int> columnsToKeep;
	vector<string> columnNames;
	for (int i = 0; i < p->paramListSize(); i++) {
		string currentColumn = p->paramAt(i)->toString();
		if (currentColumn[0] != '\'') { // It's a named column, not a value to test for
			bool addMe = true;
			for (int j = 0; j < i; j++) { // Are any columns before this one the same? (is unique so far?)
				string compareColumn = p->paramAt(j)->toString();
				if (currentColumn == compareColumn) { // Don't add it, there's already one in here.
					addMe = false;
				}
			}
			if (addMe) {
				columnsToKeep.push_back(i);
				columnNames.push_back(currentColumn);
			}
		}
	}
	workingRelation = workingRelation.project(columnsToKeep);

	// Now we rename
	workingRelation = workingRelation.rename(columnNames);

	return workingRelation;
}

