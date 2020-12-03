#include "Interpreter.h"

#include <iostream>
#include <sstream>
#include "Graph.h"

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

	// Rule Evaluation: Determining rule evaluation order
	// Step 1: Build dependency graph

	vector<Rule*> rulesForGraph;
	for (int i = 0; i < datalog->ruleListSize(); i++) {
		rulesForGraph.push_back(datalog->ruleAt(i));
	}
	Graph ruleGraph(rulesForGraph);

	// Step 2: Reverse the graph
	Graph reverseGraph = ruleGraph.returnReverseGraph();

	// Step 3: Run a depth first search on the graph and get the postorder
	for (int i = 0; i < ruleGraph.adjacencyList.size(); i++) {
		searchorder.push_back(i);
	}
	depthFirstSearchForest(reverseGraph);

	// Step 4: Run a depth first search forest on the original graph using the reversed postorder
	searchorder.clear();
	SCCList.clear();
	for (int i = postorder.size() - 1; i >= 0; i--) {
		searchorder.push_back(postorder.at(i));
	}
	postorder.clear();
	depthFirstSearchForest(ruleGraph);

	// Step 5: Evaluate the rules based on the Strongly Connected Components that you just calculated
	cout << ruleGraph.toString() << endl;
	cout << "Rule Evaluation" << endl;
	bool tuplesAdded = true;
	int totalTuplesBefore = 0;
	int totalTuplesAfter = 0;
	int passCount = 0;
	for (int i = 0; i < SCCList.size(); i++) {
		tuplesAdded = true;
		totalTuplesAfter = 0;
		passCount = 0;
		set<int>::iterator SCCiter;
		SCCiter = SCCList.at(i).begin();
		cout << "SCC: R" << *SCCiter;
		for (SCCiter++; SCCiter != SCCList.at(i).end(); SCCiter++) {
			cout << ",R" << *SCCiter;
		}
		cout << endl;
		while (tuplesAdded) {
			passCount++;
			tuplesAdded = false;
			// INSERT EVALUATION CODE HERE
			for (SCCiter = SCCList.at(i).begin(); SCCiter != SCCList.at(i).end(); SCCiter++) {
				Rule* workingRule = datalog->ruleAt(*SCCiter);
				cout << workingRule->toString() << endl;

				// STEP 1: evaluate all Predicates
				vector<Relation> processedRelations;
				for (int k = 0; k < workingRule->predListSize(); k++) {
					processedRelations.push_back(evaluatePredicate(workingRule->predAt(k)));
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
				for (int k = 0; k < workingRule->getHeadPred()->paramListSize(); k++) {
					for (int l = 0; l < joinedRelation.headerSize(); l++) {
						if (workingRule->getHeadPred()->paramAt(k)->toString() == joinedRelation.getHeaderAt(l)) {
							newColumns.push_back(l);
						}
					}
				}
				Relation projectedRelation = joinedRelation.project(newColumns);

				// STEP 4: rename the columns to match Relation in database
				vector<string> newNames;
				Relation* databaseRelation = database->getRelation(workingRule->getHeadPred()->getid());
				for (int k = 0; k < databaseRelation->headerSize(); k++) {
					newNames.push_back(databaseRelation->getHeaderAt(k));
				}
				Relation renamedRelation = projectedRelation.rename(newNames);

				// STEP 5: union the new relation with the old relation
				*databaseRelation = databaseRelation->unionRelations(renamedRelation);
			}

			// Check to see if the database has changed
			for (int j = 0; j < database->relationCount(); j++) {
				totalTuplesAfter += database->getRelationByIndex(j)->size();
			}
			if (totalTuplesAfter > totalTuplesBefore) tuplesAdded = true;
			totalTuplesBefore = totalTuplesAfter;
			totalTuplesAfter = 0;

			// Also check to see if the single rule depends on itself
			if (SCCList.at(i).size() == 1) {
				SCCiter = SCCList.at(i).begin();
				if (ruleGraph.adjacencyList.at(*SCCiter).find(*SCCiter) == ruleGraph.adjacencyList.at(*SCCiter).end()) {
					break;
				}
			}

		}
		SCCiter = SCCList.at(i).begin();
		cout << passCount << " passes: R" << *SCCiter;
		for (SCCiter++; SCCiter != SCCList.at(i).end(); SCCiter++) {
			cout << ",R" << *SCCiter;
		}
		cout << endl;
	}
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

void Interpreter::depthFirstSearchForest(Graph g) {
	marked.clear();
	map<int, set<int>>::iterator graphIter;
	for (int i = 0; i < searchorder.size(); i++) {
		for (graphIter = g.adjacencyList.begin(); graphIter != g.adjacencyList.end(); graphIter++) {
			if (searchorder.at(i) == graphIter->first) {
				if (marked.find(graphIter->first) == marked.end()) {
					connectedComponents.clear();
					depthFirstSearch(g, graphIter->first);
					SCCList.push_back(connectedComponents);
				}
			}
		}
	}
}

void Interpreter::depthFirstSearch(Graph g, int vertex) {
	marked.insert(vertex);
	connectedComponents.insert(vertex);
	set<int> adjacentVertices = g.adjacencyList.find(vertex)->second;
	set<int>::iterator iter;
	for (int i = 0; i < searchorder.size(); i++) {
		for (iter = adjacentVertices.begin(); iter != adjacentVertices.end(); iter++) {
			if (searchorder.at(i) == *iter) {
				if (marked.find(*iter) == marked.end()) {
					depthFirstSearch(g, *iter);
				}
			}
		}
	}
	postorder.push_back(vertex);
}