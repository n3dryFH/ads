#pragma once
#include <vector>

struct Edge
{
	int StartNodeID;
	int EndNodeID;
	int Weight;
	Edge(int startNode, int endNode, int weight) : StartNodeID(startNode), EndNodeID(endNode), Weight(weight) {}
};

class GraphNode
{
private:
	int key = 0;	
	bool visited = false;
	int component = 0;
	std::vector<Edge> edges;
public:
	GraphNode(int key);

	void addEdge(const Edge& edge);
	Edge* getEdge(int value);
	
	inline int getKey() const { return key; }
	inline void setKey(int value) { key = value; }
	inline int getVisited() const { return visited; }
	inline void setVisited(bool value) { visited = value; }
	inline int getNumberOfEdges() const { return edges.size(); }
	inline int getComponent() const { return component; }
	inline void setComponent(int value) { component = value; }
};