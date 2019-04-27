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

		TreeNode* LeftNode;
		TreeNode* RightNode;
		//
		////////////////////////////////////
	
	public:
		///////////////////////////////////////
		// Ihr Code hier:
		TreeNode(int nodePosID, int nodeID, const std::string& name, int alter, double einkommen, int plz);
		void print() const;		
		
		inline TreeNode* getLeft() { return LeftNode; }
		inline TreeNode* getRight() { return RightNode; }
		inline std::string getName() { return Name; }
		inline int getNodePosID() const { return NodePosID; }
		inline int getAlter() { return Alter; }
		inline double getEinkommen() { return Einkommen; }
		inline int getNodeID() { return NodeID; }
		inline int getPLZ() { return PLZ; }

		inline void setLeft(TreeNode* node) { LeftNode = node; }
		inline void setRight(TreeNode* node) { RightNode = node; }
		inline void setAlter(int value) { Alter = value; }
		inline void setEinkommen(double einkommen) { Einkommen = einkommen; }
		inline void setName(const std::string name) { Name = name; }
		inline void setPLZ(int plz) { PLZ = plz; }
		//
		////////////////////////////////////
};
