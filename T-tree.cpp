// T-tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "T-tree.h"

const int capacity = 5;

template<typename T>
inline Tree<T>::Tree()
{
	root = nullptr;
}

template<typename T>
Tree<T>::~Tree()
{
	this->clear(this->root);
}

template<typename T>
void Tree<T>::clear(Node<T>* temp)
{
	if (temp != nullptr) {
		clear(temp->getLeft());
		clear(temp->getRight());
		delete temp;
	}
}



template<typename T>
Node<T>* Tree<T>::search(T data)
{
	Node<T>* current = root;
	Node<T>* parent;
	parent = current->getParent();
	while (current != nullptr) {
		if (data > current->min && data < current->max) return current;
		if (data <= current->min) current = current->getLeft();
		if (data >= current->max) current = current->getRight();
		parent = current->getParent();
	}
	return parent;
}

template<typename T>
void Tree<T>::insert(T data)
{
	Node<T>* current = this->search(data);
	if (current == nullptr) {
		current = new Node<int>;
		root = current;
	}
	int size = current->values.size();

	// insert data in node
	current->values.push_back(data);
	int ind = size - 2;

	// locating for data
	while (data < current->values[ind] && ind > 0) {
		swap(data, current->values[ind]);
		ind -= 2;
	}
	current->min = current->values[0];
	current->max = current->values[size - 1];

	// create new node
	if (current->values.size() > capacity) {
		// data, that transfer to new node
		int newInserted = current->values[0];
		current->values.erase(current->values.begin());
		if (current->getLeft() == nullptr) {
			Node<T>* newLeft = new Node<int>;
			newLeft->setParent(current);
			current->setLeft(newLeft);
			balance(this->root);
		}
		this->insert(newInserted);
	}
}



template<typename T>
void Tree<T>::deleteItem(T data)
{
	Node<T>* temp = this->search(data);
	if (temp == nullptr) {  // if Node with this data does not wxist
		return;
	}

	if (temp->values.size() == 1) {
		// delete all node
		deleteItem(temp);
	}
	else {  // if capacity of node allow to delete elem
		int i = 0;
		for (i; i < temp->values.size() - 1; i++) {
			if (data == temp->values[i]) break;
		}
		temp->values.erase(temp->values.begin() + i);
	}
	balance(this->root);
}

template<typename T>
void Tree<T>::deleteItem(Node<T>* temp)
{
	// for leaf
	if (temp->getRight() == nullptr && temp->getLeft() == nullptr) {
		if (temp->getParent() != nullptr) {
			if (temp->getParent()->getLeft() == temp) temp->getParent()->setLeft(nullptr);
			else temp->getParent()->setRight(nullptr);
		}
		else root = nullptr;
		delete temp;
		return;
	}

	// run delete item with two links
	if (temp->getRight() != nullptr && temp->getLeft() != nullptr) {
		deleteWithTwo(temp);
		return;
	}

	// delete half-leaf
	Node<T>* parent = temp->getParent();
	Node<T> *legacy;
	// difference for right of left half-leaf
	if (temp->getRight() == nullptr) legacy = temp->getLeft();
	else legacy = temp->getRight();
	legacy->setParent(parent);
	if (parent != nullptr) {
		// also difference
		if (parent->getRight() == temp) parent->setRight(legacy);
		else parent->setLeft(legacy);
	}
	else root = legacy;
	delete temp;
}

template<typename T>
void Tree<T>::deleteWithTwo(Node<T>* temp)
{
	Node<T>* parent = temp->getParent();
	// Item, that will be transfered
	Node<T>* exchange;
	exchange = temp->getLeft();
	while (exchange->getRight()) {
		exchange = exchange->getRight();
	}

	if (parent == nullptr) root = exchange;

	Node<T>* exchangeLeft = exchange->getLeft();
	Node<T>* exchangeRight = exchange->getRight();
	Node<T>* exchangeParent = exchange->getParent();

	// set links of exchange
	exchange->setRight(temp->getRight());
	if (temp->getLeft() != exchange) exchange->setLeft(temp->getLeft());
	exchange->setParent(parent);

	// set links to exchange
	if (parent != nullptr) {
		if (parent->getRight() == temp) parent->setRight(exchange);
		else parent->setLeft(exchange);
	}
	if (temp->getLeft() != exchange) temp->getLeft()->setParent(exchange);
	else temp->setLeft(nullptr);
	temp->getRight()->setParent(exchange);

	// set relationship for item near exchange (in first place)
	if (exchangeLeft != nullptr) exchangeLeft->setParent(exchangeParent);
	if (exchangeParent != nullptr) exchangeParent->setRight(exchangeLeft);
	if (exchangeRight != nullptr) exchangeRight->setParent(exchangeLeft);

	delete temp;
	return;
}



template<typename T>
Node<T>* Tree<T>::rotateRight(Node<T>* current)
{
	Node<T>* temp = current->getLeft();
	current->setLeft(temp->getRight());
	temp->setRight(current);
	current->fixheight();
	temp->fixheight();
	if (current == this->root) root = temp;
	return temp;
}

template<typename T>
Node<T>* Tree<T>::rotateLeft(Node<T>* current)
{
	Node<T>* temp = current->getRight();
	current->setRight(temp->getLeft());
	temp->setLeft(current);
	current->fixheight();
	temp->fixheight();
	if (current == this->root) root = temp;
	return temp;
}

template<typename T>
Node<T>* Tree<T>::balance(Node<T>* current)
{
	current->fixheight();
	if (current->bfactor() == 2)
	{
		if (current->getRight()->bfactor() < 0)
			current->setRight(rotateRight(current->getRight()));
		return rotateLeft(current);
	}
	if (current->bfactor() == -2)
	{
		if (current->getLeft()->bfactor() > 0)
			current->setLeft(rotateLeft(current->getLeft()));
		return rotateRight(current);
	}
	return current;
}
