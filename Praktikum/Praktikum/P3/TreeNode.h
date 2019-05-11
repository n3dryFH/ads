/*************************************************
* ADS Praktikum 2.2
* TreeNode.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode{
	
	private:
		///////////////////////////////////////
		// Ihr Code hier:	
		int NodePosID;
		int NodeID;
		int PLZ;
		int Alter;
		std::string Name;		
		double Einkommen;	
		bool Red;

		TreeNode* LeftNode;
		TreeNode* RightNode;
		TreeNode* ParentNode;
		//
		////////////////////////////////////
	
	public:
		///////////////////////////////////////
		// Ihr Code hier:
		TreeNode(int nodePosID, int nodeID, const std::string& name, int alter, double einkommen, int plz);
		void print() const;		
		
		inline TreeNode* getLeft() { return LeftNode; }
		inline TreeNode* getRight() { return RightNode; }
		inline TreeNode* getParent() { return ParentNode; }
		inline std::string getName() const { return Name; }
		inline int getNodePosID() const { return NodePosID; }
		inline int getAlter() const { return Alter; }
		inline double getEinkommen() const { return Einkommen; }
		inline int getNodeID() const { return NodeID; }
		inline int getPLZ() const { return PLZ; }
		inline int getRed() const { return Red; }

		inline void setLeft(TreeNode* node) { LeftNode = node; }
		inline void setRight(TreeNode* node) { RightNode = node; }
		inline void setParent(TreeNode* node) { ParentNode = node; }
		inline void setAlter(int value) { Alter = value; }
		inline void setEinkommen(double einkommen) { Einkommen = einkommen; }
		inline void setName(const std::string name) { Name = name; }
		inline void setPLZ(int plz) { PLZ = plz; }
		inline void setRed(bool value) { Red = value; }
		//
		////////////////////////////////////
};
