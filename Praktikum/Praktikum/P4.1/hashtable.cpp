#include <cassert>
#include <vector>
#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) : size(size), elements(0), collisionCount(0)
{
	//*****************************
	// implement constructor here *
	//*****************************

	hashTable = new vector<int>(size);
	for (int i = 0; i < size; ++i)
		hashTable->at(i) = -1;
}

HashTable::~HashTable()
{	
	//****************************
	// implement destructor here *
	//****************************
	assert(hashTable != nullptr);
	delete hashTable;
	hashTable = nullptr;
}

int HashTable::hashValue(int item) {
	
	int index = -1; //dummy initializtation

	//******************************************
	// implement calculation of hashindex here *
	//******************************************
	// hi(k) = (k+(i^2))mod M
	bool hasCollision = false;
	int i = 0;
	do 
	{
		index = (item + (i * i)) % size;
		if (hashTable->at(index) != -1)
		{
			hasCollision = true;
			++collisionCount;
			++i;
		}
		else
			hasCollision = false;

	} while (hasCollision);
	return index;
}

int HashTable::insert(int item) {
	
	//******************************************
	// implement insertion of new element here *
	//******************************************
	int hashIndex = hashValue(item);
	assert(hashTable->at(hashIndex) == -1);
	hashTable->at(hashIndex) = item;
	++elements;
	return 0; //dummy return
}


int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}
