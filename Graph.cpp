#include "Graph.h"
#include <iostream>
#include <sstream>
using namespace std;

Graph::Graph(vector<Rule*> rules) {
	for (int i = 0; i < rules.size(); i++) {
		set<int> dependentRules;
		for (int j = 0; j < rules.at(i)->predListSize(); j++) {
			for (int k = 0; k < rules.size(); k++) {
				if (rules.at(k)->getHeadPred()->getid() == rules.at(i)->predAt(j)->getid()) {
					dependentRules.insert(k);
				}
			}
		}
		set<int>::iterator iter;
		adjacencyList.insert({ i, dependentRules });
	}
}

Graph Graph::returnReverseGraph() {
	Graph reverseGraph;
	map<int, set<int>>::iterator mapIter;
	map<int, set<int>>::iterator mapIter2;
	for (mapIter = adjacencyList.begin(); mapIter != adjacencyList.end(); mapIter++) {
		set<int> reverseDependencies;
		for (mapIter2 = adjacencyList.begin(); mapIter2 != adjacencyList.end(); mapIter2++) {
			set<int>::iterator iter;
			for (iter = mapIter2->second.begin(); iter != mapIter2->second.end(); iter++) {
				if (*iter == mapIter->first) {
					reverseDependencies.insert(mapIter2->first);
					break;
				}
			}
		}
		reverseGraph.adjacencyList.insert({ mapIter->first, reverseDependencies });
	}
	return reverseGraph;
}

string Graph::toString() {
	map<int, set<int>>::iterator mapIter;
	stringstream output;
	output << "Dependency Graph: " << endl;
	for (mapIter = adjacencyList.begin(); mapIter != adjacencyList.end(); mapIter++) {
		output << "R" << mapIter->first << ":";
		set<int>::iterator iter;
		for (iter = mapIter->second.begin(); iter != mapIter->second.end(); iter++) {
			if (iter != mapIter->second.begin()) output << ",";
			output << "R" << *iter;
		}
		output << endl;
	}
	return output.str();
}
