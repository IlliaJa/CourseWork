#pragma once
#ifndef __NODE__
#define __NODE__

#include <vector>

using namespace std;

template<typename T>
class Node {
public:
	Node(Node<T>* pparent = nullptr, Node<T>* pleft = nullptr, Node<T>* pright = nullptr, T max = T(), T min = T()){
		this->values;
		this->max = 0;
		this->min = 0;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}
	
	vector<T> values;
	T max;
	T min;
	void setParent(Node<T> *parent) {
		this->parent = parent;
	}
	Node<T>* getParent() {
		return parent;
	}
	void setLeft(Node<T> *left) {
		this->left = left;
	}
	Node<T>* getLeft() {
		return left;
	}
	void setRight(Node<T> *right) {
		this->right = right;
	}
	Node<T>* getRight() {
		return right;
	}

	// height of half-tree, where root is this node
	unsigned int height;
	// balance factor
	int bfactor() {
		return this->getRight()->height - this->getLeft()->height;
	}
	void fixheight() {
		unsigned int hLeft = this->getLeft()->height;
		unsigned int hRight = this->getRight()->height;
		this->height = (hLeft > hRight ? hLeft : hRight) + 1;
	}
private:
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
};

#endif