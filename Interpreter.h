#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DataLogProgram.h"
#include "Database.h"

class Interpreter {
private:
	DataLogProgram* datalog;
	Database* database;
public:
	Interpreter(DataLogProgram &log, Database &base);
	void Run();
	Relation evaluatePredicate(Predicate* p);
};

#endif // !INTERPRETER_H

