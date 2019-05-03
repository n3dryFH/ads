/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

////////////////////////////////////
// Ihr Code hier:



Tree::Tree() : NodeIDCounter(0), anker(nullptr)
{
}
void Tree::addNode(const std::string & name, int alter, double einkommen, int plz)
{
	int nodePosID = alter + plz + einkommen;
	TreeNode* newNode = new TreeNode(nodePosID, NodeIDCounter, name, alter, einkommen, plz);
	if (!anker)
	{
		anker = newNode;
	}
	else
	{		
		TreeNode* lastParentNode = nullptr;
		TreeNode* nodePtr = anker;
		while (nodePtr)
		{
			lastParentNode = nodePtr;
			if (newNode->getNodePosID() < nodePtr->getNodePosID())
				nodePtr = nodePtr->getLeft();
			else
				nodePtr = nodePtr->getRight();
		}

		if (newNode->getNodePosID() < lastParentNode->getNodePosID())
			lastParentNode->setLeft(newNode);
		else
			lastParentNode->setRight(newNode);
	}
	++NodeIDCounter;	
}

void Tree::deleteNode(int nodePosID)
{
	if (!anker)
		return;

	TreeNode* parentNode = anker;
	TreeNode* nodeWithPos = anker;	
	
	while (nodeWithPos->getNodePosID() != nodePosID)
	{
		if (nodePosID < nodeWithPos->getNodePosID())
		{
			parentNode = nodeWithPos;
			nodeWithPos = nodeWithPos->getLeft();
		}
		else if (nodePosID > nodeWithPos->getNodePosID())
		{
			parentNode = nodeWithPos;
			nodeWithPos = nodeWithPos->getRight();
		}			
	}	
		
	if (nodeWithPos)
	{
		if (!nodeWithPos->getLeft() && !nodeWithPos->getRight())
		{
			if (anker != nodeWithPos)
			{
				overrideCloseChildByIdWith(parentNode, nodePosID, nullptr);
				nodeWithPos = nullptr;
			}
			else
			{
				// Wurzel
				delete anker;
				anker = nullptr;
			}
		}			
		else if (nodeWithPos->getLeft() && nodeWithPos->getRight())
		{
			TreeNode* minNode = nullptr;			 
			TreeNode* minNodeParent = findParentMinNode(nodeWithPos);
			if (minNodeParent == nodeWithPos) 
			{
				minNode = minNodeParent->getRight();
				minNode->setLeft(nodeWithPos->getLeft());
			}
			else
			{
				minNode = minNodeParent->getLeft();								
				minNodeParent->setLeft(minNode->getRight());				
				minNode->setLeft(nodeWithPos->getLeft());
				minNode->setRight(nodeWithPos->getRight());
			}					
			
			if (anker != nodeWithPos)
			{
				overrideCloseChildByIdWith(parentNode, nodeWithPos->getNodePosID(), minNode);
				nodeWithPos = nullptr;
			}
			else
			{
				// Wurzel
				anker = minNode;
				delete nodeWithPos;
			}
			nodeWithPos = nullptr;
		}
		else
		{
			TreeNode* child = nodeWithPos->getLeft() ? nodeWithPos->getLeft() : nodeWithPos->getRight();
			if (anker != nodeWithPos)
			{
				overrideCloseChildByIdWith(parentNode, nodeWithPos->getNodePosID(), child);
				nodeWithPos = nullptr;
			}
			else
			{
				// Wurzel
				delete nodeWithPos;
				nodeWithPos = nullptr;
				anker = child;
			}
		}
	}	
}

bool Tree::searchNode(const std::string & name)
{	
	return searchAndPrintTreeNodeRecursive(anker, name);	
}

bool Tree::searchAndPrintTreeNodeRecursive(TreeNode * node, const std::string & name)
{
	if (!node)
		return false;

	bool bEqual = node->getName() == name;
	if (bEqual)
	{
		std::cout << "NodeID: " << node->getNodeID() << ", Name: " << node->getAlter()
			<< ", Einkommen: " << node->getEinkommen() << ", PLZ: " << node->getPLZ()
			<< ", PosID: " << node->getNodePosID() << std::endl;
	}

	bool bFoundNameOnLeft = searchAndPrintTreeNodeRecursive(node->getLeft(), name);
	bool bFoundNameOnRight = searchAndPrintTreeNodeRecursive(node->getRight(), name);
	return bEqual || bFoundNameOnLeft || bFoundNameOnRight;
}

TreeNode* Tree::findParentMinNode(TreeNode * fromNode)
{	
	TreeNode* nodePtr = fromNode->getRight();	
	TreeNode* minParent = fromNode;
	
	while (nodePtr->getLeft())
	{
		minParent = nodePtr;
		nodePtr = nodePtr->getLeft();
	}	
	return minParent;
}

void Tree::overrideCloseChildByIdWith(TreeNode* parent, int nodePosID, TreeNode* child)
{
	if (parent)
	{
		if (parent->getLeft() && parent->getLeft()->getNodePosID() == nodePosID)
		{
			delete parent->getLeft();
			parent->setLeft(child);
		}
		else if (parent->getRight() && parent->getRight()->getNodePosID() == nodePosID)
		{
			delete parent->getRight();
			parent->setRight(child);
		}
	}
}

void Tree::printAll() const
{
	std::cout << "ID | Name | Alter | Einkommen | PLZ | Pos" << std::endl;
	if (anker)	
		printTreeNodeRecursive(anker);
}

void Tree::printTreeNodeRecursive(TreeNode * node)
{
	node->print();
	if (node->getLeft())
		printTreeNodeRecursive(node->getLeft());
	if (node->getRight())
		printTreeNodeRecursive(node->getRight());
}


//
////////////////////////////////////