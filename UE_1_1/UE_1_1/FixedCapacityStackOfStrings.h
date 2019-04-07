#pragma once
#include <string>

using namespace std;

class FixedCapacityStackOfStrings
{
private:
	string* s;
	int N;
	int Capacity;
public:
	FixedCapacityStackOfStrings(int capacity) : Capacity(capacity)
	{
		s = new string[capacity];		
		N = 0;
	}
	bool isEmpty()
	{
		return N == 0;
	}

	bool isFull()
	{
		return N == Capacity;
	}

	void push(string item)
	{
		if (!isFull())
			s[N++] = item;
	}
	string pop()
	{
		if (!isEmpty())
			--N;
		return s[N];
	}

	void print()
	{
		for (unsigned int i = 0; i < Capacity; ++i)		
			cout << s[i] << endl;
	}

	void resize(int length)
	{
		string* strPtr = new string[length];
		int newLength = length > Capacity ? Capacity : length;
		for (unsigned int i = 0; i < newLength; ++i)
			strPtr[i] = s[i];
		delete[] s;		
		s = strPtr;
		Capacity = newLength;
		N = 0;		
	}

	string peek()
	{
		if (isEmpty())
			return s[0];		
		return s[N-1];
	}
};