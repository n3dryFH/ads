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

/*Tree::~Tree()
{
	if (anker)
		deleteRecursive(anker);
}*/

/*void Tree::deleteRecursive(TreeNode * node)
{
	if (node->getLeft())
		deleteRecursive(node->getLeft());

	if (node->getRight())
		deleteRecursive(node->getRight());
	delete node;
}*/

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
		TreeNode* parentNode = nullptr;
		TreeNode* nodePtr = anker;
		while (nodePtr)
		{
			parentNode = nodePtr;
			if (newNode->getNodePosID() < nodePtr->getNodePosID())
				nodePtr = nodePtr->getLeft();
			else
				nodePtr = nodePtr->getRight();
		}

		newNode->setParent(parentNode);
		if (newNode->getNodePosID() < parentNode->getNodePosID())
			parentNode->setLeft(newNode);
		else
			parentNode->setRight(newNode);	
	}
	balanceTree(newNode);
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

bool Tree::searchNode(const std::string & name) const
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
	printTableHeader();
	if (anker)
		printTreeNodePreOrderRecursive(anker);
}

bool Tree::balanceTree(TreeNode * forNewNode)
{

	TreeNode* newNodePtr = forNewNode;
	TreeNode* parentNode = forNewNode->getParent();
	while ((parentNode && parentNode->getRed()) || anker->getRed())
	{
		if (newNodePtr == anker)
		{
			newNodePtr->setRed(false);
			parentNode = nullptr;
		}
		else if (parentNode->getRed())
		{
			TreeNode* grandparentNode = parentNode->getParent();
			assert(!grandparentNode->getRed());
			TreeNode* uncleNode = (grandparentNode->getLeft() == parentNode)
				? grandparentNode->getRight()
				: grandparentNode->getLeft();

			if (uncleNode && uncleNode->getRed())
			{
				uncleNode->setRed(false);
				parentNode->setRed(false);
				grandparentNode->setRed(true);
			}
			else
			{
				// uncle is black
				if (grandparentNode->getRight() == parentNode)
				{
					if (parentNode->getRight() == newNodePtr)
					{
						rotateTreeLeft(parentNode, newNodePtr);
						parentNode->setRed(false);
						grandparentNode->setRed(true);
					}
					else
					{
						// right-left-rotation
						rotateTreeRight(newNodePtr, newNodePtr->getLeft());
						rotateTreeLeft(newNodePtr, parentNode);
						parentNode->setRed(true);
						grandparentNode->setRed(true);
						newNodePtr->setRed(false);
					}
				}
				else
				{
					if (parentNode->getLeft() == newNodePtr)
					{
						rotateTreeRight(parentNode, newNodePtr);
						parentNode->setRed(false);
						grandparentNode->setRed(true);
					}
					else
					{
						// left-right-rotation
						rotateTreeLeft(newNodePtr, newNodePtr->getRight());
						rotateTreeRight(newNodePtr, parentNode);
						parentNode->setRed(true);
						grandparentNode->setRed(true);
						newNodePtr->setRed(false);
					}
				}
			}

			newNodePtr = grandparentNode;
			parentNode = newNodePtr->getParent();
		}
		else
			throw std::exception("balanceTree failed!");
	}

	return true;
}

bool Tree::rotateTreeRight(TreeNode * parentNode, TreeNode* leftChild)
{
	if (parentNode && parentNode->getParent() && parentNode->getLeft() == leftChild)
	{
		TreeNode* grandparentNode = parentNode->getParent();
		grandparentNode->setLeft(parentNode->getRight());
		if (grandparentNode->getLeft())
			grandparentNode->getLeft()->setParent(grandparentNode);
		parentNode->setLeft(leftChild);
		parentNode->setRight(grandparentNode);
		parentNode->setParent(grandparentNode->getParent());
		if (parentNode->getParent())
		{
			TreeNode* grandgrandparentNode = parentNode->getParent();
			if (grandgrandparentNode->getLeft() == grandparentNode)
				grandgrandparentNode->setLeft(parentNode);
			else
				grandgrandparentNode->setRight(parentNode);
		}
		else
		{
			assert(anker == grandparentNode);
			anker = parentNode;
		}
		grandparentNode->setParent(parentNode);		
		return true;
	}

	return false;
}

bool Tree::rotateTreeLeft(TreeNode * parentNode, TreeNode* rightChild)
{
	if (parentNode && parentNode->getParent() && parentNode->getRight() == rightChild)
	{
		TreeNode* grandparentNode = parentNode->getParent();
		grandparentNode->setRight(parentNode->getLeft());
		if (grandparentNode->getRight())
			grandparentNode->getRight()->setParent(grandparentNode);
		parentNode->setLeft(grandparentNode);
		parentNode->setRight(rightChild);
		parentNode->setParent(grandparentNode->getParent());
		if (parentNode->getParent())
		{
			TreeNode* grandgrandparentNode = parentNode->getParent();
			if (grandgrandparentNode->getLeft() == grandparentNode)
				grandgrandparentNode->setLeft(parentNode);
			else
				grandgrandparentNode->setRight(parentNode);
		}
		else
		{
			assert(anker == grandparentNode);
			anker = parentNode;
		}
		grandparentNode->setParent(parentNode);	
		return true;
	}

	return false;
}

void Tree::printTableHeader()
{
	std::cout << "ID |"
		<< " Name" << std::setfill(' ') << std::setw(8) << "|"
		<< " Alter |"
		<< " Einkommen |"
		<< "  PLZ  |"
		<< " Pos   |"
		<< " Red" << std::endl;
	std::cout << std::setfill('-') << std::setw(4) << '+' << std::setw(13) << '+'
		<< std::setw(8) << '+' << std::setw(12) << '+' << std::setw(8) << '+'
		<< std::setw(8) << '+' << std::setw(8) << ' ' << std::endl;
}

void Tree::printLevelOrder()
{
	printTableHeader();
	if (!anker)
		return;	
	anker->print();
	printTreeNodeLevelOrderRecursive(anker);
}

void Tree::printTreeNodePreOrderRecursive(TreeNode * node)
{
	node->print();
	if (node->getLeft())
		printTreeNodePreOrderRecursive(node->getLeft());
	if (node->getRight())
		printTreeNodePreOrderRecursive(node->getRight());
}

void Tree::printTreeNodeLevelOrderRecursive(TreeNode * node)
{
	if (!node)
		return;

	if (node->getLeft())
		node->getLeft()->print();
	if (node->getRight())
		node->getRight()->print();

	printTreeNodeLevelOrderRecursive(node->getLeft());
	printTreeNodeLevelOrderRecursive(node->getRight());
}


//
////////////////////////////////////