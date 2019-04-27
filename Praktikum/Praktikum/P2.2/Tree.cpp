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

//
////////////////////////////////////
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
	// todo implement delete
	if (!anker)
		return;
	
	TreeNode* nodeToDelete = nullptr;
	if (anker->getNodePosID() == nodePosID)
	{
		nodeToDelete = anker;
	}
	else
	{
		nodeToDelete = searchForTreeNodeRecursive(anker, nodePosID);
	}

	if (nodeToDelete)
	{
		if (!nodeToDelete->getLeft() && !nodeToDelete->getRight())
			delete nodeToDelete;
		else if (nodeToDelete->getLeft() && nodeToDelete->getRight())
		{

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

TreeNode* Tree::searchForTreeNodeRecursive(TreeNode* node, int nodePosID)
{
	if (node->getNodePosID() == nodePosID)
		return node;
	
	TreeNode* searchedNode = nullptr;
	if (node->getLeft())
	{
		searchedNode = searchForTreeNodeRecursive(node->getLeft(), nodePosID);
		if (searchedNode)
			return searchedNode;
	}		

	if (node->getRight())
	{
		searchedNode = searchForTreeNodeRecursive(node->getRight(), nodePosID);
		if (searchedNode)
			return searchedNode;
	}		

	return nullptr;
}

TreeNode* Tree::findMinTreeNode(TreeNode * node)
{
	TreeNode* nodePtr = node;
	TreeNode* minNodePtr = node;
	while (nodePtr)
	{
		minNodePtr = nodePtr;
		nodePtr = nodePtr->getLeft();
	}
	return minNodePtr;
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

