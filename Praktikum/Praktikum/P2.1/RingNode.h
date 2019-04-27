/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	// Ihr Code hier:
	int OldAge;
	std::string Descripton;
	std::string SymbolicData;
	RingNode* next;

	//	
public:
	// Ihr Code hier:
	RingNode();
	RingNode(int age, const std::string& description, const std::string& data);

	inline int getAge() const { return OldAge; }
	inline std::string getDescription() const { return Descripton; }
	inline std::string getData() const { return SymbolicData; }
	inline RingNode* getNext() { return next; }

	inline void setAge(int value) { OldAge = value; }
	inline void setDescription(const std::string& description) { Descripton = description; }
	inline void setData(const std::string& data) { SymbolicData = data; }
	inline void setNext(RingNode* nextNode) { next = nextNode; }

	//
};
