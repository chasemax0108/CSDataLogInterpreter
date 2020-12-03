#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DataLogProgram.h"
#include "Database.h"
#include "Graph.h"
#include <vector>
#include <set>

class Interpreter {
private:
	DataLogProgram* datalog;
	Database* database;
	std::vector<std::set<int>> SCCList;
	std::vector<int> postorder;
	std::vector<int> searchorder;
	std::set<int> marked;
	void depthFirstSearchForest(Graph g);
	void depthFirstSearch(Graph g, int vertex);
	std::set<int> connectedComponents;
public:
	Interpreter(DataLogProgram &log, Database &base);
	void Run();
	Relation evaluatePredicate(Predicate* p);
};

#endif // !INTERPRETER_H

