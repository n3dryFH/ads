#include "graphNode.h"

GraphNode::GraphNode(int key) : key(key)
{
}

void GraphNode::addEdge(const Edge & edge)
{
	edges.push_back(edge);
}

Edge* GraphNode::getEdge(int value)
{
	if (value >= 0 && value < edges.size())
		return &edges.at(value);
	return nullptr;
}
