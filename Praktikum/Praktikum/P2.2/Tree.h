/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree{
	
	private: 
		///////////////////////////////////////
		// Ihr Code hier:	
		TreeNode* anker;
		int NodeIDCounter;

		static void printTreeNodeRecursive(TreeNode* node);
		static bool searchAndPrintTreeNodeRecursive(TreeNode* node, const std::string& name);
		static TreeNode* findParentNodeWithPosID(TreeNode* startNode, int nodePosID);
		static TreeNode* findParentNodeWithPosIDRecursive(TreeNode* parent, TreeNode* child, int nodePosID);
		static TreeNode* findParentMinNode(TreeNode * fromNode);
		static TreeNode* getCloseChildById(TreeNode* startNode, int nodePosID);
		static void overrideCloseChildByIdWith(TreeNode* parent, int nodePosID, TreeNode* child);
		//
		////////////////////////////////////	
	
	public:
		///////////////////////////////////////
		// Ihr Code hier:	
		Tree();
		void addNode(const std::string& name, int alter, double einkommen, int plz);
		void deleteNode(int nodePosID);
		bool searchNode(const std::string& name);
		void printAll() const;
		//
		////////////////////////////////////
		// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
		friend TreeNode * get_anker(Tree& TN);
};
