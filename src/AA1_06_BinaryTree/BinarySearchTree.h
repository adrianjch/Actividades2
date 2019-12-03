#pragma once
#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T> {
public:
	BinarySearchTree();
	~BinarySearchTree();
	BinaryTree::Node* Search(int);
};

template <class T> BinaryTree<T>::Node* BinarySearchTree<T>::Search(int x) {
	return nullptr;
}