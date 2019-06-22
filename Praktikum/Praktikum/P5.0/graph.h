#pragma once
#include <string>
#include <vector>

class GraphNode;

class Graph
{
private:
	int anzKnoten = 0;
	bool ger = false;
	bool gew = false;
	std::vector<GraphNode*> nodes;

	GraphNode* getNodeByKey(int key);
	void setAllUnvisited();
	bool checkVisited();
	void startDepthSearchRek(GraphNode* node);
	bool testChildComponent(GraphNode* node);

public:
	Graph();
	~Graph();

	bool init(const std::string& file);
	void printAll() const;
	bool depthSearchRek(int startKey);
	bool breadthSearchIter(int startKey);
	double prim(int startKey);
	double kruskal();

	inline int getAnzKnoten() const { return anzKnoten; }
};