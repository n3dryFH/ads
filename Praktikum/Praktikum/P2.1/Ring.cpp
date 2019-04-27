/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

// Ihr Code hier:
Ring::Ring() : AnzahlNodes(0), anker(nullptr) {}

Ring::~Ring()
{
	RingNode* ptr = anker;
	for (unsigned int i = 0; i < AnzahlNodes; ++i)
	{
		RingNode* tmpPtr = ptr;
		ptr = ptr->getNext();
		delete tmpPtr;
	}
	anker = nullptr;
}

void Ring::addNode(const std::string& description, const std::string& data)
{	
	RingNode* newNode = new RingNode(0, description, data);
	if (AnzahlNodes == 0)
	{
		anker = newNode;
		anker->setNext(anker);
		++AnzahlNodes;
	}		
	else
	{		
		// update age for all existing nodes
		RingNode* node = anker;
		for (unsigned int i = 0; i < AnzahlNodes; ++i)
		{
			node->setAge(node->getAge() + 1);
			if (i != AnzahlNodes - 1)
				node = node->getNext();	 // save ptr to last node
		}
		// add current anker to end
		if (node == anker) // check if only one node is inserted
		{
			newNode->setNext(anker); 
			anker->setNext(newNode);
			anker = newNode;
			++AnzahlNodes;
		}				
		else
		{
			node->setNext(anker);
			newNode->setNext(anker->getNext());
			anker->setNext(newNode);
			anker = newNode;

			if (AnzahlNodes == 6)
			{
				RingNode* currentMaxNode = anker->getNext();
				anker->setNext(currentMaxNode->getNext());
				delete currentMaxNode;
			}
			else
				++AnzahlNodes;
		}	
	}
}

bool Ring::search(const std::string & data)
{
	RingNode* node = anker;
	for (unsigned int i = 0; i < AnzahlNodes; ++i)
	{
		if (node->getData() == data)
		{
			std::cout << "+ Gefunden in Backup: OldAge " << node->getAge()
				<< ", Beschreibung: " << node->getDescription()
				<< ", Daten: " << node->getData() << std::endl;
			return true;
		}
		node = node->getNext();
	}
	std::cout << "+ Datensatz konnte nicht gefunden werden." << std::endl;
	return false;
}

void Ring::print() const
{
	if (anker)		
		printNodesRecursive(*anker->getNext());	
}
void Ring::printNodesRecursive(RingNode & node) const
{
	if (node.getAge() > 0)	
		printNodesRecursive(*node.getNext());				
	std::cout << "OldAge: " << node.getAge() << ", Descr: " << node.getDescription()
		<< ", Data: " << node.getData() << std::endl;
}
//
////////////////////////////////////