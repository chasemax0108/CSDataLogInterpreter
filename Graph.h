#ifndef GRAPH_H
#define GRAPH_H

#include "Rule.h"
#include <vector>
#include <map>
#include <set>
#include <stack>

class Graph {
public:
	std::map<int, std::set<int>> adjacencyList;
	Graph() {};
	Graph(std::vector<Rule*> rules);
	std::string toString();
	Graph returnReverseGraph();
};

#endif // !GRAPH_H

