/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include <string>
#include "catch.hpp"
#include "RingNode.h"

class Ring{
	
	private:
		// Ihr Code hier:	
		int AnzahlNodes;
		RingNode* anker;
		void printNodesRecursive(RingNode& node) const;
		//
		////////////////////////////////////
	public:			   
		// Ihr Code hier:
		Ring();
		~Ring();
		void addNode(const std::string& description, const std::string& data);
		bool search(const std::string& data) const;
		void print() const;
		//
		////////////////////////////////////
		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_AnzahlNodes(Ring& r);
};
