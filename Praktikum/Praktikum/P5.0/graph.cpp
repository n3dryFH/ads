#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <queue>
#include <vector>
#include <functional>
#include "graph.h"
#include "graphNode.h"

Graph::Graph()
{
}

Graph::~Graph()
{
	for (int i = 0; i < nodes.size(); ++i)
		delete nodes.at(i);
	nodes.clear();
}

GraphNode* Graph::getNodeByKey(int key)
{
	for (const auto& node : nodes)
		if (node->getKey() == key)
			return node;
	return nullptr;
}

void Graph::setAllUnvisited()
{
	for (auto& node : nodes)	
		node->setVisited(false);	
}

bool Graph::checkVisited()
{
	for (const auto& node : nodes)
		if (!node->getVisited())
			return false;
	return true;
}

bool Graph::testChildComponent(GraphNode * node)
{
	for (const auto& n : nodes)
		if (node->getComponent() != n->getComponent())
			return false;
	return true;
}

bool Graph::init(const std::string & filename)
{
	std::ifstream file;
	file.open(filename, std::ios_base::in);
	if (!file) 
	{
		std::cout << "Cannot open file." << std::endl;
		return false;
	}
	else 
	{
		std::string line;
		std::getline(file, line);
		std::istringstream iss(line);

		iss >> anzKnoten; //Erste Zeile Auslesen
		
		ger = false; // ungerichtet
		gew = true; // gewichtet
		nodes.clear();		

		//Alle Knoten anlegen
		for (int i = 0; i < anzKnoten; i++) 
		{
			//TODO
			nodes.push_back(new GraphNode(i));
		}
		//Alle Kanten anlegen
		while (std::getline(file, line)) 
		{
			//TODO
			std::istringstream iss(line);
			int startNode, endNode, weight;
			iss >> startNode;
			iss >> endNode;
			iss >> weight;
			assert(startNode >= 0 && startNode < nodes.size());
			assert(endNode >= 0 && endNode < nodes.size());
			nodes.at(startNode)->addEdge({startNode, endNode, weight}); // hinkante
			if (!ger)
				nodes.at(endNode)->addEdge({endNode, startNode, weight}); // rueckkante
		}
		return true;

	}
	 return false;	 
}

void Graph::printAll() const
{
	for (int i = 0; i < nodes.size(); ++i)
	{		
		std::cout << i;
		GraphNode* const node = nodes.at(i);
		const int numberOfEdges = node->getNumberOfEdges();
		for (int j = 0; j < numberOfEdges; ++j)
		{
			const Edge* const edge = node->getEdge(j);
			std::cout << " -> " << edge->EndNodeID << " [" << edge->Weight << "]";			
		}
		std::cout << std::endl;
	}
}

bool Graph::depthSearchRek(int startKey)
{
	setAllUnvisited();	
	startDepthSearchRek(getNodeByKey(startKey));
	return checkVisited();
}

void Graph::startDepthSearchRek(GraphNode * node)
{
	assert(node);
	node->setVisited(true);
	const int numberOfEdges = node->getNumberOfEdges();
	for (int i = 0; i < numberOfEdges; ++i)
	{
		const int nextTargetNodeID = node->getEdge(i)->EndNodeID;
		GraphNode* const nextTargetNode = getNodeByKey(nextTargetNodeID);
		assert(nextTargetNode);
		if (!nextTargetNode->getVisited())
			startDepthSearchRek(nextTargetNode);
	}
}

bool Graph::breadthSearchIter(int startKey)
{
	setAllUnvisited();
	std::queue<GraphNode*> queue;
	GraphNode* const startNode = getNodeByKey(startKey);
	assert(startNode);	
	startNode->setVisited(true);
	queue.push(startNode);
	while (!queue.empty())
	{
		GraphNode* const node = queue.front();
		queue.pop();		
		const int numberOfEdges = node->getNumberOfEdges();
		for (int i = 0; i < numberOfEdges; ++i)
		{
			const int nextTargetNodeID = node->getEdge(i)->EndNodeID;
			GraphNode* const nextTargetNode = getNodeByKey(nextTargetNodeID);
			assert(nextTargetNode);
			if (!nextTargetNode->getVisited())
			{
				nextTargetNode->setVisited(true);
				queue.push(nextTargetNode);
			}
		}
	}		
	return checkVisited();
}

double Graph::prim(int startKey)
{	
	auto compareFunc = [](const Edge* a, const Edge* b)	{ return a->Weight > b->Weight;	};
	std::priority_queue<const Edge*, std::vector<const Edge*>, decltype(compareFunc)> unvisitedEgdesQueue(compareFunc);
	auto visitFunc = [&](GraphNode* node) 
	{
		node->setVisited(true);
		const int numberOfEdges = node->getNumberOfEdges();
		for (int i = 0; i < numberOfEdges; ++i)
		{
			if (!nodes.at(node->getEdge(i)->EndNodeID)->getVisited())
				unvisitedEgdesQueue.push(node->getEdge(i));
		}
	};

	setAllUnvisited();
	GraphNode* const startNode = getNodeByKey(startKey);
	assert(startNode);

	visitFunc(startNode);	

	std::vector<const Edge*> mstEdges;
	while (!unvisitedEgdesQueue.empty())
	{		
		const Edge* edge = unvisitedEgdesQueue.top();
		unvisitedEgdesQueue.pop();

		GraphNode* const startNode = nodes.at(edge->StartNodeID);
		GraphNode* const endNode = nodes.at(edge->EndNodeID);

		if (startNode->getVisited() && endNode->getVisited())
			continue;

		mstEdges.push_back(edge);		
		if (!startNode->getVisited())
			visitFunc(startNode);
		if (!endNode->getVisited())
			visitFunc(endNode);
	}

	double mstSum = 0;
	for (const auto& mstEdge : mstEdges)
		mstSum += mstEdge->Weight;

	return mstSum;
}

double Graph::kruskal()
{	
	for (int i = 0; i < nodes.size(); ++i) // zu Beginn ist jeder Knoten ein eigener Baum
		nodes.at(i)->setComponent(i);	
	
	std::vector<const Edge*> edges;
	for (const auto& node : nodes)
	{
		const int numberOfEdges = node->getNumberOfEdges();
		for (int i = 0; i < numberOfEdges; ++i)		
			edges.push_back(node->getEdge(i));
	}	

	std::sort(edges.begin(), edges.end(), [](const Edge* a, const Edge* b) {
		return a->Weight < b->Weight;
	});

	std::vector<const Edge*> mstEdges;
	for (auto& edge : edges)
	{		
		const int startNodeIDComponent = nodes.at(edge->StartNodeID)->getComponent();
		const int endNodeIDComponent = nodes.at(edge->EndNodeID)->getComponent();
		// Wenn Knoten zu unterschiedlichen Bäumen gehört,
		// können diese mit der Kante ohne Zykel verbunden werde
		if (startNodeIDComponent != endNodeIDComponent)
		{			
			mstEdges.push_back(edge);
			for (auto& node : nodes)
				if (node->getComponent() == endNodeIDComponent) // BaumId angleichen
					node->setComponent(startNodeIDComponent);
		}

		if (mstEdges.size() >= nodes.size() - 1)
			break; // Stoppt bei Kanten = Knoten -1
	}

	double mstSum = 0;
	for (const auto& mstEdge : mstEdges)
		mstSum += mstEdge->Weight;

	return mstSum;
}
