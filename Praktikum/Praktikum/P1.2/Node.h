#pragma once

template<typename T>
class Node
{
public:
	T key;
	Node<T>* next, *prev;
public:
	Node()
	{
		next = 0;
		prev = 0;
	}
	Node(T key, Node<T> * next, Node<T> * prev)
	{
		this->key = key;
		this->next = next;
		this->prev = prev;
	}
	~Node()
	{
	}
};