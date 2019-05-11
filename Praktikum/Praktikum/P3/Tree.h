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

		bool rotateTreeRight(TreeNode* parent, TreeNode* leftChild);
		bool rotateTreeLeft(TreeNode* parent, TreeNode* rightChild);

		static void printTableHeader();
		static void printTreeNodePreOrderRecursive(TreeNode* node);
		static void printTreeNodeLevelOrderRecursive(TreeNode* node);
		static bool searchAndPrintTreeNodeRecursive(TreeNode* node, const std::string& name);
		static TreeNode* findParentMinNode(TreeNode * fromNode);
		static void overrideCloseChildByIdWith(TreeNode* parent, int childNodePosID, TreeNode* newChild);
		//static void deleteRecursive(TreeNode* node);

		//
		////////////////////////////////////	
	
	public:
		///////////////////////////////////////
		// Ihr Code hier:	
		Tree();
		//~Tree();
		void addNode(const std::string& name, int alter, double einkommen, int plz);
		void deleteNode(int nodePosID);
		bool searchNode(const std::string& name) const;
		void printAll() const;
		bool balanceTree(TreeNode * fromNode);
		void printLevelOrder();

		//
		////////////////////////////////////
		// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
		friend TreeNode * get_anker(Tree& TN);
};
