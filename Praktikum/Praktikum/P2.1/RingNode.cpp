/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"


// Ihr Code hier:
RingNode::RingNode() : OldAge(0), next(nullptr)
{
}

RingNode::RingNode(int age, const std::string & description, const std::string & data)
	: OldAge(age), Descripton(description), SymbolicData(data), next(nullptr)
{
}
// 
////////////////////////////////////


