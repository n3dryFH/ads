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

	TreeNode* parentNode = nullptr;
	TreeNode* nodeWithPos = nullptr;
	if (anker->getNodePosID() == nodePosID)	
		nodeWithPos = anker;	
	else
	{
		parentNode = findParentNodeWithPosID(anker, nodePosID);
		nodeWithPos = getCloseChildById(parentNode, nodePosID);
	}
		
	if (nodeWithPos)
	{
		if (!nodeWithPos->getLeft() && !nodeWithPos->getRight())
		{
			if (parentNode)
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
			
			if (parentNode)
			{
				overrideCloseChildByIdWith(parentNode, nodeWithPos->getNodePosID(), minNode);
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
			if (parentNode)
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

TreeNode* Tree::findParentNodeWithPosID(TreeNode* node, int nodePosID)
{
	if (node->getNodePosID() == nodePosID)
		return node;
	
	TreeNode* leftNode = findParentNodeWithPosIDRecursive(node, node->getLeft(), nodePosID);
	TreeNode* rightNode = nullptr;
	if (!leftNode)
		rightNode = findParentNodeWithPosIDRecursive(node, node->getRight(), nodePosID);

	return leftNode ? leftNode : rightNode;	
}

TreeNode * Tree::findParentNodeWithPosIDRecursive(TreeNode * parent, TreeNode * child, int nodePosID)
{
	if (child->getNodePosID() == nodePosID)
		return parent;

	TreeNode* searchedNode = nullptr;
	if (child->getLeft())
	{
		searchedNode = findParentNodeWithPosIDRecursive(child, child->getLeft(), nodePosID);
		if (searchedNode)
			return searchedNode;
	}

	if (child->getRight())
	{
		searchedNode = findParentNodeWithPosIDRecursive(child, child->getRight(), nodePosID);
		if (searchedNode)
			return searchedNode;
	}

	return nullptr;
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

TreeNode * Tree::getCloseChildById(TreeNode * startNode, int nodePosID)
{
	if (!startNode)
		return nullptr;

	return (startNode->getLeft() && startNode->getLeft()->getNodePosID() == nodePosID) ? startNode->getLeft() :
		(startNode->getRight() && startNode->getRight()->getNodePosID() == nodePosID ? startNode->getRight() : nullptr);
}

void Tree::overrideCloseChildByIdWith(TreeNode* parent, int nodePosID, TreeNode* child)
{
	if (parent)
	{
		if (parent->getLeft()->getNodePosID() == nodePosID)
		{
			delete parent->getLeft();
			parent->setLeft(child);
		}
		else if (parent->getRight()->getNodePosID() == nodePosID)
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