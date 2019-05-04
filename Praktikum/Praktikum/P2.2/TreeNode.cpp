/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>


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
	std::cout << std::setfill(' ') << std::setw(3) << NodeID << "|"
		<< std::setw(12) << Name << "|"
		<< std::setw(7) << Alter << "|"
		<< std::setw(11) << Einkommen << "|"
		<< std::setw(7) << PLZ << "|"
		<< NodePosID << std::setw(0) << std::endl;
}