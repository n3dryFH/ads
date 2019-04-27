/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>


////////////////////////////////////
// Ihr Code hier:



//
////////////////////////////////////

TreeNode::TreeNode(int nodePosID, int nodeID, const std::string & name, int alter, double einkommen, int plz)
	: NodePosID(nodePosID), NodeID(nodeID), Name(name), Alter(alter), Einkommen(einkommen), PLZ(plz),
	LeftNode(nullptr), RightNode(nullptr)
{
}

void TreeNode::print() const
{
	std::cout << NodeID << " | "
		<< Name << " | "
		<< Alter << " | "
		<< Einkommen << " | "
		<< PLZ << " | "
		<< NodePosID << std::endl;
}