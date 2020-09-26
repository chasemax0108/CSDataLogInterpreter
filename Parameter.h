#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {

public:
	virtual std::string toString() = 0;
	virtual ~Parameter() {};
	virtual void setValue(std::string str) {};
};

#endif
