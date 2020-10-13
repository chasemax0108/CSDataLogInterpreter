#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class Header {
private:
	std::vector<std::string> allNames;
public:
	Header() {};
	Header(std::vector<std::string> n);
	std::string getNameAt(int index);
	int getSize();
};

#endif // !HEADER_H

