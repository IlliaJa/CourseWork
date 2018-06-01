#pragma once
#ifndef __TREE__
#define __TREE__

#include "Node.h"

template<typename T>
class Tree {
public:
	Tree();
	~Tree();
	Node<T>* search(T data);
	void insert(T data);
	void deleteItem(T data);
	Node<T>* root;

private:
	void clear(Node<T>* temp);

	// delete as in a binary tree
	void deleteItem(Node<T>* temp);
	// two links on children
	void deleteWithTwo(Node<T>* temp);

	Node<T>* balance(Node<T>* current);
	Node<T>* rotateRight(Node<T>* current);
	Node<T>* rotateLeft(Node<T>* current);
};

#endif