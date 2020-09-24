#ifndef PLAINPARAMETER_H
#define PLAINPARAMETER_H

#include <string>
#include "Parameter.h"

class PlainParameter : public Parameter {

private:
	std::string value;

public:
	PlainParameter() {};
	PlainParameter(std::string v);
	virtual std::string toString();
	void setValue(std::string v) {
		value = v;
	}
	std::string getValue() {
		return value;
	}
};

#endif