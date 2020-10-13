#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {

private:
	std::vector<std::string> allValues;
public:
	Tuple(std::vector<std::string> p);
	std::string getParamAt(int index) const;
	int getSize() const;
	bool operator< (const Tuple& other) const;

};

#endif